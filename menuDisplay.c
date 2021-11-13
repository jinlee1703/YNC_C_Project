#define _CRT_SECURE_NO_WARNINGS		//��ó����(#) ���α׷� ���࿡ ���Ǵ� ��ũ�ο� ������� ����
#include <stdio.h>					//ǥ������� �Լ� �������
#include <string.h>					//ǥ�� ���ڿ� �Լ� �������
#include <conio.h>

#include "console.h"				//console.h ����� ������� ����
#include "drawing.h"				//drawing.h ����� ������� ����
#include "text.h"					//text.h ����� ������� ����

void menuSelect(int cnt);		//����ڰ� Ű�� �Է����� �� ���õ� �޴��� ǥ�õǵ��� �ϴ� �Լ�

//DB�� ȸ�� ������ �����ϴ� �Լ�
int menuDisplay() {
	int cnt = 0, key = 0;			//int�� �Լ� cnt�� ���� ����ڰ� ������ �޴��� ���° �޴����� �����ϰ�, key�� ���� ����ڰ� �Է��� key ���� ����
	
	system("cls");					//system�Լ��� ȭ�� �ʱ�ȭ

	consoleShow();				//����� ���� �Լ� consoleShow �Լ��� �ܼ��� ������ ũ��� ��
	drawingBorder();			//����� ���� �Լ��� �׵θ� ���
	drawingTitle();				//����� ���� �Լ��� ���α׷� ���� ���
	drawingNameTag();				//����� ���� �Լ��� �ۼ��� �й�, �̸� ���
	drawingIdtag();	//����� ���� �Լ��� �α��ε� ȸ�� ���̵� ���
	drawingExplanation();		//����� ���� �Լ��� Ű ���� ���

	gotoxy((WIDTH / 2) - 6, 12);		//gotoxy �Լ��� ����� [ª�� �� ����] �޴��� ����� ��ġ�� �̵��ϰ� printf �Լ��� ���
	printf("ª�� �� ����");

	gotoxy((WIDTH / 2) - 6, 15);		//gotoxy �Լ��� ����� [�� �� ����] �޴��� ����� ��ġ�� �̵��ϰ� printf �Լ��� ���
	printf("�� �� ����");

	gotoxy((WIDTH / 2) - 6, 18);		//gotoxy �Լ��� ����� [�꼺�� ����] �޴��� ����� ��ġ�� �̵��ϰ� printf �Լ��� ���
	printf("�꼺�� ����");

	gotoxy((WIDTH / 2) - 6, 21);		//gotoxy �Լ��� ����� [��ŷ ����] �޴��� ����� ��ġ�� �̵��ϰ� printf �Լ��� ���
	printf("��� ����");

	menuSelect(cnt);			//menuSelect �Լ��� ���� [ª�� �� ����]�� �⺻ ���� �޴��� ���

	while (1) {		//�޴� ����
		key = _getch();				//���� key�� ����ڰ� �Է��� key ���� ����

		if (key == 72) {			//key ���� 72�� ���(����Ű UpŰ)
			if (cnt > 0) {				//cnt�� 0 ���� Ŭ ���(�� ���� �޴��� �ƴ� �޴� ����)
				cnt--;						//cnt�� ���� 1����
				menuSelect(cnt);		//���õ� �޴� ���� ǥ��
			}
		}
		else if (key == 80) {		//key ���� 80�� ���(����Ű DownŰ)
			if (cnt < 3) {				//cnt�� 3 ���� ���� ���(�� �Ʒ��� �޴��� �ƴ� �޴� ����)
				cnt++;					//cnt�� ���� ���ϰ�
				menuSelect(cnt);	//���õ� �޴� ���� ǥ��
			}
		}
		else if (key == 13)				//Enter key �Է� �� ���õ� �޴� ���� ��ȯ
			return cnt;
		else if (key == 27)				//Esc key �Է� �� 4 ��ȯ (���� ȭ������ ȸ��)
			return 4;
	}
}

//����ڰ� Ű�� �Է����� �� ���õ� �޴��� ǥ�õǵ��� �ϴ� �Լ�
void menuSelect(int cnt) {
	int i = 0;				//for �ݺ����� ����ϱ� ���� int�� ���� i ���� �� 0���� �ʱ�ȭ

	for (i = 0; i < 4; i++) {						//for �ݺ����� gotoxy �Լ��� ���� 4���� �޴��� �ִ� ȭ��ǥ ǥ��(��)�� �����.(printf() �Լ��� �����)
		gotoxy((WIDTH / 2) - 10, (i * 3) + 12);
		printf("  ");
	}

	gotoxy((WIDTH / 2) - 10, (cnt * 3) + 12);			//gotoxy �Լ��� ���� ����ڰ� ������ �޴��� ������ ��ġ�� �̵��Ͽ� ȭ��ǥ(��) ���
	printf("��");
}