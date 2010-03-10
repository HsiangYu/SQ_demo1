#include <stdio.h>
#include <stdlib.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include "ecpda.h"
#include "lang.h"

static int MessagingWindowProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case MSG_CREATE:
		CreateWindow(  "button",
			       MSG_WRITE_MESSAGE,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDM_BXXXX,
			       10, 10, 295, 25,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_MAILBOX,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDM_SJX,
			       10, 45, 295, 25,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_DRAFT_BOX,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDM_CG,
			       10, 80, 295, 25,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_SEND_BOX,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDM_YFXX,
			       10, 115, 295, 25,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_RETURN,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDM1_FH,
			       10, 155, 295, 25,
			       hWnd,
			       0);
		break;

	case MSG_COMMAND:
		switch (wParam) {
		case IDM_BXXXX:
			writemsg(hWnd);
			break;
		case IDM_SJX:
			inbox(hWnd);
			break;
		case IDM_CG:
			drafts(hWnd);
			break;
		case IDM_YFXX:
			sentmsg(hWnd);
			break;
		case IDM1_FH:
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

int messaging (HWND hWnd)
{
	MSG           Msg;
	HWND          hMainWnd;
	MAINWINCREATE CreateInfo;
#ifdef _LITE_VERSION
	SetDesktopRect(0, 0, 1024, 768);
#endif
	//���f�H��
	CreateInfo.dwStyle        = WS_VISIBLE | WS_BORDER | WS_CAPTION;  //����
	CreateInfo.dwExStyle      = WS_EX_NONE;
	CreateInfo.spCaption      = MSG_MESSAGE;                        //���D�W
	CreateInfo.hMenu          = 0;                                  //�L���
	CreateInfo.hCursor        = GetSystemCursor(0);
	CreateInfo.hIcon          = 0;
	CreateInfo.MainWindowProc = MessagingWindowProc;      //�����B�z�L�{���
	CreateInfo.lx             = 0;
	CreateInfo.ty             = 0;
	CreateInfo.rx             = 320;
	CreateInfo.by             = 210;
	CreateInfo.iBkColor       = COLOR_lightwhite;
	CreateInfo.dwAddData      = 0;
	CreateInfo.hHosting       = hWnd;                       //���޵��f

//�ЫإD���f
	hMainWnd = CreateMainWindow(&CreateInfo);               //�ЫإD���f

	if (hMainWnd == HWND_INVALID) {
		return -1;
	}

//��ܥD���f
	ShowWindow(hMainWnd, SW_SHOWNORMAL);                      //��ܥD���f
//�����`��
	while (GetMessage(&Msg, hMainWnd)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
//��_������gprs��f
//�귽�M�z
	MainWindowThreadCleanup(hMainWnd);

	return 0;
}

