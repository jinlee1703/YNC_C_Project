#define _CRT_SECURE_NO_WARNINGS			//��ó����(#) ���α׷� ���࿡ ���Ǵ� ��ũ�ο� ������� ����
#include <stdio.h>						//ǥ������� �Լ� �������
#include <conio.h>

//����� ���� �������
#include "main.h"
#include "console.h"
#include "drawing.h"
#include "text.h"

//���� ȭ��(��ũ�� ��� WIDTH�� HEIGHT�� �޾ƿ����ν� ��� ȭ�� ũ�⸦ ����)�� ����ϴ� �Լ�
int mainDisplay() {
	int cnt = 0;						//�޴� ���ð��� ������ int�� ���� cnt ���� �� 0���� �ʱ�ȭ(���α׷��� ��������� �� �⺻���� [�α���]�� ���õǵ��� ��)

	system("cls");						//system �Լ��� ���� ȭ�� �ʱ�ȭ(claer)

	consoleShow();					//����� ���� �Լ� consoleShow �Լ��� �ܼ��� ������ ũ��� ��
	drawingBorder();				//����� ���� �Լ��� �׵θ� ���
	drawingTitle();					//����� ���� �Լ��� ���α׷� ���� ���
	drawingNameTag();				//����� ���� �Լ��� ���α׷� �ۼ����� �й�, �̸� ���
	drawingExplanation();			//����� ���� �Լ��� Ű ���� ���

	gotoxy((WIDTH / 2) - 4, (HEIGHT / 2) - 4);	//gotoxy �Լ��� ����� [�α���] �޴��� ����� ��ġ�� �̵��ϰ� printf �Լ��� ���
	printf("�� �� ��");

	gotoxy((WIDTH / 2) - 4, (HEIGHT / 2));		//gotoxy �Լ��� ����� [ȸ������] �޴��� ����� ��ġ�� �̵��ϰ� printf �Լ��� �̵�
	printf("ȸ������");

	gotoxy((WIDTH / 2) - 8, (HEIGHT / 2) - 4);	//gotoxy �Լ��� [�α���] �޴��� ���ʿ� '��(ȭ��ǥ)' �޴��� �����(�⺻ ���� �޴��� [�α���] �޴�)
	printf("��");

	while (1) {		//���� �ݺ���(Ű���带 ���� �޴��� ����)
		int key = 0;		//����ڰ� �Է��� Ű ���� �����ϱ� ���� int�� ���� key�� ���� �� 0���� �ʱ�ȭ

		key = _getch();		//_getch() �Լ��� ���� ���� key�� ����ڰ� Ű�� �Է����� �� Ű�� ����

		if (key == 72) {							//key ���� 72�� ���(����Ű UpŰ)
			gotoxy((WIDTH / 2) - 8, (HEIGHT / 2));			//gotoxy�� ���� Ư�� ��ǥ([ȸ������] �޴� ��ġ)�� Ŀ���� �̵��ϰ� ȭ��ǥ�� ����
			printf("  ");

			gotoxy((WIDTH / 2) - 8, (HEIGHT / 2) - 4);		//gotoxy�� ���� Ư�� ��ǥ([�α���] �޴� ��ġ)�� Ŀ���� �̵��ϰ� printf �Լ��� ȭ��ǥ ���
			printf("��");

			cnt = 0;								//���� cnt�� �޴� ���ð�(0��°) ����
		}
		else if (key == 80) {						//key ���� 80�� ���(����Ű DownŰ)
			gotoxy((WIDTH / 2) - 8, (HEIGHT / 2) - 4);		//gotoxy�� ���� Ư�� ��ǥ([�α���] �޴� ��ġ)�� Ŀ���� �̵��ϰ� ȭ��ǥ�� ����
			printf("  ");

			gotoxy((WIDTH / 2) - 8, (HEIGHT / 2));			//gotoxy�� ���� Ư�� ��ǥ([ȸ������] �޴� ��ġ)�� Ŀ���� �̵��ϰ� printf �Լ��� ȭ��ǥ ���
			printf("��");

			cnt = 1;								//���� cnt�� �޴� ���ð�(1��°) ����
		}
		else if (key == 13) {						//key ���� 13�� ���(Enter Ű)
			return cnt;									//������ �޴� ���� ��ȯ
		}
		else if (key == 27) {					//key ���� 27�� ���(Esc Ű)
			mysql_close(connection);
			exit(0);									//exit �Լ��� ���� ���α׷� ����
		}
	}
}