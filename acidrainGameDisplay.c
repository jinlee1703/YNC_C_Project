#define _CRT_SECURE_NO_WARNINGS		//전처리기(#) 프로그램 실행에 사용되는 매크로와 헤더파일 선언
#include <stdio.h>					//표준입출력 함수 헤더파일
#include <string.h>					//콘솔입출력 함수 헤더파일
#include <process.h>

#include "console.h"				//console.h 사용자 헤더파일 포함
#include "drawing.h"				//drawing.h 사용자 헤더파일 포함
#include "text.h"					//text.h 사용자 헤더파일 포함

#define WORD_CNT		20			//단어 시작 개수
#define LEVEL_COUNT		5			//레벨당 단어 증가 개수
#define LEVEL_SPEED		15			//레벨당 스피드 증가
#define MAX_WORD		50			//최대 단어 수

typedef struct fallingWords {		//산성비 단어 구조체
	int x;							//멤버 변수 : 좌표값 x y, 대기시간 wait, 출력여부 visible, 저장된 단어 text[20]
	int y;
	int wait;
	int visible;					
	char text[20];
} FW;

void inputWord();
void game(int lv);
void gameDisplayReset();

char words[1200][20] = { 0 };		//랜덤 단어 저장
FW word[MAX_WORD];					//떨어지는 단어 저장

CRITICAL_SECTION cs;			//임계구역 설정
HANDLE thread1;					//쓰레드 1 : inputWord
HANDLE thread2;					//쓰레드 2 : game

int score = 0;		//점수
int life = 3;		//남은 생명
int count = 0;		//단어 개수
int tp = 0;			//단어를 입력한 횟수(레벨마다 초기화)

//산성비 게임화면을 출력하는 함수
void acidrainGame() {
	int i = 0, j = 0;				//for 반복문을 사용하기 위한 int형 변수 i와 j 선언 후 0으로 초기화
	FILE *fp;
	char filepath[255] = { 0 };
	char user[20] = { 0 };
	
	system("cls");		//system함수로 화면 초기화

	consoleShow();				//사용자 지정 함수 consoleShow 함수로 콘솔을 지정된 크기로 엶
	drawingBorder();			//사용자 지정 함수로 테두리 출력
	drawingIdtag();	//로그인 한 ID 출력(미완성)

	for (i = 2; i < WIDTH - 2; i++) {
		gotoxy(i, 3);					//gotoxy 함수를 통해 좌표 이동 후 printf 함수로 상단선 그리기
		printf("-");

		if (i % 2 == 0) {
			gotoxy(i, HEIGHT - 5);			//gotoxy 함수를 통해 좌표 이동 후 printf 함수로 하단선 그리기(if 문을 통해 한칸 씩 띄워서 출력)
			printf("~");
		}
	}

	gotoxy((WIDTH / 2) - 14, HEIGHT - 4);				//gotoxy 함수를 통해 좌표 이동 후 사용자가 단어를 입력할 칸 출력
	printf("+--------------------------+");
	gotoxy((WIDTH / 2) - 14, HEIGHT - 3);
	printf("|                          |");
	gotoxy((WIDTH / 2) - 14, HEIGHT - 2);
	printf("+--------------------------+");

	//단어가 저장되어 잇는 파일을 불러오기
	sprintf(query, "select * from file where events_id='3' and language='eng'");		//sprintf 함수를 통해 query에 쿼리문을 저장

	mysql_query(connection, query);		//mysql_query 함수를 통해 connection(연결 정보)에 쿼리문 실행(DB에 저장되어 있는 단어 파일 조회)

	result = mysql_store_result(connection);			//result에 mysql_store_result함수를 사용하여 connection(연결정보)의 실행 결과를 저장

	row = mysql_fetch_row(result);						//실행결과를 읽어옴

	sprintf(filepath, "산성비 게임\\%s", row[3]);			//배열에 DB에 저장되어 있는 파일명과 파일 경로 저장

	if ((fp = fopen(filepath, "r")) == NULL) {
		fprintf(stderr, "파일 열기 실패!\n");
		return;
	}

	i = 0;
	while (!feof(fp)) {											//다음 줄이 있을 경우 문장을 읽어온다
		j = 0;
		while (!feof(fp)) {
			words[i][j] = fgetc(fp);
			if (words[i][j] == ' ') {
				words[i][j] = '\0';
				break;
			}
			j++;
		}
		i++;
	}
	
	//전역변수 초기화
	score = 0;		//점수
	life = 3;		//남은 생명
	count = 0;		//단어 개수
	tp = 0;			//단어를 입력한 횟수(레벨마다 초기화)

	//쓰레드 구현
	InitializeCriticalSection(&cs);															//임계구역 설정
	thread1 = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)inputWord, NULL, 0, NULL);	//아이디를 입력받는 쓰레드1
	thread2 = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)game, (void *)1, 0, NULL);	//단어를 출력하는 쓰레드2
	WaitForSingleObject(thread1, INFINITE);													//쓰레드 1 대기
	DeleteCriticalSection(&cs);																//임계구역 해제
	return 0;
}

//산성비 게임 단어를 입력받는 함수
void inputWord() {
	int i = 0;
	int cnt = 0, key = 0;		//사용자가 입력한 key 값을 저장할 int형 변수 key 선언 후 0으로 초기화
	char user[20] = { 0 };		//사용자가 입력한 문자열을 저장하기 위한 char형 배열 user을 선언 후 0으로 초기화(최대 입력 크기20)
	
	while (1) {
		EnterCriticalSection(&cs);

		if (kbhit() != 0) {
			key = _getch();			//변수 key에 사용자가 입력한 키 값을 저장
			
			if (key == ENTER_KEY || key == 32) {		//ENTER 키(13) or SPACE BAR(32)
				//텍스트박스 초기화(완료) + 카운트 더하기(완료) + 기존 표시 단어 지우기(완료)
				gotoxy((WIDTH / 2) - 14, HEIGHT - 3);
				printf("|                          |");
				for (i = 0; i < count; i++) {
					if (word[i].visible == 1 && strcmp(word[i].text, user) == 0) {
						word[i].visible = 0;
						score += 10;
						tp++;
						break;
					}
				}
				for (i = 0; i < sizeof(user); i++) {
					user[i] = '\0';
				}
				cnt = 0;
			}
			else if (key == ESC_KEY) {	// ESC 키 입력시 -1 반환
				//게임 종료(메인화면으로 돌아갈 것)
				TerminateThread(thread2, 0);
				TerminateThread(thread1, 0);
			}
			else if (key == BACKSPACE_KEY) {				// BACKSPACE(8) 입력 시 문자 지우기
				if (cnt != 0) {
					gotoxy((WIDTH / 2) - 12 + cnt, HEIGHT - 3);

					putchar('\b');				//\b(백스페이스)를 사용하여 한 비트 뒤로 이동
					putchar(' ');				// 화면에 별 표시
					putchar('\b');				//\b(백스페이스)를 사용하여 한 비트 뒤로 이동
					user[cnt--] = ' ';			//공백 저장
					continue;					//다음 입력 받음
				}
			}
			else if ((cnt >= 0 && cnt <= 20) && (key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z')) {		//영어만 입력받도록 함
				gotoxy((WIDTH / 2) - 12 + cnt, HEIGHT - 3);
				user[cnt++] = (char)key;				// 버퍼에 글자 저장하고 카운트 1 증가  
				putchar(key);							// 화면에 문자 표시
			}
			
		}
		LeaveCriticalSection(&cs);

		Sleep(1);
	}
}

void game() {
	int lv = 1;
	int speed;
	int i = 0, j = 0, check = 1, key = 0;
	int r = 0;		//랜덤 변수

lvUp:

	speed = 1000 - (lv - 1) * LEVEL_SPEED;
	count = WORD_CNT + (lv - 1) * LEVEL_COUNT;

	//단어 최대개수 조절
	if (count >= MAX_WORD)
		count = MAX_WORD - 1;

	srand((unsigned int)time(NULL));
	//단어 초기화
	for (i = 0; i < count; i++) {
		r = rand() % (WIDTH - 20) + 4;					//x값 지정
		word[i].x = r;

		r = rand() % (speed / 20);					//wait값 지정(한꺼번에 단어가 내려가지 않고 적당한 텀을 두어 내려오도록 하기 위해)
		word[i].wait = r;

		word[i].y = 4;						//y값은 0에서 순차적으로 증가

		word[i].visible = 1;

		r = rand() % 1090;
		sprintf(word[i].text, words[r]);
	}
	
	// 게임 루프
	while (check) {
		//단어 출력
		for (i = 0; i < count; i++) {
			if (word[i].wait == 0 && word[i].visible == 1) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				gotoxy(word[i].x, word[i].y);
				puts(word[i].text);
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

		//단어 y값 내리기
		for (i = 0; i < count; i++)
		{
			if (word[i].wait == 0) {
				word[i].y++;
			}
			else {
				word[i].wait--;
			}
		}

		if (count <= tp) {
			lv++;
			tp = 0;
			goto lvUp;
		}

		//생명 체크
		for (i = 0; i < count; i++) {
			if ((word[i].y >= HEIGHT - 4) && (word[i].visible == 1)) {
				life--;
				word[i].visible = 0;
				tp++;
			}
		}

		for (i = 2; i < WIDTH - 2; i++) {
			if (i % 2 == 0) {
				gotoxy(i, HEIGHT - 5);			//gotoxy 함수를 통해 좌표 이동 후 printf 함수로 하단선 그리기(if 문을 통해 한칸 씩 띄워서 출력)
				printf("~");
			}
			else {
				gotoxy(i, HEIGHT - 5);			//gotoxy 함수를 통해 좌표 이동 후 printf 함수로 하단선 그리기(if 문을 통해 한칸 씩 띄워서 출력)
				printf(" ");
			}
		}

		//점수 및 남은 생명 출력
		gotoxy(5, 2);				//gotoxy 함수를 통해 좌표 이동 후 점수 출력
		printf("LEVEL %2d", lv);
		gotoxy(5, HEIGHT - 3);				//gotoxy 함수를 통해 좌표 이동 후 점수 출력
		printf("SCORE : %5d", score);
		gotoxy(WIDTH - 15, HEIGHT - 3);		//gotoxy 함수를 통해 좌표 이동 후 남은 생명 출력
		printf("LIFE : %1d", life);
		LeaveCriticalSection(&cs);

		if (life <= 0) {
			check = 0;

			gotoxy((WIDTH / 2) - 25, (HEIGHT / 2) - 3);
			printf("+-----------------------------------------------+");
			gotoxy((WIDTH / 2) - 25, (HEIGHT / 2) - 2);
			printf("|                                               |");
			gotoxy((WIDTH / 2) - 25, (HEIGHT / 2) - 1);
			printf("|          게임 점수가 저장되었습니다           |");
			gotoxy((WIDTH / 2) - 25, (HEIGHT / 2));
			printf("|                                               |");
			gotoxy((WIDTH / 2) - 25, (HEIGHT / 2) + 1);
			printf("|                                               |");
			gotoxy((WIDTH / 2) - 25, (HEIGHT / 2) + 2);
			printf("|     아무 키나 누르시면 메뉴로 돌아갑니다.     |");
			gotoxy((WIDTH / 2) - 25, (HEIGHT / 2) + 3);
			printf("|                                               |");
			gotoxy((WIDTH / 2) - 25, (HEIGHT / 2) + 4);
			printf("+-----------------------------------------------+");

			_getch();

			sprintf(query, "insert into typing VALUES ('%s', 3, %d, %d, curdate())", login_id, score, NULL);		//sprintf 함수를 통해 query에 쿼리문을 저장

			mysql_query(connection, query);		//mysql_query 함수를 통해 connection(연결 정보)에 쿼리문 실행(insert문으로 타이핑 정보 저장)

			TerminateThread(thread1, 0);
			TerminateThread(thread2, 0);
		}

		Sleep(speed);
		gameDisplayReset();
	}
}

void gameDisplayReset() {
	int i = 0, j = 0;
	unsigned long dw;
	COORD spot = { 2, 0 };
	
	for (i = 4; i < HEIGHT - 5; i++) {
		spot.Y = i;
		FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', WIDTH - 4, spot, &dw);
	}
}