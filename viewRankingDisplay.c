#define _CRT_SECURE_NO_WARNINGS		//전처리기(#) 프로그램 실행에 사용되는 매크로와 헤더파일 선언
#include <stdio.h>					//표준입출력 함수 헤더파일
#include <conio.h>					//콘솔 입출력 헤더파일
#include <string.h>					//표준 문자열 함수 헤더파일
#include <stdlib.h>					//표준 라이브러리 헤더파일
#include <windows.h>				//윈도우 응용 프로그램을 위한 헤더파일

#include "console.h"		//console.h 사용자 헤더파일 포함
#include "drawing.h"		//drawing.h 사용자 헤더파일 포함
#include "text.h"			//text.h 사용자 헤더파일 포함

void viewChart(int cnt);		//메뉴 선택시 차트가 출력되도록 하는 사용자 지정 함수(미구현)
void viewSelect(int cnt);		//키 입력 시 메뉴를 선택하도록 하는 함수

//[랭킹 보기] 메뉴 선택 시 화면이 나타나도록 하는 함수
void viewRanking() {
	int cnt = 0, key = 0;			//몇 번째 카테고리(랭킹 분류)를 선택했는지를 저장할 int형 변수 cnt와 사용자가 입력한 키 값을 저장할 변수 key 선언 후 0으로 초기화

	system("cls");					//system함수로 화면 초기화

	consoleShow();				//사용자 지정 함수 consoleShow 함수로 콘솔을 지정된 크기로 엶
	drawingBorder();			//사용자 지정 함수로 테두리 출력
	drawingIdtag();	//로그인 한 ID 출력(미완성)

	gotoxy(20, 5);					//gotoxy 함수로 출력할 [짧은 글 점수] 카테고리를 출력할 위치로 이동하고 printf 함수로 출력
	printf("짧은 글 점수");

	gotoxy(55, 5);					//gotoxy 함수로 출력할 [긴 글 점수] 카테고리를 출력할 위치로 이동하고 printf 함수로 출력
	printf("긴 글 점수");

	gotoxy(90, 5);					//gotoxy 함수로 출력할 [산성비 게임] 카테고리를 출력할 위치로 이동하고 printf 함수로 출력
	printf("산성비 게임 점수");

	gotoxy(16, 5);					//gotoxy 함수를 통해 사용자가 선택한 메뉴의 왼쪽의 위치로 이동하여 화살표(▶) 출력
	printf("▶");
	viewChart(cnt);			//선택한 카테고리에 해당하는 차트 출력

	//sprintf 함수를 통해 query에 쿼리문을 저장
	sprintf(query, "select member_id, events_id, format(avg(typing_speed),0), format(avg(typing_percent),0), date_format(typing_date, '%%m-%%d') from typing where member_id = '%s' and events_id != '3'", login_id);

	mysql_query(connection, query);		//mysql_query 함수를 통해 connection(연결 정보)에 쿼리문 실행(DB에 저장되어 있는 있는 전체 타이핑 데이터의 평균을 조회)

	result = mysql_store_result(connection);			//result에 mysql_store_result함수를 사용하여 connection(연결정보)의 실행 결과를 저장

	row = mysql_fetch_row(result);

	gotoxy(6, 2);
	printf("평균 타수 : %s타 \t 평균 정확도 : %s%%", row[2], row[3]);

	while (1) {						//무한 반복문(esc 키를 입력하면 메뉴 선택 화면으로 돌아감)
		key = _getch();					//변수 key에 사용자가 입력한 key 값을 저장
		if (key == 72) {				//key 값이 72일 경우(방향키 Up키)
			if (cnt > 0) {					//cnt가 0 보다 클 경우(맨 위의 메뉴가 아닌 메뉴 선택)
				cnt--;						//cnt의 값을 1빼고
				viewSelect(cnt);		//선택된 카테고리를 표시하도록 함수 호출
				viewChart(cnt);		//선택된 카테고리에 해당하는 차트를 출력하도록 함수 호출
			}
		}
		else if (key == 80) {			//key 값이 80일 경우(방향키 Down키)
			if (cnt < 2) {					//cnt가 2 보다 작을 경우(맨 아래의 메뉴가 아닌 메뉴 선택)
				cnt++;						//cnt의 값을 더하고
				viewSelect(cnt);		//선택된 카테고리를 표시하도록 함수 호출
				viewChart(cnt);		//선택된 카테고리에 해당하는 차트를 출력하도록 함수 호출
			}
		}
		else if (key == 27) {			//Esc key 입력 시 4 반환 (메인 화면으로 회귀)
			break;
		}
	}
}

//키 입력 시 메뉴를 선택하도록 하는 함수
void viewSelect(int cnt) {
	int i = 0;							//for 반복문을 사용하기 위한 int형 변수 i 선언 후 0으로 초기화

	for (i = 0; i < 4; i++) {			//for 반복문과 gotoxy 함수를 통해 4개의 메뉴에 있는 화살표 표시(▶)를 지운다.(printf() 함수로 덮어쓰기)
		gotoxy(16 + (i * 35), 5);
		printf("  ");
	}

	gotoxy(16 + (cnt * 35), 5);			//gotoxy 함수를 통해 사용자가 선택한 메뉴의 왼쪽의 위치로 이동하여 화살표(▶) 출력
	printf("▶");
}

void viewChart(int cnt) {
	int i = 0, j = 0;							//for 반복문에 사용되기 위한 int 형 변수 i와 j 선언 후 0으로 초기화
	int grp = 0, total_speed = 0, total_percent = 0;
	unsigned long dw;
	COORD spot = { 7, 8 };
	int r = 0;

	//테두리 그리기
	for (i = 7; i < HEIGHT - 2; i++) {				
		for (j = 6; j < WIDTH - 6; j++) {
			gotoxy(j, i);
			if (i == 7 || i == HEIGHT - 3) {
				if (j == 6 || j == WIDTH - 7)
					printf("+");
				else
					printf("-");				//가로줄
			}
			else if (j == 6 || j == WIDTH - 7)
				printf("|");					//세로줄
		}
	}

	//차트 영역 초기화
	for (i = 8; i < HEIGHT - 3; i++) {
		spot.Y = i;
		FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', WIDTH - 14, spot, &dw);
	}

	//[차트 표현]
	sprintf(query, "(select member_id, events_id, format(avg(typing_speed),0), format(avg(typing_percent),0), date_format(typing_date, '%%m-%%d') from typing where member_id = '%s' and events_id = '%d' group by typing_date order by 5 desc limit 10) order by 5", login_id, cnt + 1);		//sprintf 함수를 통해 query에 쿼리문을 저장

	mysql_query(connection, query);		//mysql_query 함수를 통해 connection(연결 정보)에 쿼리문 실행(DB에 저장되어 있는 선택한 모드에 해당하는 타이핑 데이터를 날짜별로 그룹화하여 조회)
										//먼 날짜 순으로 데이터가 있는 최신 10개(일)의 데이터만 출력

	result = mysql_store_result(connection);			//result에 mysql_store_result함수를 사용하여 connection(연결정보)의 실행 결과를 저장

	i = 0;

	srand((unsigned int)time(NULL));

	while (((row = mysql_fetch_row(result)) != NULL) && i != 10) {			
		gotoxy(12 + (i * 10), HEIGHT - 4);
		printf("%s", row[4]);			//printf 함수를 사용하여 날짜 출력(
		
		grp = atoi(row[2]) / 50;			//50타(점) 당 칸씩 기록

		if (grp > 20)								//최대 1000타 까지 표현 가능(1000타 보다 높을 경우 1000타와 동일)
			grp = 20;

		r = rand() % 6 + 9;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), r);
		for (j = 0; j < grp; j++) {					//막대 차트 출력
			gotoxy(13 + (i * 10), HEIGHT - 6 - j);
			printf("■");
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

		if (cnt != 2) {		//짧은글, 긴글 연습
			gotoxy(11 + (i * 10), HEIGHT - 27);			//차트 레이블 출력
			printf("%s타", row[2]);						//(타수)
			gotoxy(11 + (i * 10), HEIGHT - 26);			//(정확도)
			printf(" %s%%", row[3]);
		}
		else {				//산성비 게임
			gotoxy(11 + (i * 10), HEIGHT - 26);			//차트 레이블 출력
			printf("%s점", row[2]);	
		}
		
		i++;
	}
}