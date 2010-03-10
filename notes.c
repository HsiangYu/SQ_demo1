#include <stdio.h>
#include <stdlib.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include "ecpda.h"
#include "lang.h"


struct DATA {
	char notedata[1000];

};
struct DATA note;




//�R���O�ƦC�����w���@��
static void delnote (HWND hWnd)
{

	indexV = SendMessage(GetDlgItem(hWnd, IDN_NCHAR), LB_GETCURSEL, 0, 0);
	SendMessage(GetDlgItem(hWnd, IDN_NCHAR), LB_DELETESTRING, indexV, 0);
}

static void view (HWND hWnd)
{
	indexV = SendMessage(GetDlgItem(hWnd, IDN_NCHAR), LB_GETCURSEL, 0, 0);
	SendMessage(GetDlgItem(hWnd, IDN_NCHAR), LB_GETTEXT, indexV, (LPARAM)buffN);
}

//�N�O�ƥ����e�g�J���

static void writesave_note(HWND hWnd)
{
	int count  = 0;
	int index2 = 0;
	fp    = fopen("file.dat", "w");
	count = SendMessage(GetDlgItem(hWnd, IDN_NCHAR), LB_GETCOUNT, 0, 0);
	for (index2 = 0; index2 < count; index2++) {
		SendMessage(GetDlgItem(hWnd, IDN_NCHAR), LB_GETTEXT, index2, (LPARAM)note.notedata);
		fwrite(&note, sizeof(struct DATA), 1, fp);
	}
	fclose(fp);
}

//Ū����󤺮e�A��ܨ�O�ƥ��C���

static void read_note(HWND hWnd)
{
	int   i         = 0;
	off_t file_size = 0;
	SendMessage(GetDlgItem(hWnd, IDN_NCHAR), LB_RESETCONTENT, 0, (LPARAM)0);
	if ((fp = fopen("file.dat", "r")) == NULL) {
		MessageBox(hWnd, MSG_READ_FILE_ERROR, NULL, MB_OK);
	}
	while (!feof(fp)) {
		fread(&note, sizeof(struct DATA), 1, fp);
		if (!feof(fp)) {
			SendMessage(GetDlgItem(hWnd, IDN_NCHAR), LB_ADDSTRING, i++, (LPARAM)note.notedata);
		}
	}
	fclose(fp);
}

static int NotesWindowProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{

	hwindowDlg = hWnd;
	switch (message) {
	case MSG_CREATE:


		CreateWindow(  "LISTBOX",
			       "",
			       LBS_NOTIFY  | WS_VISIBLE | WS_VSCROLL | WS_BORDER,
			       IDN_NCHAR,
			       10, 10, 215, 165,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_NEW,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDN_TJ,
			       235, 10, 70, 25,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_VIEW,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDN_CK,
			       235, 50, 70, 25,
			       hWnd,
			       0);

		CreateWindow(  "button",
			       MSG_DELECT,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDN_SC,
			       235, 90, 70, 25,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_RETURN,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDN_FH,
			       235, 130, 70, 25,
			       hWnd,
			       0);

		read_note(hWnd);
		SendMessage(GetDlgItem(hWnd, IDN_NCHAR), LB_SETCURSEL, 0, 0);
		break;
	case MSG_COMMAND:

		switch (wParam) {
		case IDN_TJ:
			addnote(hWnd);
			break;
		case IDN_CK:
			view(hWnd);
			viewnote(hWnd);
			break;
		case IDN_GD:
			more_note(hWnd);
			break;
		case IDN_SC:
			if (MessageBox(hWnd, MSG_DELECT, MSG_SAVE, MB_YESNO) == IDYES) {
				delnote(hWnd);
			}
			break;
		case IDN_FH:
			writesave_note(hWnd);
			DestroyMainWindow(hWnd);
			PostQuitMessage(hWnd);
			break;
		}
		break;
	case MSG_CLOSE:
		writesave_note(hWnd);
		DestroyMainWindow(hWnd);
		PostQuitMessage(hWnd);
		break;
	}
	return DefaultMainWinProc(hWnd, message, wParam, lParam);
}

int notes(HWND hWnd)
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
	CreateInfo.spCaption      = MSG_MEMO;                           //���D�W
	CreateInfo.hMenu          = 0;                                  //�L���
	CreateInfo.hCursor        = GetSystemCursor(0);
	CreateInfo.hIcon          = 0;
	CreateInfo.MainWindowProc = NotesWindowProc;      //�����B�z�L�{���
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

