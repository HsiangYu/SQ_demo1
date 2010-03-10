#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
//#include <minigui/dti.c>

#include "hello.h"
#include "gprs.h"
#include "tty.h"
#include "lang.h"


static DLGTEMPLATE DlgBoxInputChar =
{
	WS_BORDER | WS_CAPTION,
	WS_EX_NONE,
	0, 0, 320, 240,
	MSG_ADD_CONTACT,
	0, 0,
	5, NULL,
	0
};

static CTRLDATA CtrlInputChar [] =
{
	{
		CTRL_STATIC,
		WS_VISIBLE | SS_CENTER,
		10, 10, 80, 25,
		IDC_NAME,
		MSG_NAME,
		0
	},
	{
		CTRL_STATIC,
		WS_VISIBLE | SS_CENTER,
		10, 70, 80, 25,
		IDC_NUMBER,
		MSG_NUMBER,
		0
	},
	{
		CTRL_SLEDIT,
		WS_VISIBLE | WS_TABSTOP | WS_BORDER | SS_NOTIFY,
		10, 40, 130, 20,
		IDC_CHAR,
		NULL,
		0
	},
	{
		CTRL_SLEDIT,
		WS_VISIBLE | WS_TABSTOP | WS_BORDER | SS_NOTIFY,
		10, 100, 130, 20,
		IDC_CHAR1,
		NULL,
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		220, 160, 70, 25,
		IDC_RETURN1,
		MSG_RETURN,
		0
	}
};

static void my2_proc (HWND hwnd, int id, int nc, DWORD add_data)
{
	SendMessage(GetDlgItem(hwindowDlg, IDC_CHAR), LB_RESETCONTENT, 0, 0);
}

static void add_phone(HWND hDlg)
{
	GetWindowText(GetDlgItem(hDlg, IDC_CHAR), buff1, sizeof(buff1));
	GetWindowText(GetDlgItem(hDlg, IDC_CHAR1), buff2, sizeof(buff2));
	strcat(buff1, ":");
	strcat(buff1, buff2);
	SendMessage(GetDlgItem(hwindowDlg, IDC_CHAR2), LB_ADDSTRING, 0, (LPARAM)buff1);
}

static int InputCharDialogBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
//    static PLOGFONT my_font;
	HWND hwnd1, hwnd2;
	switch (message) {
	case MSG_INITDIALOG:
		hwnd1 = CreateWindow(CTRL_BUTTON, MSG_ADD,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_ADD, 30, 160, 70, 25, hDlg, 0);

		hwnd2 = CreateWindow(CTRL_BUTTON, MSG_DELECT,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_DEL1, 125, 160, 70, 25, hDlg, 0);

	case MSG_COMMAND:
		switch (wParam) {
		case IDC_ADD:
			add_phone(hDlg);
			break;
		case IDC_DEL1:
			SetWindowText(GetDlgItem(hDlg, IDC_CHAR), "");
			SetWindowText(GetDlgItem(hDlg, IDC_CHAR1), "");
			break;
		case IDC_RETURN1:
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

void Add(HWND hWnd)
{
	DlgBoxInputChar.controls = CtrlInputChar;
	DialogBoxIndirectParam(&DlgBoxInputChar, hWnd, InputCharDialogBoxProc, 0L);

}

