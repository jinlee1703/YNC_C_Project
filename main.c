#define _CRT_SECURE_NO_WARNINGS		//��ó����(#) ���α׷� ���࿡ ���Ǵ� ��ũ�ο� ������� ����
#include <stdio.h>					//ǥ������� �Լ� �������
#include <conio.h>					//�ܼ� ����� �������
#include <string.h>					//ǥ�� ���ڿ� �Լ� �������
#include <stdlib.h>					//ǥ�� ���̺귯�� �������
#include <Windows.h>				//������ ���� ���α׷��� ���� �������

#include "console.h"		//console.h ����� ������� ����
#include "drawing.h"		//drawing.h ����� ������� ����
#include "text.h"			//text.h ����� ������� ����

//����� �Լ� ����
int mainDisplay();				//[���� ȭ��]
void signupDisplay();			//[ȸ������ ȭ��]
int menuDisplay();				//[�޴� ���� ȭ��]
void menuSelect();				//�޴� ���� �Լ�

int loginDisplay();				//[�α���] ȭ��
void shortTestDisplay();		//[ª�� �� ����] �޴�
void longTestDisplay();			//[�� �� ����] �޴�
void acidrainGame();			//[�꼺�� ����] �޴�
void viewRanking();				//[��ŷ ����] �޴�

//���� �Լ�
int main(void) {
	int main_select = 0;		//mainDisplay���� ������ �����Ͽ�����(�α���or ȸ������) �����ϴ� ���� ����
	
	mysql_init(&conn);				//mysql_init �Լ��� ���� MYSQL ����ü ���� conn(�ּ�)�� ���ڷ� �޾� �ʱ�ȭ

	//mysq_real_connect �Լ� ���� : mysql_real_connect(MYSQL ����ü, DB�ּ�, DB ID, DB PASSWORD, DB �̸�, ��Ʈ��ȣ, ����, ����(flag))
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);	//mysql_real_connect �Լ��� ���� MYSQL�� ������ �õ��Ͽ� ����� �ּҸ� connection�� ����

	if (connection == NULL) {					//connection�� NULL�� ���(���� ����, �ش��ϴ� ���������� ����)
		fprintf(stderr, "error : %s", mysql_error(&conn));		//fprintf �Լ��� ���� ���۾���(stderr) mysql_error(&conn�� ���� �޽��� ���ڿ� ����)�� ��ȯ�� ���� �޽���(����) ���
		return 1;												//main �Լ� ����
	}

	while (1) {
		main_select = mainDisplay();			//[���� ȭ��]���� [�α���,ȸ������] ���� ���� ����
		
		if (main_select == 0) {								//[���� ȭ��]���� [�α���] ���� ��
			if (loginDisplay() == 0) {						//�α��� ȭ���� 0�� ��ȯ���� ��(�α��� ����, DB���� ȸ�������� ��ȸ�ؼ� �α���)
menu:			switch (menuDisplay()) {						//�޴� ȭ�� (� �޴����� esc�� ���� ��� �޴� ����ȭ������ ���ư�)
				case 0:											//[�޴� ����ȭ��]���� [ª���� ����] ���� ��
					shortTestDisplay();							//[ª�� �� ���� ȭ��]�� �ҷ�����, ����Ǹ�(ESCŰ�� �Է��ϸ�) �ٽ� [�޴� ����] ȭ������ �̵�
					goto menu;
				case 1:											//[�޴� ����ȭ��]���� [�� �� ����] ���� ��
					longTestDisplay();					//[�� �� ���� ȭ��]�� �ҷ�����, ����Ǹ�(ESCŰ�� �Է��ϸ�) �ٽ� [�޴� ����] ȭ������ �̵�
					goto menu;
				case 2:											//[�޴� ����ȭ��]���� [�꼺�� ����] ���� ��
					acidrainGame();								//[�꼺�� ���� ȭ��]�� �ҷ�����, ����Ǹ� �ٽ� [�޴� ����] ȭ������ �̵�
					goto menu;
				case 3:											//[�޴� ����ȭ��]���� [��ŷ ����] ���� ��
					viewRanking();								//[��ŷ ���� ȭ��]�� �ҷ�����, ����Ǹ�(ESCŰ�� �Է��ϸ�) �ٽ� [�޴� ����] ȭ������ �̵�
					goto menu;
				case 4:											//[�޴� ����ȭ��]���� ESCŰ �Է� �� ���� ȭ������ �̵�
					continue;
				}
			}
			else {												//�� �� ���� ȭ������ �̵� : ex) [�޴� ����ȭ��]���� ESC Ű �Է� ��
				continue;
			}
		}
		else if (main_select == 1) {						//���� ȭ�鿡�� [ȸ������] ���� ��
			signupDisplay();					//[ȸ������ ȭ��] �ҷ���
			continue;											//ȸ������ ����(���� or ����) �� �ٽ� ���� ȭ������ �̵�
		}
	}

	return 0;
}