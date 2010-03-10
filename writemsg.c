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

char msg[1000];

static void save_msg(HWND hWnd)
{

	fp = fopen(FILE_SAVE_MSG_DAT, "a+");
	GetWindowText(GetDlgItem(hWnd, IDW_WCHAR), msg, sizeof(msg));

	SendMessage(GetDlgItem(hWnd, IDW_WCHAR), LB_GETTEXT, 0, (LPARAM)msg);
	fwrite(&msg, sizeof(msg), 1, fp);

	fclose(fp);
}

static int WritemsgWindowProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
	hwindowDlg = hWnd;
	switch (message) {
	case MSG_CREATE:
		CreateWindow(  "MLEDIT",
			       "",
			       WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_BASELINE | ES_AUTOWRAP | ES_LEFT | WS_VSCROLL,
			       IDW_WCHAR,
			       10, 10, 295, 105,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_SEND,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDW_JX,
			       10, 155, 70, 25,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_SAVE,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDW_BC,
			       85, 155, 70, 25,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_RETURN,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDW_FH,
			       235, 155, 70, 25,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_DELECT,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDW_SC,
			       160, 155, 70, 25,
			       hWnd,
			       0);

		break;

	case MSG_COMMAND:
		switch (wParam) {
		case IDW_JX:
			GetWindowText(GetDlgItem(hWnd, IDW_WCHAR), buff2, sizeof(buff2));
			phonenumber(hWnd);
			//    sendto(hWnd);
			break;
		case IDW_BC:

			save_msg(hWnd);
			DestroyMainWindow(hWnd);
			PostQuitMessage(hWnd);
			break;
		case IDW_SC:
			GetWindowText(GetDlgItem(hWnd, IDW_WCHAR), buffW, sizeof(buffW));
			i            = strlen(buffW);
			buffW[i - 1] = '\0';
			SetWindowText(GetDlgItem(hWnd, IDW_WCHAR), buffW);
			break;
		case IDW_FH:
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

int writemsg(HWND hWnd)
{
	MSG           Msg;
	HWND          hMainWnd;
	MAINWINCREATE CreateInfo;

	//���f�H��
	CreateInfo.dwStyle        = WS_VISIBLE | WS_BORDER | WS_CAPTION;  //����
	CreateInfo.dwExStyle      = WS_EX_NONE;
	CreateInfo.spCaption      = MSG_WRITE_NEW_MESSAGE;                      //���D�W
	CreateInfo.hMenu          = 0;                                          //�L���
	CreateInfo.hCursor        = GetSystemCursor(0);
	CreateInfo.hIcon          = 0;
	CreateInfo.MainWindowProc = WritemsgWindowProc;      //�����B�z�L�{���
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

