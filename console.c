#define _CRT_SECURE_NO_WARNINGS			//��ó����(#) ���α׷� ���࿡ ���Ǵ� ��ũ�ο� ������� ����
#include <stdio.h>						//ǥ������� �Լ� �������
#include <Windows.h>					//������ ���� ���α׷��� ���� �������

#include "main.h"						//main.h ����� ������� ����(��ũ�� ����� ��ϵǾ� ����)

//main.c�� ����Ǿ� �ִ� ��ũ�� ��� WIDTH(w)�� HEGIHT(h)�� �޾ƿ� �ܼ� â�� ũ�⸦ �����Ͽ� �����Ű�� �Լ�
void consoleShow() {
	char cmd_buffer[255] = { 0 };		//system �Լ��� �����ų ������ �����ϴ� char�� cmd_buffer �迭

	sprintf(cmd_buffer, "mode con: cols=%d lines=%d", WIDTH, HEIGHT);			//cmd_buffer�� system�Լ��� �� ������ ����(%d �������� WIDTH�� HEIGHT�� �Է�)
	system(cmd_buffer);													//system �Լ��� ���� ȭ��ũ�� ����
}

//�ܼ�â�� Ư�� ��ġ�� Ŀ���� �̵���Ű�� �Լ� : x�� ����(cols), y�� liness ��ġ�� �޾ƿ�
void gotoxy(int x, int y) {
	COORD Pos = { x, y };												//COORD ����ü�� ������ Pos�� ��ǥ��(x, y)�� ����
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);		//Pos�� ��ǥ���� ���� �ܼ� â�� �̵�
}

//Ư�� Ű�� �ԷµǾ����� Ȯ���ϴ� �Լ� : �� �Լ��� VK_RETURN(Enter Ű)�� �Է����� ��� ���۰� �����ִ� ��찡 ���� getch() �Լ��� �ӽ� ��ü�Ͽ���
BOOL isKeyDown(int key) {
	return (GetAsyncKeyState(key) && 0x8000 != 0);
}