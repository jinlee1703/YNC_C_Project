#define _CRT_SECURE_NO_WARNINGS		//��ó����(#) ���α׷� ���࿡ ���Ǵ� ��ũ�ο� ������� ����
#include <stdio.h>					//ǥ������� �Լ� �������
#include <conio.h>					//�ܼ� ����� �������
#include <string.h>					//ǥ�� ���ڿ� �Լ� �������
#include <stdlib.h>					//ǥ�� ���̺귯�� �������
#include <windows.h>				//������ ���� ���α׷��� ���� �������

#include "console.h"		//console.h ����� ������� ����
#include "drawing.h"		//drawing.h ����� ������� ����
#include "text.h"			//text.h ����� ������� ����

void viewChart(int cnt);		//�޴� ���ý� ��Ʈ�� ��µǵ��� �ϴ� ����� ���� �Լ�(�̱���)
void viewSelect(int cnt);		//Ű �Է� �� �޴��� �����ϵ��� �ϴ� �Լ�

//[��ŷ ����] �޴� ���� �� ȭ���� ��Ÿ������ �ϴ� �Լ�
void viewRanking() {
	int cnt = 0, key = 0;			//�� ��° ī�װ�(��ŷ �з�)�� �����ߴ����� ������ int�� ���� cnt�� ����ڰ� �Է��� Ű ���� ������ ���� key ���� �� 0���� �ʱ�ȭ

	system("cls");					//system�Լ��� ȭ�� �ʱ�ȭ

	consoleShow();				//����� ���� �Լ� consoleShow �Լ��� �ܼ��� ������ ũ��� ��
	drawingBorder();			//����� ���� �Լ��� �׵θ� ���
	drawingIdtag();	//�α��� �� ID ���(�̿ϼ�)

	gotoxy(20, 5);					//gotoxy �Լ��� ����� [ª�� �� ����] ī�װ��� ����� ��ġ�� �̵��ϰ� printf �Լ��� ���
	printf("ª�� �� ����");

	gotoxy(55, 5);					//gotoxy �Լ��� ����� [�� �� ����] ī�װ��� ����� ��ġ�� �̵��ϰ� printf �Լ��� ���
	printf("�� �� ����");

	gotoxy(90, 5);					//gotoxy �Լ��� ����� [�꼺�� ����] ī�װ��� ����� ��ġ�� �̵��ϰ� printf �Լ��� ���
	printf("�꼺�� ���� ����");

	gotoxy(16, 5);					//gotoxy �Լ��� ���� ����ڰ� ������ �޴��� ������ ��ġ�� �̵��Ͽ� ȭ��ǥ(��) ���
	printf("��");
	viewChart(cnt);			//������ ī�װ��� �ش��ϴ� ��Ʈ ���

	//sprintf �Լ��� ���� query�� �������� ����
	sprintf(query, "select member_id, events_id, format(avg(typing_speed),0), format(avg(typing_percent),0), date_format(typing_date, '%%m-%%d') from typing where member_id = '%s' and events_id != '3'", login_id);

	mysql_query(connection, query);		//mysql_query �Լ��� ���� connection(���� ����)�� ������ ����(DB�� ����Ǿ� �ִ� �ִ� ��ü Ÿ���� �������� ����� ��ȸ)

	result = mysql_store_result(connection);			//result�� mysql_store_result�Լ��� ����Ͽ� connection(��������)�� ���� ����� ����

	row = mysql_fetch_row(result);

	gotoxy(6, 2);
	printf("��� Ÿ�� : %sŸ \t ��� ��Ȯ�� : %s%%", row[2], row[3]);

	while (1) {						//���� �ݺ���(esc Ű�� �Է��ϸ� �޴� ���� ȭ������ ���ư�)
		key = _getch();					//���� key�� ����ڰ� �Է��� key ���� ����
		if (key == 72) {				//key ���� 72�� ���(����Ű UpŰ)
			if (cnt > 0) {					//cnt�� 0 ���� Ŭ ���(�� ���� �޴��� �ƴ� �޴� ����)
				cnt--;						//cnt�� ���� 1����
				viewSelect(cnt);		//���õ� ī�װ��� ǥ���ϵ��� �Լ� ȣ��
				viewChart(cnt);		//���õ� ī�װ��� �ش��ϴ� ��Ʈ�� ����ϵ��� �Լ� ȣ��
			}
		}
		else if (key == 80) {			//key ���� 80�� ���(����Ű DownŰ)
			if (cnt < 2) {					//cnt�� 2 ���� ���� ���(�� �Ʒ��� �޴��� �ƴ� �޴� ����)
				cnt++;						//cnt�� ���� ���ϰ�
				viewSelect(cnt);		//���õ� ī�װ��� ǥ���ϵ��� �Լ� ȣ��
				viewChart(cnt);		//���õ� ī�װ��� �ش��ϴ� ��Ʈ�� ����ϵ��� �Լ� ȣ��
			}
		}
		else if (key == 27) {			//Esc key �Է� �� 4 ��ȯ (���� ȭ������ ȸ��)
			break;
		}
	}
}

//Ű �Է� �� �޴��� �����ϵ��� �ϴ� �Լ�
void viewSelect(int cnt) {
	int i = 0;							//for �ݺ����� ����ϱ� ���� int�� ���� i ���� �� 0���� �ʱ�ȭ

	for (i = 0; i < 4; i++) {			//for �ݺ����� gotoxy �Լ��� ���� 4���� �޴��� �ִ� ȭ��ǥ ǥ��(��)�� �����.(printf() �Լ��� �����)
		gotoxy(16 + (i * 35), 5);
		printf("  ");
	}

	gotoxy(16 + (cnt * 35), 5);			//gotoxy �Լ��� ���� ����ڰ� ������ �޴��� ������ ��ġ�� �̵��Ͽ� ȭ��ǥ(��) ���
	printf("��");
}

void viewChart(int cnt) {
	int i = 0, j = 0;							//for �ݺ����� ���Ǳ� ���� int �� ���� i�� j ���� �� 0���� �ʱ�ȭ
	int grp = 0, total_speed = 0, total_percent = 0;
	unsigned long dw;
	COORD spot = { 7, 8 };
	int r = 0;

	//�׵θ� �׸���
	for (i = 7; i < HEIGHT - 2; i++) {				
		for (j = 6; j < WIDTH - 6; j++) {
			gotoxy(j, i);
			if (i == 7 || i == HEIGHT - 3) {
				if (j == 6 || j == WIDTH - 7)
					printf("+");
				else
					printf("-");				//������
			}
			else if (j == 6 || j == WIDTH - 7)
				printf("|");					//������
		}
	}

	//��Ʈ ���� �ʱ�ȭ
	for (i = 8; i < HEIGHT - 3; i++) {
		spot.Y = i;
		FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', WIDTH - 14, spot, &dw);
	}

	//[��Ʈ ǥ��]
	sprintf(query, "(select member_id, events_id, format(avg(typing_speed),0), format(avg(typing_percent),0), date_format(typing_date, '%%m-%%d') from typing where member_id = '%s' and events_id = '%d' group by typing_date order by 5 desc limit 10) order by 5", login_id, cnt + 1);		//sprintf �Լ��� ���� query�� �������� ����

	mysql_query(connection, query);		//mysql_query �Լ��� ���� connection(���� ����)�� ������ ����(DB�� ����Ǿ� �ִ� ������ ��忡 �ش��ϴ� Ÿ���� �����͸� ��¥���� �׷�ȭ�Ͽ� ��ȸ)
										//�� ��¥ ������ �����Ͱ� �ִ� �ֽ� 10��(��)�� �����͸� ���

	result = mysql_store_result(connection);			//result�� mysql_store_result�Լ��� ����Ͽ� connection(��������)�� ���� ����� ����

	i = 0;

	srand((unsigned int)time(NULL));

	while (((row = mysql_fetch_row(result)) != NULL) && i != 10) {			
		gotoxy(12 + (i * 10), HEIGHT - 4);
		printf("%s", row[4]);			//printf �Լ��� ����Ͽ� ��¥ ���(
		
		grp = atoi(row[2]) / 50;			//50Ÿ(��) �� ĭ�� ���

		if (grp > 20)								//�ִ� 1000Ÿ ���� ǥ�� ����(1000Ÿ ���� ���� ��� 1000Ÿ�� ����)
			grp = 20;

		r = rand() % 6 + 9;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), r);
		for (j = 0; j < grp; j++) {					//���� ��Ʈ ���
			gotoxy(13 + (i * 10), HEIGHT - 6 - j);
			printf("��");
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

		if (cnt != 2) {		//ª����, ��� ����
			gotoxy(11 + (i * 10), HEIGHT - 27);			//��Ʈ ���̺� ���
			printf("%sŸ", row[2]);						//(Ÿ��)
			gotoxy(11 + (i * 10), HEIGHT - 26);			//(��Ȯ��)
			printf(" %s%%", row[3]);
		}
		else {				//�꼺�� ����
			gotoxy(11 + (i * 10), HEIGHT - 26);			//��Ʈ ���̺� ���
			printf("%s��", row[2]);	
		}
		
		i++;
	}
}