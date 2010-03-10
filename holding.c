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
#define IDC_HDGD              1001
#define IDC_HDJTKNAME         1000
#define IDC_HDJTKNUMBER       2000
#define IDC_HDJTKTIME         3000
#define IDC_HDTHSJ            4000
#define IDC_HDZZTHZ           5000
#define _ID_HTIMER	      801
#define MSG_MISSED            903
static int htime = 0;
typedef struct count_time {
	int h;
	int m;
	int s;

} CT;


static DLGTEMPLATE HoldInitProgress =
{
	WS_BORDER,
	WS_EX_NONE,
	0, 40, 320, 200,
	"",
	0, 0,
	6, NULL,
	0
};


static CTRLDATA HoldingProgress [] =
{
	{
		"button", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 225, 165, 90, 30, IDC_HDGD, "Hung up 掛斷", 0
	},
	{
		CTRL_STATIC,
		WS_CHILD | SS_NOTIFY | SS_CENTER | WS_VISIBLE,
		100, 100, 100, 20,
		IDC_HDJTKNAME,
		"",
		0
	},
	{
		CTRL_STATIC,
		WS_CHILD | SS_NOTIFY | SS_CENTER | WS_VISIBLE,
		50, 40, 100, 20,
		IDC_HDTHSJ,
		MSG_TALK_TIME,
		0
	},
	{
		CTRL_STATIC,
		WS_CHILD | SS_NOTIFY | SS_CENTER | WS_VISIBLE,
		90, 70, 120, 20,
		IDC_HDZZTHZ,
		MSG_ON_THE_PHONE,
		0
	},
	{
		CTRL_STATIC,
		WS_CHILD | SS_NOTIFY | SS_CENTER | WS_VISIBLE,
		140, 40, 100, 20,
		IDC_HDJTKTIME,
		"",
		0
	},
	{
		CTRL_STATIC,
		WS_CHILD | SS_NOTIFY | SS_CENTER | WS_VISIBLE,
		100, 100, 100, 20,
		IDC_HDJTKNUMBER,
		"",
		0
	}
};

static int HoldBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{

	char timebuffer[20] = {0};
	CT   counttime;
	counttime.h = 0;
	counttime.m = 0;
	counttime.s = 0;
	//CL r;
	switch (message) {
	case MSG_INITDIALOG:
		c_holding = hDlg;
		calltype  = 2;
		SetTimer(hDlg, _ID_HTIMER, 100);
		SetWindowText(GetDlgItem(hDlg, IDC_HDJTKNUMBER), PhoneNumt);
		return 0;
	case MSG_TIMER:
	{
		if (wParam == _ID_HTIMER) {

			counttime.s = htime % 60;
			counttime.m = htime / 60;
			counttime.h = htime / 3600;
			sprintf(timebuffer, "%02d:%02d:%02d", counttime.h, counttime.m, counttime.s);
			SetDlgItemText(hDlg, IDC_HDJTKTIME, timebuffer);
			//SetWindowText(GetDlgItem(hDlg,IDC_HDJTKTIME),timebuffer);
			htime++;
		}
		return 0;
	}
	case MSG_MISSED:
		htime = 0;
		KillTimer(hDlg, _ID_HTIMER);
		EndDialog(hDlg, wParam);
		return 0;

	case MSG_COMMAND:
	{
		switch (wParam)	{
		case IDC_HDGD:
			htime = 0;
			KillTimer(hDlg, _ID_HTIMER);
			EndDialog(hDlg, wParam);
			gprs_hold();
			break;
		}
		return 0;
	}


	case MSG_CLOSE:
		htime = 0;
		KillTimer(hDlg, _ID_HTIMER);
		EndDialog(hDlg, wParam);
		break;
	}
	return DefaultDialogProc(hDlg, message, wParam, lParam);
}

static void Holding(HWND hDlg)
{
	//制定對話框模版

	HoldInitProgress.controls = HoldingProgress;

	DialogBoxIndirectParam(&HoldInitProgress, hDlg, HoldBoxProc, 0L);
}

/*
   //測試所用
   int MiniGUIMain (int argc, const char* argv[])
   {


    Holding(HWND_DESKTOP);

    return 0;
   }
 */

