#include <stdio.h>
#include <stdlib.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include "ecpda.h"


static void delnote (HWND hWnd)
{
	int indexN;
	indexN = SendMessage(GetDlgItem(hwindowDlg, IDN_NCHAR), LB_GETCURSEL, 0, 0);
	SendMessage(GetDlgItem(hwindowDlg, IDN_NCHAR), LB_DELETESTRING, indexN, 0);
}

static int ViewnoteWindowProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
	int indexV;
	hwindowDlg = hWnd;

	switch (message) {
	case MSG_CREATE:

		CreateWindow(  "MLEDIT",
			       "",
			       WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_BASELINE | ES_AUTOWRAP | ES_LEFT | WS_VSCROLL | ES_READONLY,
			       IDV_VCHAR,
			       10, 10, 215, 165,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_EDIT,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDV_BJ,
			       235, 45, 70, 25,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_DELECT,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDV_SC,
			       235, 90, 70, 25,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_RETURN,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDV_FH,
			       235, 135, 70, 25,
			       hWnd,
			       0);


		SetWindowText(GetDlgItem(hWnd, IDV_VCHAR), buffN);
		break;

	case MSG_COMMAND:
		switch (wParam) {
		case IDV_BJ:
			GetWindowText(GetDlgItem(hWnd, IDV_VCHAR), buffB, sizeof(buffB));
			edit_note(hWnd);
			DestroyMainWindow(hWnd);
			PostQuitMessage(hWnd);
			break;
			// case IDV_FS:
			//       //  send_note(hWnd);
			break;
		case IDV_SC:
			if (MessageBox(hWnd, MSG_DELECT, MSG_SAVE, MB_YESNO) == IDYES) {
				delnote(hWnd);
			}
			DestroyMainWindow(hWnd);
			PostQuitMessage(hWnd);
			break;
		case IDV_FH:
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

int viewnote(HWND hWnd)
{

	MSG           Msg;
	HWND          hMainWnd;
	MAINWINCREATE CreateInfo;

	//���f�H��
	CreateInfo.dwStyle        = WS_VISIBLE | WS_BORDER | WS_CAPTION;  //����
	CreateInfo.dwExStyle      = WS_EX_NONE;
	CreateInfo.spCaption      = MSG_VIEW_NOTE;                      //���D�W
	CreateInfo.hMenu          = 0;                                  //�L���
	CreateInfo.hCursor        = GetSystemCursor(0);
	CreateInfo.hIcon          = 0;
	CreateInfo.MainWindowProc = ViewnoteWindowProc;      //�����B�z�L�{���
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

