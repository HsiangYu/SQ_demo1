
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
		"�o�e�u�H",
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
//�^�ը��
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
		//Ū����󤤹q�ܰO��
		records_read(FULLPATH, missedcall);
		//�]�m�^�ը��
		SetNotificationCallback(GetDlgItem(hDlg, IDC_WJLDLBK), missedcall_notif_proc);
		//�V�C��ؤ��K�[����
		for (j = 0; j < records_count; j++) {
			SendMessage(GetDlgItem(hDlg, IDC_WJLDLBK), LB_INSERTSTRING, j, (LPARAM)missedcall[j].Phone_num);
		}
		return 0;

	case MSG_COMMAND:
	{
		switch (wParam)	{
		// �������s�A�N�襤���q�ܬ������q�ܩI�s�X�h
		case IDC_WJLDBD:
			strcpy(PhoneNumt, missedcall[missed_index].Phone_num);
			pthread_create(&th_missed, NULL, (void *)Holding, NULL);
			len = strlen(PhoneNumt);
			gprs_call(PhoneNumt, len);
			EndDialog(hDlg, 0);
			return 0;


		//�s�x���s �A�N�q�ܬ����s�x��q�ܥ���
		case IDC_WJLDSAVE:

			return 0;

		//�o�u�H���s
		case IDC_WJLDFSDX:

			return 0;

		// �R�����s
		case IDC_WJLDDEL:
			//�V�C��ؤ��o�e�����A�R���C��ؤ�missed_index ���ޭȪ�����
			SendMessage(GetDlgItem(hDlg, IDC_WJLDLBK), LB_DELETESTRING, missed_index, 0);
			//�R����󤤹������ޭȪ����e�A�N���^�g��FULLPATH���w�����
			records_delete(FULLPATH, missedcall, missed_index, records_count);
			return 0;

		//��^���s
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


