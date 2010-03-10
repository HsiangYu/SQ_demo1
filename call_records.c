#include <stdio.h>
#include <string.h>
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include "lang.h"
//#include "tty.c"
//#include "gprs.c"
typedef struct call_log {
	int index;
	char name[20];
	char Phone_num[40];
} CL;
char PhoneNumt[40] = {0};
HWND c_holding;
int  calltype;
#include "holding.c"
CL  Dialedcall[20] = {0};
CL  missedcall[20] = {0};
CL  receivedcall[20] = {0};
int records_count = 0;

//通話記錄刪除函數
void records_delete(char* PATHNAME, CL* logbuff, int records_index, int records_max)
{
	FILE *fd;
	int  i;
	//printf("records_index is %d, records_max is %d\n",records_index,records_max);

	if ((fd = fopen(PATHNAME, "w")) == NULL) {
		MessageBox(0, PATHNAME, "error", MB_OK);
		return;
	}
	for (; records_index < records_max; records_index++) {
		logbuff[records_index].index = records_index;
		strcpy(logbuff[records_index].name, logbuff[records_index + 1].name);
		strcpy(logbuff[records_index].Phone_num, logbuff[records_index + 1].Phone_num);
	}
	for (i = 0; i < records_max - 1; i++) {
		fwrite(&logbuff[i], sizeof(CL), 1, fd);
		//printf("%s \n ",logbuff[i].Phone_num);
	}
	fclose(fd);

}

//通話紀錄寫函數
void records_write(char* PATHNAME, CL* logbuff)
{
	FILE *fd;
	if ((fd = fopen(PATHNAME, "a+")) == NULL) {
		MessageBox(0, PATHNAME, "error", MB_OK);
		return;
	}
	fwrite(logbuff, sizeof(CL), 1, fd);
	fclose(fd);
}

//通話紀錄讀函數
void records_read(char* PATHNAME, CL* logbuff)
{
	FILE *fd;
	int  i;
	records_count = 0;
	if ((fd = fopen(PATHNAME, "r")) == NULL) {
		MessageBox(0, PATHNAME, "error", MB_OK);
		return;
	}

	for (i = 0; ((i < 20) && (!feof(fd))); i++) {
		fread(&logbuff[i], sizeof(CL), 1, fd);
		records_count++;
	}
	records_count = records_count - 1;

	fclose(fd);

}

#include "All_time.c"
#include "Call_time.c"
#include "Delete_all.c"
#include "Dialed_calls.c"
#include "Last_time.c"
#include "Missed_calls.c"
#include "Received_calls.c"

#define IDC_BUTTEN211       211
#define IDC_BUTTEN212       212
#define IDC_BUTTEN213       213
#define IDC_BUTTEN214       214
#define IDC_BUTTEN215       215
#define IDC_BUTTEN216       216
#define IDC_BUTTEN217       217



static DLGTEMPLATE CallrecordsInitProgress =
{
	WS_BORDER,
	WS_EX_NONE,
	0, 40, 320, 200,
	"",
	0, 0,
	6, NULL,
	0
};

static CTRLDATA CallrecordsProgress [] =
{
	{"button", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 0,     0, 320, 30, IDC_BUTTEN211, MSG_MISSED_CALL, 0},
	{"button", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 0,    30, 320, 30, IDC_BUTTEN212, MSG_DIALED_CALLS, 0},
	{"button", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 0,    60, 320, 30, IDC_BUTTEN213, MSG_RECEIVED_CALLS, 0},
	{"button", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 0,    90, 320, 30, IDC_BUTTEN214, MSG_DELETE_ALL, 0},
	{"button", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 0,   120, 320, 30, IDC_BUTTEN215, MSG_AIR_TIME, 0},
	{"button", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 160, 160,  90, 30, IDC_BUTTEN217, MSG_RETURN, 0}
};

static int CallrecordsProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case MSG_INITDIALOG:

		return 0;

	case MSG_COMMAND:
	{
		switch (wParam)	{
		case IDC_BUTTEN211:

			Missedcallwindow(hDlg);
			return 0;

		case IDC_BUTTEN212:
			createDialedwindow(hDlg);
			return 0;

		case IDC_BUTTEN213:
			createReceivedwindow(hDlg);
			return 0;

		case IDC_BUTTEN214:
			deleteallnumber(hDlg);
			return 0;
		case IDC_BUTTEN215:
			Calltimewindow(hDlg);
			return 0;
		case IDC_BUTTEN216:
			//確定按鈕功能函數
			return 0;
		case IDC_BUTTEN217:

			EndDialog(hDlg, wParam);
			return 0;
		}
		return 0;
	}


	case MSG_CLOSE:
		EndDialog(hDlg, wParam);
		return 0;
	}
	return DefaultDialogProc(hDlg, message, wParam, lParam);
}

int Callrecords(HWND hDlg)
{
	//制定對話框模版
	CallrecordsInitProgress.controls = CallrecordsProgress;

	DialogBoxIndirectParam(&CallrecordsInitProgress, hDlg, CallrecordsProc, 0L);
	return 0;
}

