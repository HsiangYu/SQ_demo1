#include <stdio.h>
//#include <time.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
//#include <minigui/mgext.h>
#include <string.h>
#include "hello.h"
#include "gprs.h"
#include "tty.h"
#include "mini133.h"


/** Structure of the coolbar item info */
typedef struct _COOLBARITEMINFO {
	/** Reserved, do not use. */
	int insPos;

	/**
	 * Identifier of the item. When the user clicked the item, this control
	 * will send a notification message to the parent window
	 * with the notification code to be equal to this identifier.
	 */
	int id;

	/**
	 * Type of the item, can be one of the following values:
	 * - TYPE_BARITEM
	 *   The item is a separator (a vertical line).
	 * - TYPE_BMPITEM
	 *   The item is a bitmap.
	 * - TYPE_TEXTITEM
	 *   The item is text.
	 */
	int ItemType;

	/**
	 * Pointer to the bitmap of the item, valid when the type is TYPE_BMPITEM.
	 */
	PBITMAP Bmp;

	/**
	 * Hint text of the item, will be displayed in the tooltip window.
	 */
	const char *ItemHint;

	/**
	 * Caption of the item, valid when the type is TPYE_TEXTITEM.
	 */
	const char *Caption;

	/** Additional data of the item */
	DWORD dwAddData;
} COOLBARITEMINFO;
//channing add

static long int KState = 0, KStateTmp;


//鍵盤顯示內容
static const char * caption[] =
{
	"  1  ", "  2  ", "  3  ",
	"  4  ", "  5  ", "  6  ",
	"  7  ", "  8  ", "  9  ",
	"  *  ", "  0  ", "  #  ",
};

//按鍵ID
static const int KeyV[] =
{
	41, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 43,
	58, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 28,
	42, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54,
	29, 56, 57, 100, 97, 14
};

//創建CAPS和SHIFT鍵都未觸發的鍵盤
static void CreateKbd (HWND hWnd)
{
	HWND            cb1, cb2, cb3, cb4;
	COOLBARITEMINFO item;
	int             i;

	cb1 = CreateWindow(CTRL_COOLBAR,
			   "",
			   WS_CHILD | WS_VISIBLE,
			   IDC_CB,
			   0, 0, 230, 16,
			   hWnd,
			   0);

	cb2 = CreateWindow(CTRL_COOLBAR,
			   "",
			   WS_CHILD | WS_VISIBLE,
			   IDC_CB,
			   0, 22, 230, 16,
			   hWnd,
			   0);
	cb3 = CreateWindow(CTRL_COOLBAR,
			   "",
			   WS_CHILD | WS_VISIBLE,
			   IDC_CB,
			   0, 44, 230, 16,
			   hWnd,
			   0);
	cb4 = CreateWindow(CTRL_COOLBAR,
			   "",
			   WS_CHILD | WS_VISIBLE,
			   IDC_CB,
			   0, 66, 230, 16,
			   hWnd,
			   0);

	item.ItemType  = TYPE_TEXTITEM;
	item.Bmp       = NULL;
	item.dwAddData = 0;
	item.ItemHint  = NULL;

	for (i = 0; i < 3; i++) {
		item.insPos  = i;
		item.id      = i;
		item.Caption = caption[i];
		SendMessage(cb1, CBM_ADDITEM, 0, (LPARAM)&item);
	}
	for (i = 3; i < 6; i++) {
		item.insPos  = i;
		item.id      = i;
		item.Caption = caption[i];
		SendMessage(cb2, CBM_ADDITEM, 0, (LPARAM)&item);
	}
	for (i = 6; i < 9; i++) {
		item.insPos  = i;
		item.id      = i;
		item.Caption = caption[i];
		SendMessage(cb3, CBM_ADDITEM, 0, (LPARAM)&item);
	}
	for (i = 9; i < 12; i++) {
		item.insPos  = i;
		item.id      = i;
		item.Caption = caption[i];
		SendMessage(cb4, CBM_ADDITEM, 0, (LPARAM)&item);
	}
}

static int KeyBoardPro (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
	HWND Kbs, Kbb;
	char buff[2];
	int  num;

	switch (message) {
	case MSG_CREATE:
		//創建鍵盤控件
		CreateKbd(hWnd);
		break;

	case MSG_COMMAND:   //鍵盤事件觸發
	{
		int id    = LOWORD(wParam);
		int keyid = HIWORD(wParam);
		int KeyValue;
		if (id == IDC_CB) {
			switch (keyid) {
			case 0:
				SendMessage(Input, MSG_GETTEXT, 20, (LPARAM)buffer);
				strcat(buffer, "1");
				SendMessage(Input, MSG_SETTEXT, 0, (LPARAM)buffer);
				break;
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:

				KeyValue = KeyV[keyid];
				//SendMessage (InputEdit, MSG_KEYDOWN, KeyValue, KState);
				SendMessage(Input, MSG_GETTEXT, 20, (LPARAM)buffer);
				sprintf(buff, "%d", KeyValue);
				strcat(buffer, buff);
				SendMessage(Input, MSG_SETTEXT, 0, (LPARAM)buffer);
				break;
			case 9:
				SendMessage(Input, MSG_GETTEXT, 20, (LPARAM)buffer);
				strcat(buffer, "*");
				SendMessage(Input, MSG_SETTEXT, 0, (LPARAM)buffer);
				break;
			case 10:
				SendMessage(Input, MSG_GETTEXT, 20, (LPARAM)buffer);
				strcat(buffer, "0");
				SendMessage(Input, MSG_SETTEXT, 0, (LPARAM)buffer);
				break;
			case 11:
				SendMessage(Input, MSG_GETTEXT, 20, (LPARAM)buffer);
				strcat(buffer, "#");
				SendMessage(Input, MSG_SETTEXT, 0, (LPARAM)buffer);
				break;

			}
		}
	}
	break;
	//用於在銷毀時退出的代碼，重要不然會死掉。
	case MSG_DESTROY:
		DestroyAllControls(hWnd);
		return 0;

	case MSG_CLOSE:
		DestroyMainWindow(hWnd);
		PostQuitMessage(hWnd);

		return 0;

	}
	return DefaultMainWinProc(hWnd, message, wParam, lParam);
}

int coolbar (HWND hWnd)
{
	MSG           Msg;
	HWND          hKB;
	MAINWINCREATE CreateInfo;

#ifdef _LITE_VERSION
	SetDesktopRect(0, 0, 1024, 768);
#endif
	if (!InitMiniGUIExt()) {
		return 2;
	}

	//設置鍵盤窗口屬性
	CreateInfo.dwStyle        = WS_VISIBLE | WS_THINFRAME;
	CreateInfo.dwExStyle      = WS_EX_TOPMOST | WS_EX_TOOLWINDOW;
	CreateInfo.spCaption      = "  ";
	CreateInfo.hMenu          = 0;
	CreateInfo.hCursor        = GetSystemCursor(IDC_ARROW);
	CreateInfo.hIcon          = 0;
	CreateInfo.MainWindowProc = KeyBoardPro;
	CreateInfo.lx             = 246;
	CreateInfo.ty             = 105;
	CreateInfo.rx             = 317;
	CreateInfo.by             = 215;
	CreateInfo.iBkColor       = GetWindowElementColor(BKC_CONTROL_DEF);
	CreateInfo.dwAddData      = 0;
	CreateInfo.dwReserved     = 0;
	CreateInfo.hHosting       = hWnd;
	//創建鍵盤窗口
	hKB = CreateMainWindow(&CreateInfo);
	if (hKB == HWND_INVALID) {
		return -1;
	}

	//顯示鍵盤窗口
	ShowWindow(hKB, SW_SHOWNORMAL);

	while (GetMessage(&Msg, hKB)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	MiniGUIExtCleanUp();
	MainWindowThreadCleanup(hKB);
	return 0;
}

#ifndef _LITE_VERSION
//#include <minigui/dti.c>
#endif

