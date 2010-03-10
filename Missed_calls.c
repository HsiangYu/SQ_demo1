
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
#define IDC_WJLDBACK       301
#define IDC_WJLDDEL        302
#define IDC_WJLDSAVE       303
#define IDC_WJLDFSDX       304
#define IDC_WJLDBD         305
#define IDC_WJLDJTK        306
#define IDC_WJLDLBK        307

#define FULLPATH           FILE_MISSED_CALL_DAT
pthread_t th_missed;
int       missed_index;

CTRLDATA Missedcalls[] =
{
	{
		"button",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		230, 140, 80, 30,
		IDC_WJLDBACK,
		MSG_RETURN,
		0
	},
	{
		"button",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		230, 50, 80, 30,
		IDC_WJLDDEL,
		MSG_DELECT,
		0
	},
	{
		"button",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		230, 95, 80, 30,
		IDC_WJLDSAVE,
		MSG_SAVE,
		0
	},

	/*{
		"button",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		230, 40, 80, 30,
		IDC_WJLDFSDX,
		"發送短信",
		0
	   },*/
	{
		"button",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		230, 3, 80, 30,
		IDC_WJLDBD,
		MSG_DIAL,
		0
	},
	{
		CTRL_STATIC,
		WS_CHILD | SS_GROUPBOX | WS_VISIBLE,
		5, 5, 215, 185,
		IDC_WJLDJTK,
		MSG_MISSED_CALL,
		0
	},
	{
		CTRL_LISTBOX,
		WS_VISIBLE | WS_VSCROLL | WS_BORDER | LBS_NOTIFY,
		9, 25, 206, 160,
		IDC_WJLDLBK,
		"",
		0
	}
};

DLGTEMPLATE Missed =
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
//回調函數
static void missedcall_notif_proc(HWND hWnd, int id, int nc, DWORD add_data)
{
	switch (nc) {
	case LBN_CLICKED:
	{

		missed_index = SendMessage(hWnd, LB_GETCURSEL, 0, 0);

	}
	}
}

/*******************************************************************************/

static int MissedWinProc(HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
	int j;
	int len;
	switch (message) {
	case MSG_INITDIALOG:
		//讀取文件中電話記錄
		records_read(FULLPATH, missedcall);
		//設置回調函數
		SetNotificationCallback(GetDlgItem(hDlg, IDC_WJLDLBK), missedcall_notif_proc);
		//向列表框中添加條目
		for (j = 0; j < records_count; j++) {
			SendMessage(GetDlgItem(hDlg, IDC_WJLDLBK), LB_INSERTSTRING, j, (LPARAM)missedcall[j].Phone_num);
		}
		return 0;

	case MSG_COMMAND:
	{
		switch (wParam)	{
		// 撥打按鈕，將選中的電話紀錄中電話呼叫出去
		case IDC_WJLDBD:
			strcpy(PhoneNumt, missedcall[missed_index].Phone_num);
			pthread_create(&th_missed, NULL, (void *)Holding, NULL);
			len = strlen(PhoneNumt);
			gprs_call(PhoneNumt, len);
			EndDialog(hDlg, 0);
			return 0;


		//存儲按鈕 ，將電話紀錄存儲到電話本中
		case IDC_WJLDSAVE:

			return 0;

		//發短信按鈕
		case IDC_WJLDFSDX:

			return 0;

		// 刪除按鈕
		case IDC_WJLDDEL:
			//向列表框中發送消息，刪除列表框中missed_index 索引值的條目
			SendMessage(GetDlgItem(hDlg, IDC_WJLDLBK), LB_DELETESTRING, missed_index, 0);
			//刪除文件中對應索引值的內容，將文件回寫到FULLPATH指定的文件
			records_delete(FULLPATH, missedcall, missed_index, records_count);
			return 0;

		//返回按鈕
		case IDC_WJLDBACK:
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
static void Missedcallwindow(HWND hwnd)
{
	Missed.controls = Missedcalls;

	DialogBoxIndirectParam(&Missed, hwnd, MissedWinProc, 0L);
}

/*******************************************************************************/

/*
   int MiniGUIMain (int argc, const char* argv[])
   {
 #ifdef _LITE_VERSION
    SetDesktopRect(0, 0, 1024, 768);
 #endif
    createMissed(HWND_DESKTOP);
    MiniGUIExtCleanUp ();
		return 0;
   }

 #ifndef _LITE_VERSION
 #include <minigui/dti.c>
 #endif

 */


