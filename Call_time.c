// Zhou wanxin

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
#define IDC_BUTTEN411       411
#define IDC_BUTTEN412       412
#define IDC_BUTTEN416       416
#define IDC_BUTTEN417       417



static DLGTEMPLATE CalltimeInitProgress =
{
	WS_BORDER,
	WS_EX_NONE,
	0, 40, 320, 200,
	"",
	0, 0,
	3, NULL,
	0
};

static CTRLDATA CalltimeProgress [] =
{
	{
		"button", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 0, 0, 320, 30, IDC_BUTTEN411, MSG_LAST_TALK_TIME, 0
	},

	{
		"button", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 0, 30, 320, 30, IDC_BUTTEN412, MSG_TOTAL_TALK_TIME, 0
	},

	{
		"button", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 216, 130, 90, 30, IDC_BUTTEN417, MSG_RETURN, 0
	}
};

static int CalltimeProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case MSG_INITDIALOG:

		return 0;

	case MSG_COMMAND:
	{
		switch (wParam)	{
		case IDC_BUTTEN411:
			//上次通話時間窗口函數
			LastTimewindow(hDlg);
			return 0;
		case IDC_BUTTEN412:
			//全部通話時間窗口函數
			AllTimewindow(hDlg); //參數列表未
			return 0;

		case IDC_BUTTEN416:
			//確定按鈕功能函數確定
			return 0;
		case IDC_BUTTEN417:

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

static void Calltimewindow(HWND hDlg)
{
	//制定對話框模版
	CalltimeInitProgress.controls = CalltimeProgress;

	DialogBoxIndirectParam(&CalltimeInitProgress, hDlg, CalltimeProc, 0L);
}

/*
   //測試所用
   int MiniGUIMain (int argc, const char* argv[])
   {


    Calltime(HWND_DESKTOP);

    return 0;
   }
 */


