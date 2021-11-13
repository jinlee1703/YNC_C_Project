#define _CRT_SECURE_NO_WARNINGS		//��ó����(#) ���α׷� ���࿡ ���Ǵ� ��ũ�ο� ������� ����
#include <stdio.h>					//ǥ������� �Լ� �������
#include <conio.h>					//�ܼ������ �Լ� �������
#include <time.h>

#include "main.h"

//���ۿ� id�� �Է¹޴� �Լ�(���� �����ڸ� ����)
int get_id(char *buf) {
	int cnt = 0, key;  //�Է� ���� ���� ���� ������ int�� ���� cnt�� �� Ű ���� ������ key ����

	while (1) {
		key = _getch();					//�� ���� �Է¹޾� key�� ����

		if (key == ENTER_KEY) {									//ENTER Ű(13) �Է� �� �ݺ��� ����
			break;
		}
		else if (key == BACKSPACE_KEY && cnt != 0) {					// BACKSPACE(8) �Է� �� ���� �����(���ڿ��� �Էµ��� �ʾ��� ��쿡�� ������ ����)
			putchar('\b');									//\b(�齺���̽�)�� ����Ͽ� �� ��Ʈ �ڷ� �̵�
			putchar(' ');									//ȭ�鿡 ���� ǥ��
			putchar('\b');									//\b(�齺���̽�)�� ����Ͽ� �� ��Ʈ �ڷ� �̵�
			buf[cnt--] = ' ';								//������ ������ ���� ���� ' '(����) ó��(���)
			continue;
		}
		else if ((cnt <= ID_SIZE - 1) && ((key >= 'a' && key <= 'z') || (key >= '0' && key <= '9'))) {		// �ִ� ũ�⸦ �Ѿ�� �ʾ����� ���ڸ� ���(����� ���ڸ� �Է� ����)
			buf[cnt++] = (char)key;										// ���ۿ� ���� �����ϰ� ī��Ʈ 1 ����  
			
			putchar(key);												// ȭ�鿡 ���� ǥ��
		}
		else if (key == 27) {								//ESC Ű(27) �Է� �� -1 ��ȯ(���� ȭ������ ���ư� ��)
			return -1;
		}
	}

	buf[cnt] = '\0';				// ���ڿ��� ����� ���� ���� ���ڸ� ������ �������� ����
	return 0;
}

//���ۿ� id�� �Է¹޴� �Լ�(���� �����ڸ� ����, �Է� �� *�� ǥ��)
int get_pw(char *buf) {
	int cnt = 0, key;  //�Է� ���� ���� ���� ������ int�� ���� cnt�� �� Ű ���� ������ key ����

	while (1) {
		key = _getch();					// �� ���� �Է¹���

		if (key == 13) {				//ENTER Ű(13) �Է� �� �ݺ��� ����
			break;
		}
		if (key == 8 && cnt != 0) {		// BACKSPACE(8) �Է� �� ���� �����(���ڿ��� �Էµ��� �ʾ��� ��쿡�� ������ ����)
			putchar('\b');				//\b(�齺���̽�)�� ����Ͽ� �� ��Ʈ �ڷ� �̵�
			putchar(' ');				// ȭ�鿡 �� ǥ��
			putchar('\b');				//\b(�齺���̽�)�� ����Ͽ� �� ��Ʈ �ڷ� �̵�
			buf[cnt--] = ' ';			//���� ����
			continue;					//���� �Է� ����
		}
		else if ((cnt <= PW_SIZE - 1) && ((key >= 'a' && key <= 'z') || (key >= '0' && key <= '9'))) {			// �ִ� ũ�⸦ �Ѿ�� �ʾ����� ���ڸ� ��� (����� ���ڸ� �Է� ����)
			
			buf[cnt++] = (char)key;											// ���ۿ� ���� �����ϰ� ī��Ʈ 1 ����  
			putchar('*');													// ȭ�鿡 �� ǥ��
		}
		else if (key == 27) {												//ESC Ű(27) �Է� �� -1 ��ȯ(���� ȭ������ ���ư� ��)
			return -1;
		}
	}

	buf[cnt] = '\0';				// ���ڿ��� ����� ���� �� ���� ������
	return 0;
}

//����ڿ��� Ÿ�ڿ��� �����͸� �Է¹޴� �Լ� : Ÿ��, ��Ȯ�� �����
int get_Typing(char *text, char *user, TA *data, int mode) {	
	int key = 0, cnt = 0 ,i = 0;;				//Ű���� ������ int�� ���� key�� �Է��� ���ڼ��� ���� int�� ���� cnt, for �ݺ����� ����ϱ� ���� i�� ���� �� 0���� �ʱ�ȭ
	static clock_t start_t, now_t;				//Ÿ�ڿ����� ó�� ����(�Է�)������ �ð��� �� ���ķ� �Է��� �ð��� ���ϱ� ���� clock_t ����ü ���� ����(time.h�� ����Ǿ� ����)
	//�������� : ��ۿ����� ��� �� ������ �ƴ� 5���嵿�� Ÿ���� ��Ȯ���� �̾����� �ϱ� ������ ���������� ������
	//static int cnt = 0;							//�Է��� ���ڼ��� ���� int�� ���� cnt ���� �� 0���� �ʱ�ȭ
	static int tt = 0;							//���� �ð��� �� Ÿ������ �ð��� ���Ͽ� Ÿ���� ���ϱ� ���� int�� ���� tt ������ 0���� �ʱ�ȭ
	static int res;								//Ÿ���� �����ϱ� ���� int�� ���� res�� �����ϰ� 0���� �ʱ�ȭ
	static int pp = 0;							//�Է��� ���ڼ��� ���� ��Ȯ���� Ȯ���ϱ� ���� int�� ���� pp �� 0���� �ʱ�ȭ����
	static int numberOfCalls = 0;				//�� �� ���� �� ��� ȣ��� Ƚ���� ���� ���� �������� numberOfCalls�� ����
	static int totalNumberOfCh = 0;				//����ڰ� �Է��� �� Ƚ���� ���� ���� �������� totalNumberOfCh ����

	while (1) {	
		key = _getch();				// �� ���� �Է¹���

		if ((key == ENTER_KEY) || (strlen(text) == (cnt + 1)) && (key != BACKSPACE_KEY)) {			//ENTER or �Է��� ������ ����Ʈ���� ������ ���(�ڵ� ���� ó��)
			if (mode == 2) {
				numberOfCalls++;										//��� ������ ��� ȣ��� Ƚ�� +1(���� �� ����� ����)
				
			}
			if ((mode == 1) || (numberOfCalls == 5)) {					//ª�� ���̰ų� �� �� 5��° ���ϰ�� ��������
				numberOfCalls = 0;
				tt = 0;
				res = 0;
				pp = 0;
				i = 0;
				cnt = 0;
				totalNumberOfCh = 0;
			}
				
			return 1;
		}
		else if (key == BACKSPACE_KEY) {					// BACKSPACE(8) �Է� �� ���� �����
			if (cnt != 0) {
				if (mode == 1)
					gotoxy(6 + cnt, 15);											//���ڸ� �Է��ϱ� ���� ��ǥ ����(ª�� ��)
				else if (mode == 2)
					gotoxy(6 + cnt, 9 + (numberOfCalls * 3 * 2));				//���ڸ� �Է��ϱ� ���� ��ǥ ����(�� ��)

				putchar('\b');				//\b(�齺���̽�)�� ����Ͽ� �� ��Ʈ �ڷ� �̵�
				putchar(' ');				// ȭ�鿡 �� ǥ��
				putchar('\b');				//\b(�齺���̽�)�� ����Ͽ� �� ��Ʈ �ڷ� �̵�
				user[cnt--] = ' ';			//���� ����
				continue;					//���� �Է� ����
			}
		}
		else if (key == ESC_KEY) {		//ESC
			numberOfCalls = 0;		//ȣ�� Ƚ�� �ʱ�ȭ
			tt = 0;
			res = 0;
			pp = 0;
			i = 0;
			cnt = 0;
			totalNumberOfCh = 0;
			return -1;
		}
		else {
			/*ª�� �� ���� (�� �� ������ ���, �ؽ�Ʈ�ڽ� ��ġ ���� �ٸ��� ������ �Ű����� mode�� ���� ��� ����)*/
			if (mode == 1) {									
				user[cnt++] = (char)key;						//���ۿ� ���� �����ϰ� ī��Ʈ 1 ����
				
				//[Ÿ�� �Է¿� ���� Ÿ��, ��Ȯ�� ����]
				if (cnt == 1)	start_t = clock();				//ó�� �Է� �� ���� start_t�� clock �Լ��� ���� ���� ����(�ð�)�� ����

				now_t = clock();								//Ű�� �Է� ���� ���� ���� ����(�ð�)�� ����

				tt = (int)((now_t - start_t) / CLOCKS_PER_SEC) + 1;	//���� tt�� ���� Ű �Է� �ð��� ó�� Ű�� �Է����� �ð��� ���� �̸� COLCKS_PER_SEC�� ���� �������ν� �Ҹ��� �ð��� 1�� ����

				res = (int)1000 * (cnt + 1) / (tt * 30);			//���� res�� �⺻ Ÿ�� 1000�� Ÿ������ Ƚ�� +1��  tt�� 30�� ���� ���� ���Ͽ� ����(Ÿ�� �ӵ� ���ϴ� ���)

				pp = 0;											//��Ȯ�� ���� ���� ī��Ʈ�ϱ� ���� ���� pp�� 0���� �ʱ�ȭ

				for (i = 0; i < cnt; i++) {						//for �ݺ����� ����Ͽ� �Է��� ���� ��ü�� �Է��� ���ڿ� ���Ͽ� ���� ��� pp�� 1�� ����
					if (text[i] == user[i])
						pp++;
				}

				data->speed = res;								//�����ͷ� �޾ƿ� �Ű�����(����ü ����)�� ������� speed�� Ÿ�� ����
				data->percent = pp * 100 / (cnt);				//�����ͷ� �޾ƿ� �Ű�����(����ü ����)�� ������� percent�� ��Ȯ�� ����

				//[Ÿ�� �Է¿� ���� Ÿ��, ��Ȯ�� ����]
				gotoxy(6, 10);					//Ÿ�� ����� ���� ��ǥ ����
				printf("Ÿ�� : %4d Ÿ", data->speed);		//Ÿ�� ���

				gotoxy(40, 10);					//��Ȯ�� ����� ���� ��ǥ ����
				printf("��Ȯ�� : %3d %%", data->percent);	//��Ȯ�� ���

				gotoxy(6 + cnt - 1, 15);		//���ڸ� �Է��ϱ� ���� ��ǥ ����
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				putchar(key);					//�Է��� ���� ���
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			/*��� ����*/
			else if (mode == 2) {		
				user[cnt++] = (char)key;						//���ۿ� ���� �����ϰ� ī��Ʈ 1 ����
				totalNumberOfCh++;

				//[Ÿ�� �Է¿� ���� Ÿ��, ��Ȯ�� ����]
				if (cnt == 1 && numberOfCalls == 0)	start_t = clock();				//ó�� �Է� �� ���� start_t�� clock �Լ��� ���� ���� ����(�ð�)�� ����
				
				now_t = clock();								//Ű�� �Է� ���� ���� ���� ����(�ð�)�� ����

				tt = (int)((now_t - start_t) / CLOCKS_PER_SEC) + 1;	//���� tt�� ���� Ű �Է� �ð��� ó�� Ű�� �Է����� �ð��� ���� �̸� COLCKS_PER_SEC�� ���� �������ν� �Ҹ��� �ð��� 1�� ����

				res = (int)1000 * (totalNumberOfCh + 1) / (tt * 30);	//���� res�� �⺻ Ÿ�� 1000�� Ÿ������ Ƚ�� +1��  tt�� 30�� ���� ���� ���Ͽ� ����(Ÿ�� �ӵ� ���ϴ� ���)

				//pp = 0;										//��Ȯ�� ���� ���� ī��Ʈ�ϱ� ���� ���� pp�� 0���� �ʱ�ȭ

				if (text[cnt - 1] == user[cnt - 1])						//�Է��� ���� ��ü�� �Է��� ���ڿ� ���Ͽ� ���� ��� pp�� 1�� ����
					pp++;

				data->speed = res;								//�����ͷ� �޾ƿ� �Ű�����(����ü ����)�� ������� speed�� Ÿ�� ����
				data->percent = pp * 100 / (totalNumberOfCh);				//�����ͷ� �޾ƿ� �Ű�����(����ü ����)�� ������� percent�� ��Ȯ�� ����

				//[Ÿ�� �Է¿� ���� Ÿ��, ��Ȯ�� ����]
				gotoxy(6, 4);					//Ÿ�� ����� ���� ��ǥ ����
				printf("Ÿ�� : %4d Ÿ", data->speed);		//Ÿ�� ���

				gotoxy(40, 4);					//��Ȯ�� ����� ���� ��ǥ ����
				printf("��Ȯ�� : %3d %%", data->percent);	//��Ȯ�� ���

				gotoxy(6 + cnt - 1, 9 + (numberOfCalls * 3 * 2));						//���ڸ� �Է��ϱ� ���� ��ǥ ����
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				putchar(key);					//�Է��� ���� ���
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
		}
	}
}