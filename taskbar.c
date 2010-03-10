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

static BOOL KBON;               //��L���A�A�ʵ���L�O�_�w�g���}
static      hMainWnd;           //MC-PDA���D���f�y�`


/********************************************************************************************
* Function Name:		NotifChange()
* Function Discription:	call back function of the �u��ܵ��f�v item
********************************************************************************************/
static void NotifChange (HWND hwnd, int id, int nc, DWORD add_data)
{
	HWND TWnd;
	//���г����ӱ����
	if (nc == STN_CLICKED) {
		if ((TWnd = GetNextMainWindow(hMainWnd)) != 0) {
			//��D���f�ᦳ���f�ɡA��ܸӵ��f
			ShowWindow(TWnd, SW_SHOWNORMAL);
		} else if ((TWnd = GetNextMainWindow(GetActiveWindow())) != hMainWnd &&
			   TWnd != 0) {
			//��̤W�h���f�U�����f�A�B�����f���O�D���f�ɡA��ܸӵ��f
			ShowWindow(TWnd, SW_SHOWNORMAL);
		}
	}
}

/********************************************************************************************
* Function Name:		NotifInput()
* Function Discription:	call back function of the �u��J�k�v item
********************************************************************************************/
static void NotifInput (HWND hwnd, int id, int nc, DWORD add_data)
{
	//�����I���ӱ����
	if (nc == STN_CLICKED) {
		if (KBON == TURE) {
			//�p�G��L�S�����}�A�h�����L�A�P�ɱNKBON���A�]�m��FALSE
			KBON = FALSE;
			KeyBoard(hwnd);
		} else  {
			HWND Kb;
			KBON = TURE;
			//�p�G��L�w�g���}�A�h�P����L
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
		//�Ыءu��J�k�v�R�A��
		CreateWindow("static", MSG_INPUT_METHOD,
			     WS_VISIBLE | SS_NOTIFY | SS_CENTER,
			     IDC_TASKBAR_INPUT,
			     0, 4, 50, 16,
			     hWnd,
			     0);
		//�إߡu��J�k�v�R�A�ئ^�s���
		SetNotificationCallback(GetDlgItem(hWnd, IDC_TASKBAR_INPUT), NotifInput);
		break;
	//�����q�D���f�o�Ӫ������A���������浡�f�C
	case IDC_TASKBAR_CLOSEOUT:
		DestroyAllControls(hWnd);
		DestroyMainWindow(hWnd);
		PostQuitMessage(hWnd);
		return 0;

	case MSG_COMMAND:       //�D���f���R�O
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

	//�]�m���f�ݩ�
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

	//�Ы�TaskBar�D���f
	hTaskBar      = CreateMainWindow(&CreateInfo);
	TaskBarWindow = hTaskBar;
	if (hTaskBar == HWND_INVALID) {
		exit(-1);
	}

	//��ܵ��f
	ShowWindow(hTaskBar, SW_SHOWNORMAL);

	while (GetMessage(&Msg, hTaskBar)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	MiniGUIExtCleanUp();
	MainWindowThreadCleanup(hTaskBar);
	return 0;
}

