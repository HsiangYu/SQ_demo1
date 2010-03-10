#include <stdio.h>
#include <stdlib.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include "ecpda.h"
#include "lang.h"

void writesave_msg()
{
	FILE *fp;
	if ((fp = fopen(FILE_SEND_MSG_DAT, "a+")) == NULL) {
		printf("open file error");
		return;
	}
	fwrite(&buff1, sizeof(buff1), 1, fp);
	fwrite(&buff2, sizeof(buff2), 1, fp);
	fclose(fp);

}

struct message {
	char hm[20];
	char nr[500];
} msg;

static int Send_msgWindowProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
	hwindowDlg = hWnd;
	switch (message) {
	case MSG_CREATE:
		CreateWindow(  "STATIC",
			       MSG_NUMBER,
			       WS_VISIBLE | WS_TABSTOP | WS_BORDER | SS_NOTIFY,
			       IDS_HM,
			       10, 70, 70, 25,
			       hWnd,
			       0);

		CreateWindow(  "SLEDIT",
			       "",
			       WS_VISIBLE | WS_TABSTOP | WS_BORDER | SS_NOTIFY | ES_READONLY,
			       IDS2_SCHAR,
			       90, 70, 215, 25,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_SEND,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDS_FS,
			       10, 155, 70, 25,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_RETURN,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDS3_FH,
			       235, 155, 70, 25,
			       hWnd,
			       0);
		SetWindowText(GetDlgItem(hWnd, IDS2_SCHAR), buffP);
		break;

	case MSG_COMMAND:
		switch (wParam) {
		case IDS_FS:
			GetWindowText(GetDlgItem(hWnd, IDS2_SCHAR), buff1, sizeof(buff1));
			MessageBox(hWnd, buff1, "text1", MB_OK);
			MessageBox(hWnd, buff2, "text2", MB_OK);
			//msg_send(buff1, buff2);
			writesave_msg();
			msg_send(buff1, buff2);
			DestroyMainWindow(hWnd);
			PostQuitMessage(hWnd);
			break;
		case IDS3_FH:
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

int send_msg(HWND hWnd)
{
	MSG           Msg;
	HWND          hMainWnd;
	MAINWINCREATE CreateInfo;

	//���f�H��
	CreateInfo.dwStyle        = WS_VISIBLE | WS_BORDER | WS_CAPTION;  //����
	CreateInfo.dwExStyle      = WS_EX_NONE;
	CreateInfo.spCaption      = MSG_SEND_MSG;                       //���D�W
	CreateInfo.hMenu          = 0;                                  //�L���
	CreateInfo.hCursor        = GetSystemCursor(0);
	CreateInfo.hIcon          = 0;
	CreateInfo.MainWindowProc = Send_msgWindowProc;      //�����B�z�L�{���
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

