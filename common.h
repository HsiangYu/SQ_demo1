#ifndef COMMON_H
#define COMMON_H

/*#include "stdio.h"
 #include "string.h"
 #include "stdlib.h"

 #include "minigui/common.h"
 #include "minigui/minigui.h"
 #include "minigui/gdi.h"
 #include "minigui/window.h"
 #include "minigui/control.h"*/

#include "lang.h"


#define MSG_USERSEND            4320
#define IDC_BUTTEN1             1001
#define IDC_BUTTEN2             1002
#define IDC_BUTTEN3             1003
//#define MSG_RING  11100
#define MSG_NEWMSG              11101
#define MSG_USRHOLD             1231
#define IDC_STATIC_SEARCH       212
#define MSG_SEARCH              1232
#define MSG_ALARM               1233
#define IDC_STATIC_SEARCH       212
#define MSG_SEARCH              1232
#define MSG_MISSED              1788

int  FLAG = 0;
int  calltype;  //�I�s���� 1�����a�Q�~�I�s�A2���~�a�I�s���a�Τ�
char PhoneNum[40] = {0};
char Tel_Num[40] = {0};
char Data[20] = {0};
char Msg_text[70] = {0};   //�u�H���e
int  Mes_count   = 0;
int  Mes_index   = 0;
char netname[20] = {0};
int  pb_flag = 0;
HWND hsm;
HWND hMainWnd;
HWND h_calling;
HWND c_holding;
int  pb_count;

//�w�q�u�H���c��
typedef struct PDA_message {
	int index;
	char name[20];
	char PhoneNumber[20];
	char Msgtime[20];
	char Msgtext[70];
} Message;

//�w�q�x�����c��
typedef struct ALARMCLOCK {

	int h;
	int m;
	int s;
	int status;
} AT;

//�w�q�ɶ����c��
typedef struct time {
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
} TIME;

//�w�q�q�ܥ����c��
typedef struct phonebook {
	int index;
	char name[40];
	char Phonenum[40];
} PB;

//�w�q�p�ɵ��c��
typedef struct count_time {
	int h;
	int m;
	int s;

} CT;

//�w�q�q�ܰO�����c�D
typedef struct call_log {
	int index;
	char name[20];
	char Phone_num[40];
} CL;
HWND c_holding;
AT   alarmsave;
void timewrite(CT buffer, int l)
{
	FILE *fp, *fd;
	int  m;
	char s[100];
	if ((fp = fopen(FILE_LAST_TIME_DAT, "w")) == NULL) {
		MessageBox(0, FILE_FILE_ERROR, "error", MB_OK);
		return;
	}
	if ((fd = fopen(FILE_ALLCALLTIME_DAT, "w")) == NULL) {
		MessageBox(0, FILE_FILE_ERROR, "error", MB_OK);
		return;
	} else  {
		fread(&m, sizeof(int), 1, fd);
	}
	m = m + l;
	fwrite(&m, sizeof(int), 1, fd);
	fwrite(&buffer, sizeof(CT), 1, fp);
	//sprintf(s,"%d,%d,%d ",buffer.h,buffer.m,buffer.s);
	//MessageBox(0,"f",s,MB_OK);
	//sprintf(s,"%d",m);
	//MessageBox(0,s,"g",MB_OK);
	fclose(fp);
	fclose(fd);
}

#endif

