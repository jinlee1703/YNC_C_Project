#define _CRT_SECURE_NO_WARNINGS		//��ó����(#) ���α׷� ���࿡ ���Ǵ� ��ũ�ο� ������� ����
#include <stdio.h>					//ǥ������� �Լ� �������
#include <conio.h>					//�ܼ������ �Լ� �������
#include <string.h>					//ǥ�� ���ڿ� �Լ� �������
#include <Windows.h>				//������ ���� ���α׷��� ���� �������

#include "main.h"			//main.h ����� ������� ����
#include "console.h"		//console.h ����� ������� ����
#include "drawing.h"		//drawing.h ����� ������� ����
#include "text.h"			//text.h ����� ������� ����


//�α��� ȭ���� ����ϰ� DB�� ����Ǿ��ִ� ȸ�������� ���� �α��� ���� ���θ� ��ȯ�ϴ� ����� �Լ�
int loginDisplay() {
	char id[255] = { 0 };		//�Է��� id�� ������ char�� �迭 id�� ũ�� 255�� �����Ͽ� 0���� �ʱ�ȭ
	char pw[255] = { 0 };		//�Է��� id�� ������ char�� �迭 id�� ũ�� 255�� �����Ͽ� 0���� �ʱ�ȭ

	system("cls");				//system�Լ��� ȭ�� �ʱ�ȭ

	consoleShow();			//����� ���� �Լ� consoleShow �Լ��� �ܼ��� ������ ũ��� ��
	drawingBorder();		//����� ���� �Լ��� �׵θ� ���
	drawingTitle();			//����� ���� �Լ��� ���α׷� ���� ���
	drawingNameTag();			//����� ���� �Լ��� ���α׷� �ۼ����� �й�, �̸� ���

	gotoxy((WIDTH / 2) - 30, (HEIGHT / 2) - 8);											//gotoxy �Լ��� ����� ȭ�� ������ ����� ��ġ�� �̵��ϰ� printf �Լ��� ���
	printf("�� �׸��� �Է��ϰ� ENTER Ű �Է� �� ���� �׸����� �̵��մϴ�.");

	drawingTextBox(16, "���̵� : ");		//���̵� �Է��� �ؽ�Ʈ�ڽ� ���
	drawingTextBox(21, "��й�ȣ : ");	//��й�ȣ�� �Է��� �ؽ�Ʈ�ڽ� ���

	gotoxy((WIDTH / 2) - 11, 16);			//����� �Լ� gotoxy �Լ��� ���̵� �Է¹��� ��ġ�� �̵�
	if (get_id(id) == -1)			//����� �Լ� get_id�� ���� ���̵� �Է¹ް� ��ȯ���� -1(ESC Ű �Է�)�̸� �α��� ȭ�� ����(���� ȭ������ �̵�)
		return 1;

	gotoxy((WIDTH / 2) - 11, 21);			//����� �Լ� gotoxy �Լ��� ��й�ȣ�� �Է¹��� ��ġ�� �̵�
	if (get_pw(pw) == -1)			//����� �Լ� get_pw�� ���� ��й�ȣ�� �Է¹ް� ��ȯ���� -1(ESC Ű �Է�)�̸� �α��� ȭ�� ����(���� ȭ������ �̵�)
		return 1;

	gotoxy((WIDTH / 2) - 36, 31);			//gotoxy�� ���� �α��� ���� ���θ� ����� ��ġ�� �̵�

	sprintf(query, "select * from member where member_id='%s' and member_pw='%s'", id, pw);		//sprintf �Լ��� ���� query�� �������� ����

	mysql_query(connection, query);		//mysql_query �Լ��� ���� connection(���� ����)�� ������ ����(select���� ���� �Է��� id�� pw�� ��ġ�ϴ� ȸ���� �ִ��� Ȯ��)

	result = mysql_store_result(connection);			//result�� mysql_store_result�Լ��� ����Ͽ� connection(��������)�� ���� ����� ����

	if (mysql_num_rows(result) == 1) {			//strcmp �Լ��� ���� id�� pw���� �����ϴ��� ��
		sprintf(login_id, id);
		printf("�α��� ����! �ƹ� Ű�� ������ �޴� ȭ������ �̵��մϴ�.");		//�α��� ���� �޽��� ���
		_getch();																//�ƹ� Ű�� �Է� ����
		mysql_free_result(result);							//mysql_free_result �Լ��� ����Ͽ� �޸𸮿� result�� ���� ����(����)
		return 0;																//0(����) ��ȯ
	}
	else {
		printf("�α��� ����! �ƹ� Ű�� ������ ���� ȭ������ ���ư��ϴ�.");		//�α��� ���� �޽��� ���
		_getch();																//�ƹ� Ű�� �Է� ����
		mysql_free_result(result);							//mysql_free_result �Լ��� ����Ͽ� �޸𸮿� result�� ���� ����(����)
		return 1;																//0(����) ��ȯ
	}
}