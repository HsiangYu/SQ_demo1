#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include "ecpda.h"
#include "lang.h"


static void add_note(HWND hWnd)
{
	GetWindowText(GetDlgItem(hWnd, IDA_ACHAR), buffA, sizeof(buffA));

	SendMessage(GetDlgItem(hwindowDlg, IDN_NCHAR), LB_ADDSTRING, 0, (LPARAM)buffA);
}

static int AddnoteWindowProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case MSG_CREATE:


		CreateWindow(  "MLEDIT",
			       "",
			       WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_BASELINE | ES_AUTOWRAP | ES_LEFT | WS_VSCROLL,
			       IDA_ACHAR,
			       10, 10, 215, 165,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_SAVE,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDA_BC,
			       235, 10, 70, 25,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_DELECT,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDA_SC,
			       235, 80, 70, 25,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_RETURN,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDA_FH,
			       235, 150, 70, 25,
			       hWnd,
			       0);

		break;

	case MSG_COMMAND:
		switch (wParam) {
		case IDA_BC:
			add_note(hWnd);
			DestroyMainWindow(hWnd);
			PostQuitMessage(hWnd);
			break;
		case IDA_SC:
			GetWindowText(GetDlgItem(hWnd, IDA_ACHAR), buffA, sizeof(buffA));
			i            = strlen(buffA);
			buffA[i - 1] = '\0';
			SetWindowText(GetDlgItem(hWnd, IDA_ACHAR), buffA);
			break;
		case IDA_FH:
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

int addnote(HWND hWnd)
{
	MSG           Msg;
	HWND          hMainWnd;
	MAINWINCREATE CreateInfo;

	//窗口信息
	CreateInfo.dwStyle        = WS_VISIBLE | WS_BORDER | WS_CAPTION;  //風格
	CreateInfo.dwExStyle      = WS_EX_NONE;
	CreateInfo.spCaption      = MSG_ADD_NOTE;                       //標題名
	CreateInfo.hMenu          = 0;                                  //無菜單
	CreateInfo.hCursor        = GetSystemCursor(0);
	CreateInfo.hIcon          = 0;
	CreateInfo.MainWindowProc = AddnoteWindowProc;      //消息處理過程函數
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

