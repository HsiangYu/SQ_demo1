/********************************************************************************************
* File Name:		taskbar.c
* Copy Right:		Neusoft
* Author:		ChenShui ChenChao ZhangJianWei
* Function discription:	Create taskbar
********************************************************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include <minigui/mgext.h>

#include "pda.h"

#define IDC_TASKBAR_INPUT       199

static BOOL KBON;               //鍵盤狀態，監視鍵盤是否已經打開
static      hMainWnd;           //MC-PDA的主窗口句柄


/********************************************************************************************
* Function Name:		NotifChange()
* Function Discription:	call back function of the 「顯示窗口」 item
********************************************************************************************/
static void NotifChange (HWND hwnd, int id, int nc, DWORD add_data)
{
	HWND TWnd;
	//當鼠標單擊該控件時
	if (nc == STN_CLICKED) {
		if ((TWnd = GetNextMainWindow(hMainWnd)) != 0) {
			//當主窗口後有窗口時，顯示該窗口
			ShowWindow(TWnd, SW_SHOWNORMAL);
		} else if ((TWnd = GetNextMainWindow(GetActiveWindow())) != hMainWnd &&
			   TWnd != 0) {
			//當最上層窗口下有窗口，且此窗口不是主窗口時，顯示該窗口
			ShowWindow(TWnd, SW_SHOWNORMAL);
		}
	}
}

/********************************************************************************************
* Function Name:		NotifInput()
* Function Discription:	call back function of the 「輸入法」 item
********************************************************************************************/
static void NotifInput (HWND hwnd, int id, int nc, DWORD add_data)
{
	//鼠標點擊該控件時
	if (nc == STN_CLICKED) {
		if (KBON == TURE) {
			//如果鍵盤沒有打開，則顯示鍵盤，同時將KBON狀態設置為FALSE
			KBON = FALSE;
			KeyBoard(hwnd);
		} else  {
			HWND Kb;
			KBON = TURE;
			//如果鍵盤已經打開，則銷毀鍵盤
			Kb = GetFirstHosted(GetParent(hwnd));
			DestroyAllControls(Kb);
			DestroyMainWindow(Kb);
			PostQuitMessage(Kb);
		}
	}
}

/********************************************************************************************
* Function Name:		TaskBarPro()
* Function Discription:	Processing function of the TaskBar window
********************************************************************************************/
static int TaskBarPro (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case MSG_CREATE:
		//創建「輸入法」靜態框
		CreateWindow("static", MSG_INPUT_METHOD,
			     WS_VISIBLE | SS_NOTIFY | SS_CENTER,
			     IDC_TASKBAR_INPUT,
			     0, 4, 50, 16,
			     hWnd,
			     0);
		//建立「輸入法」靜態框回叫函數
		SetNotificationCallback(GetDlgItem(hWnd, IDC_TASKBAR_INPUT), NotifInput);
		break;
	//接受從主窗口發來的消息，關閉任務欄窗口。
	case IDC_TASKBAR_CLOSEOUT:
		DestroyAllControls(hWnd);
		DestroyMainWindow(hWnd);
		PostQuitMessage(hWnd);
		return 0;

	case MSG_COMMAND:       //主窗口菜單命令
		switch (wParam)	{

		}

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

/********************************************************************************************
* Function Name:		TaskBar()
* Function Discription:	create the TaskBar window
********************************************************************************************/
void * TaskBar (void *arg)
{
	MSG           Msg;
	HWND          hTaskBar, *phMainWnd = arg;
	MAINWINCREATE CreateInfo;

	hMainWnd = *phMainWnd;

	if (!InitMiniGUIExt()) {
		exit(2);
	}

	KBON = TURE;

	//設置窗口屬性
	CreateInfo.dwStyle        = WS_VISIBLE | WS_BORDER;
	CreateInfo.dwExStyle      = WS_EX_TOPMOST | WS_EX_TOOLWINDOW;
	CreateInfo.spCaption      = " ";
	CreateInfo.hMenu          = 0;
	CreateInfo.hCursor        = GetSystemCursor(0);
	CreateInfo.hIcon          = 0;
	CreateInfo.MainWindowProc = TaskBarPro;
	CreateInfo.lx             = 250;
	CreateInfo.ty             = 214;
	CreateInfo.rx             = 320;
	CreateInfo.by             = 240;
	CreateInfo.iBkColor       = GetWindowElementColor(BKC_CONTROL_DEF);
	CreateInfo.dwAddData      = 0;
	CreateInfo.dwReserved     = 0;
	CreateInfo.hHosting       = HWND_DESKTOP;

	//創建TaskBar主窗口
	hTaskBar      = CreateMainWindow(&CreateInfo);
	TaskBarWindow = hTaskBar;
	if (hTaskBar == HWND_INVALID) {
		exit(-1);
	}

	//顯示窗口
	ShowWindow(hTaskBar, SW_SHOWNORMAL);

	while (GetMessage(&Msg, hTaskBar)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	MiniGUIExtCleanUp();
	MainWindowThreadCleanup(hTaskBar);
	return 0;
}

