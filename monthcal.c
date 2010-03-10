/*
** $Id: monthcal.c,v 1.4 2003/11/23 13:09:22 weiym Exp $
**
** monthcal.c: Sample program for MiniGUI Programming Guide
**      Usage of MONTHCALENDAR control.
**
** Copyright (C) 2003 Feynman Software.
**
** License: GPL
*/


#include <stdlib.h>
#include <time.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
//#include <minigui/mywindows.h>
//#include <minigui/mgext.h>
#include "mini133.h"

#include "lang.h"


/** Structure of the system time */
typedef struct _SYSTEMTIME {
	/** Year number of the date */
	int year;
	/** Month number of the date */
	int month;
	/** Day number of the date */
	int day;
	/** Weekday number of the date */
	int weekday;
} SYSTEMTIME;

/**
 * \var typedef SYSTEMTIME *PSYSTEMTIME;
 * \brief Data type of the pointer to a SYSTEMTIME.
 */
typedef SYSTEMTIME *PSYSTEMTIME;
//channing add


#define IDC_MC       100
#define IDC_OK       101



CTRLDATA CtrlTime[] =
{
	{
		"monthcalendar",
		WS_CHILD | WS_VISIBLE | MCS_NOTIFY | MCS_CHN,
		10, 10, 300, 180,
		IDC_MC,
		"",
		0
	},
	{
		"button",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 190, 50, 25,
		IDC_OK,
		MSG_OK,
		0
	}
};

DLGTEMPLATE DlgTime =
{
	WS_VISIBLE | WS_CAPTION | WS_BORDER,
	WS_EX_NONE,
	0, 0, 320, 240,
	"日曆",
	0, 0,
	2, CtrlTime,
	0
};

/*******************************************************************************/

static int TimeWinProc(HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case MSG_INITDIALOG:
		break;

	case MSG_COMMAND:
	{
		int id = LOWORD(wParam);
		if (id == IDC_OK) {
			char       info[100];
			SYSTEMTIME date;
			SendMessage(GetDlgItem(hDlg, IDC_MC), MCM_GETCURDATE, 0, (LPARAM)&date);
			//    sprintf (info, "修改成功 ", date.year, date.month, date.day);
			sprintf(info, " modify ok ", date.year, date.month, date.day);
			MessageBox(hDlg, info, " 完成 ", MB_OK);
			EndDialog(hDlg, 0);
		}
	}
	break;

	case MSG_CLOSE:
	{
		EndDialog(hDlg, 0);
	}
		return 0;
	}

	return DefaultDialogProc(hDlg, message, wParam, lParam);
}

/*******************************************************************************/

int CreateMonthcalDialog (HWND hWnd)
{
#ifdef _LITE_VERSION
	SetDesktopRect(0, 0, 1024, 768);
#endif

	if (!InitMiniGUIExt()) {
		return 2;
	}

	DlgTime.controls = CtrlTime;

	DialogBoxIndirectParam(&DlgTime, HWND_DESKTOP, TimeWinProc, 0L);

	MiniGUIExtCleanUp();

	return 0;
}

