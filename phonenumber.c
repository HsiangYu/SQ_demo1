#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include "ecpda.h"



static int PhonenumberWindowProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case MSG_CREATE:
		CreateWindow(  "STATIC",
			       MSG_NUMBER,
			       WS_VISIBLE | WS_TABSTOP | WS_BORDER | SS_NOTIFY,
			       IDP_HM,
			       10, 20, 70, 25,
			       hWnd,
			       0);

		CreateWindow(  "SLEDIT",
			       "",
			       WS_VISIBLE | WS_TABSTOP | WS_BORDER | SS_NOTIFY,
			       IDP_PCHAR,
			       10, 70, 295, 25,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_OK,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDP_QD,
			       10, 125, 70, 25,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_RETURN,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDP_FH,
			       10, 155, 70, 25,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_DELECT,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDP_SC,
			       235, 155, 70, 25,
			       hWnd,
			       0);

		break;

	case MSG_COMMAND:
		switch (wParam) {
		case IDP_QD:
			GetWindowText(GetDlgItem(hWnd, IDP_PCHAR), buffP, sizeof(buffP));
			send_msg(hWnd);
			break;
		case IDP_SC:
			GetWindowText(GetDlgItem(hWnd, IDP_PCHAR), buffP, sizeof(buffP));
			i            = strlen(buffP);
			buffP[i - 1] = '\0';
			SetWindowText(GetDlgItem(hWnd, IDP_PCHAR), buffP);
			break;
		case IDP_FH:
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

int phonenumber(HWND hWnd)
{
	MSG           Msg;
	HWND          hMainWnd;
	MAINWINCREATE CreateInfo;

	//窗口信息
	CreateInfo.dwStyle        = WS_VISIBLE | WS_BORDER | WS_CAPTION;  //風格
	CreateInfo.dwExStyle      = WS_EX_NONE;
	CreateInfo.spCaption      = MSG_PHONE_NUMBER;                           //標題名
	CreateInfo.hMenu          = 0;                                          //無菜單
	CreateInfo.hCursor        = GetSystemCursor(0);
	CreateInfo.hIcon          = 0;
	CreateInfo.MainWindowProc = PhonenumberWindowProc;      //消息處理過程函數
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

