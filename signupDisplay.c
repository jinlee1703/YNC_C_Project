#define _CRT_SECURE_NO_WARNINGS		//��ó����(#) ���α׷� ���࿡ ���Ǵ� ��ũ�ο� ������� ����
#include <stdio.h>					//ǥ������� �Լ� �������
#include <string.h>					//ǥ�� ���ڿ� �Լ� �������

#include "main.h"					//main.h ����� ������� ����
#include "console.h"				//console.h ����� ������� ����
#include "drawing.h"				//drawing.h ����� ������� ����
#include "text.h"					//text.h ����� ������� ����

//DB�� ȸ�� ������ �����ϴ� �Լ�
void signupDisplay() {
	char id[255] = { 0 };		//����ڰ� �Է��� id�� ������ char�� �迭 id�� ũ�� 255�� �����Ͽ� 0���� �ʱ�ȭ
	char pw[255] = { 0 };		//����ڰ� �Է��� pw�� ������ char�� �迭 pw�� ũ�� 255�� �����Ͽ� 0���� �ʱ�ȭ
	char pw2[255] = { 0 };		//����ڰ� �Է��� pw Ȯ���� ������ char�� �迭 pw2�� ũ�� 255�� �����Ͽ� 0���� �ʱ�ȭ

	while (1) {			//���� �ݺ�
		system("cls");			//system�Լ��� ȭ�� �ʱ�ȭ

		consoleShow();		//����� ���� �Լ� consoleShow �Լ��� �ܼ��� ������ ũ��� ��
		drawingBorder();	//����� ���� �Լ��� �׵θ� ���
		drawingTitle();		//����� ���� �Լ��� ���α׷� ���� ���

		gotoxy((WIDTH / 2) - 30, (HEIGHT / 2) - 8);		//gotoxy �Լ��� ����� ȭ�� ������ ����� ��ġ�� �̵��ϰ� printf �Լ��� ���
		printf("�� �׸��� �Է��ϰ� ENTER Ű �Է� �� ���� �׸����� �̵��մϴ�.");

		drawingTextBox(16, "���̵� : ");			//���̵� �Է��� �ؽ�Ʈ�ڽ� ���
		drawingTextBox(21, "��й�ȣ : ");		//��й�ȣ�� �Է��� �ؽ�Ʈ�ڽ� ���
		drawingTextBox(26, "��й�ȣ Ȯ�� : ");	//��й�ȣ Ȯ���� �Է��� �ؽ�Ʈ�ڽ� ���

		gotoxy((WIDTH / 2) - 11, 16);			//����� �Լ� gotoxy �Լ��� ���̵� �Է¹��� ��ġ�� �̵�
		if (get_id(id) == -1)			//����� �Լ� get_id�� ���� ���̵� �Է¹ް� ��ȯ���� -1(ESC Ű �Է�)�̸� �α��� ȭ�� ����(���� ȭ������ �̵�)
			return;

		gotoxy((WIDTH / 2) - 11, 21);			//����� �Լ� gotoxy �Լ��� ��й�ȣ�� �Է¹��� ��ġ�� �̵�
		if (get_pw(pw) == -1)			//����� �Լ� get_pw�� ���� ��й�ȣ�� �Է¹ް� ��ȯ���� -1(ESC Ű �Է�)�̸� �α��� ȭ�� ����(���� ȭ������ �̵�)
			return;

		gotoxy((WIDTH / 2) - 11, 26);			//����� �Լ� gotoxy �Լ��� ��й�ȣ Ȯ���� �Է¹��� ��ġ�� �̵�
		if (get_pw(pw2) == -1)		//����� �Լ� get_pw�� ���� ��й�ȣ Ȯ���� �Է¹ް� ��ȯ���� -1(ESC Ű �Է�)�̸� �α��� ȭ�� ����(���� ȭ������ �̵�)
			return;

		sprintf(query, "select * from member where member_id='%s'", id);		//sprintf �Լ��� ���� query�� �������� ����

		mysql_query(connection, query);		//mysql_query �Լ��� ���� connection(���� ����)�� ������ ����(select���� ���� �Է��� id�� �ߺ��Ǵ� ȸ���� �ִ��� Ȯ��)

		result = mysql_store_result(connection);			//result�� mysql_store_result�Լ��� ����Ͽ� connection(��������)�� ���� ����� ����
		
		if (strcmp(id, "") != 0 && strcmp(pw, "") != "" &&  mysql_num_rows(result) == 0 && strcmp(pw, pw2) == 0) {		//DB�� �ߺ��Ǵ� ���̵� ����(�̿ϼ�) pw�� pw Ȯ���� �������
			//[ DB�� ���� ]
			sprintf(query, "insert into member (`member_id`, `member_pw`) VALUES ('%s', '%s')", id, pw);		//sprintf �Լ��� ���� query�� �������� ����

			mysql_query(connection, query);		//mysql_query �Լ��� ���� connection(���� ����)�� ������ ����(select���� ���� �Է��� id�� �ߺ��Ǵ� ȸ���� �ִ��� Ȯ��)

			result = mysql_store_result(connection);			//result�� mysql_store_result�Լ��� ����Ͽ� connection(��������)�� ���� ����� ����

			mysql_free_result(result);							//mysql_free_result �Լ��� ����Ͽ� �޸𸮿� result�� ���� ����(����)

			gotoxy((WIDTH / 2) - 36, 31);	//ȸ������ �Ϸ� �޽����� ����� ��ġ�� �̵� �� printf �Լ��� ȸ�� ���� �Ϸ� �޽��� ���
			printf("ȸ�� ������ �Ϸ�Ǿ����ϴ�. �ƹ� Ű�� ������ �α��� ȭ������ ���ư��ϴ�.");
			_getch();					//�ƹ�Ű �Է� ����
			break;						//�ݺ��� ����
		}
		else {							//DB�� �ߺ��Ǵ� ���̵� �ְų�(�̿ϼ�) pw�� pw Ȯ���� �ٸ� ���
			gotoxy((WIDTH / 2) - 52, 31);	//ȸ������ ���� �޽����� ����� ��ġ�� �̵� �� printf �Լ��� ȸ�� ���� �Ϸ� �޽��� ���
			printf("���̵� Ȥ�� ��й�ȣ�� �߸� �Ǿ����ϴ�. ���̵�� �ߺ����� �ʰ�, ��й�ȣ�� ��й�ȣ Ȯ���� ���ƾ� �մϴ�.");

			while (1) {						//�޽����� ��µǾ��� �� while �ݺ����� ���� ���� �ൿ�� ó��
				if (_getch() == VK_ESCAPE)		//�޽����� ��µǾ��� �� ESC�� �Է������� ������(����ȭ������ �̵�)
					return;
				else
					break;						//�� ���� Ű�� �Է����� �� ���� �޽��� ��� �� ó������ ����
			}
		}
	}
}