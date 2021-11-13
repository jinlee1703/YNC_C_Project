#define _CRT_SECURE_NO_WARNINGS		//전처리기(#) 프로그램 실행에 사용되는 매크로와 헤더파일 선언
#include <stdio.h>					//표준입출력 함수 헤더파일
#include <conio.h>					//콘솔 입출력 헤더파일
#include <string.h>					//표준 문자열 함수 헤더파일
#include <stdlib.h>					//표준 라이브러리 헤더파일
#include <Windows.h>				//윈도우 응용 프로그램을 위한 헤더파일

#include "console.h"		//console.h 사용자 헤더파일 포함
#include "drawing.h"		//drawing.h 사용자 헤더파일 포함
#include "text.h"			//text.h 사용자 헤더파일 포함

//사용자 함수 선언
int mainDisplay();				//[메인 화면]
void signupDisplay();			//[회원가입 화면]
int menuDisplay();				//[메뉴 선택 화면]
void menuSelect();				//메뉴 선택 함수

int loginDisplay();				//[로그인] 화면
void shortTestDisplay();		//[짧은 글 연습] 메뉴
void longTestDisplay();			//[긴 글 연습] 메뉴
void acidrainGame();			//[산성비 게임] 메뉴
void viewRanking();				//[랭킹 보기] 메뉴

//메인 함수
int main(void) {
	int main_select = 0;		//mainDisplay에서 무엇을 선택하였는지(로그인or 회원가입) 저장하는 변수 선언
	
	mysql_init(&conn);				//mysql_init 함수를 통해 MYSQL 구조체 변수 conn(주소)를 인자로 받아 초기화

	//mysq_real_connect 함수 형식 : mysql_real_connect(MYSQL 구조체, DB주소, DB ID, DB PASSWORD, DB 이름, 포트번호, 소켓, 보안(flag))
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);	//mysql_real_connect 함수를 통해 MYSQL에 연결을 시도하여 결과의 주소를 connection에 저장

	if (connection == NULL) {					//connection이 NULL일 경우(연결 실패, 해당하는 연결정보가 없음)
		fprintf(stderr, "error : %s", mysql_error(&conn));		//fprintf 함수를 통해 버퍼없이(stderr) mysql_error(&conn의 에러 메시지 문자열 리턴)로 반환된 에러 메시지(원인) 출력
		return 1;												//main 함수 종료
	}

	while (1) {
		main_select = mainDisplay();			//[메인 화면]에서 [로그인,회원가입] 선택 여부 저장
		
		if (main_select == 0) {								//[메인 화면]에서 [로그인] 선택 시
			if (loginDisplay() == 0) {						//로그인 화면이 0을 반환했을 때(로그인 성공, DB에서 회원정보를 조회해서 로그인)
menu:			switch (menuDisplay()) {						//메뉴 화면 (어떤 메뉴든지 esc를 누를 경우 메뉴 선택화면으로 돌아감)
				case 0:											//[메뉴 선택화면]에서 [짧은글 연습] 선택 시
					shortTestDisplay();							//[짧은 글 연습 화면]을 불러오고, 종료되면(ESC키를 입력하면) 다시 [메뉴 선택] 화면으로 이동
					goto menu;
				case 1:											//[메뉴 선택화면]에서 [긴 글 연습] 선택 시
					longTestDisplay();					//[긴 글 연습 화면]을 불러오고, 종료되면(ESC키를 입력하면) 다시 [메뉴 선택] 화면으로 이동
					goto menu;
				case 2:											//[메뉴 선택화면]에서 [산성비 게임] 선택 시
					acidrainGame();								//[산성비 게임 화면]을 불러오고, 종료되면 다시 [메뉴 선택] 화면으로 이동
					goto menu;
				case 3:											//[메뉴 선택화면]에서 [랭킹 보기] 선택 시
					viewRanking();								//[랭킹 보기 화면]을 불러오고, 종료되면(ESC키를 입력하면) 다시 [메뉴 선택] 화면으로 이동
					goto menu;
				case 4:											//[메뉴 선택화면]에서 ESC키 입력 시 메인 화면으로 이동
					continue;
				}
			}
			else {												//그 외 메인 화면으로 이동 : ex) [메뉴 선택화면]에서 ESC 키 입력 시
				continue;
			}
		}
		else if (main_select == 1) {						//메인 화면에서 [회원가입] 선택 시
			signupDisplay();					//[회원가입 화면] 불러옴
			continue;											//회원가입 종료(성공 or 실패) 시 다시 메인 화면으로 이동
		}
	}

	return 0;
}