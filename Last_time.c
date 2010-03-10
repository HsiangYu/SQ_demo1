/*
 #include <stdio.h>
 #include <minigui/common.h>
 #include <minigui/minigui.h>
 #include <minigui/gdi.h>
 #include <minigui/window.h>
 #include <minigui/control.h>

 #ifndef _LITE_VERSION
 #include <minigui/dti.c>
 #endif
 */
#define IDC_LTJTK           1001
#define IDC_LTQK            1002
#define IDC_LTBACK          1003
#define IDC_LTJTKTIME       1004
char lasttime[20] = {0};

void timeread(char *buffer)
{
	FILE *fp;
	if ((fp = fopen(FILE_LAST_TIME_DAT, "r")) == NULL) {
		MessageBox(0, "z", "z", MB_OK);
		return;
	}
	fread(buffer, sizeof(lasttime), 1, fp);
//	MessageBox(0,"z","",MB_OK);
//	printf("%d,%d,%d ",buffer->h,buffer->m,buffer->s);
	fclose(fp);
}

FILE *FP;

static DLGTEMPLATE LasttimeProgress =
{
	WS_BORDER,
	WS_EX_NONE,
	0, 40, 320, 200,
	"",
	0, 0,
	4, NULL,
	0
};

static CTRLDATA LastInitProgress [] =
{
	{
		"button", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 150, 165, 90, 30, IDC_LTBACK, MSG_RETURN, 0
	},
	{
		"button", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 1, 115, 318, 30, IDC_LTQK, MSG_CLEAR, 0
	},
	{
		CTRL_STATIC,
		WS_CHILD | SS_GROUPBOX | WS_VISIBLE,
		5, 5, 310, 105,
		IDC_LTJTK,
		MSG_LAST_TIME_TALK_TIME,
		0
	},
	{
		CTRL_STATIC,
		WS_CHILD | SS_NOTIFY | SS_CENTER | WS_VISIBLE,
		90, 50, 140, 20,
		IDC_LTJTKTIME,
		"",
		0
	},
};

static int LastTimeProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
	char lbuf[20] = {0};
	switch (message) {
	case MSG_INITDIALOG:
		timeread(lasttime);
		//	sprintf(lbuf,"%02d:%02d:%02d",lasttime.h, lasttime.m, lasttime.s);
		SetWindowText(GetDlgItem(hDlg, IDC_LTJTKTIME), lasttime);
		return 0;

	case MSG_COMMAND:
	{
		switch (wParam)	{
		case IDC_LTQK:

			sprintf(lasttime, "%02d:%02d:%02d", 0, 0, 0);
			SetWindowText(GetDlgItem(hDlg, IDC_LTJTKTIME), lasttime);
			if ((FP = fopen(FILE_LAST_TIME_DAT, "w")) == NULL) {
				MessageBox(0, FILE_FILE_ERROR, MSG_ERROR, MB_OK);
				return;
			}
			fwrite(&lasttime, sizeof(lasttime), 1, FP);
			return 0;
		case IDC_LTBACK:
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

int LastTimewindow(HWND hDlg)
{
	//制定對話框模版
	LasttimeProgress.controls = LastInitProgress;

	DialogBoxIndirectParam(&LasttimeProgress, hDlg, LastTimeProc, 0L);
}

/*

   //測試所用
   int MiniGUIMain (int argc, const char* argv[])
   {


    LastTime(HWND_DESKTOP);

    return 0;
   }


 */

