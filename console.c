#define _CRT_SECURE_NO_WARNINGS			//전처리기(#) 프로그램 실행에 사용되는 매크로와 헤더파일 선언
#include <stdio.h>						//표준입출력 함수 헤더파일
#include <Windows.h>					//윈도우 응용 프로그램을 위한 헤더파일

#include "main.h"						//main.h 사용자 헤더파일 선언(매크로 상수가 기록되어 있음)

//main.c에 선언되어 있는 매크로 상수 WIDTH(w)와 HEGIHT(h)를 받아와 콘솔 창의 크기를 지정하여 실행시키는 함수
void consoleShow() {
	char cmd_buffer[255] = { 0 };		//system 함수에 실행시킬 문장을 저장하는 char형 cmd_buffer 배열

	sprintf(cmd_buffer, "mode con: cols=%d lines=%d", WIDTH, HEIGHT);			//cmd_buffer에 system함수에 들어갈 문장을 저장(%d 형식으로 WIDTH와 HEIGHT를 입력)
	system(cmd_buffer);													//system 함수를 통해 화면크기 설정
}

//콘솔창의 특정 위치로 커서를 이동시키는 함수 : x는 가로(cols), y는 liness 위치를 받아옴
void gotoxy(int x, int y) {
	COORD Pos = { x, y };												//COORD 구조체로 선언한 Pos에 좌표값(x, y)을 저장
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);		//Pos의 좌표값을 토대로 콘솔 창에 이동
}

//특정 키가 입력되었는지 확인하는 함수 : 이 함수로 VK_RETURN(Enter 키)을 입력했을 경우 버퍼가 남아있는 경우가 생겨 getch() 함수로 임시 대체하였음
BOOL isKeyDown(int key) {
	return (GetAsyncKeyState(key) && 0x8000 != 0);
}