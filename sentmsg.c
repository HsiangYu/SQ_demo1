#include <stdio.h>
#include <stdlib.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include "ecpda.h"
#include "lang.h"

static char msg[1000];
static void delnote (HWND hWnd)
{
	int indexN;
	indexN = SendMessage(GetDlgItem(hwindowDlg, IDN_NCHAR), LB_GETCURSEL, 0, 0);
	SendMessage(GetDlgItem(hwindowDlg, IDN_NCHAR), LB_DELETESTRING, indexN, 0);
}

static void read_msg(HWND hWnd)
{
	int   i         = 0;
	off_t file_size = 0;
	SendMessage(GetDlgItem(hWnd, IDS1_SCHAR), LB_RESETCONTENT, 0, (LPARAM)0);
	if ((fp = fopen(FILE_SEND_MSG_DAT, "r")) == NULL) {
		MessageBox(hWnd, MSG_READ_FILE_ERROR, NULL, MB_OK);
	}
	while (!feof(fp)) {
		fread(&msg, sizeof(msg), 1, fp);
		if (!feof(fp)) {
			SendMessage(GetDlgItem(hWnd, IDS1_SCHAR), LB_ADDSTRING, i++, (LPARAM)msg);
		}
	}
	fclose(fp);
}

static int SentmsgWindowProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case MSG_CREATE:
		CreateWindow(  "LISTBOX",
			       "",
			       LBS_NOTIFY  | WS_VISIBLE | WS_VSCROLL | WS_BORDER,
			       IDS1_SCHAR,
			       10, 10, 295, 105,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_VIEW,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDS_CK,
			       10, 155, 70, 25,
			       hWnd,
			       0);

		CreateWindow(  "button",
			       MSG_RETURN,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDS1_FH,
			       235, 155, 70, 25,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_DELECT,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDS_SC,
			       130, 155, 70, 25,
			       hWnd,
			       0);
		read_msg(hWnd);
		break;

	case MSG_COMMAND:
		switch (wParam)	{
		case IDS1_FH:
			DestroyMainWindow(hWnd);
			PostQuitMessage(hWnd);
			break;
		case IDS_SC:
			if (MessageBox(hWnd, MSG_DELECT, MSG_MESSAGE, MB_YESNO) == IDYES) {
				delnote(hWnd);
			}
			DestroyMainWindow(hWnd);
			PostQuitMessage(hWnd);
			break;
		}
		break;
	case MSG_CLOSE:
		DestroyMainWindow(hWnd);
		PostQuitMessage(hWnd);
		break;
	}
	return DefaultMainWinProc(hWnd, message, wParam, lParam);
}

int sentmsg(HWND hWnd)
{
	MSG           Msg;
	HWND          hMainWnd;
	MAINWINCREATE CreateInfo;

	//窗口信息
	CreateInfo.dwStyle        = WS_VISIBLE | WS_BORDER | WS_CAPTION;  //風格
	CreateInfo.dwExStyle      = WS_EX_NONE;
	CreateInfo.spCaption      = MSG_SENTMSG;                        //標題名
	CreateInfo.hMenu          = 0;                                  //無菜單
	CreateInfo.hCursor        = GetSystemCursor(0);
	CreateInfo.hIcon          = 0;
	CreateInfo.MainWindowProc = SentmsgWindowProc;      //消息處理過程函數
	CreateInfo.lx             = 0;
	CreateInfo.ty             = 0;
	CreateInfo.rx             = 320;
	CreateInfo.by             = 210;
	CreateInfo.iBkColor       = COLOR_lightwhite;
	CreateInfo.dwAddData      = 0;
	CreateInfo.hHosting       = hWnd;                       //托管窗口

//創建主窗口
	hMainWnd = CreateMainWindow(&CreateInfo);               //創建主窗口

	if (hMainWnd == HWND_INVALID) {
		return -1;
	}

//顯示主窗口
	ShowWindow(hMainWnd, SW_SHOWNORMAL);                      //顯示主窗口
//消息循環
	while (GetMessage(&Msg, hMainWnd)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
//恢復並關閉gprs串口
//資源清理
	MainWindowThreadCleanup(hMainWnd);

	return 0;
}

