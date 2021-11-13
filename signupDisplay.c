#define _CRT_SECURE_NO_WARNINGS		//전처리기(#) 프로그램 실행에 사용되는 매크로와 헤더파일 선언
#include <stdio.h>					//표준입출력 함수 헤더파일
#include <string.h>					//표준 문자열 함수 헤더파일

#include "main.h"					//main.h 사용자 헤더파일 포함
#include "console.h"				//console.h 사용자 헤더파일 포함
#include "drawing.h"				//drawing.h 사용자 헤더파일 포함
#include "text.h"					//text.h 사용자 헤더파일 포함

//DB에 회원 정보를 저장하는 함수
void signupDisplay() {
	char id[255] = { 0 };		//사용자가 입력한 id를 저장할 char형 배열 id를 크기 255로 선언하여 0으로 초기화
	char pw[255] = { 0 };		//사용자가 입력한 pw를 저장할 char형 배열 pw를 크기 255로 선언하여 0으로 초기화
	char pw2[255] = { 0 };		//사용자가 입력한 pw 확인을 저장할 char형 배열 pw2를 크기 255로 선언하여 0으로 초기화

	while (1) {			//무한 반복
		system("cls");			//system함수로 화면 초기화

		consoleShow();		//사용자 지정 함수 consoleShow 함수로 콘솔을 지정된 크기로 엶
		drawingBorder();	//사용자 지정 함수로 테두리 출력
		drawingTitle();		//사용자 지정 함수로 프로그램 제목 출력

		gotoxy((WIDTH / 2) - 30, (HEIGHT / 2) - 8);		//gotoxy 함수로 출력할 화면 설명을 출력할 위치로 이동하고 printf 함수로 출력
		printf("각 항목을 입력하고 ENTER 키 입력 시 다음 항목으로 이동합니다.");

		drawingTextBox(16, "아이디 : ");			//아이디를 입력할 텍스트박스 출력
		drawingTextBox(21, "비밀번호 : ");		//비밀번호를 입력할 텍스트박스 출력
		drawingTextBox(26, "비밀번호 확인 : ");	//비밀번호 확인을 입력할 텍스트박스 출력

		gotoxy((WIDTH / 2) - 11, 16);			//사용자 함수 gotoxy 함수로 아이디를 입력받을 위치로 이동
		if (get_id(id) == -1)			//사용자 함수 get_id를 통해 아이디를 입력받고 반환값이 -1(ESC 키 입력)이면 로그인 화면 종료(메인 화면으로 이동)
			return;

		gotoxy((WIDTH / 2) - 11, 21);			//사용자 함수 gotoxy 함수로 비밀번호를 입력받을 위치로 이동
		if (get_pw(pw) == -1)			//사용자 함수 get_pw를 통해 비밀번호를 입력받고 반환값이 -1(ESC 키 입력)이면 로그인 화면 종료(메인 화면으로 이동)
			return;

		gotoxy((WIDTH / 2) - 11, 26);			//사용자 함수 gotoxy 함수로 비밀번호 확인을 입력받을 위치로 이동
		if (get_pw(pw2) == -1)		//사용자 함수 get_pw를 통해 비밀번호 확인을 입력받고 반환값이 -1(ESC 키 입력)이면 로그인 화면 종료(메인 화면으로 이동)
			return;

		sprintf(query, "select * from member where member_id='%s'", id);		//sprintf 함수를 통해 query에 쿼리문을 저장

		mysql_query(connection, query);		//mysql_query 함수를 통해 connection(연결 정보)에 쿼리문 실행(select문을 통해 입력한 id와 중복되는 회원이 있는지 확인)

		result = mysql_store_result(connection);			//result에 mysql_store_result함수를 사용하여 connection(연결정보)의 실행 결과를 저장
		
		if (strcmp(id, "") != 0 && strcmp(pw, "") != "" &&  mysql_num_rows(result) == 0 && strcmp(pw, pw2) == 0) {		//DB에 중복되는 아이디가 없고(미완성) pw와 pw 확인이 같을경우
			//[ DB에 저장 ]
			sprintf(query, "insert into member (`member_id`, `member_pw`) VALUES ('%s', '%s')", id, pw);		//sprintf 함수를 통해 query에 쿼리문을 저장

			mysql_query(connection, query);		//mysql_query 함수를 통해 connection(연결 정보)에 쿼리문 실행(select문을 통해 입력한 id와 중복되는 회원이 있는지 확인)

			result = mysql_store_result(connection);			//result에 mysql_store_result함수를 사용하여 connection(연결정보)의 실행 결과를 저장

			mysql_free_result(result);							//mysql_free_result 함수를 사용하여 메모리에 result의 내용 제거(해제)

			gotoxy((WIDTH / 2) - 36, 31);	//회원가입 완료 메시지를 출력할 위치로 이동 후 printf 함수로 회원 가입 완료 메시지 출력
			printf("회원 가입이 완료되었습니다. 아무 키나 누르면 로그인 화면으로 돌아갑니다.");
			_getch();					//아무키 입력 받음
			break;						//반복문 종료
		}
		else {							//DB에 중복되는 아이디가 있거나(미완성) pw와 pw 확인이 다를 경우
			gotoxy((WIDTH / 2) - 52, 31);	//회원가입 실패 메시지를 출력할 위치로 이동 후 printf 함수로 회원 실패 완료 메시지 출력
			printf("아이디 혹은 비밀번호가 잘못 되었습니다. 아이디는 중복되지 않고, 비밀번호와 비밀번호 확인이 같아야 합니다.");

			while (1) {						//메시지가 출력되었을 때 while 반복문을 통해 다음 행동을 처리
				if (_getch() == VK_ESCAPE)		//메시지가 출력되었을 때 ESC를 입력했으면 나가기(메인화면으로 이동)
					return;
				else
					break;						//그 외의 키를 입력했을 때 오류 메시지 출력 후 처음부터 시작
			}
		}
	}
}