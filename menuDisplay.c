#define _CRT_SECURE_NO_WARNINGS		//전처리기(#) 프로그램 실행에 사용되는 매크로와 헤더파일 선언
#include <stdio.h>					//표준입출력 함수 헤더파일
#include <string.h>					//표준 문자열 함수 헤더파일
#include <conio.h>

#include "console.h"				//console.h 사용자 헤더파일 포함
#include "drawing.h"				//drawing.h 사용자 헤더파일 포함
#include "text.h"					//text.h 사용자 헤더파일 포함

void menuSelect(int cnt);		//사용자가 키를 입력했을 때 선택된 메뉴가 표시되도록 하는 함수

//DB에 회원 정보를 저장하는 함수
int menuDisplay() {
	int cnt = 0, key = 0;			//int형 함수 cnt를 통해 사용자가 선택한 메뉴가 몇번째 메뉴인지 저장하고, key를 통해 사용자가 입력한 key 값을 저장
	
	system("cls");					//system함수로 화면 초기화

	consoleShow();				//사용자 지정 함수 consoleShow 함수로 콘솔을 지정된 크기로 엶
	drawingBorder();			//사용자 지정 함수로 테두리 출력
	drawingTitle();				//사용자 지정 함수로 프로그램 제목 출력
	drawingNameTag();				//사용자 지정 함수로 작성자 학번, 이름 출력
	drawingIdtag();	//사용자 지정 함수로 로그인된 회원 아이디 출력
	drawingExplanation();		//사용자 지정 함수로 키 설명 출력

	gotoxy((WIDTH / 2) - 6, 12);		//gotoxy 함수로 출력할 [짧은 글 연습] 메뉴를 출력할 위치로 이동하고 printf 함수로 출력
	printf("짧은 글 연습");

	gotoxy((WIDTH / 2) - 6, 15);		//gotoxy 함수로 출력할 [긴 글 연습] 메뉴를 출력할 위치로 이동하고 printf 함수로 출력
	printf("긴 글 연습");

	gotoxy((WIDTH / 2) - 6, 18);		//gotoxy 함수로 출력할 [산성비 게임] 메뉴를 출력할 위치로 이동하고 printf 함수로 출력
	printf("산성비 게임");

	gotoxy((WIDTH / 2) - 6, 21);		//gotoxy 함수로 출력할 [랭킹 보기] 메뉴를 출력할 위치로 이동하고 printf 함수로 출력
	printf("기록 보기");

	menuSelect(cnt);			//menuSelect 함수를 통해 [짧은 글 연습]이 기본 선택 메뉴로 출력

	while (1) {		//메뉴 선택
		key = _getch();				//변수 key에 사용자가 입력한 key 값을 저장

		if (key == 72) {			//key 값이 72일 경우(방향키 Up키)
			if (cnt > 0) {				//cnt가 0 보다 클 경우(맨 위의 메뉴가 아닌 메뉴 선택)
				cnt--;						//cnt의 값을 1빼고
				menuSelect(cnt);		//선택된 메뉴 변경 표시
			}
		}
		else if (key == 80) {		//key 값이 80일 경우(방향키 Down키)
			if (cnt < 3) {				//cnt가 3 보다 작을 경우(맨 아래의 메뉴가 아닌 메뉴 선택)
				cnt++;					//cnt의 값을 더하고
				menuSelect(cnt);	//선택된 메뉴 변경 표시
			}
		}
		else if (key == 13)				//Enter key 입력 시 선택된 메뉴 값을 반환
			return cnt;
		else if (key == 27)				//Esc key 입력 시 4 반환 (메인 화면으로 회귀)
			return 4;
	}
}

//사용자가 키를 입력했을 때 선택된 메뉴가 표시되도록 하는 함수
void menuSelect(int cnt) {
	int i = 0;				//for 반복문을 사용하기 위한 int형 변수 i 선언 후 0으로 초기화

	for (i = 0; i < 4; i++) {						//for 반복문과 gotoxy 함수를 통해 4개의 메뉴에 있는 화살표 표시(▶)를 지운다.(printf() 함수로 덮어쓰기)
		gotoxy((WIDTH / 2) - 10, (i * 3) + 12);
		printf("  ");
	}

	gotoxy((WIDTH / 2) - 10, (cnt * 3) + 12);			//gotoxy 함수를 통해 사용자가 선택한 메뉴의 왼쪽의 위치로 이동하여 화살표(▶) 출력
	printf("▶");
}