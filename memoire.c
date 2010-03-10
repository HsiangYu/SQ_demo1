#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <popt.h>
#include <unistd.h>
#include <stdio.h>


#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
//#include <minigui/mywindows.h>
#include <minigui/control.h>
//#include <minigui/mgext.h>

#include "memoire.h"
#include "mini133.h"

static FILE * fp;
static int edit();
static int  index1;
static char buffer[900];
static char times[100];
HWND        hcwd;
HWND        ExhWnd;
#define MSG_REPAINT       100
#define IDL_DELETE1       101
static int itemCount = 0;



static DLGTEMPLATE DlgcrFiles =
{
	WS_VISIBLE | WS_BORDER | WS_CAPTION,
	WS_EX_NONE,
	0, 0, 320, 240,
	"memoire",
	0, 0,
	4, NULL,
	0
};
static CTRLDATA CtrlcrFiles[] =
{
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		100, 190, 60, 25,
		IDC_SAVE1,
		"save",
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		190, 195, 70, 20,
		IDC_RET3,
		"return",
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		0, 195, 70, 20,
		IDC_ADDTIME1,
		"addtime",
		0
	},
	{
		"mledit",
		WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | SVS_AUTOSORT | WS_TABSTOP,
		0, 0, 320, 190,
		IDC_LIST3,
		"",
		0
	},
};

static int CreatWinProc(HWND CrhWnd, int message, WPARAM wParam, LPARAM lParam)
{
	struct tm * ptime;
	time_t    now;



	switch (message) {


	case MSG_COMMAND:
		switch (wParam)	{
		case IDC_ADDTIME1:

			fp = fopen("a.txt", "a+");
			SendMessage(GetDlgItem(CrhWnd, IDC_LIST3), MSG_GETTEXT, 100, (LPARAM)buffer);
			time(&now);
			ptime = localtime(&now);
			sprintf(times, "%dYear %dMonth %dDay / %dHout %dMinute %dSecond" /*"%d年%d月%d日 %d時%d分%d秒"*/, ptime->tm_year + 1900, ptime->tm_mon + 1, ptime->tm_mday, ptime->tm_hour, ptime->tm_min, ptime->tm_sec);

			strcat(buffer, times);
			memset(times, 0, 100);
			SendMessage(GetDlgItem(CrhWnd, IDC_LIST3), MSG_SETTEXT, sizeof(buffer), (LPARAM)buffer);
			fclose(fp);
			break;
		case IDC_SAVE1:
			fp = fopen("a.txt", "a+");
			SendMessage(GetDlgItem(CrhWnd, IDC_LIST3), MSG_GETTEXT, 100, (LPARAM)buffer);
			fwrite(buffer, 900, 1, fp);
			fclose(fp);
			SendMessage(hcwd, MSG_REPAINT, 0, 0);
			EndDialog(CrhWnd, wParam);
			break;
		case	IDC_RET3:
			memset(buffer, 0, 900);
			EndDialog(CrhWnd, 0);


			break;
		}
		break;



	case MSG_CLOSE:

		EndDialog(CrhWnd, 0);
		return 0;
	}


	return DefaultDialogProc(CrhWnd, message, wParam, lParam);
}

static int create (HWND CrhWnd)
{
	DlgcrFiles.controls = CtrlcrFiles;
	DialogBoxIndirectParam(&DlgcrFiles,  CrhWnd, CreatWinProc, 0L);
}

static DLGTEMPLATE DlgedFiles =
{
	WS_VISIBLE | WS_BORDER | WS_CAPTION,
	WS_EX_NONE,
	0, 0, 320, 240,
	"memoire",
	0, 0,
	4, NULL,
	0
};
static CTRLDATA CtrledFiles[] =
{
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		100, 190, 60, 25,
		IDC_SAVE,
		"save",
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		190, 195, 70, 20,
		IDC_RET2,
		"return",
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		0, 195, 70, 20,
		IDC_ADDTIME,
		"addtime",
		0
	},
	{
		"mledit",
		WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | SVS_AUTOSORT | WS_TABSTOP,
		0, 0, 320, 190,
		IDC_LIST2,
		"",
		0
	},
};



static int EditWinProc(HWND EdhWnd, int message, WPARAM wParam, LPARAM lParam)
{
	struct tm * ptime;
	time_t    now;
	switch (message) {
	case MSG_INITDIALOG:
		SendMessage(GetDlgItem(EdhWnd, IDC_LIST2), MSG_SETTEXT, 900, (LPARAM)buffer);
		return 1;

	case MSG_COMMAND:
		switch (wParam)	{
		case IDC_ADDTIME:

			fp = fopen("a.txt", "a+");
			SendMessage(GetDlgItem(EdhWnd, IDC_LIST2), MSG_GETTEXT, 100, (LPARAM)buffer);
			time(&now);
			ptime = localtime(&now);
			sprintf(times, "%dYear %dMonth %dDay / %dHout %dMinute %dSecond" /*"%d年%d月%d日 %d時%d分%d秒"*/, ptime->tm_year + 1900, ptime->tm_mon + 1, ptime->tm_mday, ptime->tm_hour, ptime->tm_min, ptime->tm_sec);
			strcat(buffer, times);
			memset(times, 0, 100);
			SendMessage(GetDlgItem(EdhWnd, IDC_LIST2), MSG_SETTEXT, sizeof(buffer), (LPARAM)buffer);
			fclose(fp);
			break;
		case  IDC_SAVE:
			SendMessage(hcwd, IDL_DELETE1, 0, 0);
			fp = fopen("a.txt", "a+");
			SendMessage(GetDlgItem(EdhWnd, IDC_LIST2), MSG_GETTEXT, 100, (LPARAM)buffer);
			fwrite(buffer, 900, 1, fp);
			fclose(fp);

			SendMessage(hcwd, MSG_REPAINT, 0, 0);
			EndDialog(EdhWnd, wParam);
			break;
		case	IDC_RET2:

			EndDialog(EdhWnd, 0);
			break;
		}
		break;



	case MSG_CLOSE:
		EndDialog(EdhWnd, 0);
		return 0;
	}


	return DefaultDialogProc(EdhWnd, message, wParam, lParam);
}

static int edit (HWND EdhWnd)
{
	DlgedFiles.controls = CtrledFiles;
	DialogBoxIndirectParam(&DlgedFiles,  EdhWnd, EditWinProc, 0L);
}

static DLGTEMPLATE DlgexaFiles =
{
	WS_VISIBLE | WS_BORDER | WS_CAPTION,
	WS_EX_NONE,
	0, 0, 320, 240,
	"memoire",
	0, 0,
	4, NULL,
	0
};
static CTRLDATA CtrlexaFiles[] =
{
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		0, 195, 70, 20,
		IDC_DELETE1,
		"delete",
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		100, 190, 60, 25,
		IDC_EXAMINE,
		"edit",
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		190, 195, 70, 20,
		IDC_RET1,
		"return",
		0
	},

	{
		"mledit",
		WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | SVS_AUTOSORT,
		0, 0, 320, 190,
		IDC_LIST1,
		"",
		0
	},
};


static int ExamineWinProc(HWND ExhWnd, int message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {

	case MSG_INITDIALOG:
		SendMessage(GetDlgItem(ExhWnd, IDC_LIST1), EM_SETREADONLY, 1, 0);
		SendMessage(GetDlgItem(ExhWnd, IDC_LIST1), MSG_SETTEXT, sizeof(buffer), (LPARAM)buffer);
		return 1;

	case MSG_COMMAND:
		switch (wParam)	{
		case IDC_EXAMINE:
			edit(ExhWnd);
			EndDialog(ExhWnd, 0);
			break;

		case IDC_DELETE1:
			SendMessage(hcwd, IDL_DELETE1, 0, 0);
			EndDialog(ExhWnd, 0);
			break;


		case IDC_RET1:

			EndDialog(ExhWnd, 0);

			return 0;
		}
		break;

	case MSG_CLOSE:
		EndDialog(ExhWnd, 0);

		return 0;
	}

	return DefaultDialogProc(ExhWnd, message, wParam, lParam);
}

static void examine (HWND ExhWnd)
{
	DlgexaFiles.controls = CtrlexaFiles;
	DialogBoxIndirectParam(&DlgexaFiles, ExhWnd, ExamineWinProc, 0L);
}

static void ReadForList(HWND hWnd)
{
	LISTBOXITEMINFO lbii;
	int             i;
	itemCount = SendDlgItemMessage(hWnd, IDC_LIST, LB_GETCOUNT, 0, (LPARAM)0);
	for (i = 0; i < itemCount; i++) {
		SendDlgItemMessage(hWnd, IDC_LIST, LB_DELETESTRING, i, (LPARAM)0);
	}
	fp = fopen("a.txt", "r");
	for (i = 0; !feof(fp); i++) {
		fread(buffer, 900, 1, fp);
		lbii.string = buffer;
		lbii.cmFlag = CMFLAG_BLANK;
		lbii.hIcon  = 0;
		SendDlgItemMessage(hWnd, IDC_LIST, LB_ADDSTRING, 0, (LPARAM)lbii.string);
	}
	SendDlgItemMessage(hWnd, IDC_LIST, LB_DELETESTRING, i, (LPARAM)0);
	fclose(fp);
}

static int ListWinProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
	HWND hCode;
	int  i = 0;
	int  j = 0;
	switch (message) {
	case MSG_CREATE:
		CreateWindow(CTRL_BUTTON,
			     "edit",
			     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			     IDC_EDIT,
			     0, 0, 60, 25,
			     hWnd,

			     0);
		CreateWindow(CTRL_BUTTON,
			     "delete",
			     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			     IDC_DELETE,
			     60, 0, 60, 25,
			     hWnd,

			     0);
		CreateWindow(CTRL_BUTTON,
			     "clear",
			     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			     IDC_CLEAR,
			     120, 0, 60, 25,
			     hWnd,

			     0);


		CreateWindow(CTRL_BUTTON,
			     "examine",
			     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			     IDC_OPEN,
			     100, 190, 60, 25,
			     hWnd,

			     0);
		CreateWindow(CTRL_BUTTON,
			     "new",
			     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			     IDC_CREATE,
			     0, 195, 70, 20,
			     hWnd,

			     0);
		CreateWindow(CTRL_BUTTON,
			     "cancel",
			     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			     IDC_RET,
			     190, 195, 70, 20,
			     hWnd,

			     0);
		CreateWindow(CTRL_LISTBOX,
			     "",
			     WS_VISIBLE | WS_VSCROLL | WS_BORDER | LBS_NOTIFY,
			     IDC_LIST,
			     0, 25, 320, 165,
			     hWnd,


			     0);

		ReadForList(hWnd);


		break;

	case MSG_REPAINT:
		ReadForList(hWnd);
		break;

	case IDL_DELETE1:
		index1 = SendMessage(GetDlgItem(hWnd, IDC_LIST), LB_GETCURSEL, 0, 0);
		SendMessage(GetDlgItem(hWnd, IDC_LIST), LB_DELETESTRING, index1, 0);
		itemCount = SendDlgItemMessage(hWnd, IDC_LIST, LB_GETCOUNT, 0, (LPARAM)0);
		fp        = fopen("a.txt", "w");
		for (i = 0; i < itemCount; i++) {
			SendDlgItemMessage(hWnd, IDC_LIST, LB_GETTEXT, i, (LPARAM)buffer);
			fwrite(buffer, 900, 1, fp);
		}
		fclose(fp);
		break;

	case MSG_COMMAND:
		switch (wParam)	{
		case IDC_CREATE:

			memset(buffer, 0, 900);
			memset(times, 0, 100);
			create(hWnd);
			break;

		case IDC_EDIT:
			index1 = SendMessage(GetDlgItem(hWnd, IDC_LIST), LB_GETCURSEL, 0, 0);
			SendMessage(GetDlgItem(hWnd, IDC_LIST), LB_GETTEXT, index1, (LPARAM)buffer);
			edit(hWnd);
			break;


		case IDC_DELETE:
			index1 = SendMessage(GetDlgItem(hWnd, IDC_LIST), LB_GETCURSEL, 0, 0);
			SendMessage(GetDlgItem(hWnd, IDC_LIST), LB_DELETESTRING, index1, 0);
			itemCount = SendDlgItemMessage(hWnd, IDC_LIST, LB_GETCOUNT, 0, (LPARAM)0);
			fp        = fopen("a.txt", "w");
			for (i = 0; i < itemCount; i++) {
				SendDlgItemMessage(hWnd, IDC_LIST, LB_GETTEXT, i, (LPARAM)buffer);
				fwrite(buffer, 900, 1, fp);
			}
			fclose(fp);

			break;


		case IDC_CLEAR:
			SendMessage(GetDlgItem(hWnd, IDC_LIST), LB_RESETCONTENT, 0, 0);

			fp = fopen("a.txt", "w");

			fclose(fp);
			break;


		case IDC_OPEN:

			index1 = SendMessage(GetDlgItem(hWnd, IDC_LIST), LB_GETCURSEL, 0, 0);

			SendMessage(GetDlgItem(hWnd, IDC_LIST), LB_GETTEXT, index1, (LPARAM)buffer);

			examine(hWnd);
			break;

		case IDC_RET:
			DestroyAllControls(hWnd);
			DestroyMainWindow(hWnd);
			PostQuitMessage(hWnd);
			return 0;
		}

		break;

	case MSG_CLOSE:
		DestroyMainWindow(hWnd);
		PostQuitMessage(hWnd);
		return 0;
	}

	return DefaultMainWinProc(hWnd, message, wParam, lParam);
}

int CreateMemoireDialog (HWND hWnd)
{
	MSG           Msg;
	MAINWINCREATE CreateInfo;



	CreateInfo.dwStyle        = WS_VISIBLE | WS_BORDER | WS_CAPTION;
	CreateInfo.dwExStyle      = WS_EX_NONE;
	CreateInfo.spCaption      = MSG_NOTE;
	CreateInfo.hMenu          = 0;
	CreateInfo.hCursor        = GetSystemCursor(IDC_ARROW);
	CreateInfo.hIcon          = 0;
	CreateInfo.MainWindowProc = ListWinProc;
	CreateInfo.lx             = 0;
	CreateInfo.ty             = 0;
	CreateInfo.rx             = 320;
	CreateInfo.by             = 240;
	CreateInfo.iBkColor       = GetWindowElementColor(BKC_CONTROL_DEF);
	CreateInfo.dwAddData      = 0;
	CreateInfo.dwReserved     = 0;
	CreateInfo.hHosting       = hWnd;



	hcwd = CreateMainWindow(&CreateInfo);


	ShowWindow(hcwd, SW_SHOWNORMAL);

	while (GetMessage(&Msg, hcwd)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	MainWindowThreadCleanup(hcwd);

	return 0;
}

