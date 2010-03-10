#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
//#include <minigui/mywindows.h>
//#include <minigui/mgext.h>
#include "phoneseting.h"

#include "lang.h"

#define IDC_TIMESET	   500
#define IDC_HELLOSET	   501
#define IDC_PHONERET	   503
#define IDC_SETBACK	   504
static DLGTEMPLATE PhoneSetData =
{
	WS_BORDER, //| WS_CAPTION,
	WS_EX_NONE,
	0, 40, 320, 200,
	MSG_PHONE_SET,
	0, 0,
	3, NULL,
	0
};

static CTRLDATA phonesetData[] =
{
	{
		CTRL_BUTTON,
		WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP | WS_GROUP,
		0, 0, 320, 40,
		IDC_TIMESET,
		MSG_PHONE_SET1,
		0
	},
	{
		CTRL_BUTTON,
		WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP | WS_GROUP,
		0, 40, 320, 40,
		IDC_HELLOSET,
		MSG_PHONE_SET2,
		0
	},

	{
		CTRL_BUTTON,
		WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP | WS_GROUP,
		160, 160, 70, 25,
		IDC_SETBACK,
		MSG_RETURN,
		0
	},
};

static int phone_setProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
	int i;
	switch (message) {
	case MSG_INITDIALOG:
		return 0;

	case MSG_COMMAND:
	{
		switch (wParam)	{
		case IDC_SETBACK:
			EndDialog(hDlg, 0);
			return 0;
		case IDC_TIMESET:
			timeset(hDlg);
			return 0;
		case IDC_HELLOSET:
			salutation(hDlg);
			return 0;

		}
	}
	break;

	case MSG_CLOSE:
	{
		EndDialog(hDlg, wParam);
	}
		return 0;
	}
	return DefaultDialogProc(hDlg, message, wParam, lParam);
}

int phone_set(HWND hWnd)
{


	PhoneSetData.controls = phonesetData;

	DialogBoxIndirectParam(&PhoneSetData, hWnd, phone_setProc, 0L);
	return 0;
}

