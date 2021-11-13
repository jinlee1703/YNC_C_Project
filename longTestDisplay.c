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

void shortTextbox(int col);			//gotoxy와 printf 함수와 for문을 사용하여 텍스트박스를 출력하는 사용자 함수
int longTestSelectDisplay();		//어떤 긴 글을 타이핑 할건지 선택하는 화면이 출력되는 함수
void longTestSelect(int cnt);		//키보드를 입력할 때마다 해당하는 긴 글 옆에 ▶ 표시가 출력되는 함수

#define BACKSPACE 8							//Backspace 키 값을 매크로 상수로 선언
#define ENTER 13							//ENTER 키 값을 매크로 상수로 선언

int max;			//긴글 선택 가능 개수
char title[45];		//짧은글 코드 저장하기

void longTestDisplay() {
	char text[5][WIDTH - 10] = { 0 };		//DB에 저장되어 있는 문장(사용자가 입력할 문장)을 출력할 2차원 char형 배열 text
	char user[5][WIDTH - 10] = { 0 };			//사용자가 입력한 문장을 저장할 char형 배열 user
	int i = 0, j = 0;						//for 반복문에 사용될 int형 변수 i, j 선언 후 0으로 초기화
	int cnt = 0;					//사용자가 입력하고 있는 줄이 몇번째 줄인지 저장하기 위한 int형 변수 cnt 선언 후 0으로 초기화
	FILE *fp;					//짧은 글이 저장되어 있는 파일을 불러오기 위한 구조체 파일 포인터 정의
	char filepath[255] = { 0 };
	TA data;
	int key = 0;				//계속 할 것인지 여부를 확인하기 위해 key 값을 입력받기 위한 int형 변수 key 선언 후 0으로 초기화

	if (longTestSelectDisplay() == -1)
		return;

	/*[파일 불러오기]*/
	sprintf(filepath, "긴 글\\%s", title);			//배열에 DB에 저장되어 있는 파일명과 파일 경로 저장

	if ((fp = fopen(filepath, "r")) == NULL) {
		fprintf(stderr, "파일 열기 실패!\n");
		return;
	}

nextPage:
	system("cls");					//system함수로 화면 초기화

	consoleShow();				//사용자 지정 함수 consoleShow 함수로 콘솔을 지정된 크기로 엶
	drawingBorder();			//사용자 지정 함수로 테두리 출력
	drawingIdtag();				//로그인 한 ID 출력

	gotoxy(6, 4);					//타수 출력을 위한 좌표 변경
	printf("타수 : %4d 타", 0);			//타수 출력

	gotoxy(40, 4);					//정확도 출력을 위한 좌표 변경
	printf("정확도 : %3d %%", 0);		//정확도 출력

	for (i = 0; i < 10; i++) {		//for 반복문을 사용하여 10개의 문장 박스 출력(5개 : 입력할 문장, 5개 : 입력될 위치)
		drawingTestTextbox(6 + (i * 3));			//문장 박스 출력
	}

	for (i = 0; i < 5; i++) {					//for 반복문을 사용하여 문장 출력(5개)
		if (!feof(fp)) {											//다음 줄이 있을 경우 문장을 읽어온다
			fgets(text[i], WIDTH - 10, fp);								//(배열 text에 저장)
			gotoxy(6, 6 + (i * 3 * 2));									//문장 출력을 위한 좌표 변경
			printf("%s", text[i]);										//문장 출력
			testTextboxClear(9 + (i * 3 * 2));							//입력할 위치 초기화
			sprintf(user[i], "");;										//입력할 문장(빼열) 초기화
		}
		else {
			sprintf(text[i], "");
		}
	}

	while (1) {					//무한 반복(Esc키를 누르기 전까지)
		for (i = 0; i < 5; i++) {
			gotoxy(6, 9 + (i * 3 * 2));						//입력할 위치로 이동
			if (strcmp(text[i], "") != 0) {							//문장이 존재할 경우에 타이핑이 가능함
				if (get_Typing(text[i], user[i], &data, 2) == -1)			//문자를 입력 받고 반환값이 -1인 경우(Esc입력)
					goto end;											//반복문 종료(메뉴 화면으로 돌아감)
			}
		}

		system("cls");				//system함수로 화면 초기화
		consoleShow();				//사용자 지정 함수 consoleShow 함수로 콘솔을 지정된 크기로 엶
		drawingBorder();			//사용자 지정 함수로 테두리 출력
		drawingIdtag();				//로그인 한 ID 출력

		if (feof(fp)) {											//다음 줄이 없을 경우 긴글 연습 종료 문구 출력
			gotoxy((WIDTH / 2) - 29, 15);
			printf("+--------------------------------------------------------+");
			gotoxy((WIDTH / 2) - 29, 16);
			printf("|                                                        |");
			gotoxy((WIDTH / 2) - 29, 17);
			printf("|       아무 키나 누르시면 메뉴화면으로 돌아갑니다       |");
			gotoxy((WIDTH / 2) - 29, 18);
			printf("|                                                        |");
			gotoxy((WIDTH / 2) - 29, 19);
			printf("+--------------------------------------------------------+");

			_getch();		//아무 키나 입력할 경우 반복문종료(메인 화면으로 이동)
			break;
		}

		/*[다음 페이지로 넘어갈 것인지 메시지 출력]*/
		gotoxy((WIDTH / 2) - 21, 13);
		printf("+----------------------------------------+");
		gotoxy((WIDTH / 2) - 21, 14);
		printf("|                                        |");
		gotoxy((WIDTH / 2) - 21, 15);
		printf("|           계속 하시겠습니까?           |");
		gotoxy((WIDTH / 2) - 21, 16);
		printf("|                                        |");
		gotoxy((WIDTH / 2) - 21, 17);
		printf("|                                        |");
		gotoxy((WIDTH / 2) - 21, 18);
		printf("|          계속하기 : Enter key          |");
		gotoxy((WIDTH / 2) - 21, 19);
		printf("|                                        |");
		gotoxy((WIDTH / 2) - 21, 20);
		printf("|        메뉴로 돌아가기 : Esc key       |");
		gotoxy((WIDTH / 2) - 21, 21);
		printf("|                                        |");
		gotoxy((WIDTH / 2) - 21, 22);
		printf("+----------------------------------------+");

request:key = _getch();

		if (key == ENTER_KEY) {
			/*[DB에 타이핑 정보 저장]*/
			sprintf(query, "insert into typing VALUES ('%s', 2, %d, %d, curdate())", login_id, data.speed, data.percent);		//sprintf 함수를 통해 query에 쿼리문을 저장
			mysql_query(connection, query);						//mysql_query 함수를 통해 connection(연결 정보)에 쿼리문 실행(insert문으로 타이핑 정보 저장)

			goto nextPage;	//파일 다음 페이지 출력
		}
		else if (key == ESC_KEY) {
			break;
		}
		else {
			goto request;
		}
	}
end:
	fclose(fp);
}

int longTestSelectDisplay() {
	int i = 0, j = 0, key = 0, cnt =0;			//for반복문을 사용하기 위한 int형 변수 i와 j, 사용자가 입력한 키값을 저장할 key, 긴 글 선택을 위한 cnt를 선언 후 0으로 초기화
	char arr[10][45] = { 0 };

	system("cls");				//system함수로 화면 초기화

	consoleShow();				//사용자 지정 함수 consoleShow 함수로 콘솔을 지정된 크기로 엶
	drawingBorder();			//사용자 지정 함수로 테두리 출력

	gotoxy((WIDTH / 2) - 6, 4);		//제목 출력
	printf("긴 글 선 택");

	for (i = 7; i < HEIGHT - 3; i++) {				//테두리 그리기
		for (j = 20; j < WIDTH - 20; j += 2) {
			gotoxy(j, i);
			if (i == 7 || i == HEIGHT - 4)			//가로줄
				printf("■");
			else if (j == 20 || j == WIDTH - 22)		//세로줄
				printf("■");
		}
	}

	//[긴 글 리스트 출력]
	sprintf(query, "select substring(file_name, 1, char_length(file_name) - 4) from file where events_id='2' and language='eng' order by file_id");		//sprintf 함수를 통해 query에 쿼리문을 저장

	mysql_query(connection, query);		//mysql_query 함수를 통해 connection(연결 정보)에 쿼리문 실행(DB에 저장되어 있는 긴글연습 파일 조회)

	result = mysql_store_result(connection);			//result에 mysql_store_result함수를 사용하여 connection(연결정보)의 실행 결과를 저장

	i = 0;

	//while 반복문 : row에 mysql_fetch_row 함수를 사용하여 result(주소)를 한 행(줄)씩 읽어와 저장하고 줄이 비어있을 때(마지막)까지 또는 10행까지만 반복
	while (((row = mysql_fetch_row(result)) != NULL) && i != 10) {	
		gotoxy(28, 10 + (i * 2));
		sprintf(arr[i], "%s", row[0]);
		printf("%s ", arr[i]);			//printf 함수를 사용하여 파일의 제목 출력 출력
		i++;
	}

	//[메뉴 선택]
	max = i;
	longTestSelect(cnt);

	while (1) {		//메뉴 선택
		key = _getch();				//변수 key에 사용자가 입력한 key 값을 저장

		if (key == 72) {			//key 값이 72일 경우(방향키 Up키)
			if (cnt > 0) {				//cnt가 0 보다 클 경우(맨 위의 메뉴가 아닌 메뉴 선택)
				cnt--;						//cnt의 값을 1빼고
				longTestSelect(cnt);		//선택된 메뉴 변경 표시
			}
		}
		else if (key == 80) {		//key 값이 80일 경우(방향키 Down키)
			if (cnt < max -1) {				//cnt가 3 보다 작을 경우(맨 아래의 메뉴가 아닌 메뉴 선택)
				cnt++;					//cnt의 값을 더하고
				longTestSelect(cnt);	//선택된 메뉴 변경 표시
			}
		}
		else if (key == 13) {		//Enter key 입력 시 선택된 메뉴 값을 반환
			sprintf(title, "%s\.dat", arr[cnt]);
			break;
		}
		else if (key == 27)				//Esc key 입력 시 4 반환 (메인 화면으로 회귀)
			return -1;
	}
}

void longTestSelect(int cnt) {
	int i = 0;				//for 반복문을 사용하기 위한 int형 변수 i 선언 후 0으로 초기화

	for (i = 0; i < max; i++) {						//for 반복문과 gotoxy 함수를 통해 4개의 메뉴에 있는 화살표 표시(▶)를 지운다.(printf() 함수로 덮어쓰기)
		gotoxy(24, 10 + (i * 2));
		printf("  ");
	}

	gotoxy(24, 10 + (cnt * 2));						//gotoxy 함수를 통해 사용자가 선택한 메뉴의 왼쪽의 위치로 이동하여 화살표(▶) 출력
	printf("▶");
}