#include <stdio.h>			//표준입출력 함수 헤더파일
#include <Windows.h>		//윈도우 응용 프로그램을 위한 헤더파일

#include "main.h"
#include "console.h"		//console.h 사용자 헤더파일 포함

//화면 테두리를 그려주는 함수
void drawingBorder() {
	int i = 0, j = 0;		//for 반복문에 사용될 int형 변수 i와 j 선언 후 0으로 초기화

	for (i = 0; i < HEIGHT; i++) {				//테두리 그리기
		for (j = 0; j < WIDTH; j += 2) {
			gotoxy(j, i);
			if (i == 0 || i == HEIGHT - 1) {			//가로줄
				printf("■");
			}
			else if (j == 0 || j == WIDTH - 2)		//세로줄
				printf("■");
		}
	}
}

//화면 중앙 상단에 게임 제목(Title)을 출력하는 함수
void drawingTitle() {
	//제목 출력 : 28비트
	gotoxy((WIDTH / 2) - 14, 4);
	printf("+--------------------------+");
	gotoxy((WIDTH / 2) - 14, 5);
	printf("| 타 자 연 습  프 로 그 램 |");
	gotoxy((WIDTH / 2) - 14, 6);
	printf("+--------------------------+");
}

//화면 좌측 상단에 학번, 이름을 출력하는 함수
void drawingNameTag() {
	gotoxy(2, 1);
	printf(" 학번 : 1705026");
	gotoxy(2, 2);
	printf(" 이름 : 이진우");
}

//화면 중앙 하단에 키 조작 설명을 출력하는 함수
void drawingExplanation() {
	gotoxy((WIDTH / 2) - 11, 25);
	printf("메뉴 조작 : '↑↓' KEY \n");
	gotoxy((WIDTH / 2) - 12, 28);
	printf("선택 완료 : 'ENTER' KEY \n");
	gotoxy((WIDTH / 2) - 11, 31);
	printf("이전 메뉴 : 'ESC' KEY \n");
}

//텍스트박스 형태를 출력하는 함수
void drawingTextBox(int col, char text[]) {
	int stl = (int)strlen(text) + 1;

	gotoxy((WIDTH / 2) - 12, col - 1);
	printf("+----------------------+");
	gotoxy((WIDTH / 2) - 12 - stl, col);
	printf("%s |", text);
	gotoxy((WIDTH / 2) - 12, col + 1);
	printf("+----------------------+");
	gotoxy((WIDTH / 2) + 11, col);
	printf("|");
}

//로그인 후 화면에서 로그인 된 아이디를 화면 우측 상단에 출력하는 함수
void drawingIdtag() {
	gotoxy(WIDTH - 30, 2);
	printf("Player :  %s 님", login_id);
}

//gotoxy와 printf 함수와 for문을 사용하여 텍스트박스를 출력하는 사용자 함수(긴글연습, 짧은 글 연습 사용)
void drawingTestTextbox(int col) {
	int i = 0;								//for반복문을 사용하기 위한 int형 변수 i 선언 후 0으로 초기화

	gotoxy(4, col - 1);		printf("+");	//화면에 텍스트 박스 출력
	gotoxy(4, col + 1);		printf("+");
	for (i = 5; i < WIDTH - 5; i++) {
		gotoxy(i, col - 1);	printf("-");
		gotoxy(i, col + 1);	printf("-");
	}
	gotoxy(WIDTH - 5, col - 1);	printf("+");
	gotoxy(WIDTH - 5, col + 1);	printf("+");
	gotoxy(4, col);		printf("|");
	gotoxy(WIDTH - 5, col);		printf("|");
}

//gotoxy와 printf 함수와 for문을 사용하여 출력된 텍스트박스의 내용(화면 상)을 지우는 사용자 함수(긴글연습, 짧은 글 연습 사용)
void testTextboxClear(int col) {
	int i = 0;

	for (i = 5; i < WIDTH - 6; i++) {
		gotoxy(i, col);
		printf(" ");
	}
}