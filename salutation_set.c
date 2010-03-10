#include <stdio.h>
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
//#include <minigui/mywindows.h>
//#include <minigui/mgext.h>
#include "lang.h"

#define IDC_SOK          130
#define IDC_SRET         131
#define IDC_SBOX         132
#define IDC_STITLE       133


HWND InputEdit;
HWND KB_hwnd;

static int SalutationProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
	FILE * fp;
	char buffer1[100];
	switch (message) {
	case MSG_CREATE:
		CreateWindow(CTRL_STATIC, MSG_HELLO, WS_CHILD | SS_GROUPBOX | WS_VISIBLE, IDC_STITLE, 2, 2, 315, 198, hWnd, 0);
		CreateWindow(CTRL_MLEDIT, "", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | WS_VSCROLL, IDC_SBOX, 5, 20, 305, 70, hWnd, 0);
		CreateWindow(CTRL_BUTTON, MSG_OK, WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_SOK, 235, 134, 80, 30, hWnd, 0);
		CreateWindow(CTRL_BUTTON, MSG_RETURN, WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_SRET, 145, 134, 80, 30, hWnd, 0);
		InputEdit = GetDlgItem(hWnd, IDC_SBOX);
		return 0;

	case MSG_COMMAND:
	{
		switch (wParam)	{
		case IDC_SOK:
			GetWindowText(GetDlgItem(hWnd, IDC_SBOX), buffer1, 100);
			fp = fopen("wenhouyu", "w");
			if (fp == NULL) {
				MessageBox(hWnd, MSG_CREAT_FILE_ERROR, MSG_ERROR, MB_OK | MB_ICONEXCLAMATION);
			} else  {
				fwrite(buffer1, 100, 1, fp);
			}
			fclose(fp);
			return 0;
		case IDC_SRET:
			SendMessage(KB_hwnd, MSG_CLOSE, 0, 0);
			DestroyMainWindow(hWnd);
			PostQuitMessage(hWnd);
			return 0;

		}
		return 0;
	}

	case MSG_CLOSE:
		DestroyMainWindow(hWnd);
		PostQuitMessage(hWnd);
		return 0;
	}
	return DefaultMainWinProc(hWnd, message, wParam, lParam);
}

int salutation(HWND hWnd)
{
	MSG           Msg;
	HWND          hMainWnd;
	MAINWINCREATE CreateInfo;
	pthread_t     th_kb;
	CreateInfo.dwStyle        = WS_VISIBLE | WS_BORDER;
	CreateInfo.dwExStyle      = WS_EX_NONE;
	CreateInfo.spCaption      = "";
	CreateInfo.hMenu          = 0;
	CreateInfo.hCursor        = GetSystemCursor(0);
	CreateInfo.hIcon          = 0;
	CreateInfo.MainWindowProc = SalutationProc;
	CreateInfo.lx             = 0;
	CreateInfo.ty             = 40;
	CreateInfo.rx             = 320;
	CreateInfo.by             = 240;
	CreateInfo.iBkColor       = COLOR_lightwhite;
	CreateInfo.dwAddData      = 0;
	CreateInfo.hHosting       = hWnd;

	//pthread_create(&th_kb,NULL,(void *)KeyBoard,NULL);

	hMainWnd = CreateMainWindow(&CreateInfo);
	if (hMainWnd == HWND_INVALID) {
		return -1;
	}
	ShowWindow(hMainWnd, SW_SHOWNORMAL);
	while (GetMessage(&Msg, hMainWnd)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	pthread_join(th_kb, NULL);

	MainWindowThreadCleanup(hMainWnd);
	return 0;
}

