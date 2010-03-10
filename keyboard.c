#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
//#include <minigui/mgext.h>
//#include <minigui/mywindows.h>
#include "gprs.h"
#include "tty.h"
#include "hello.h"
#include "lang.h"



static DLGTEMPLATE DlgBoxInputChar =
{
	WS_BORDER | WS_CAPTION,
	WS_EX_NONE,
	0, 0, 320, 240,
	MSG_INPUT_NUMBER,
	0, 0,
	20, NULL,
	0
};

static CTRLDATA CtrlInputChar [] =
{
	{
		CTRL_STATIC,
		WS_VISIBLE | SS_CENTER,
		30, 5, 70, 25,
		IDC_NUMBER1,
		MSG_NUMBER,
		0
	},
	{
		CTRL_SLEDIT,
		WS_VISIBLE | WS_TABSTOP | WS_BORDER | SS_NOTIFY,
		125, 5, 130, 20,
		IDC_CHAR3,
		NULL,
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		30, 35, 70, 25,
		IDC_K1,
		"1",
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		125, 35, 70, 25,
		IDC_K2,
		"2",
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		220, 35, 70, 25,
		IDC_K3,
		"3",
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		30, 65, 70, 25,
		IDC_K4,
		"4",
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		125, 65, 70, 25,
		IDC_K5,
		"5",
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		220, 65, 70, 25,
		IDC_K6,
		"6",
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		30, 95, 70, 25,
		IDC_K7,
		"7",
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		125, 95, 70, 25,
		IDC_K8,
		"8",
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		220, 95, 70, 25,
		IDC_K9,
		"9",
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		30, 125, 70, 25,
		IDC_KMI,
		"*",
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		125, 125, 70, 25,
		IDC_K0,
		"0",
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		220, 125, 70, 25,
		IDC_KJING,
		"#",
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		30, 155, 70, 25,
		IDC_CALL2,
		MSG_CALL,
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		220, 155, 70, 25,
		IDC_MORE2,
		MSG_MORE_DATA,
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		30, 185, 70, 25,
		IDC_RETURN3,
		MSG_RETURN,
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		220, 185, 70, 25,
		IDC_DEL3,
		MSG_DELECT,
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		125, 185, 70, 25,
		IDC_COOLBAR,
		MSG_KEYBOARD,
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		125, 155, 70, 25,
		IDC_HOLD,
		MSG_HUNG_UP,
		0
	}
};


static void NotifInput (HWND hwnd, int id, int nc, DWORD add_data)
{
	static int flag = 0;
	//鼠標點擊該控件時
	if (nc == BN_CLICKED) {
		if (flag == 0) {
			//如果鍵盤沒有打開，則顯示鍵盤，同時將KBON狀態設置為FALSE
			flag = 1;
			coolbar(GetParent(hwnd));
		} else  {
			HWND Kb;
			flag = 0;
			//如果鍵盤已經打開，則銷毀鍵盤
			Kb = GetFirstHosted(GetParent(hwnd));
			DestroyAllControls(Kb);
			DestroyMainWindow(Kb);
			PostQuitMessage(Kb);
		}
	}
}

static int InputCharDialogBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)

{
	hwindowDlg = hDlg;

	switch (message) {
	case MSG_INITDIALOG:
		Input = GetDlgItem(hDlg, IDC_CHAR3);
		SetNotificationCallback(GetDlgItem(hDlg, IDC_COOLBAR), NotifInput);
		return 1;

	//break;
	case MSG_COMMAND:
		switch (wParam) {
		case IDC_K1:
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_GETTEXT, 20, (LPARAM)buffer);
			strcat(buffer, "1");
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_SETTEXT, 0, (LPARAM)buffer);
			break;
		case IDC_K2:
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_GETTEXT, 20, (LPARAM)buffer);
			strcat(buffer, "2");
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_SETTEXT, 0, (LPARAM)buffer);
			break;
		case IDC_K3:
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_GETTEXT, 20, (LPARAM)buffer);
			strcat(buffer, "3");
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_SETTEXT, 0, (LPARAM)buffer);
			break;
		case IDC_K4:
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_GETTEXT, 20, (LPARAM)buffer);
			strcat(buffer, "4");
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_SETTEXT, 0, (LPARAM)buffer);
			break;
		case IDC_K5:
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_GETTEXT, 20, (LPARAM)buffer);
			strcat(buffer, "5");
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_SETTEXT, 0, (LPARAM)buffer);
			break;
		case IDC_K6:
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_GETTEXT, 20, (LPARAM)buffer);
			strcat(buffer, "6");
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_SETTEXT, 0, (LPARAM)buffer);
			break;
		case IDC_K7:
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_GETTEXT, 20, (LPARAM)buffer);
			strcat(buffer, "7");
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_SETTEXT, 0, (LPARAM)buffer);
			break;
		case IDC_K8:
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_GETTEXT, 20, (LPARAM)buffer);
			strcat(buffer, "8");
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_SETTEXT, 0, (LPARAM)buffer);
			break;
		case IDC_K9:
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_GETTEXT, 20, (LPARAM)buffer);
			strcat(buffer, "9");
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_SETTEXT, 0, (LPARAM)buffer);
			break;
		case IDC_KMI:
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_GETTEXT, 20, (LPARAM)buffer);
			strcat(buffer, "*");
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_SETTEXT, 0, (LPARAM)buffer);
			break;
		case IDC_K0:
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_GETTEXT, 20, (LPARAM)buffer);
			strcat(buffer, "0");
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_SETTEXT, 0, (LPARAM)buffer);
			break;
		case IDC_KJING:
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_GETTEXT, 20, (LPARAM)buffer);
			strcat(buffer, "#");
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_SETTEXT, 0, (LPARAM)buffer);
			break;
		case IDC_CALL2:
			SendMessage(GetDlgItem(hDlg, IDC_CHAR3), MSG_GETTEXT, 20, (LPARAM)buffer);
			gprs_call(buffer, strlen(buffer));
			break;
		case IDC_HOLD:
			gprs_hold();
			break;
//      case IDC_COOLBAR:
//              coolbar(hDlg);
//              break;
		case IDC_DEL3:
			SetWindowText(GetDlgItem(hDlg, IDC_CHAR3), "");
			break;
		case IDC_RETURN3:
			EndDialog(hDlg, wParam);
			break;
		}
		break;
	case MSG_CLOSE:
		EndDialog(hDlg, wParam);
		break;
	}
	return DefaultDialogProc(hDlg, message, wParam, lParam);

}

void keyboard(hwindowDlg)
{
	DlgBoxInputChar.controls = CtrlInputChar;
	DialogBoxIndirectParam(&DlgBoxInputChar, hwindowDlg, InputCharDialogBoxProc, 0L);

}

