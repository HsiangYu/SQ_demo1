#include <string.h>

//Zhou wanxin

/*
 #include <stdlib.h>


 #include <minigui/common.h>
 #include <minigui/minigui.h>
 #include <minigui/gdi.h>
 #include <minigui/window.h>
 #include <minigui/control.h>
 #include <minigui/mywindows.h>
 #include <minigui/mgext.h>
 */

#include "lang.h"


#define IDC_YBDHBACK       401
#define IDC_YBDHDEL        402
#define IDC_YBDHSAVE       403
#define IDC_YBDHFSDX       404
#define IDC_YBDHBD         405
#define IDC_YBDHJTK        406
#define IDC_YBDHLBK        407
int       Dialed_index;
pthread_t th_dialecall;

CTRLDATA Dialedcalls[] =
{
	{
		"button",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		230, 140, 80, 30,
		IDC_YBDHBACK,
		MSG_RETURN,
		0
	},
	{
		"button",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		230, 50, 80, 30,
		IDC_YBDHDEL,
		MSG_DELECT,
		0
	},
	{
		"button",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		230, 95, 80, 30,
		IDC_YBDHSAVE,
		MSG_SAVE,
		0
	},

	/*{
		"button",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		230, 40, 80, 30,
		IDC_YBDHFSDX,
		"µo°eµu«H",
		0
	   },*/
	{
		"button",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		230, 3, 80, 30,
		IDC_YBDHBD,
		MSG_DIAL,
		0
	},
	{
		CTRL_STATIC,
		WS_CHILD | SS_GROUPBOX | WS_VISIBLE,
		5, 5, 215, 185,
		IDC_YBDHJTK,
		MSG_DIALED_CALLS,
		0
	},
	{
		CTRL_LISTBOX,
		WS_VISIBLE | WS_VSCROLL | WS_BORDER | LBS_NOTIFY,
		9, 25, 206, 160,
		IDC_YBDHLBK,
		"",
		0
	}
};

DLGTEMPLATE Dialed =
{
	WS_VISIBLE | WS_BORDER,
	WS_EX_NONE,
	0, 40, 320, 200,
	"",
	0, 0,
	7, NULL,
	0
};

/*******************************************************************************/

static void Dialedcall_notif_proc(HWND hWnd, int id, int nc, DWORD add_data)
{

	switch (nc) {
	case LBN_CLICKED:
	{
		//MessageBox(0,"","",MB_OK);
		Dialed_index = SendMessage(hWnd, LB_GETCURSEL, 0, 0);
		//printf("%d", Dialed_index);
	}
	}
}

/*******************************************************************************/

static int DialedWinProc(HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{

	int j, len;
	switch (message) {
	case MSG_INITDIALOG:
		records_read(FILE_DIALED_CALL_DAT, Dialedcall);
		//MessageBox(0,"","",MB_OK);
		SetNotificationCallback(GetDlgItem(hDlg, IDC_YBDHLBK), Dialedcall_notif_proc);
		//SetNotificationCallback (GetDlgItem (hDlg, IDC_LBK), note_notif_proc);
		for (j = 0; j < records_count; j++) {
			SendMessage(GetDlgItem(hDlg, IDC_YBDHLBK), LB_INSERTSTRING, j, (LPARAM)Dialedcall[j].Phone_num);
		}
		return 0;

	case MSG_COMMAND:
	{
		switch (wParam)	{
		//¼·¥´«ö¶s
		case IDC_YBDHBD:
			strcpy(PhoneNumt, Dialedcall[Dialed_index].Phone_num);
			pthread_create(&th_dialecall, NULL, (void *)Holding, NULL);
			len = strlen(PhoneNumt);
			gprs_call(PhoneNumt, len);
			EndDialog(hDlg, 0);
			return 0;

		//¦sÀx«ö¶s
		case IDC_YBDHSAVE:
			return 0;

		//µo°eµu«H«ö¶s
		case IDC_YBDHFSDX:
			return 0;

		//§R°£«ö¶s
		case IDC_YBDHDEL:
			records_delete(FILE_DIALED_CALL_DAT, Dialedcall, Dialed_index, records_count);
			records_count--;
			SendMessage(GetDlgItem(hDlg, IDC_YBDHLBK), LB_DELETESTRING, Dialed_index, 0);

			return 0;
		//ªð¦^«ö¶s
		case IDC_YBDHBACK:
			EndDialog(hDlg, 0);
			return 0;
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
static void createDialedwindow(HWND hwnd)
{
	Dialed.controls = Dialedcalls;

	DialogBoxIndirectParam(&Dialed, hwnd, DialedWinProc, 0L);
}

/*******************************************************************************/

/*
   int MiniGUIMain (int argc, const char* argv[])
   {
 #ifdef _LITE_VERSION
    SetDesktopRect(0, 0, 1024, 768);
 #endif
    createDialed(HWND_DESKTOP);
    MiniGUIExtCleanUp ();
		return 0;
   }

 #ifndef _LITE_VERSION
 #include <minigui/dti.c>
 #endif
 */



