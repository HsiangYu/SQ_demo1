#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include "ecpda.h"


static void add_note(HWND hWnd)
{       //          char aa[10];
	GetWindowText(GetDlgItem(hWnd, IDE_ECHAR), buffN, sizeof(buffN));
	// sprintf(aa,"%d",indexV);
	// MessageBox(hWnd,aa,"test",MB_OK);
	//   SendMessage(GetDlgItem(hwindowDlg,IDN_NCHAR),LB_ADDSTRING,indexV,(LPARAM)buffN);
	SendMessage(GetDlgItem(hwindowDlg, IDN_NCHAR), LB_INSERTSTRING, indexV, (LPARAM)buffN);
}

static int Edit_noteWindowProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{

	switch (message) {
	case MSG_CREATE:


		CreateWindow(  "MLEDIT",
			       "",
			       WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_BASELINE | ES_AUTOWRAP | ES_LEFT | WS_VSCROLL,
			       IDE_ECHAR,
			       10, 10, 215, 165,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_SAVE,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDE_BC,
			       235, 10, 70, 25,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_DELECT,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDE_SC,
			       235, 80, 70, 25,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_RETURN,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDE_FH,
			       235, 150, 70, 25,
			       hWnd,
			       0);
		SetWindowText(GetDlgItem(hWnd, IDE_ECHAR), buffB);
		break;

	case MSG_COMMAND:
		switch (wParam) {
		case IDE_BC:
			add_note(hWnd);
			DestroyMainWindow(hWnd);
			PostQuitMessage(hWnd);
			break;
		case IDE_SC:
			GetWindowText(GetDlgItem(hWnd, IDE_ECHAR), buffE, sizeof(buffE));
			i            = strlen(buffE);
			buffE[i - 1] = '\0';
			SetWindowText(GetDlgItem(hWnd, IDE_ECHAR), buffE);
			break;
		case IDE_FH:
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

int edit_note(HWND hWnd) //,int indexV)
{
	MSG           Msg;
	HWND          hMainWnd;
	MAINWINCREATE CreateInfo;

	//���f�H��
	CreateInfo.dwStyle        = WS_VISIBLE | WS_BORDER | WS_CAPTION;  //����
	CreateInfo.dwExStyle      = WS_EX_NONE;
	CreateInfo.spCaption      = MSG_EDIT_NOTE;                      //���D�W
	CreateInfo.hMenu          = 0;                                  //�L���
	CreateInfo.hCursor        = GetSystemCursor(0);
	CreateInfo.hIcon          = 0;
	CreateInfo.MainWindowProc = Edit_noteWindowProc;      //�����B�z�L�{���
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

