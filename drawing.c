#include <stdio.h>			//ǥ������� �Լ� �������
#include <Windows.h>		//������ ���� ���α׷��� ���� �������

#include "main.h"
#include "console.h"		//console.h ����� ������� ����

//ȭ�� �׵θ��� �׷��ִ� �Լ�
void drawingBorder() {
	int i = 0, j = 0;		//for �ݺ����� ���� int�� ���� i�� j ���� �� 0���� �ʱ�ȭ

	for (i = 0; i < HEIGHT; i++) {				//�׵θ� �׸���
		for (j = 0; j < WIDTH; j += 2) {
			gotoxy(j, i);
			if (i == 0 || i == HEIGHT - 1) {			//������
				printf("��");
			}
			else if (j == 0 || j == WIDTH - 2)		//������
				printf("��");
		}
	}
}

//ȭ�� �߾� ��ܿ� ���� ����(Title)�� ����ϴ� �Լ�
void drawingTitle() {
	//���� ��� : 28��Ʈ
	gotoxy((WIDTH / 2) - 14, 4);
	printf("+--------------------------+");
	gotoxy((WIDTH / 2) - 14, 5);
	printf("| Ÿ �� �� ��  �� �� �� �� |");
	gotoxy((WIDTH / 2) - 14, 6);
	printf("+--------------------------+");
}

//ȭ�� ���� ��ܿ� �й�, �̸��� ����ϴ� �Լ�
void drawingNameTag() {
	gotoxy(2, 1);
	printf(" �й� : 1705026");
	gotoxy(2, 2);
	printf(" �̸� : ������");
}

//ȭ�� �߾� �ϴܿ� Ű ���� ������ ����ϴ� �Լ�
void drawingExplanation() {
	gotoxy((WIDTH / 2) - 11, 25);
	printf("�޴� ���� : '���' KEY \n");
	gotoxy((WIDTH / 2) - 12, 28);
	printf("���� �Ϸ� : 'ENTER' KEY \n");
	gotoxy((WIDTH / 2) - 11, 31);
	printf("���� �޴� : 'ESC' KEY \n");
}

//�ؽ�Ʈ�ڽ� ���¸� ����ϴ� �Լ�
void drawingTextBox(int col, char text[]) {
	int stl = (int)strlen(text) + 1;

	gotoxy((WIDTH / 2) - 12, col - 1);
	printf("+----------------------+");
	gotoxy((WIDTH / 2) - 12 - stl, col);
	printf("%s |", text);
	gotoxy((WIDTH / 2) - 12, col + 1);
	printf("+----------------------+");
	gotoxy((WIDTH / 2) + 11, col);
	printf("|");
}

//�α��� �� ȭ�鿡�� �α��� �� ���̵� ȭ�� ���� ��ܿ� ����ϴ� �Լ�
void drawingIdtag() {
	gotoxy(WIDTH - 30, 2);
	printf("Player :  %s ��", login_id);
}

//gotoxy�� printf �Լ��� for���� ����Ͽ� �ؽ�Ʈ�ڽ��� ����ϴ� ����� �Լ�(��ۿ���, ª�� �� ���� ���)
void drawingTestTextbox(int col) {
	int i = 0;								//for�ݺ����� ����ϱ� ���� int�� ���� i ���� �� 0���� �ʱ�ȭ

	gotoxy(4, col - 1);		printf("+");	//ȭ�鿡 �ؽ�Ʈ �ڽ� ���
	gotoxy(4, col + 1);		printf("+");
	for (i = 5; i < WIDTH - 5; i++) {
		gotoxy(i, col - 1);	printf("-");
		gotoxy(i, col + 1);	printf("-");
	}
	gotoxy(WIDTH - 5, col - 1);	printf("+");
	gotoxy(WIDTH - 5, col + 1);	printf("+");
	gotoxy(4, col);		printf("|");
	gotoxy(WIDTH - 5, col);		printf("|");
}

//gotoxy�� printf �Լ��� for���� ����Ͽ� ��µ� �ؽ�Ʈ�ڽ��� ����(ȭ�� ��)�� ����� ����� �Լ�(��ۿ���, ª�� �� ���� ���)
void testTextboxClear(int col) {
	int i = 0;

	for (i = 5; i < WIDTH - 6; i++) {
		gotoxy(i, col);
		printf(" ");
	}
}