#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "minigui/common.h"
#include "minigui/minigui.h"
#include "minigui/gdi.h"
#include "minigui/window.h"
#include "minigui/control.h"
//#include <minigui/mgext.h>
#include "pda.h"

#define	true              1
#define	false             0


#define	IDC_TIP           140
#define	IDC_TIP1          141
#define	IDC_TIP2          142
#define	IDC_TIP3          143
#define	IDC_INPUT         144
#define	IDC_INPUT1        145
#define	IDC_INPUT2        146
#define	IDL_BOX           147
#define	IDC_INSERT        148
#define	IDC_INSERT1       149
#define	IDC_RET           150
#define	IDC_CLOCK         153
#define	_ID_TIMER1        155

static const char * box[] =
{
	MSG_ON,
	MSG_OFF,
};

extern S s1;

static int AlarmDialogProc(HWND	hcwd, int message, WPARAM wParam, LPARAM lParam)
{
	FILE      * fp;
	HDC       hdc;
	RECT      rc;
	HWND      hc;
	HWND      hDlg;
	int       num1, num2, num3;
	struct tm *ptime;
	time_t    now;
	char      buffer1[5];
	char      buffer2[5];
	char      buffer3[5];
	char      buffer4[5];
	char      buff1[50];
	switch (message) {
	case MSG_CREATE:

		SetTimer(hcwd, _ID_TIMER1, 100);
		CreateWindow(CTRL_STATIC, MSG_HOUR, WS_VISIBLE | ES_CENTER, IDC_TIP,
			     10, 10, 50, 20, hcwd, 0);
		CreateWindow(CTRL_STATIC, MSG_MINUTE, WS_VISIBLE | ES_CENTER, IDC_TIP1,
			     10, 40, 50, 20, hcwd, 0);
		CreateWindow(CTRL_STATIC, MSG_SECORD, WS_VISIBLE | ES_CENTER, IDC_TIP2,
			     10, 70, 50, 20, hcwd, 0);
		CreateWindow(CTRL_STATIC, MSG_STATUS, WS_VISIBLE | ES_CENTER, IDC_TIP3,
			     10, 100, 50, 20, hcwd, 0);
		hc = CreateWindow(CTRL_COMBOBOX, "", WS_VISIBLE | CBS_DROPDOWNLIST | CBS_NOTIFY, IDL_BOX,
				  70, 100, 200, 20, hcwd, 40);

		SendMessage(hc, CB_ADDSTRING, 0, (LPARAM)box[0]);
		SendMessage(hc, CB_ADDSTRING, 0, (LPARAM)box[1]);

		CreateWindow(CTRL_SLEDIT, "", WS_VISIBLE | WS_BORDER, IDC_INPUT,
			     70, 10, 200, 20, hcwd, 0);
		SendMessage(GetDlgItem(hcwd, IDC_INPUT), EM_LIMITTEXT, 2, 0L);
		CreateWindow(CTRL_SLEDIT, "", WS_VISIBLE | WS_BORDER, IDC_INPUT1,
			     70, 40, 200, 20, hcwd, 0);
		SendMessage(GetDlgItem(hcwd, IDC_INPUT1), EM_LIMITTEXT, 2, 0L);
		CreateWindow(CTRL_SLEDIT, "", WS_VISIBLE | WS_BORDER, IDC_INPUT2,
			     70, 70, 200, 20, hcwd, 0);
		SendMessage(GetDlgItem(hcwd, IDC_INPUT2), EM_LIMITTEXT, 2, 0L);
		CreateWindow(CTRL_BUTTON, MSG_SET_ALARM_CLOCK, WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_INSERT,
			     30, 150, 90, 30, hcwd, 0);
		CreateWindow(CTRL_BUTTON, MSG_CANCEL, WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_RET,
			     160, 150, 90, 30, hcwd, 0);
		CreateWindow(CTRL_BUTTON, MSG_SOFT_DISK, WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_INSERT1,
			     250, 190, 60, 30, hcwd, 0);
		CreateWindow(CTRL_SLEDIT, "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, IDC_CLOCK,
			     20, 190, 190, 25, hcwd, 0);

		return 0;

	case MSG_TIMER:
	{
		if (wParam == _ID_TIMER1) {
			time(&now);
			ptime =	localtime(&now);
			sprintf(buff1, MSG_DISPLAY_TIME,
				ptime->tm_year + 1900, ptime->tm_mon + 1, ptime->tm_mday,
				ptime->tm_hour, ptime->tm_min, ptime->tm_sec);
			SendMessage(GetDlgItem(hcwd, IDC_CLOCK), MSG_SETTEXT, 0, (LPARAM)buff1);
		}
	}
	break;

	case MSG_COMMAND:
	{
		switch (wParam)	{
		case IDC_INSERT:
			GetWindowText(GetDlgItem(hcwd, IDC_INPUT), buffer1, 5);
			num1 = atoi(buffer1);
			GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, 5);
			num2 = atoi(buffer2);
			GetWindowText(GetDlgItem(hcwd, IDC_INPUT2), buffer3, 5);
			num3 = atoi(buffer3);
			if (num1 > 24 || num2 > 60 || num3 > 60) {
				MessageBox(hcwd, MSG_ILLEGAL_SET, MSG_INDICATION, MB_OK);
			} else{
				MessageBox(hcwd, MSG_SET_OK, MSG_INDICATION, MB_OK);
			}

			GetWindowText(GetDlgItem(hcwd, IDC_INPUT), s1.hour, 5);
			GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), s1.minute, 5);
			GetWindowText(GetDlgItem(hcwd, IDC_INPUT2), s1.second, 5);
			GetWindowText(GetDlgItem(hcwd, IDL_BOX), s1.change, 5);

			fp = fopen("clockset", "w");
			if (fp == NULL)	{
				MessageBox(hcwd, MSG_CREAT_FILE_ERROR, "error", MB_OK | MB_ICONEXCLAMATION);
			} else	{
				fwrite(&s1, sizeof(S), 1, fp);
			}
			fclose(fp);
			return 0;

		case IDC_RET:
			KillTimer(hcwd, _ID_TIMER1);

			DestroyAllControls(hcwd);
			DestroyMainWindow(hcwd);
			PostQuitMessage(hcwd);
			return 0;
		}
	}
	break;


	case MSG_CLOSE:
		KillTimer(hcwd, _ID_TIMER1);

		DestroyAllControls(hcwd);
		DestroyMainWindow(hcwd);
		PostQuitMessage(hcwd);
		return 0;
	}
	return DefaultMainWinProc(hcwd, message, wParam, lParam);
}

int CreateAlarmDialog(HWND hWnd)
{
	MSG           Msg;
	HWND          hcwd;
	MAINWINCREATE CreateInfo;
#ifdef _LITE_VERSION
	SetDesktopRect(0, 0, 1024, 768);
#endif
	CreateInfo.dwStyle        = WS_VISIBLE | WS_BORDER | WS_CAPTION;
	CreateInfo.dwExStyle      = WS_EX_NONE;
	CreateInfo.spCaption      = MSG_ALARM_CLOCK;
	CreateInfo.hMenu          = 0;
	CreateInfo.hCursor        = GetSystemCursor(0);
	CreateInfo.hIcon          = 0;
	CreateInfo.MainWindowProc = AlarmDialogProc;
	CreateInfo.lx             = 0;
	CreateInfo.ty             = 0;

	CreateInfo.rx        = 320;
	CreateInfo.by        = 240;
	CreateInfo.iBkColor  = COLOR_lightwhite;
	CreateInfo.dwAddData = 0;
	CreateInfo.hHosting  = hWnd;

	hcwd = CreateMainWindow(&CreateInfo);

	ShowWindow(hcwd, SW_SHOWNORMAL);

	while (GetMessage(&Msg, hcwd)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	MainWindowThreadCleanup(hcwd);
	return 0;
}

