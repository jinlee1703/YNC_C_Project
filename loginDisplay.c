#define _CRT_SECURE_NO_WARNINGS		//전처리기(#) 프로그램 실행에 사용되는 매크로와 헤더파일 선언
#include <stdio.h>					//표준입출력 함수 헤더파일
#include <conio.h>					//콘솔입출력 함수 헤더파일
#include <string.h>					//표준 문자열 함수 헤더파일
#include <Windows.h>				//윈도우 응용 프로그램을 위한 헤더파일

#include "main.h"			//main.h 사용자 헤더파일 포함
#include "console.h"		//console.h 사용자 헤더파일 포함
#include "drawing.h"		//drawing.h 사용자 헤더파일 포함
#include "text.h"			//text.h 사용자 헤더파일 포함


//로그인 화면을 출력하고 DB에 저장되어있는 회원정보를 통해 로그인 성공 여부를 반환하는 사용자 함수
int loginDisplay() {
	char id[255] = { 0 };		//입력한 id를 저장할 char형 배열 id를 크기 255로 선언하여 0으로 초기화
	char pw[255] = { 0 };		//입력한 id를 저장할 char형 배열 id를 크기 255로 선언하여 0으로 초기화

	system("cls");				//system함수로 화면 초기화

	consoleShow();			//사용자 지정 함수 consoleShow 함수로 콘솔을 지정된 크기로 엶
	drawingBorder();		//사용자 지정 함수로 테두리 출력
	drawingTitle();			//사용자 지정 함수로 프로그램 제목 출력
	drawingNameTag();			//사용자 지정 함수로 프로그램 작성자의 학번, 이름 출력

	gotoxy((WIDTH / 2) - 30, (HEIGHT / 2) - 8);											//gotoxy 함수로 출력할 화면 설명을 출력할 위치로 이동하고 printf 함수로 출력
	printf("각 항목을 입력하고 ENTER 키 입력 시 다음 항목으로 이동합니다.");

	drawingTextBox(16, "아이디 : ");		//아이디를 입력할 텍스트박스 출력
	drawingTextBox(21, "비밀번호 : ");	//비밀번호를 입력할 텍스트박스 출력

	gotoxy((WIDTH / 2) - 11, 16);			//사용자 함수 gotoxy 함수로 아이디를 입력받을 위치로 이동
	if (get_id(id) == -1)			//사용자 함수 get_id를 통해 아이디를 입력받고 반환값이 -1(ESC 키 입력)이면 로그인 화면 종료(메인 화면으로 이동)
		return 1;

	gotoxy((WIDTH / 2) - 11, 21);			//사용자 함수 gotoxy 함수로 비밀번호를 입력받을 위치로 이동
	if (get_pw(pw) == -1)			//사용자 함수 get_pw를 통해 비밀번호를 입력받고 반환값이 -1(ESC 키 입력)이면 로그인 화면 종료(메인 화면으로 이동)
		return 1;

	gotoxy((WIDTH / 2) - 36, 31);			//gotoxy를 통해 로그인 성공 여부를 출력할 위치로 이동

	sprintf(query, "select * from member where member_id='%s' and member_pw='%s'", id, pw);		//sprintf 함수를 통해 query에 쿼리문을 저장

	mysql_query(connection, query);		//mysql_query 함수를 통해 connection(연결 정보)에 쿼리문 실행(select문을 통해 입력한 id와 pw가 일치하는 회원이 있는지 확인)

	result = mysql_store_result(connection);			//result에 mysql_store_result함수를 사용하여 connection(연결정보)의 실행 결과를 저장

	if (mysql_num_rows(result) == 1) {			//strcmp 함수를 통해 id와 pw값이 존재하는지 비교
		sprintf(login_id, id);
		printf("로그인 성공! 아무 키나 누르면 메뉴 화면으로 이동합니다.");		//로그인 성공 메시지 출력
		_getch();																//아무 키나 입력 받음
		mysql_free_result(result);							//mysql_free_result 함수를 사용하여 메모리에 result의 내용 제거(해제)
		return 0;																//0(성공) 반환
	}
	else {
		printf("로그인 실패! 아무 키나 누르면 메인 화면으로 돌아갑니다.");		//로그인 성공 메시지 출력
		_getch();																//아무 키나 입력 받음
		mysql_free_result(result);							//mysql_free_result 함수를 사용하여 메모리에 result의 내용 제거(해제)
		return 1;																//0(성공) 반환
	}
}