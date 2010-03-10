#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "minigui/common.h"
#include "minigui/minigui.h"
#include "minigui/gdi.h"
#include "minigui/window.h"
#include "minigui/control.h"
#include "pda.h"
#define true              1
#define false             0

#define IDC_INPUT1        120
#define IDC_INPUT2        121
#define IDC_INPUT3        122
#define IDC_INPUT4        123
#define IDC_INPUT5        124
#define IDC_INPUT6        125
#define IDC_INPUT7        126
#define IDC_INPUT8        127
#define IDC_INPUT9        128
#define IDC_RET1          129
#define IDC_RET2          130
#define IDC_INSERT        132
#define IDC_INSERT1       133
#define IDC_INSERT2       134
#define IDC_INSERT3       135
#define IDC_INSERT4       136
#define IDC_INSERT5       137
#define IDC_INSERT6       138
#define IDC_INSERT7       139

#define   Max             140

int flag1 = 0;
int flag2 = 0;
int flag3 = 0;

static int CounterDialogProc(HWND hcwd, int message, WPARAM wParam, LPARAM lParam)
{
	HDC          hdc;
	RECT         rc;
	int          itemcount, i;
	char         buffer1[Max];
	char         buffer2[Max];
	static char  buffer3[Max];
	static float tal;
	static float tall;
	static float sum;
	char         *str;
	static char  ter1[Max] = {'+', '\0'};
	static char  ter2[Max] = {'-', '\0'};
	static char  ter3[Max] = {'*', '\0'};
	static char  ter4[Max] = {'/', '\0'};

	switch (message) {
	case MSG_CREATE:
		flag1 = 0;
		CreateWindow(CTRL_EDIT, "", WS_VISIBLE | WS_BORDER | ES_RIGHT, IDC_INPUT1,
			     15, 10, 280, 25, hcwd, 0);
		CreateWindow(CTRL_BUTTON, MSG_RETURN, WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_RET1,
			     15, 45, 80, 25, hcwd, 0);
		CreateWindow(CTRL_BUTTON, "C", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_RET2,
			     105, 45, 80, 25, hcwd, 0);
		CreateWindow(CTRL_BUTTON, "9", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_INPUT2,
			     15, 80, 60, 25, hcwd, 0);
		CreateWindow(CTRL_BUTTON, "8", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_INPUT3,
			     85, 80, 60, 25, hcwd, 0);
		CreateWindow(CTRL_BUTTON, "7", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_INPUT4,
			     155, 80, 60, 25, hcwd, 0);
		CreateWindow(CTRL_BUTTON, "+", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_INPUT5,
			     225, 80, 60, 25, hcwd, 0);
		CreateWindow(CTRL_BUTTON, "6", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_INPUT6,
			     15, 115, 60, 25, hcwd, 0);
		CreateWindow(CTRL_BUTTON, "5", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_INPUT7,
			     85, 115, 60, 25, hcwd, 0);
		CreateWindow(CTRL_BUTTON, "4", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_INPUT8,
			     155, 115, 60, 25, hcwd, 0);
		CreateWindow(CTRL_BUTTON, "-", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_INPUT9,
			     225, 115, 60, 25, hcwd, 0);
		CreateWindow(CTRL_BUTTON, "3", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_INSERT,
			     15, 150, 60, 25, hcwd, 0);
		CreateWindow(CTRL_BUTTON, "2", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_INSERT1,
			     85, 150, 60, 25, hcwd, 0);
		CreateWindow(CTRL_BUTTON, "1", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_INSERT2,
			     155, 150, 60, 25, hcwd, 0);
		CreateWindow(CTRL_BUTTON, "*", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_INSERT3,
			     225, 150, 60, 25, hcwd, 0);
		CreateWindow(CTRL_BUTTON, "0", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_INSERT4,
			     15, 185, 60, 25, hcwd, 0);
		CreateWindow(CTRL_BUTTON, ".", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_INSERT5,
			     85, 185, 60, 25, hcwd, 0);
		CreateWindow(CTRL_BUTTON, "/", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_INSERT6,
			     155, 185, 60, 25, hcwd, 0);
		CreateWindow(CTRL_BUTTON, "=", WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, IDC_INSERT7,
			     195, 45, 80, 25, hcwd, 0);
		break;

	case MSG_COMMAND:
	{
		switch (wParam)	{
		case IDC_INPUT2:
			if (flag3 == 1) {
				GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
				buffer2[0] = '\0';
				SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			}
			GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
			strcpy(buffer1, "9");
			strcat(buffer2, buffer1);
			SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			flag3 = 0;
			return 0;
		case IDC_INPUT3:
			if (flag3 == 1) {
				GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
				buffer2[0] = '\0';
				SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			}
			GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
			strcpy(buffer1, "8");
			strcat(buffer2, buffer1);
			SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			flag3 = 0;
			return 0;
		case IDC_INPUT4:
			if (flag3 == 1) {
				GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
				buffer2[0] = '\0';
				SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			}
			GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
			strcpy(buffer1, "7");
			strcat(buffer2, buffer1);
			SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			flag3 = 0;
			return 0;
		case IDC_INPUT6:
			if (flag3 == 1) {
				GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
				buffer2[0] = '\0';
				SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			}
			GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
			strcpy(buffer1, "6");
			strcat(buffer2, buffer1);
			SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			flag3 = 0;
			return 0;
		case IDC_INPUT7:
			if (flag3 == 1) {
				GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
				buffer2[0] = '\0';
				SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			}
			GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
			strcpy(buffer1, "5");
			strcat(buffer2, buffer1);
			SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			flag3 = 0;
			return 0;
		case IDC_INPUT8:
			if (flag3 == 1) {
				GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
				buffer2[0] = '\0';
				SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			}
			GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
			strcpy(buffer1, "4");
			strcat(buffer2, buffer1);
			SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			flag3 = 0;
			return 0;
		case IDC_INSERT:
			if (flag3 == 1) {
				GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
				buffer2[0] = '\0';
				SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			}
			GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
			strcpy(buffer1, "3");
			strcat(buffer2, buffer1);
			SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			flag3 = 0;
			return 0;
		case IDC_INSERT1:
			if (flag3 == 1) {
				GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
				buffer2[0] = '\0';
				SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			}
			GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
			strcpy(buffer1, "2");
			strcat(buffer2, buffer1);
			SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			flag3 = 0;
			return 0;
		case IDC_INSERT2:
			if (flag3 == 1) {
				GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
				buffer2[0] = '\0';
				SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			}
			GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
			strcpy(buffer1, "1");
			strcat(buffer2, buffer1);
			SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			flag3 = 0;
			return 0;
		case IDC_INSERT4:
			if (flag3 == 1) {
				GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
				buffer2[0] = '\0';
				SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			}
			if (strcmp(buffer3, ter4) != 0)	{
				GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
				strcpy(buffer1, "0");
				strcat(buffer2, buffer1);
				SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
				flag3 = 0;
			}
			return 0;

		case IDC_INSERT5:
			if (flag1 == 0)	{
				flag1 = 1;
				GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
				if (buffer2[0] == '\0') {
					strcpy(buffer1, "0");
					strcat(buffer2, buffer1);
					strcpy(buffer1, ".");
					strcat(buffer2, buffer1);
				} else   {
					strcpy(buffer1, ".");
					strcat(buffer2, buffer1);
				}
				SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			}
			return 0;


		case IDC_INPUT5:
			if (flag2 == 1) {
				GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
				str = buffer2;
				tal = atof(str);
				if (strcmp(buffer3, ter1) == 0)	{
					sum = tall + tal;
					sprintf(buffer2, "%f", sum);
					SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
				} else if (strcmp(buffer3, ter2) == 0) {
					sum = tall - tal;
					sprintf(buffer2, "%f", sum);
					SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
				} else if (strcmp(buffer3, ter3) == 0)            {
					sum = tall * tal;
					sprintf(buffer2, "%f", sum);
					SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
				} else if (strcmp(buffer3, ter4) == 0)            {
					sum = tall / tal;
					sprintf(buffer2, "%f", sum);
					SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
				}
			}
			GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
			str  = buffer2;
			tall = atof(str);
			strcpy(buffer3, "+");
			buffer2[0] = '\0';
			SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			flag1 = 0;
			flag2 = 1;
			return 0;
		case IDC_INPUT9:
			if (flag2 == 1) {
				GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
				str = buffer2;
				tal = atof(str);
				if (strcmp(buffer3, ter1) == 0)	{
					sum = tall + tal;
					sprintf(buffer2, "%f", sum);
					SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
				} else if (strcmp(buffer3, ter2) == 0)       {
					sum = tall - tal;
					sprintf(buffer2, "%f", sum);
					SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
				} else if (strcmp(buffer3, ter3) == 0)              {
					sum = tall * tal;
					sprintf(buffer2, "%f", sum);
					SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
				} else if (strcmp(buffer3, ter4) == 0)              {
					sum = tall / tal;
					sprintf(buffer2, "%f", sum);
					SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
				}
			}
			GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
			str  = buffer2;
			tall = atof(str);
			strcpy(buffer3, "-");
			buffer2[0] = '\0';
			SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			flag1 = 0;
			return 0;
		case IDC_INSERT3:
			if (flag2 == 1) {
				GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
				str = buffer2;
				tal = atof(str);
				if (strcmp(buffer3, ter1) == 0)	{
					sum = tall + tal;
					sprintf(buffer2, "%f", sum);
					SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
				} else if (strcmp(buffer3, ter2) == 0) {
					sum = tall - tal;
					sprintf(buffer2, "%f", sum);
					SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
				} else if (strcmp(buffer3, ter3) == 0)            {
					sum = tall * tal;
					sprintf(buffer2, "%f", sum);
					SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
				} else if (strcmp(buffer3, ter4) == 0)            {
					sum = tall / tal;
					sprintf(buffer2, "%f", sum);
					SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
				}
			}
			GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
			str  = buffer2;
			tall = atof(str);
			strcpy(buffer3, "*");
			buffer2[0] = '\0';
			SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			flag1 = 0;
			return 0;
		case IDC_INSERT6:
			if (flag2 == 1) {
				GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
				str = buffer2;
				tal = atof(str);
				if (strcmp(buffer3, ter1) == 0)	{
					sum = tall + tal;
					sprintf(buffer2, "%f", sum);
					SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
				} else if (strcmp(buffer3, ter2) == 0) {
					sum = tall - tal;
					sprintf(buffer2, "%f", sum);
					SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
				} else if (strcmp(buffer3, ter3) == 0)            {
					sum = tall * tal;
					sprintf(buffer2, "%f", sum);
					SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
				} else if (strcmp(buffer3, ter4) == 0)            {
					sum = tall / tal;
					sprintf(buffer2, "%f", sum);
					SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
				}
			}
			GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
			str  = buffer2;
			tall = atof(str);
			strcpy(buffer3, "/");
			buffer2[0] = '\0';
			SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			flag1 = 0;
			return 0;
		case IDC_INSERT7:
			GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
			str = buffer2;
			//MessageBox(0,str,"",MB_OK);
			//MessageBox(0,buffer1,"",MB_OK);
			//printf("%f",tall);
			tal   = atof(str);
			flag1 = 1;
			if (strcmp(buffer3, ter1) == 0)	{
				sum = tall + tal;
				sprintf(buffer2, "%f", sum);
				SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			} else if (strcmp(buffer3, ter2) == 0)       {
				sum = tall - tal;
				sprintf(buffer2, "%f", sum);
				SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			} else if (strcmp(buffer3, ter3) == 0)               {
				sum = tall * tal;
				sprintf(buffer2, "%f", sum);
				SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			} else if (strcmp(buffer3, ter4) == 0)              {
				sum = tall / tal;
				sprintf(buffer2, "%f", sum);
				SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			}
			flag2 = 0;
			flag3 = 1;
			return 0;

		case IDC_RET2:
			GetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2, Max);
			buffer2[0] = '\0';
			SetWindowText(GetDlgItem(hcwd, IDC_INPUT1), buffer2);
			flag1 = 0;
			return 0;

		case IDC_RET1:
			//DestroyAllControls(hcwd);
			DestroyMainWindow(hcwd);
			PostQuitMessage(hcwd);
			return 0;
		}
	}
	break;

	case MSG_DESTROY:
		DestroyAllControls(hcwd);
		return 0;

	case MSG_CLOSE:
		DestroyMainWindow(hcwd);
		PostQuitMessage(hcwd);
		return 0;
	}
	return DefaultMainWinProc(hcwd, message, wParam, lParam);
}

int CreateCounterDialog(HWND hWnd)
{
	MSG           Msg;
	HWND          hcwd;
	MAINWINCREATE CreateInfo;
#ifdef _LITE_VERSION
	SetDesktopRect(0, 0, 1024, 768);
#endif
	CreateInfo.dwStyle        = WS_VISIBLE | WS_BORDER | WS_CAPTION;
	CreateInfo.dwExStyle      = WS_EX_NONE;
	CreateInfo.spCaption      = MSG_CALCULATION;
	CreateInfo.hMenu          = 0;
	CreateInfo.hCursor        = GetSystemCursor(0);
	CreateInfo.hIcon          = 0;
	CreateInfo.MainWindowProc = CounterDialogProc;
	CreateInfo.lx             = 0;
	CreateInfo.ty             = 0;
	CreateInfo.rx             = 320;
	CreateInfo.by             = 240;
	CreateInfo.iBkColor       = COLOR_lightwhite;
	CreateInfo.dwAddData      = 0;
	CreateInfo.hHosting       = hWnd;

	hcwd = CreateMainWindow(&CreateInfo);

	ShowWindow(hcwd, SW_SHOWNORMAL);

	while (GetMessage(&Msg, hcwd)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	MainWindowThreadCleanup(hcwd);
	return 0;
}

