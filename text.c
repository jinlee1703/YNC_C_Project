#define _CRT_SECURE_NO_WARNINGS		//전처리기(#) 프로그램 실행에 사용되는 매크로와 헤더파일 선언
#include <stdio.h>					//표준입출력 함수 헤더파일
#include <conio.h>					//콘솔입출력 함수 헤더파일
#include <time.h>

#include "main.h"

//버퍼에 id를 입력받는 함수(현재 영문자만 지원)
int get_id(char *buf) {
	int cnt = 0, key;  //입력 받은 글자 수를 저장할 int형 변수 cnt와 와 키 값을 저장할 key 선언

	while (1) {
		key = _getch();					//한 글자 입력받아 key에 저장

		if (key == ENTER_KEY) {									//ENTER 키(13) 입력 시 반복문 종료
			break;
		}
		else if (key == BACKSPACE_KEY && cnt != 0) {					// BACKSPACE(8) 입력 시 문자 지우기(문자열이 입력되지 않았을 경우에는 지우지 않음)
			putchar('\b');									//\b(백스페이스)를 사용하여 한 비트 뒤로 이동
			putchar(' ');									//화면에 공백 표시
			putchar('\b');									//\b(백스페이스)를 사용하여 한 비트 뒤로 이동
			buf[cnt--] = ' ';								//버퍼의 마지막 원소 값을 ' '(공백) 처리(비움)
			continue;
		}
		else if ((cnt <= ID_SIZE - 1) && ((key >= 'a' && key <= 'z') || (key >= '0' && key <= '9'))) {		// 최대 크기를 넘어가지 않았으면 글자를 출력(영어와 숫자만 입력 받음)
			buf[cnt++] = (char)key;										// 버퍼에 글자 저장하고 카운트 1 증가  
			
			putchar(key);												// 화면에 문자 표시
		}
		else if (key == 27) {								//ESC 키(27) 입력 시 -1 반환(메인 화면으로 돌아갈 것)
			return -1;
		}
	}

	buf[cnt] = '\0';				// 문자열로 만들기 위해 종료 문자를 버퍼의 마지막에 삽입
	return 0;
}

//버퍼에 id를 입력받는 함수(현재 영문자만 지원, 입력 시 *로 표시)
int get_pw(char *buf) {
	int cnt = 0, key;  //입력 받은 글자 수를 저장할 int형 변수 cnt와 와 키 값을 저장할 key 선언

	while (1) {
		key = _getch();					// 한 글자 입력받음

		if (key == 13) {				//ENTER 키(13) 입력 시 반복문 종료
			break;
		}
		if (key == 8 && cnt != 0) {		// BACKSPACE(8) 입력 시 문자 지우기(문자열이 입력되지 않았을 경우에는 지우지 않음)
			putchar('\b');				//\b(백스페이스)를 사용하여 한 비트 뒤로 이동
			putchar(' ');				// 화면에 별 표시
			putchar('\b');				//\b(백스페이스)를 사용하여 한 비트 뒤로 이동
			buf[cnt--] = ' ';			//공백 저장
			continue;					//다음 입력 받음
		}
		else if ((cnt <= PW_SIZE - 1) && ((key >= 'a' && key <= 'z') || (key >= '0' && key <= '9'))) {			// 최대 크기를 넘어가지 않았으면 글자를 출력 (영어와 숫자만 입력 받음)
			
			buf[cnt++] = (char)key;											// 버퍼에 글자 저장하고 카운트 1 증가  
			putchar('*');													// 화면에 별 표시
		}
		else if (key == 27) {												//ESC 키(27) 입력 시 -1 반환(메인 화면으로 돌아갈 것)
			return -1;
		}
	}

	buf[cnt] = '\0';				// 문자열로 만들기 위해 널 문자 마무리
	return 0;
}

//사용자에게 타자연습 데이터를 입력받는 함수 : 타수, 정확도 출력함
int get_Typing(char *text, char *user, TA *data, int mode) {	
	int key = 0, cnt = 0 ,i = 0;;				//키값을 저장할 int형 변수 key와 입력한 글자수를 세는 int형 변수 cnt, for 반복문을 사용하기 위한 i를 선언 후 0으로 초기화
	static clock_t start_t, now_t;				//타자연습을 처음 시작(입력)했을때 시간과 그 이후로 입력한 시간을 비교하기 위한 clock_t 구조체 변수 선언(time.h에 선언되어 있음)
	//정적변수 : 긴글연습일 경우 한 문장이 아닌 5문장동안 타수와 정확도가 이어져야 하기 때문에 정적변수로 선언함
	//static int cnt = 0;							//입력한 글자수를 세는 int형 변수 cnt 선언 후 0으로 초기화
	static int tt = 0;							//시작 시간과 매 타이핑한 시간을 비교하여 타수를 구하기 위한 int형 변수 tt 선언후 0으로 초기화
	static int res;								//타수를 저장하기 위한 int형 변수 res를 선언하고 0으로 초기화
	static int pp = 0;							//입력한 글자수를 세어 정확도를 확인하기 위한 int형 변수 pp 후 0으로 초기화선언
	static int numberOfCalls = 0;				//긴 글 연습 일 경우 호출된 횟수를 세기 위해 정적변수 numberOfCalls를 선언
	static int totalNumberOfCh = 0;				//사용자가 입력한 총 횟수를 세기 위한 정적변수 totalNumberOfCh 선언

	while (1) {	
		key = _getch();				// 한 글자 입력받음

		if ((key == ENTER_KEY) || (strlen(text) == (cnt + 1)) && (key != BACKSPACE_KEY)) {			//ENTER or 입력할 문자의 바이트수와 동일할 경우(자동 엔터 처리)
			if (mode == 2) {
				numberOfCalls++;										//긴글 연습일 경우 호출된 횟수 +1(다음 줄 출력을 위해)
				
			}
			if ((mode == 1) || (numberOfCalls == 5)) {					//짧은 글이거나 긴 글 5번째 줄일경우 정적변수
				numberOfCalls = 0;
				tt = 0;
				res = 0;
				pp = 0;
				i = 0;
				cnt = 0;
				totalNumberOfCh = 0;
			}
				
			return 1;
		}
		else if (key == BACKSPACE_KEY) {					// BACKSPACE(8) 입력 시 문자 지우기
			if (cnt != 0) {
				if (mode == 1)
					gotoxy(6 + cnt, 15);											//문자를 입력하기 위한 좌표 변경(짧은 글)
				else if (mode == 2)
					gotoxy(6 + cnt, 9 + (numberOfCalls * 3 * 2));				//문자를 입력하기 위한 좌표 변경(긴 글)

				putchar('\b');				//\b(백스페이스)를 사용하여 한 비트 뒤로 이동
				putchar(' ');				// 화면에 별 표시
				putchar('\b');				//\b(백스페이스)를 사용하여 한 비트 뒤로 이동
				user[cnt--] = ' ';			//공백 저장
				continue;					//다음 입력 받음
			}
		}
		else if (key == ESC_KEY) {		//ESC
			numberOfCalls = 0;		//호출 횟수 초기화
			tt = 0;
			res = 0;
			pp = 0;
			i = 0;
			cnt = 0;
			totalNumberOfCh = 0;
			return -1;
		}
		else {
			/*짧은 글 연습 (긴 글 연습과 방식, 텍스트박스 위치 등이 다르기 때문에 매개변수 mode를 통해 모드 설정)*/
			if (mode == 1) {									
				user[cnt++] = (char)key;						//버퍼에 글자 저장하고 카운트 1 증가
				
				//[타자 입력에 따라 타수, 정확도 변경]
				if (cnt == 1)	start_t = clock();				//처음 입력 시 변수 start_t에 clock 함수를 통해 시작 지점(시간)을 저장

				now_t = clock();								//키를 입력 했을 때의 시작 지점(시간)을 저장

				tt = (int)((now_t - start_t) / CLOCKS_PER_SEC) + 1;	//변수 tt에 현재 키 입력 시간과 처음 키를 입력했을 시간을 빼고 이를 COLCKS_PER_SEC를 통해 나눔으로써 소모한 시간에 1을 더함

				res = (int)1000 * (cnt + 1) / (tt * 30);			//변수 res에 기본 타수 1000에 타이핑한 횟수 +1에  tt에 30을 곱한 값을 곱하여 저장(타자 속도 구하는 방식)

				pp = 0;											//정확한 글자 수를 카운트하기 위한 변수 pp를 0으로 초기화

				for (i = 0; i < cnt; i++) {						//for 반복문을 사용하여 입력한 글자 전체를 입력할 글자와 비교하여 같을 경우 pp를 1씩 더함
					if (text[i] == user[i])
						pp++;
				}

				data->speed = res;								//포인터로 받아온 매개변수(구조체 변수)의 멤버변수 speed에 타수 저장
				data->percent = pp * 100 / (cnt);				//포인터로 받아온 매개변수(구조체 변수)의 멤버변수 percent에 정확도 저장

				//[타자 입력에 따라 타수, 정확도 변경]
				gotoxy(6, 10);					//타수 출력을 위한 좌표 변경
				printf("타수 : %4d 타", data->speed);		//타수 출력

				gotoxy(40, 10);					//정확도 출력을 위한 좌표 변경
				printf("정확도 : %3d %%", data->percent);	//정확도 출력

				gotoxy(6 + cnt - 1, 15);		//문자를 입력하기 위한 좌표 변경
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				putchar(key);					//입력한 문자 출력
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			/*긴글 연습*/
			else if (mode == 2) {		
				user[cnt++] = (char)key;						//버퍼에 글자 저장하고 카운트 1 증가
				totalNumberOfCh++;

				//[타자 입력에 따라 타수, 정확도 변경]
				if (cnt == 1 && numberOfCalls == 0)	start_t = clock();				//처음 입력 시 변수 start_t에 clock 함수를 통해 시작 지점(시간)을 저장
				
				now_t = clock();								//키를 입력 했을 때의 시작 지점(시간)을 저장

				tt = (int)((now_t - start_t) / CLOCKS_PER_SEC) + 1;	//변수 tt에 현재 키 입력 시간과 처음 키를 입력했을 시간을 빼고 이를 COLCKS_PER_SEC를 통해 나눔으로써 소모한 시간에 1을 더함

				res = (int)1000 * (totalNumberOfCh + 1) / (tt * 30);	//변수 res에 기본 타수 1000에 타이핑한 횟수 +1에  tt에 30을 곱한 값을 곱하여 저장(타자 속도 구하는 방식)

				//pp = 0;										//정확한 글자 수를 카운트하기 위한 변수 pp를 0으로 초기화

				if (text[cnt - 1] == user[cnt - 1])						//입력한 글자 전체를 입력할 글자와 비교하여 같을 경우 pp를 1씩 더함
					pp++;

				data->speed = res;								//포인터로 받아온 매개변수(구조체 변수)의 멤버변수 speed에 타수 저장
				data->percent = pp * 100 / (totalNumberOfCh);				//포인터로 받아온 매개변수(구조체 변수)의 멤버변수 percent에 정확도 저장

				//[타자 입력에 따라 타수, 정확도 변경]
				gotoxy(6, 4);					//타수 출력을 위한 좌표 변경
				printf("타수 : %4d 타", data->speed);		//타수 출력

				gotoxy(40, 4);					//정확도 출력을 위한 좌표 변경
				printf("정확도 : %3d %%", data->percent);	//정확도 출력

				gotoxy(6 + cnt - 1, 9 + (numberOfCalls * 3 * 2));						//문자를 입력하기 위한 좌표 변경
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				putchar(key);					//입력한 문자 출력
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
		}
	}
}