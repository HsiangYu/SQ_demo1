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
#define IDC_YJDHBACK       501
#define IDC_YJDHDEL        502
#define IDC_YJDHSAVE       503
#define IDC_YJDHFSDX       504
#define IDC_YJDHBD         505
#define IDC_YJDHJTK        506
#define IDC_YJDHLBK        507

pthread_t th_received;
int       received_index;

CTRLDATA Receivedcalls[] =
{
	{
		"button",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		230, 140, 80, 30,
		IDC_YJDHBACK,
		MSG_RETURN,
		0
	},
	{
		"button",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		230, 50, 80, 30,
		IDC_YJDHDEL,
		MSG_DELECT,
		0
	},
	{
		"button",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		230, 95, 80, 30,
		IDC_YJDHSAVE,
		MSG_SAVE,
		0
	},

	/*{
		"button",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		230, 40, 80, 30,
		IDC_YJDHFSDX,
		"µo°eµu«H",
		0
	   },*/
	{
		"button",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		230, 3, 80, 30,
		IDC_YJDHBD,
		MSG_CALL,
		0
	},
	{
		CTRL_STATIC,
		WS_CHILD | SS_GROUPBOX | WS_VISIBLE,
		5, 5, 215, 185,
		IDC_YJDHJTK,
		MSG_RECEIVED_CALLS,
		0
	},
	{
		CTRL_LISTBOX,
		WS_VISIBLE | WS_VSCROLL | WS_BORDER | LBS_NOTIFY,
		9, 25, 206, 160,
		IDC_YJDHLBK,
		"",
		0
	}
};

DLGTEMPLATE Received =
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

static void received_notif_proc(HWND hWnd, int id, int nc, DWORD add_data)
{
	switch (nc) {
	case LBN_CLICKED:
	{

		received_index = SendMessage(GetDlgItem(hWnd, IDC_YJDHLBK), LB_GETCURSEL, 0, 0);

	}
	}
}

/*******************************************************************************/

static int ReceivedWinProc(HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
	int j;
	int len;
	CL  receivedcall[20];
	switch (message) {
	case MSG_INITDIALOG:
		records_read(FILE_RECEIVED_CALLS_DAT, receivedcall);
		SetNotificationCallback(GetDlgItem(hDlg, IDC_YJDHLBK), received_notif_proc);
		for (j = 0; j < records_count; j++) {
			SendMessage(GetDlgItem(hDlg, IDC_YJDHLBK), LB_INSERTSTRING, j, (LPARAM)receivedcall[j].Phone_num);
		}
		return 0;

	case MSG_COMMAND:
	{
		switch (wParam)	{
		//µo°eµu«H
		case IDC_YJDHFSDX:
			return 0;

		//¼·¥´«ö¶s
		case IDC_YJDHBD:
			strcpy(PhoneNumt, receivedcall[received_index].Phone_num);
			pthread_create(&th_received, NULL, (void *)Holding, NULL);
			len = strlen(PhoneNumt);
			gprs_call(PhoneNumt, len);
			EndDialog(hDlg, 0);
			return 0;

		//¦sÀx«ö¶s
		case IDC_YJDHSAVE:
			return 0;

		//§R°£«ö¶s
		case IDC_YJDHDEL:
			SendMessage(GetDlgItem(hDlg, IDC_YJDHLBK), LB_DELETESTRING, received_index, 0);
			records_delete(FILE_RECEIVED_CALLS_DAT, receivedcall, received_index, records_count);
			return 0;


		//ªð¦^«ö¶s
		case IDC_YJDHBACK:
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
static void createReceivedwindow(HWND hwnd)
{
	Received.controls = Receivedcalls;

	DialogBoxIndirectParam(&Received, hwnd, ReceivedWinProc, 0L);
}

/*******************************************************************************/

/*
   int MiniGUIMain (int argc, const char* argv[])
   {
 #ifdef _LITE_VERSION
    SetDesktopRect(0, 0, 1024, 768);
 #endif
    createReceived(HWND_DESKTOP);
    MiniGUIExtCleanUp ();
		return 0;
   }

 #ifndef _LITE_VERSION
 #include <minigui/dti.c>
 #endif

 */


