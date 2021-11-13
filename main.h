//��ũ�� ��� ����
//â�� ũ�� ����
#define WIDTH 120			//�ܼ�â�� ���ο� ���θ� ��ũ�� ����� ����
#define HEIGHT 36

//���̵�� ��й�ȣ�� �ִ� �Է� ����(����Ʈ) ����
#define ID_SIZE 20				//���̵� �ؽ�Ʈ�ڽ��� �ִ� �Է� ũ�⸦ ��ũ�� ����� ����
#define PW_SIZE 20				//��й�ȣ �ؽ�Ʈ�ڽ��� �ִ� �Է� ũ�⸦ ��ũ�� ����� ����

//Ű ���� ��ũ�� ����� ����
#define ESC_KEY 27
#define ENTER_KEY 13
#define BACKSPACE_KEY 8

//DB ���� ���� ����
#include <mysql.h>						//mysql(�����ͺ��̽�)�� �Լ����� ����ϱ� ���� ��������� ����
#pragma comment (lib, "libmysql.lib")	//libmysql.lib(���̺귯��)�� ����ϱ� ���� ���α׷��� �߰� ���Ӽ��� "libmysql.lib"�� �߰����ִ� �ڵ�

#define DB_HOST "127.0.0.1"		//DB ȣ��Ʈ�� �ּ�(DB IP)�� ���� (127.0.0.1 = �ڽ��� ��ǻ�͸� �ǹ�)
#define DB_USER "root"			//DB�� ���̵�
#define DB_PASS	"abc123"		//DB�� ��й�ȣ
#define DB_NAME "typingDB"			//DB�� �̸�

MYSQL *connection;		//mysql�� ����ϱ� ���� MYSQL ����ü�� ������ ���� ����(mysql_real_connect �Լ��� ��ȯ��(�ּ�) ����)
MYSQL conn;				//mysql ������ ���� MYSQL ����ü ���� ����(mysql_real_connect �Լ��� ���ڷ� ���)
MYSQL_RES *result;		//mysql�� ����� �� ������ ��ü ������� �����ϱ� ���� MYSQL_RES ����ü�� ������ ���� result ����(mysql_sotre_result �Լ��� �����ּ� ����)
MYSQL_ROW row;			//mysql�� ����� �� result�� �� �پ� �о���� ���� MYSQL_ROW ����ü ���� row�� ���� ��(mysql_fetch_row �Լ��� ��ȯ�� ����)
char query[255];		//�������� �����ϱ� ���� char�� �迭(���ڿ�) query�� ũ�⸦ 255�� ����
char login_id[20];		//�α��ο� �������� �� �� ���̵� �����ϱ� ���� char�� �迭(���ڿ�) login_id ����

//����ڰ� Ÿ������ ����� ���� �� ����ϱ� ���� ����ü �����ͷ� ���� ����ü typingData ����(TA�� ������)
#ifndef _TA_						//���Ǻ� �������� ���� ����ü �ߺ� ������ ����
#define _TA_

typedef struct typingData {
	int speed;
	int percent;
} TA;

#endif