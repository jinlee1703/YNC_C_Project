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

//ª�� �� ���� ȭ���� ����ϴ� �Լ�
void shortTestDisplay() {
	/*char texts[][];*/
	char text[WIDTH - 10];		//DB�� ����Ǿ� �ִ� ����(����ڰ� �Է��� ����)�� ����� char�� �迭 text
	char user[WIDTH - 10];		//����ڰ� �Է��� ������ ������ char�� �迭 user
	FILE *fp;					//ª�� ���� ����Ǿ� �ִ� ������ �ҷ����� ���� ����ü ���� ������ ����
	char filepath[255] = { 0 };
	TA data;

	system("cls");					//system�Լ��� ȭ�� �ʱ�ȭ

	consoleShow();				//����� ���� �Լ� consoleShow �Լ��� �ܼ��� ������ ũ��� ��
	drawingBorder();			//����� ���� �Լ��� �׵θ� ���
	drawingIdtag();	//�α��� �� ID ���(�̿ϼ�)

	drawingTestTextbox(12);			//���� �ڽ� ���
	drawingTestTextbox(15);			//�Է� �ڽ� ���

	gotoxy(6, 10);				//Ÿ�� ����� ���� ��ǥ ����
	printf("Ÿ�� : %4d Ÿ", 0);		//Ÿ�� ���

	gotoxy(40, 10);				//��Ȯ�� ����� ���� ��ǥ ����
	printf("��Ȯ�� : %3d %%", 0);	//��Ȯ�� ���

	sprintf(query, "select * from file where events_id = '1' and language = 'eng'");		//sprintf �Լ��� ���� query�� �������� ����

	mysql_query(connection, query);		//mysql_query �Լ��� ���� connection(���� ����)�� ������ ����(select���� ���� �ѱ� ª���� ������ �̸��� ��ȸ)

	result = mysql_store_result(connection);			//result�� mysql_store_result�Լ��� ����Ͽ� connection(��������)�� ���� ����� ����

	row = mysql_fetch_row(result);						//�� �� �� �������� �о��

	sprintf(filepath, "ª�� ��\\%s", row[3]);			//�迭�� DB�� ����Ǿ� �ִ� ���ϸ�� ���� ��� ����

	if ((fp = fopen(filepath, "r")) == NULL) {
		fprintf(stderr, "���� ���� ����!\n");
		return;
	}

	while (1) {				//���� �ݺ�(EscŰ�� ������ ������)
		if (!feof(fp)) {											//���� ���� ���� ��� ������ �о�´�
			fgets(text, WIDTH - 10, fp);							//(�迭 text�� ����)
		} 
		else {
			//�������� ���ư���
			break;
		}
		
		gotoxy(6, 12);												//���� ����� ���� ��ǥ ����
		printf("%s", text);											//���� ���//������ text�� ����(���� DB�� ������ �о���� �κ����� ������ ����)

		gotoxy(6, 15);
		if (get_Typing(text, user, &data, 1) == -1)									//���ڸ� �Է� �ް� ��ȯ���� -1�� ���(Esc�Է�)
			break;													//�ݺ��� ����(�޴� ȭ������ ���ư�)

		sprintf(query, "insert into typing VALUES ('%s', 1, %d, %d, curdate())", login_id, data.speed, data.percent);		//sprintf �Լ��� ���� query�� �������� ����

		mysql_query(connection, query);		//mysql_query �Լ��� ���� connection(���� ����)�� ������ ����(insert������ Ÿ���� ���� ����)

		testTextboxClear(12);		//�Է��� ������ �ִ� �ؽ�Ʈ�ڽ� �ʱ�ȭ
		testTextboxClear(15);		//�Է��� ������ �ִ� �ؽ�Ʈ�ڽ� �ʱ�ȭ
	}
	fclose(fp);
}