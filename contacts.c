#include <stdio.h>
#include <stdlib.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include "hello.h"
#include "gprs.h"
#include "tty.h"

#include "lang.h"


struct DATA {
	char peopledata[100];

};
struct DATA phone;


static DLGTEMPLATE DlgBoxInputChar =
{
	WS_BORDER | WS_CAPTION,
	WS_EX_NONE,
	0, 0, 320, 240,
	MSG_PHONEBOOK,
	0, 0,
	9, NULL,
	0
};
static CTRLDATA CtrlInputChar [] =
{
	{
		CTRL_LISTBOX,
		LBS_NOTIFY  | WS_VISIBLE | WS_VSCROLL | WS_BORDER,
		25, 70, 265, 75,
		IDC_CHAR2,
		NULL,
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		25, 5, 265, 25,
		IDC_OPTIONS,
		MSG_OPTION,
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		25, 35, 265, 25,
		IDC_NEW,
		MSG_ADD_FRIEND,
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		5, 155, 70, 25,
		IDC_CALL,
		MSG_CALL,
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		160, 155, 70, 25,
		IDC_MORE,
		MSG_MORE_DATA,
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		5, 185, 70, 25,
		IDC_RETURN,
		MSG_RETURN,
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		85, 185, 70, 25,
		IDC_SAVE,
		MSG_SAVE,
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		85, 155, 70, 25,
		IDC_DEL,
		MSG_DELECT,
		0
	},
	{
		CTRL_BUTTON,
		WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
		240, 155, 70, 25,
		IDC_KEYBOARD,
		MSG_KEYBOARD,
		0
	}
//    {
//        CTRL_BUTTON,
//        WS_TABSTOP | WS_VISIBLE | BS_BEFPUSHBUTTON,
//        245, 185, 70, 25,
//        IDC_,
//        "",
//        0
//    }
};

static void my2_proc (HWND hwnd, int id, int nc, DWORD add_data)
{
	SendMessage(GetDlgItem(GetParent(hwnd), IDC_CHAR2), LB_RESETCONTENT, 0, 0);
}

static void writesave(HWND hDlg)
{
	int count  = 0;
	int index2 = 0;
	fp    = fopen(FILE_PHONELIST, "w");
	count = SendMessage(GetDlgItem(hDlg, IDC_CHAR2), LB_GETCOUNT, 0, 0);
	for (index2 = 0; index2 < count; index2++) {
		SendMessage(GetDlgItem(hDlg, IDC_CHAR2), LB_GETTEXT, index2, (LPARAM)phone.peopledata);
		fwrite(&phone, sizeof(struct DATA), 1, fp);
	}
	fclose(fp);
}

static void fill_box(HWND hDlg)
{
	int   i         = 0;
	off_t file_size = 0;
	SendMessage(GetDlgItem(hDlg, IDC_CHAR2), LB_RESETCONTENT, 0, (LPARAM)0);
	if ((fp = fopen(FILE_PHONELIST, "r")) == NULL) {
		MessageBox(hDlg, MSG_READ_PHTOLIST_ERROR, NULL, MB_OK);
	}
	while (!feof(fp)) {
		fread(&phone, sizeof(struct DATA), 1, fp);
		if (!feof(fp)) {
			SendMessage(GetDlgItem(hDlg, IDC_CHAR2), LB_ADDSTRING, i, (LPARAM)phone.peopledata);
		}
	}
	fclose(fp);
}

static int InputCharDialogBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)

{
	hwindowDlg = hDlg;

//    HWND hwnd2;
	switch (message) {
	case MSG_INITDIALOG:
		hwnd2 = CreateWindow(CTRL_BUTTON, MSG_CLEAR,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_CLEAN, 160, 185, 70, 25, hDlg, 0);
		SetNotificationCallback(hwnd2, my2_proc);

		fill_box(hDlg);
		break;

	case MSG_COMMAND:
		switch (wParam) {
		case IDC_NEW:
			Add(hwindowDlg);
			return 0;
		case IDC_DEL:
			del();
			break;
		case IDC_CALL:
			//          index3=SendMessage(GetDlgItem(hwindowDlg,IDC_CHAR2),LB_GETCURSEL,0,0);

			break;
		case IDC_SAVE:
			writesave(hDlg);
			return 0;
		case IDC_KEYBOARD:
			keyboard(hwindowDlg);
			break;
		case IDC_RETURN:
			EndDialog(hDlg, wParam);
			break;
		}
		break;
	case MSG_CLOSE:
		EndDialog(hDlg, wParam);
		break;
	}
	return DefaultDialogProc(hDlg, message, wParam, lParam);
}

void Menu()
{
	DlgBoxInputChar.controls = CtrlInputChar;
	DialogBoxIndirectParam(&DlgBoxInputChar, HWND_DESKTOP, InputCharDialogBoxProc, 0L);
}

