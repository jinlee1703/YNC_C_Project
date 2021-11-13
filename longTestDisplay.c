#define _CRT_SECURE_NO_WARNINGS		//��ó����(#) ���α׷� ���࿡ ���Ǵ� ��ũ�ο� ������� ����
#include <stdio.h>					//ǥ������� �Լ� �������
#include <conio.h>					//�ܼ������ �Լ� �������
#include <string.h>					//ǥ�� ���ڿ� �Լ� �������
#include <windows.h>
#include <stdlib.h>					
#include <time.h>
#include <math.h>

#include "main.h"					//main.h ����� ������� ����
#include "console.h"				//console.h ����� ������� ����
#include "drawing.h"				//drawing.h ����� ������� ����
#include "text.h"					//text.h ����� ������� ����

void shortTextbox(int col);			//gotoxy�� printf �Լ��� for���� ����Ͽ� �ؽ�Ʈ�ڽ��� ����ϴ� ����� �Լ�
int longTestSelectDisplay();		//� �� ���� Ÿ���� �Ұ��� �����ϴ� ȭ���� ��µǴ� �Լ�
void longTestSelect(int cnt);		//Ű���带 �Է��� ������ �ش��ϴ� �� �� ���� �� ǥ�ð� ��µǴ� �Լ�

#define BACKSPACE 8							//Backspace Ű ���� ��ũ�� ����� ����
#define ENTER 13							//ENTER Ű ���� ��ũ�� ����� ����

int max;			//��� ���� ���� ����
char title[45];		//ª���� �ڵ� �����ϱ�

void longTestDisplay() {
	char text[5][WIDTH - 10] = { 0 };		//DB�� ����Ǿ� �ִ� ����(����ڰ� �Է��� ����)�� ����� 2���� char�� �迭 text
	char user[5][WIDTH - 10] = { 0 };			//����ڰ� �Է��� ������ ������ char�� �迭 user
	int i = 0, j = 0;						//for �ݺ����� ���� int�� ���� i, j ���� �� 0���� �ʱ�ȭ
	int cnt = 0;					//����ڰ� �Է��ϰ� �ִ� ���� ���° ������ �����ϱ� ���� int�� ���� cnt ���� �� 0���� �ʱ�ȭ
	FILE *fp;					//ª�� ���� ����Ǿ� �ִ� ������ �ҷ����� ���� ����ü ���� ������ ����
	char filepath[255] = { 0 };
	TA data;
	int key = 0;				//��� �� ������ ���θ� Ȯ���ϱ� ���� key ���� �Է¹ޱ� ���� int�� ���� key ���� �� 0���� �ʱ�ȭ

	if (longTestSelectDisplay() == -1)
		return;

	/*[���� �ҷ�����]*/
	sprintf(filepath, "�� ��\\%s", title);			//�迭�� DB�� ����Ǿ� �ִ� ���ϸ�� ���� ��� ����

	if ((fp = fopen(filepath, "r")) == NULL) {
		fprintf(stderr, "���� ���� ����!\n");
		return;
	}

nextPage:
	system("cls");					//system�Լ��� ȭ�� �ʱ�ȭ

	consoleShow();				//����� ���� �Լ� consoleShow �Լ��� �ܼ��� ������ ũ��� ��
	drawingBorder();			//����� ���� �Լ��� �׵θ� ���
	drawingIdtag();				//�α��� �� ID ���

	gotoxy(6, 4);					//Ÿ�� ����� ���� ��ǥ ����
	printf("Ÿ�� : %4d Ÿ", 0);			//Ÿ�� ���

	gotoxy(40, 4);					//��Ȯ�� ����� ���� ��ǥ ����
	printf("��Ȯ�� : %3d %%", 0);		//��Ȯ�� ���

	for (i = 0; i < 10; i++) {		//for �ݺ����� ����Ͽ� 10���� ���� �ڽ� ���(5�� : �Է��� ����, 5�� : �Էµ� ��ġ)
		drawingTestTextbox(6 + (i * 3));			//���� �ڽ� ���
	}

	for (i = 0; i < 5; i++) {					//for �ݺ����� ����Ͽ� ���� ���(5��)
		if (!feof(fp)) {											//���� ���� ���� ��� ������ �о�´�
			fgets(text[i], WIDTH - 10, fp);								//(�迭 text�� ����)
			gotoxy(6, 6 + (i * 3 * 2));									//���� ����� ���� ��ǥ ����
			printf("%s", text[i]);										//���� ���
			testTextboxClear(9 + (i * 3 * 2));							//�Է��� ��ġ �ʱ�ȭ
			sprintf(user[i], "");;										//�Է��� ����(����) �ʱ�ȭ
		}
		else {
			sprintf(text[i], "");
		}
	}

	while (1) {					//���� �ݺ�(EscŰ�� ������ ������)
		for (i = 0; i < 5; i++) {
			gotoxy(6, 9 + (i * 3 * 2));						//�Է��� ��ġ�� �̵�
			if (strcmp(text[i], "") != 0) {							//������ ������ ��쿡 Ÿ������ ������
				if (get_Typing(text[i], user[i], &data, 2) == -1)			//���ڸ� �Է� �ް� ��ȯ���� -1�� ���(Esc�Է�)
					goto end;											//�ݺ��� ����(�޴� ȭ������ ���ư�)
			}
		}

		system("cls");				//system�Լ��� ȭ�� �ʱ�ȭ
		consoleShow();				//����� ���� �Լ� consoleShow �Լ��� �ܼ��� ������ ũ��� ��
		drawingBorder();			//����� ���� �Լ��� �׵θ� ���
		drawingIdtag();				//�α��� �� ID ���

		if (feof(fp)) {											//���� ���� ���� ��� ��� ���� ���� ���� ���
			gotoxy((WIDTH / 2) - 29, 15);
			printf("+--------------------------------------------------------+");
			gotoxy((WIDTH / 2) - 29, 16);
			printf("|                                                        |");
			gotoxy((WIDTH / 2) - 29, 17);
			printf("|       �ƹ� Ű�� �����ø� �޴�ȭ������ ���ư��ϴ�       |");
			gotoxy((WIDTH / 2) - 29, 18);
			printf("|                                                        |");
			gotoxy((WIDTH / 2) - 29, 19);
			printf("+--------------------------------------------------------+");

			_getch();		//�ƹ� Ű�� �Է��� ��� �ݺ�������(���� ȭ������ �̵�)
			break;
		}

		/*[���� �������� �Ѿ ������ �޽��� ���]*/
		gotoxy((WIDTH / 2) - 21, 13);
		printf("+----------------------------------------+");
		gotoxy((WIDTH / 2) - 21, 14);
		printf("|                                        |");
		gotoxy((WIDTH / 2) - 21, 15);
		printf("|           ��� �Ͻðڽ��ϱ�?           |");
		gotoxy((WIDTH / 2) - 21, 16);
		printf("|                                        |");
		gotoxy((WIDTH / 2) - 21, 17);
		printf("|                                        |");
		gotoxy((WIDTH / 2) - 21, 18);
		printf("|          ����ϱ� : Enter key          |");
		gotoxy((WIDTH / 2) - 21, 19);
		printf("|                                        |");
		gotoxy((WIDTH / 2) - 21, 20);
		printf("|        �޴��� ���ư��� : Esc key       |");
		gotoxy((WIDTH / 2) - 21, 21);
		printf("|                                        |");
		gotoxy((WIDTH / 2) - 21, 22);
		printf("+----------------------------------------+");

request:key = _getch();

		if (key == ENTER_KEY) {
			/*[DB�� Ÿ���� ���� ����]*/
			sprintf(query, "insert into typing VALUES ('%s', 2, %d, %d, curdate())", login_id, data.speed, data.percent);		//sprintf �Լ��� ���� query�� �������� ����
			mysql_query(connection, query);						//mysql_query �Լ��� ���� connection(���� ����)�� ������ ����(insert������ Ÿ���� ���� ����)

			goto nextPage;	//���� ���� ������ ���
		}
		else if (key == ESC_KEY) {
			break;
		}
		else {
			goto request;
		}
	}
end:
	fclose(fp);
}

int longTestSelectDisplay() {
	int i = 0, j = 0, key = 0, cnt =0;			//for�ݺ����� ����ϱ� ���� int�� ���� i�� j, ����ڰ� �Է��� Ű���� ������ key, �� �� ������ ���� cnt�� ���� �� 0���� �ʱ�ȭ
	char arr[10][45] = { 0 };

	system("cls");				//system�Լ��� ȭ�� �ʱ�ȭ

	consoleShow();				//����� ���� �Լ� consoleShow �Լ��� �ܼ��� ������ ũ��� ��
	drawingBorder();			//����� ���� �Լ��� �׵θ� ���

	gotoxy((WIDTH / 2) - 6, 4);		//���� ���
	printf("�� �� �� ��");

	for (i = 7; i < HEIGHT - 3; i++) {				//�׵θ� �׸���
		for (j = 20; j < WIDTH - 20; j += 2) {
			gotoxy(j, i);
			if (i == 7 || i == HEIGHT - 4)			//������
				printf("��");
			else if (j == 20 || j == WIDTH - 22)		//������
				printf("��");
		}
	}

	//[�� �� ����Ʈ ���]
	sprintf(query, "select substring(file_name, 1, char_length(file_name) - 4) from file where events_id='2' and language='eng' order by file_id");		//sprintf �Լ��� ���� query�� �������� ����

	mysql_query(connection, query);		//mysql_query �Լ��� ���� connection(���� ����)�� ������ ����(DB�� ����Ǿ� �ִ� ��ۿ��� ���� ��ȸ)

	result = mysql_store_result(connection);			//result�� mysql_store_result�Լ��� ����Ͽ� connection(��������)�� ���� ����� ����

	i = 0;

	//while �ݺ��� : row�� mysql_fetch_row �Լ��� ����Ͽ� result(�ּ�)�� �� ��(��)�� �о�� �����ϰ� ���� ������� ��(������)���� �Ǵ� 10������� �ݺ�
	while (((row = mysql_fetch_row(result)) != NULL) && i != 10) {	
		gotoxy(28, 10 + (i * 2));
		sprintf(arr[i], "%s", row[0]);
		printf("%s ", arr[i]);			//printf �Լ��� ����Ͽ� ������ ���� ��� ���
		i++;
	}

	//[�޴� ����]
	max = i;
	longTestSelect(cnt);

	while (1) {		//�޴� ����
		key = _getch();				//���� key�� ����ڰ� �Է��� key ���� ����

		if (key == 72) {			//key ���� 72�� ���(����Ű UpŰ)
			if (cnt > 0) {				//cnt�� 0 ���� Ŭ ���(�� ���� �޴��� �ƴ� �޴� ����)
				cnt--;						//cnt�� ���� 1����
				longTestSelect(cnt);		//���õ� �޴� ���� ǥ��
			}
		}
		else if (key == 80) {		//key ���� 80�� ���(����Ű DownŰ)
			if (cnt < max -1) {				//cnt�� 3 ���� ���� ���(�� �Ʒ��� �޴��� �ƴ� �޴� ����)
				cnt++;					//cnt�� ���� ���ϰ�
				longTestSelect(cnt);	//���õ� �޴� ���� ǥ��
			}
		}
		else if (key == 13) {		//Enter key �Է� �� ���õ� �޴� ���� ��ȯ
			sprintf(title, "%s\.dat", arr[cnt]);
			break;
		}
		else if (key == 27)				//Esc key �Է� �� 4 ��ȯ (���� ȭ������ ȸ��)
			return -1;
	}
}

void longTestSelect(int cnt) {
	int i = 0;				//for �ݺ����� ����ϱ� ���� int�� ���� i ���� �� 0���� �ʱ�ȭ

	for (i = 0; i < max; i++) {						//for �ݺ����� gotoxy �Լ��� ���� 4���� �޴��� �ִ� ȭ��ǥ ǥ��(��)�� �����.(printf() �Լ��� �����)
		gotoxy(24, 10 + (i * 2));
		printf("  ");
	}

	gotoxy(24, 10 + (cnt * 2));						//gotoxy �Լ��� ���� ����ڰ� ������ �޴��� ������ ��ġ�� �̵��Ͽ� ȭ��ǥ(��) ���
	printf("��");
}