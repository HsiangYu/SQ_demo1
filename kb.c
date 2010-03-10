/********************************************************************************************
* File Name:		kb.c
* Copy Right:		Neusoft
* Author:		ChenShui ChenChao ZhangJianWei
* Function discription:	Create keyboard
********************************************************************************************/

#include <stdio.h>
#include <time.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include <minigui/mgext.h>
#include "mini133.h"

#include "pda.h"

//鍵盤功能鍵鍵值
#define IDC_KB       100

//記錄鍵盤各行按鍵個數
#define KBL1         10
#define KBL2         11
#define KBL3         11
#define KBL4         10

//鍵盤顯示內容
static const char * caption[] =
{
	"1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
	"q", "w", "e", "r", "t", "y", "u", "i", "o", "p",
	"a", "s", "d", "f", "g", "h", "j", "k", "l",
	"z", "x", "c", "v", "b", "n", "m",  ";", ",", ".", "<- ", "*", "#"
};


//CAPS和SHIFT鍵都觸發後鍵盤顯示內容
/*
static const char * caption3[] =
{
	"   ~ ", "  ! ", " @ ", " # ", " $ ", " % ", " ^ ", " & ", " * ", " ( ", " ) ", " _ ", " + ",
	" Tab ", " q ", " w ", " e ", " r ", " t ", " y ", " u ", " i ", " o ", " p ", " { ", " } ", " | ",
	" Caps ", " a ", " s ", " d ", " f ", " g ", " h ", " j ", " k ", " l ", " : ", " \" ", " Enter ",
	" Shift ", " z ", " x ", " c ", " v ", " b ", " n ", " m ", " < ", " > ", " ? ", "  Shift ",
	" Ctrl  ", "  Alt ", "    Space       ", "   Alt ", "   Ctrl ",  " Backspace "
};
*/
//按鍵ID
static const int KeyV[] =
{
	2,   3,  4,  5,  6,  7,  8,  9, 10, 11,
	16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 
	30, 31, 32, 33, 34, 35, 36, 37, 38, 
	44, 45, 46, 47, 48, 49, 50, 39, 51, 52, 14 ,53,54,55,56,
};





//創建CAPS和SHIFT鍵都未觸發的鍵盤
static void CreateKbd (HWND hWnd)
{
	HWND            cb1, cb2, cb3, cb4, cb5;
	COOLBARITEMINFO item;
	int             i;

	cb1 = CreateWindow(CTRL_COOLBAR,
			   "",
			   WS_CHILD | WS_VISIBLE | CBS_BMP_16X16,
			   IDC_KB,
			   0, 0, 230, 16,
			   hWnd,
			   0);

	cb2 = CreateWindow(CTRL_COOLBAR,
			   "",
			   WS_CHILD | WS_VISIBLE,
			   IDC_KB,
			   0, 22, 230, 16,
			   hWnd,
			   0);

	cb3 = CreateWindow(CTRL_COOLBAR,
			   "",
			   WS_CHILD | WS_VISIBLE,
			   IDC_KB,
			   0, 44, 230, 16,
			   hWnd,
			   0);

	cb4 = CreateWindow(CTRL_COOLBAR,
			   "",
			   WS_CHILD | WS_VISIBLE,
			   IDC_KB,
			   0, 66, 230, 16,
			   hWnd,
			   0);

	item.ItemType  = TYPE_TEXTITEM;
	item.Bmp       = NULL;
	item.dwAddData = 0;
	item.ItemHint  = NULL;
	for (i = 0; i < KBL1; i++) {
		item.insPos  = i;
		item.id      = i;
		item.Caption = caption[i];
		SendMessage(cb1, CBM_ADDITEM, 0, (LPARAM)&item);
	}

	for (i = KBL1; i < KBL1 + KBL2; i++) {
		item.insPos  = i;
		item.id      = i;
		item.Caption = caption[i];
		SendMessage(cb2, CBM_ADDITEM, 0, (LPARAM)&item);
	}

	for (i = KBL1 + KBL2; i < KBL1 + KBL2 + KBL3; i++) {
		item.insPos  = i;
		item.id      = i;
		item.Caption = caption[i];
		SendMessage(cb3, CBM_ADDITEM, 0, (LPARAM)&item);
	}

	for (i = KBL1 + KBL2 + KBL3; i < KBL1 + KBL2 + KBL3 + KBL4; i++) {
		item.insPos  = i;
		item.id      = i;
		item.Caption = caption[i];
		SendMessage(cb4, CBM_ADDITEM, 0, (LPARAM)&item);
	}
}

/********************************************************************************************
* Function Name:		KeyBoardPro()
* Function Discription:	Processing function of the KeyBoard window
********************************************************************************************/
static int KeyBoardPro (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
	HWND        Kbs, Kbb;
	static char Text[100], PhoneNum[40];
	switch (message) {
	case MSG_CREATE:
		//創建鍵盤控件
		CreateKbd(hWnd);
		break;

	case MSG_COMMAND:   //鍵盤事件觸發
	{
		int id       = LOWORD(wParam);
		int keyid    = HIWORD(wParam);
		int KeyValue = KeyV[keyid];
		if (id == IDC_KB) {
			//其它按鍵觸發時，發送鍵盤按鍵消息
			SendMessage(InputEdit, MSG_KEYDOWN, KeyValue, 0L);

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

int KeyBoard (HWND hWnd)
{
	MSG           Msg;
	HWND          hKB;
	MAINWINCREATE CreateInfo;

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
	CreateInfo.lx             = 145;
	CreateInfo.ty             = 121;
	CreateInfo.rx             = 320;
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

