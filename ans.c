#include <stdio.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include "hello.h"
#include "tty.h"
#include "gprs.h"
#include "lang.h"


//對話框模版，設置對話框的屬性
static DLGTEMPLATE DlgInitProgress =
{
	WS_BORDER | WS_CAPTION,
	WS_EX_NONE,
	0, 0, 320, 240,
	"Call" /*"來電"*/,
	0, 0,
	3, NULL,
	0
};


//對話框模版，設置各個控件的屬性
static CTRLDATA CtrlInitProgress [] =
{
	{
		CTRL_SLEDIT,
		WS_VISIBLE | WS_TABSTOP | WS_BORDER,
		40, 30, 170, 30,
		IDC_Edit,
		NULL,
		0
	},
	{
		"button",
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		40, 140, 60, 30,
		IDC_Ans,
		MSG_ACCEPT,
		0
	},
	{
		"button",
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		130, 140, 60, 30,
		IDC_Refuse,
		MSG_REJECT,
		0
	}
};

static int InitDialogBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {

	//注意這個和主窗口創建的區別，這個是對話框特有的，在主窗口基礎上增添的。和CREATE一個時機發送出來的。
	case MSG_INITDIALOG:
		SendMessage(GetDlgItem(hDlg, IDC_Edit), MSG_SETTEXT, 0, (LPARAM)PhoneNum);
		return 0;

	//處理通知消息
	case MSG_COMMAND:
		switch (wParam) {
		case  IDC_Ans:
			gprs_ans();
			break;
		case  IDC_Refuse:
			gprs_hold();
			break;
		}
		break;
	case MSG_CLOSE:
		EndDialog(hDlg, wParam);
		break;
	}

	return DefaultDialogProc(hDlg, message, wParam, lParam);
}

static void InitDialogBox (HWND hWnd)
{
	//制定對話框模版
	DlgInitProgress.controls = CtrlInitProgress;

	DialogBoxIndirectParam(&DlgInitProgress, hWnd, InitDialogBoxProc, 0L);
}

//測試所用
//int MiniGUIMain (int argc, const char* argv[])
void ans(void)
{


	InitDialogBox(HWND_DESKTOP);

	//return 0;
}

