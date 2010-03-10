#include <stdio.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include "hello.h"
#include "tty.h"
#include "gprs.h"
#include "lang.h"


//��ܮؼҪ��A�]�m��ܮت��ݩ�
static DLGTEMPLATE DlgInitProgress =
{
	WS_BORDER | WS_CAPTION,
	WS_EX_NONE,
	0, 0, 320, 240,
	"Call" /*"�ӹq"*/,
	0, 0,
	3, NULL,
	0
};


//��ܮؼҪ��A�]�m�U�ӱ����ݩ�
static CTRLDATA CtrlInitProgress [] =
{
	{
		CTRL_SLEDIT,
		WS_VISIBLE | WS_TABSTOP | WS_BORDER,
		40, 30, 170, 30,
		IDC_Edit,
		NULL,
		0
	},
	{
		"button",
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		40, 140, 60, 30,
		IDC_Ans,
		MSG_ACCEPT,
		0
	},
	{
		"button",
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		130, 140, 60, 30,
		IDC_Refuse,
		MSG_REJECT,
		0
	}
};

static int InitDialogBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {

	//�`�N�o�өM�D���f�Ыت��ϧO�A�o�ӬO��ܮدS�����A�b�D���f��¦�W�W�K���C�MCREATE�@�Ӯɾ��o�e�X�Ӫ��C
	case MSG_INITDIALOG:
		SendMessage(GetDlgItem(hDlg, IDC_Edit), MSG_SETTEXT, 0, (LPARAM)PhoneNum);
		return 0;

	//�B�z�q������
	case MSG_COMMAND:
		switch (wParam) {
		case  IDC_Ans:
			gprs_ans();
			break;
		case  IDC_Refuse:
			gprs_hold();
			break;
		}
		break;
	case MSG_CLOSE:
		EndDialog(hDlg, wParam);
		break;
	}

	return DefaultDialogProc(hDlg, message, wParam, lParam);
}

static void InitDialogBox (HWND hWnd)
{
	//��w��ܮؼҪ�
	DlgInitProgress.controls = CtrlInitProgress;

	DialogBoxIndirectParam(&DlgInitProgress, hWnd, InitDialogBoxProc, 0L);
}

//���թҥ�
//int MiniGUIMain (int argc, const char* argv[])
void ans(void)
{


	InitDialogBox(HWND_DESKTOP);

	//return 0;
}

