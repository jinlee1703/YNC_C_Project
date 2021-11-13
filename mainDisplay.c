#define _CRT_SECURE_NO_WARNINGS			//전처리기(#) 프로그램 실행에 사용되는 매크로와 헤더파일 선언
#include <stdio.h>						//표준입출력 함수 헤더파일
#include <conio.h>

//사용자 지정 헤더파일
#include "main.h"
#include "console.h"
#include "drawing.h"
#include "text.h"

//메인 화면(매크로 상수 WIDTH와 HEIGHT를 받아옴으로써 모든 화면 크기를 통일)을 출력하는 함수
int mainDisplay() {
	int cnt = 0;						//메뉴 선택값을 저장할 int형 변수 cnt 선언 후 0으로 초기화(프로그램을 실행시켰을 때 기본으로 [로그인]이 선택되도록 함)

	system("cls");						//system 함수를 통해 화면 초기화(claer)

	consoleShow();					//사용자 지정 함수 consoleShow 함수로 콘솔을 지정된 크기로 엶
	drawingBorder();				//사용자 지정 함수로 테두리 출력
	drawingTitle();					//사용자 지정 함수로 프로그램 제목 출력
	drawingNameTag();				//사용자 지정 함수로 프로그램 작성자의 학번, 이름 출력
	drawingExplanation();			//사용자 지정 함수로 키 설명 출력

	gotoxy((WIDTH / 2) - 4, (HEIGHT / 2) - 4);	//gotoxy 함수로 출력할 [로그인] 메뉴를 출력할 위치로 이동하고 printf 함수로 출력
	printf("로 그 인");

	gotoxy((WIDTH / 2) - 4, (HEIGHT / 2));		//gotoxy 함수로 출력할 [회원가입] 메뉴를 출력할 위치로 이동하고 printf 함수로 이동
	printf("회원가입");

	gotoxy((WIDTH / 2) - 8, (HEIGHT / 2) - 4);	//gotoxy 함수로 [로그인] 메뉴의 왼쪽에 '▶(화살표)' 메뉴를 출력함(기본 선택 메뉴는 [로그인] 메뉴)
	printf("▶");

	while (1) {		//무한 반복문(키보드를 통해 메뉴를 선택)
		int key = 0;		//사용자가 입력한 키 값을 저장하기 위한 int형 변수 key를 선언 후 0으로 초기화

		key = _getch();		//_getch() 함수를 통해 변수 key에 사용자가 키를 입력했을 때 키를 저장

		if (key == 72) {							//key 값이 72일 경우(방향키 Up키)
			gotoxy((WIDTH / 2) - 8, (HEIGHT / 2));			//gotoxy를 통해 특정 좌표([회원가입] 메뉴 위치)로 커서를 이동하고 화살표를 지움
			printf("  ");

			gotoxy((WIDTH / 2) - 8, (HEIGHT / 2) - 4);		//gotoxy를 통해 특정 좌표([로그인] 메뉴 위치)로 커서를 이동하고 printf 함수로 화살표 출력
			printf("▶");

			cnt = 0;								//변수 cnt에 메뉴 선택값(0번째) 저장
		}
		else if (key == 80) {						//key 값이 80일 경우(방향키 Down키)
			gotoxy((WIDTH / 2) - 8, (HEIGHT / 2) - 4);		//gotoxy를 통해 특정 좌표([로그인] 메뉴 위치)로 커서를 이동하고 화살표를 지움
			printf("  ");

			gotoxy((WIDTH / 2) - 8, (HEIGHT / 2));			//gotoxy를 통해 특정 좌표([회원가입] 메뉴 위치)로 커서를 이동하고 printf 함수로 화살표 출력
			printf("▶");

			cnt = 1;								//변수 cnt에 메뉴 선택값(1번째) 저장
		}
		else if (key == 13) {						//key 값이 13일 경우(Enter 키)
			return cnt;									//선택한 메뉴 값을 반환
		}
		else if (key == 27) {					//key 값이 27일 경우(Esc 키)
			mysql_close(connection);
			exit(0);									//exit 함수를 통해 프로그램 종료
		}
	}
}