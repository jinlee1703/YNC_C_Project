#define _CRT_SECURE_NO_WARNINGS		//전처리기(#) 프로그램 실행에 사용되는 매크로와 헤더파일 선언
#include <stdio.h>					//표준입출력 함수 헤더파일
#include <conio.h>					//콘솔입출력 함수 헤더파일
#include <string.h>					//표준 문자열 함수 헤더파일
#include <windows.h>
#include <stdlib.h>					
#include <time.h>
#include <math.h>

#include "main.h"					//main.h 사용자 헤더파일 포함
#include "console.h"				//console.h 사용자 헤더파일 포함
#include "drawing.h"				//drawing.h 사용자 헤더파일 포함
#include "text.h"					//text.h 사용자 헤더파일 포함

//짧은 글 연습 화면을 출력하는 함수
void shortTestDisplay() {
	/*char texts[][];*/
	char text[WIDTH - 10];		//DB에 저장되어 있는 문장(사용자가 입력할 문장)을 출력할 char형 배열 text
	char user[WIDTH - 10];		//사용자가 입력한 문장을 저장할 char형 배열 user
	FILE *fp;					//짧은 글이 저장되어 있는 파일을 불러오기 위한 구조체 파일 포인터 정의
	char filepath[255] = { 0 };
	TA data;

	system("cls");					//system함수로 화면 초기화

	consoleShow();				//사용자 지정 함수 consoleShow 함수로 콘솔을 지정된 크기로 엶
	drawingBorder();			//사용자 지정 함수로 테두리 출력
	drawingIdtag();	//로그인 한 ID 출력(미완성)

	drawingTestTextbox(12);			//문장 박스 출력
	drawingTestTextbox(15);			//입력 박스 출력

	gotoxy(6, 10);				//타수 출력을 위한 좌표 변경
	printf("타수 : %4d 타", 0);		//타수 출력

	gotoxy(40, 10);				//정확도 출력을 위한 좌표 변경
	printf("정확도 : %3d %%", 0);	//정확도 출력

	sprintf(query, "select * from file where events_id = '1' and language = 'eng'");		//sprintf 함수를 통해 query에 쿼리문을 저장

	mysql_query(connection, query);		//mysql_query 함수를 통해 connection(연결 정보)에 쿼리문 실행(select문을 통해 한글 짧은글 파일의 이름을 조회)

	result = mysql_store_result(connection);			//result에 mysql_store_result함수를 사용하여 connection(연결정보)의 실행 결과를 저장

	row = mysql_fetch_row(result);						//한 행 씩 실행결과를 읽어옴

	sprintf(filepath, "짧은 글\\%s", row[3]);			//배열에 DB에 저장되어 있는 파일명과 파일 경로 저장

	if ((fp = fopen(filepath, "r")) == NULL) {
		fprintf(stderr, "파일 열기 실패!\n");
		return;
	}

	while (1) {				//무한 반복(Esc키를 누르기 전까지)
		if (!feof(fp)) {											//다음 줄이 있을 경우 문장을 읽어온다
			fgets(text, WIDTH - 10, fp);							//(배열 text에 저장)
		} 
		else {
			//메인으로 돌아가기
			break;
		}
		
		gotoxy(6, 12);												//문장 출력을 위한 좌표 변경
		printf("%s", text);											//문장 출력//문장을 text에 저장(추후 DB의 문장을 읽어오는 부분으로 변경할 예정)

		gotoxy(6, 15);
		if (get_Typing(text, user, &data, 1) == -1)									//문자를 입력 받고 반환값이 -1인 경우(Esc입력)
			break;													//반복문 종료(메뉴 화면으로 돌아감)

		sprintf(query, "insert into typing VALUES ('%s', 1, %d, %d, curdate())", login_id, data.speed, data.percent);		//sprintf 함수를 통해 query에 쿼리문을 저장

		mysql_query(connection, query);		//mysql_query 함수를 통해 connection(연결 정보)에 쿼리문 실행(insert문으로 타이핑 정보 저장)

		testTextboxClear(12);		//입력할 문장이 있는 텍스트박스 초기화
		testTextboxClear(15);		//입력한 문장이 있는 텍스트박스 초기화
	}
	fclose(fp);
}