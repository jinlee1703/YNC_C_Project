//매크로 상수 정의
//창의 크기 정의
#define WIDTH 120			//콘솔창의 가로와 세로를 매크로 상수로 정의
#define HEIGHT 36

//아이디와 비밀번호의 최대 입력 글자(바이트) 정의
#define ID_SIZE 20				//아이디 텍스트박스의 최대 입력 크기를 매크로 상수로 정의
#define PW_SIZE 20				//비밀번호 텍스트박스의 최대 입력 크기를 매크로 상수로 정의

//키 값을 매크로 상수로 정의
#define ESC_KEY 27
#define ENTER_KEY 13
#define BACKSPACE_KEY 8

//DB 접속 정보 정의
#include <mysql.h>						//mysql(데이터베이스)의 함수들을 사용하기 위한 헤더파일을 포함
#pragma comment (lib, "libmysql.lib")	//libmysql.lib(라이브러리)를 사용하기 위해 프로그램의 추가 종속성에 "libmysql.lib"을 추가해주는 코드

#define DB_HOST "127.0.0.1"		//DB 호스트의 주소(DB IP)를 저장 (127.0.0.1 = 자신의 컴퓨터를 의미)
#define DB_USER "root"			//DB의 아이디
#define DB_PASS	"abc123"		//DB의 비밀번호
#define DB_NAME "typingDB"			//DB의 이름

MYSQL *connection;		//mysql을 사용하기 위해 MYSQL 구조체의 포인터 변수 선언(mysql_real_connect 함수의 반환값(주소) 저장)
MYSQL conn;				//mysql 접속을 위해 MYSQL 구조체 변수 선언(mysql_real_connect 함수의 인자로 사용)
MYSQL_RES *result;		//mysql을 사용할 때 쿼리의 전체 결과값을 저장하기 위한 MYSQL_RES 구조체의 포인터 변수 result 선언(mysql_sotre_result 함수의 시작주소 저장)
MYSQL_ROW row;			//mysql을 사용할 때 result를 한 줄씩 읽어오기 위해 MYSQL_ROW 구조체 변수 row를 선언 후(mysql_fetch_row 함수의 반환값 저장)
char query[255];		//쿼리문을 저장하기 위한 char형 배열(문자열) query의 크기를 255로 선언
char login_id[20];		//로그인에 성공했을 때 그 아이디를 저장하기 위한 char형 배열(문자열) login_id 선언

//사용자가 타이핑한 결과를 저장 및 출력하기 위해 구조체 포인터로 사용될 구조체 typingData 선언(TA로 재정의)
#ifndef _TA_						//조건부 컴파일을 통해 구조체 중복 선언을 방지
#define _TA_

typedef struct typingData {
	int speed;
	int percent;
} TA;

#endif