#include <stdio.h>
#include <stdlib.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include "ecpda.h"
#include "lang.h"


char msg[1000];



//讀取文件內容，顯示到記事本列表框

static void read_msg(HWND hWnd)
{
	int   i         = 0;
	off_t file_size = 0;
	SendMessage(GetDlgItem(hWnd, IDD_DCHAR), LB_RESETCONTENT, 0, (LPARAM)0);
	if ((fp = fopen("file1.dat", "r")) == NULL) {
		MessageBox(hWnd, MSG_READ_FILE_ERROR, NULL, MB_OK);
	}
	while (!feof(fp)) {
		fread(&msg, sizeof(msg), 1, fp);
		if (!feof(fp)) {
			SendMessage(GetDlgItem(hWnd, IDD_DCHAR), LB_ADDSTRING, i++, (LPARAM)msg);
		}
	}
	fclose(fp);
}

static int DraftsWindowProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
	hwindowDlg = hWnd;
	switch (message) {
	case MSG_CREATE:
		CreateWindow(  "LISTBOX",
			       "",
			       LBS_NOTIFY  | WS_VISIBLE | WS_VSCROLL | WS_BORDER,
			       IDD_DCHAR,
			       10, 10, 295, 105,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_EDIT,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDD_BJ,
			       10, 155, 70, 25,
			       hWnd,
			       0);

		/*     CreateWindow(  "button",
				    "更多",
				    WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				    IDD_GD,
				    235, 125, 70, 25,
				    hWnd,
				    0);
		 */
		CreateWindow(  "button",
			       MSG_RETURN,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDD_FH,
			       235, 155, 70, 25,
			       hWnd,
			       0);
		CreateWindow(  "button",
			       MSG_DELECT,
			       WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			       IDD_SC,
			       130, 155, 70, 25,
			       hWnd,
			       0);
		read_msg(hWnd);

		break;

	case MSG_COMMAND:
		switch (wParam) {

		case IDD_FH:
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

int drafts(HWND hWnd)
{
	MSG           Msg;
	HWND          hMainWnd;
	MAINWINCREATE CreateInfo;

	//窗口信息
	CreateInfo.dwStyle        = WS_VISIBLE | WS_BORDER | WS_CAPTION;  //風格
	CreateInfo.dwExStyle      = WS_EX_NONE;
	CreateInfo.spCaption      = MSG_DRAFT;                          //標題名
	CreateInfo.hMenu          = 0;                                  //無菜單
	CreateInfo.hCursor        = GetSystemCursor(0);
	CreateInfo.hIcon          = 0;
	CreateInfo.MainWindowProc = DraftsWindowProc;      //消息處理過程函數
	CreateInfo.lx             = 0;
	CreateInfo.ty             = 0;
	CreateInfo.rx             = 320;
	CreateInfo.by             = 240;
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

