//Zhou wanxin

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

#define IDC_ALLJTK           2001
#define IDC_ALLQK            2002
#define IDC_ALLBACK          2003
#define IDC_ALLJTKTIME       2004
int  atl;
FILE *pp;

extern int maintime;


static DLGTEMPLATE AlltimeProgress =
{
	WS_BORDER,
	WS_EX_NONE,
	0, 40, 320, 200,
	"",
	0, 0,
	4, NULL,
	0
};

static CTRLDATA AllInitProgress [] =
{
	{
		"button", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 150, 165, 90, 30, IDC_ALLBACK, MSG_RETURN, 0
	},
	{
		"button", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 1, 115, 318, 30, IDC_ALLQK, MSG_CLEAR, 0
	},
	{
		CTRL_STATIC,
		WS_CHILD | SS_GROUPBOX | WS_VISIBLE,
		5, 5, 310, 105,
		IDC_ALLJTK,
		MSG_ALL_TIME,
		0
	},
	{
		CTRL_STATIC,
		WS_CHILD | SS_NOTIFY | SS_CENTER | WS_VISIBLE,
		90, 50, 140, 20,
		IDC_ALLJTKTIME,
		"",
		0
	},
};

static int AllTimeProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
	char atbuffer[20];
	switch (message) {
	case MSG_INITDIALOG:

		sprintf(atbuffer, "%02d:%02d:%02d", maintime / 3600, (maintime % 3600) / 60, (maintime % 3600) % 60);
		SetWindowText(GetDlgItem(hDlg, IDC_ALLJTKTIME), atbuffer);
		return 0;

	case MSG_COMMAND:
	{
		switch (wParam)	{
		case IDC_ALLQK:
			sprintf(atbuffer, "%02d:%02d:%02d", 0, 0, 0);
			SetWindowText(GetDlgItem(hDlg, IDC_ALLJTKTIME), atbuffer);
			if ((pp = fopen(FILE_ALLCALLTIME_DAT, "w")) == NULL) {
				MessageBox(0, FILE_FILE_ERROR, "error", MB_OK);
				return;
			}
			atl = 0;
			fwrite(&atl, sizeof(int), 1, pp);
			return 0;
		case IDC_ALLBACK:
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

static void AllTimewindow(HWND hDlg)
{
	//制定對話框模版
	AlltimeProgress.controls = AllInitProgress;

	DialogBoxIndirectParam(&AlltimeProgress, hDlg, AllTimeProc, 0L);
}

/*
   //測試所用
   int MiniGUIMain (int argc, const char* argv[])
   {


    AllTime(HWND_DESKTOP);

    return 0;
   }
 */

