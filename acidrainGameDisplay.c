#define _CRT_SECURE_NO_WARNINGS		//��ó����(#) ���α׷� ���࿡ ���Ǵ� ��ũ�ο� ������� ����
#include <stdio.h>					//ǥ������� �Լ� �������
#include <string.h>					//�ܼ������ �Լ� �������
#include <process.h>

#include "console.h"				//console.h ����� ������� ����
#include "drawing.h"				//drawing.h ����� ������� ����
#include "text.h"					//text.h ����� ������� ����

#define WORD_CNT		20			//�ܾ� ���� ����
#define LEVEL_COUNT		5			//������ �ܾ� ���� ����
#define LEVEL_SPEED		15			//������ ���ǵ� ����
#define MAX_WORD		50			//�ִ� �ܾ� ��

typedef struct fallingWords {		//�꼺�� �ܾ� ����ü
	int x;							//��� ���� : ��ǥ�� x y, ���ð� wait, ��¿��� visible, ����� �ܾ� text[20]
	int y;
	int wait;
	int visible;					
	char text[20];
} FW;

void inputWord();
void game(int lv);
void gameDisplayReset();

char words[1200][20] = { 0 };		//���� �ܾ� ����
FW word[MAX_WORD];					//�������� �ܾ� ����

CRITICAL_SECTION cs;			//�Ӱ豸�� ����
HANDLE thread1;					//������ 1 : inputWord
HANDLE thread2;					//������ 2 : game

int score = 0;		//����
int life = 3;		//���� ����
int count = 0;		//�ܾ� ����
int tp = 0;			//�ܾ �Է��� Ƚ��(�������� �ʱ�ȭ)

//�꼺�� ����ȭ���� ����ϴ� �Լ�
void acidrainGame() {
	int i = 0, j = 0;				//for �ݺ����� ����ϱ� ���� int�� ���� i�� j ���� �� 0���� �ʱ�ȭ
	FILE *fp;
	char filepath[255] = { 0 };
	char user[20] = { 0 };
	
	system("cls");		//system�Լ��� ȭ�� �ʱ�ȭ

	consoleShow();				//����� ���� �Լ� consoleShow �Լ��� �ܼ��� ������ ũ��� ��
	drawingBorder();			//����� ���� �Լ��� �׵θ� ���
	drawingIdtag();	//�α��� �� ID ���(�̿ϼ�)

	for (i = 2; i < WIDTH - 2; i++) {
		gotoxy(i, 3);					//gotoxy �Լ��� ���� ��ǥ �̵� �� printf �Լ��� ��ܼ� �׸���
		printf("-");

		if (i % 2 == 0) {
			gotoxy(i, HEIGHT - 5);			//gotoxy �Լ��� ���� ��ǥ �̵� �� printf �Լ��� �ϴܼ� �׸���(if ���� ���� ��ĭ �� ����� ���)
			printf("~");
		}
	}

	gotoxy((WIDTH / 2) - 14, HEIGHT - 4);				//gotoxy �Լ��� ���� ��ǥ �̵� �� ����ڰ� �ܾ �Է��� ĭ ���
	printf("+--------------------------+");
	gotoxy((WIDTH / 2) - 14, HEIGHT - 3);
	printf("|                          |");
	gotoxy((WIDTH / 2) - 14, HEIGHT - 2);
	printf("+--------------------------+");

	//�ܾ ����Ǿ� �մ� ������ �ҷ�����
	sprintf(query, "select * from file where events_id='3' and language='eng'");		//sprintf �Լ��� ���� query�� �������� ����

	mysql_query(connection, query);		//mysql_query �Լ��� ���� connection(���� ����)�� ������ ����(DB�� ����Ǿ� �ִ� �ܾ� ���� ��ȸ)

	result = mysql_store_result(connection);			//result�� mysql_store_result�Լ��� ����Ͽ� connection(��������)�� ���� ����� ����

	row = mysql_fetch_row(result);						//�������� �о��

	sprintf(filepath, "�꼺�� ����\\%s", row[3]);			//�迭�� DB�� ����Ǿ� �ִ� ���ϸ�� ���� ��� ����

	if ((fp = fopen(filepath, "r")) == NULL) {
		fprintf(stderr, "���� ���� ����!\n");
		return;
	}

	i = 0;
	while (!feof(fp)) {											//���� ���� ���� ��� ������ �о�´�
		j = 0;
		while (!feof(fp)) {
			words[i][j] = fgetc(fp);
			if (words[i][j] == ' ') {
				words[i][j] = '\0';
				break;
			}
			j++;
		}
		i++;
	}
	
	//�������� �ʱ�ȭ
	score = 0;		//����
	life = 3;		//���� ����
	count = 0;		//�ܾ� ����
	tp = 0;			//�ܾ �Է��� Ƚ��(�������� �ʱ�ȭ)

	//������ ����
	InitializeCriticalSection(&cs);															//�Ӱ豸�� ����
	thread1 = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)inputWord, NULL, 0, NULL);	//���̵� �Է¹޴� ������1
	thread2 = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)game, (void *)1, 0, NULL);	//�ܾ ����ϴ� ������2
	WaitForSingleObject(thread1, INFINITE);													//������ 1 ���
	DeleteCriticalSection(&cs);																//�Ӱ豸�� ����
	return 0;
}

//�꼺�� ���� �ܾ �Է¹޴� �Լ�
void inputWord() {
	int i = 0;
	int cnt = 0, key = 0;		//����ڰ� �Է��� key ���� ������ int�� ���� key ���� �� 0���� �ʱ�ȭ
	char user[20] = { 0 };		//����ڰ� �Է��� ���ڿ��� �����ϱ� ���� char�� �迭 user�� ���� �� 0���� �ʱ�ȭ(�ִ� �Է� ũ��20)
	
	while (1) {
		EnterCriticalSection(&cs);

		if (kbhit() != 0) {
			key = _getch();			//���� key�� ����ڰ� �Է��� Ű ���� ����
			
			if (key == ENTER_KEY || key == 32) {		//ENTER Ű(13) or SPACE BAR(32)
				//�ؽ�Ʈ�ڽ� �ʱ�ȭ(�Ϸ�) + ī��Ʈ ���ϱ�(�Ϸ�) + ���� ǥ�� �ܾ� �����(�Ϸ�)
				gotoxy((WIDTH / 2) - 14, HEIGHT - 3);
				printf("|                          |");
				for (i = 0; i < count; i++) {
					if (word[i].visible == 1 && strcmp(word[i].text, user) == 0) {
						word[i].visible = 0;
						score += 10;
						tp++;
						break;
					}
				}
				for (i = 0; i < sizeof(user); i++) {
					user[i] = '\0';
				}
				cnt = 0;
			}
			else if (key == ESC_KEY) {	// ESC Ű �Է½� -1 ��ȯ
				//���� ����(����ȭ������ ���ư� ��)
				TerminateThread(thread2, 0);
				TerminateThread(thread1, 0);
			}
			else if (key == BACKSPACE_KEY) {				// BACKSPACE(8) �Է� �� ���� �����
				if (cnt != 0) {
					gotoxy((WIDTH / 2) - 12 + cnt, HEIGHT - 3);

					putchar('\b');				//\b(�齺���̽�)�� ����Ͽ� �� ��Ʈ �ڷ� �̵�
					putchar(' ');				// ȭ�鿡 �� ǥ��
					putchar('\b');				//\b(�齺���̽�)�� ����Ͽ� �� ��Ʈ �ڷ� �̵�
					user[cnt--] = ' ';			//���� ����
					continue;					//���� �Է� ����
				}
			}
			else if ((cnt >= 0 && cnt <= 20) && (key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z')) {		//��� �Է¹޵��� ��
				gotoxy((WIDTH / 2) - 12 + cnt, HEIGHT - 3);
				user[cnt++] = (char)key;				// ���ۿ� ���� �����ϰ� ī��Ʈ 1 ����  
				putchar(key);							// ȭ�鿡 ���� ǥ��
			}
			
		}
		LeaveCriticalSection(&cs);

		Sleep(1);
	}
}

void game() {
	int lv = 1;
	int speed;
	int i = 0, j = 0, check = 1, key = 0;
	int r = 0;		//���� ����

lvUp:

	speed = 1000 - (lv - 1) * LEVEL_SPEED;
	count = WORD_CNT + (lv - 1) * LEVEL_COUNT;

	//�ܾ� �ִ밳�� ����
	if (count >= MAX_WORD)
		count = MAX_WORD - 1;

	srand((unsigned int)time(NULL));
	//�ܾ� �ʱ�ȭ
	for (i = 0; i < count; i++) {
		r = rand() % (WIDTH - 20) + 4;					//x�� ����
		word[i].x = r;

		r = rand() % (speed / 20);					//wait�� ����(�Ѳ����� �ܾ �������� �ʰ� ������ ���� �ξ� ���������� �ϱ� ����)
		word[i].wait = r;

		word[i].y = 4;						//y���� 0���� ���������� ����

		word[i].visible = 1;

		r = rand() % 1090;
		sprintf(word[i].text, words[r]);
	}
	
	// ���� ����
	while (check) {
		//�ܾ� ���
		for (i = 0; i < count; i++) {
			if (word[i].wait == 0 && word[i].visible == 1) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				gotoxy(word[i].x, word[i].y);
				puts(word[i].text);
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

		//�ܾ� y�� ������
		for (i = 0; i < count; i++)
		{
			if (word[i].wait == 0) {
				word[i].y++;
			}
			else {
				word[i].wait--;
			}
		}

		if (count <= tp) {
			lv++;
			tp = 0;
			goto lvUp;
		}

		//���� üũ
		for (i = 0; i < count; i++) {
			if ((word[i].y >= HEIGHT - 4) && (word[i].visible == 1)) {
				life--;
				word[i].visible = 0;
				tp++;
			}
		}

		for (i = 2; i < WIDTH - 2; i++) {
			if (i % 2 == 0) {
				gotoxy(i, HEIGHT - 5);			//gotoxy �Լ��� ���� ��ǥ �̵� �� printf �Լ��� �ϴܼ� �׸���(if ���� ���� ��ĭ �� ����� ���)
				printf("~");
			}
			else {
				gotoxy(i, HEIGHT - 5);			//gotoxy �Լ��� ���� ��ǥ �̵� �� printf �Լ��� �ϴܼ� �׸���(if ���� ���� ��ĭ �� ����� ���)
				printf(" ");
			}
		}

		//���� �� ���� ���� ���
		gotoxy(5, 2);				//gotoxy �Լ��� ���� ��ǥ �̵� �� ���� ���
		printf("LEVEL %2d", lv);
		gotoxy(5, HEIGHT - 3);				//gotoxy �Լ��� ���� ��ǥ �̵� �� ���� ���
		printf("SCORE : %5d", score);
		gotoxy(WIDTH - 15, HEIGHT - 3);		//gotoxy �Լ��� ���� ��ǥ �̵� �� ���� ���� ���
		printf("LIFE : %1d", life);
		LeaveCriticalSection(&cs);

		if (life <= 0) {
			check = 0;

			gotoxy((WIDTH / 2) - 25, (HEIGHT / 2) - 3);
			printf("+-----------------------------------------------+");
			gotoxy((WIDTH / 2) - 25, (HEIGHT / 2) - 2);
			printf("|                                               |");
			gotoxy((WIDTH / 2) - 25, (HEIGHT / 2) - 1);
			printf("|          ���� ������ ����Ǿ����ϴ�           |");
			gotoxy((WIDTH / 2) - 25, (HEIGHT / 2));
			printf("|                                               |");
			gotoxy((WIDTH / 2) - 25, (HEIGHT / 2) + 1);
			printf("|                                               |");
			gotoxy((WIDTH / 2) - 25, (HEIGHT / 2) + 2);
			printf("|     �ƹ� Ű�� �����ø� �޴��� ���ư��ϴ�.     |");
			gotoxy((WIDTH / 2) - 25, (HEIGHT / 2) + 3);
			printf("|                                               |");
			gotoxy((WIDTH / 2) - 25, (HEIGHT / 2) + 4);
			printf("+-----------------------------------------------+");

			_getch();

			sprintf(query, "insert into typing VALUES ('%s', 3, %d, %d, curdate())", login_id, score, NULL);		//sprintf �Լ��� ���� query�� �������� ����

			mysql_query(connection, query);		//mysql_query �Լ��� ���� connection(���� ����)�� ������ ����(insert������ Ÿ���� ���� ����)

			TerminateThread(thread1, 0);
			TerminateThread(thread2, 0);
		}

		Sleep(speed);
		gameDisplayReset();
	}
}

void gameDisplayReset() {
	int i = 0, j = 0;
	unsigned long dw;
	COORD spot = { 2, 0 };
	
	for (i = 4; i < HEIGHT - 5; i++) {
		spot.Y = i;
		FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', WIDTH - 4, spot, &dw);
	}
}