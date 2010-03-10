/*
 #include <stdlib.h>
 #include <minigui/common.h>
 #include <minigui/minigui.h>
 #include <minigui/gdi.h>
 #include <minigui/window.h>
 #include <minigui/control.h>
 #include <minigui/mywindows.h>
 #include <minigui/mgext.h>

 #ifndef _LITE_VERSION
 #include <minigui/dti.c>
 #endif
 */

#include "lang.h"


#define IDC_BUTTEN331       331
#define IDC_BUTTEN332       332
#define IDC_BUTTEN333       333
#define IDC_BUTTEN334       334
#define IDC_BUTTEN335       335
#define IDC_BUTTEN336       336

static DLGTEMPLATE DeleteInitProgress =
{
	WS_BORDER,
	WS_EX_NONE,
	0, 40, 320, 200,
	"",
	0, 0,
	5, NULL,
	0
};

static CTRLDATA deleteallProgress [] =
{
	{
		"button", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 216, 130, 90, 30, IDC_BUTTEN332, MSG_RETURN, 0
	},

	{
		"button", WS_CHILD | BS_AUTO3STATE | WS_VISIBLE, 0, 30, 180, 30, IDC_BUTTEN333, MSG_MISSED_CALL, 0
	},

	{
		"button", WS_CHILD | BS_AUTO3STATE | WS_VISIBLE, 0, 60, 180, 30, IDC_BUTTEN334, MSG_RECEIVED_CALLS, 0
	},

	{
		"button", WS_CHILD | BS_AUTO3STATE | WS_VISIBLE, 0, 90, 180, 30, IDC_BUTTEN335, MSG_DIALED_CALLS, 0
	},

	{
		"button", WS_CHILD | BS_AUTO3STATE | WS_VISIBLE, 0, 120, 180, 30, IDC_BUTTEN336, MSG_DELETE_ALL, 0
	},
};

static int DeleteBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case MSG_INITDIALOG:

		return 0;

	case MSG_COMMAND:
	{
		switch (wParam)	{
		case IDC_BUTTEN331:

			return 0;
		case IDC_BUTTEN332:

			EndDialog(hDlg, wParam);
			return 0;

		case IDC_BUTTEN333:

			return 0;
		case IDC_BUTTEN334:

			return 0;
		case IDC_BUTTEN335:

			return 0;

		case IDC_BUTTEN336:

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

static void deleteallnumber(HWND hDlg)
{
	//制定對話框模版
	DeleteInitProgress.controls = deleteallProgress;

	DialogBoxIndirectParam(&DeleteInitProgress, hDlg, DeleteBoxProc, 0L);
}

/*
   //測試所用

   int MiniGUIMain (int argc, const char* argv[])
   {


    deleteallnumber(HWND_DESKTOP);

    return 0;
   }

 */
