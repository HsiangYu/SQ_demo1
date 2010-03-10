#include <stdio.h>
#include <stdlib.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include "hello.h"
#include "lang.h"


static DLGTEMPLATE DlgBoxInputChar =
{
	WS_BORDER | WS_CAPTION,
	WS_EX_NONE,
	150, 50, 150, 110,
	MSG_OK,
	0, 0,
	2, NULL,
	0
};

static CTRLDATA CtrlInputChar [] =
{
	{
		CTRL_STATIC,
		WS_VISIBLE | SS_CENTER,
		20, 5, 100, 40,
		IDC_STATIC,
		MSG_DELECT_CONTACT_PERSONS,
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		85, 40, 45, 30,
		IDC_NO,
		MSG_CANCEL,
		0
	}
};

static void my1_proc (HWND hwnd)
{
	int index1;
	index1 = SendMessage(GetDlgItem(hwindowDlg, IDC_CHAR2), LB_GETCURSEL, 0, 0);
	SendMessage(GetDlgItem(hwindowDlg, IDC_CHAR2), LB_DELETESTRING, index1, 0);
}

static int InputCharDialogBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
	HWND hwnd1;
	switch (message) {
	case MSG_INITDIALOG:
		hwnd1 = CreateWindow(CTRL_BUTTON, MSG_ACCEPT,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_YES, 10, 40, 45, 30, hDlg, 0);
		break;

	case MSG_COMMAND:
		switch (wParam) {
		case IDC_NO:
			EndDialog(hDlg, wParam);
			break;
		case IDC_YES:
			my1_proc(hwindowDlg);
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

void del(void)
{
	DlgBoxInputChar.controls = CtrlInputChar;
	DialogBoxIndirectParam(&DlgBoxInputChar, hwindowDlg, InputCharDialogBoxProc, 0L);
}

