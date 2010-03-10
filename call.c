#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/mywindows.h>
#include <minigui/control.h>
#include <minigui/mgext.h>

#include "tty.h"

#include "call.h"

#include "gprs.h"
#include "lang.h"


extern void *message_read_com(void *age);
char       buffer[20] = {0};
char       buffer1[20] = {0};
int        flag = 0;
extern int maintime;   //把這個變量放到主函數開頭位置
FILE       *fp;
static int T    = 0;
static int KBOn = 0;
static int flagcall;

static void ContactNotifProc (HWND hcwd, int id, int nc, DWORD add_data)
{
	if (nc == EN_CLICKED) {
		hedit = GetDlgItem(hcwd, IDC_KB);
		SendMessage(GetDlgItem(hcwd, IDC_EDIT), MSG_SETTEXT, 1, (LPARAM)buff);
	}
}

static int CallWinProc(HWND hcwd, int message, WPARAM wParam, LPARAM lParam)
{
	HWND Kb;
	switch (message) {
	case MSG_CREATE:
		CreateWindow(CTRL_STATIC,
			     MSG_INPUT_NUMBER,
			     WS_VISIBLE,
			     IDC_STA,
			     0, 0, 80, 20,
			     hcwd,
			     0);
		CreateWindow(CTRL_STATIC,
			     "",
			     WS_VISIBLE,
			     IDC_STAW,
			     100, 20, 120, 20,
			     hcwd,
			     0);
		hedit = CreateWindow(CTRL_EDIT,
				     "",
				     WS_CHILD | WS_VISIBLE | WS_BORDER,
				     IDC_EDIT,
				     100, 0, 120, 20,
				     hcwd,
				     0);
		SetNotificationCallback(GetDlgItem(hcwd, IDC_EDIT), ContactNotifProc);

		/*CreateWindow ( CTRL_BUTTON,
			     "編輯",
						     WS_CHILD|WS_VISIBLE,
			     IDC_MAKE,
						     120,50,65,20,
			     hcwd,
			     0);*/
		CreateWindow( CTRL_BUTTON,
			      MSG_OK,
			      WS_CHILD | WS_VISIBLE,
			      IDC_OK,
			      50, 50, 65, 20,
			      hcwd,
			      0);
		CreateWindow( CTRL_BUTTON,
			      MSG_PHONEBOOK,
			      WS_CHILD | WS_VISIBLE,
			      IDC_BOOK,
			      255, 0, 65, 30,
			      hcwd,
			      0);
		CreateWindow( CTRL_BUTTON,
			      MSG_CANCEL,
			      WS_CHILD | WS_VISIBLE,
			      IDC_CANCEL,
			      190, 50, 65, 20,
			      hcwd,
			      0);
		CreateWindow( CTRL_BUTTON,
			      "1",
			      WS_CHILD | WS_VISIBLE,
			      IDC_NUM1,
			      50, 80, 65, 20,
			      hcwd,
			      0);
		CreateWindow( CTRL_BUTTON,
			      "2",
			      WS_CHILD | WS_VISIBLE,
			      IDC_NUM2,
			      120, 80, 65, 20,
			      hcwd,
			      0);
		CreateWindow( CTRL_BUTTON,
			      "3",
			      WS_CHILD | WS_VISIBLE,
			      IDC_NUM3,
			      190, 80, 65, 20,
			      hcwd,
			      0);
		CreateWindow( CTRL_BUTTON,
			      "4",
			      WS_CHILD | WS_VISIBLE,
			      IDC_NUM4,
			      50, 110, 65, 20,
			      hcwd,
			      0);
		CreateWindow( CTRL_BUTTON,
			      "5",
			      WS_CHILD | WS_VISIBLE,
			      IDC_NUM5,
			      120, 110, 65, 20,
			      hcwd,
			      0);
		CreateWindow( CTRL_BUTTON,
			      "6",
			      WS_CHILD | WS_VISIBLE,
			      IDC_NUM6,
			      190, 110, 65, 20,
			      hcwd,
			      0);
		CreateWindow( CTRL_BUTTON,
			      "7",
			      WS_CHILD | WS_VISIBLE,
			      IDC_NUM7,
			      50, 140, 65, 20,
			      hcwd,
			      0);
		CreateWindow( CTRL_BUTTON,
			      "8",
			      WS_CHILD | WS_VISIBLE,
			      IDC_NUM8,
			      120, 140, 65, 20,
			      hcwd,
			      0);
		CreateWindow( CTRL_BUTTON,
			      "9",
			      WS_CHILD | WS_VISIBLE,
			      IDC_NUM9,
			      190, 140, 65, 20,
			      hcwd,
			      0);
		CreateWindow( CTRL_BUTTON,
			      "*",
			      WS_CHILD | WS_VISIBLE,
			      IDC_NUMX,
			      50, 170, 65, 20,
			      hcwd,
			      0);
		CreateWindow( CTRL_BUTTON,
			      "0",
			      WS_CHILD | WS_VISIBLE,
			      IDC_NUM0,
			      120, 170, 65, 20,
			      hcwd,
			      0);
		CreateWindow( CTRL_BUTTON,
			      "#",
			      WS_CHILD | WS_VISIBLE,
			      IDC_NUMY,
			      190, 170, 65, 20,
			      hcwd,
			      0);
		CreateWindow( CTRL_BUTTON,
			      MSG_EXIT,
			      WS_CHILD | WS_VISIBLE,
			      IDC_NUMQ,
			      0, 190, 65, 30,
			      hcwd,
			      0);

		/* CreateWindow ( CTRL_BUTTON,
				      "軟鍵盤",
							      WS_CHILD|WS_VISIBLE,
				      IDC_NUMS,
							      255,190,65,30,
				      hcwd,
				      0);	 */
		SetTimer(hcwd, _IDC_TIMER, 100);

		break;
	case MSG_TIMER:
	{
		if (wParam == _IDC_TIMER) {
			if (flag) {
				T++;
				maintime = maintime + T;
				sprintf(buffer, "%02d:%02d:%02d", T / 3600, (T % 3600) / 60, (T % 3600) % 60);
				SetWindowText(GetDlgItem(hcwd, IDC_STAW), buffer);
			}
		}
	}
	case MSG_COMMAND:
	{
		switch (wParam)	{
		case IDC_NUM1:
			SendMessage(GetDlgItem(hcwd, IDC_NUM1), MSG_GETTEXT, 1, (LPARAM)buff1);
			strcat(buff, buff1);
			SendMessage(GetDlgItem(hcwd, IDC_EDIT), MSG_SETTEXT, 1, (LPARAM)buff);
			break;
		case IDC_NUM2:
			SendMessage(GetDlgItem(hcwd, IDC_NUM2), MSG_GETTEXT, 1, (LPARAM)buff1);
			strcat(buff, buff1);
			SendMessage(GetDlgItem(hcwd, IDC_EDIT), MSG_SETTEXT, 1, (LPARAM)buff);
			break;
		case IDC_NUM3:
			SendMessage(GetDlgItem(hcwd, IDC_NUM3), MSG_GETTEXT, 1, (LPARAM)buff1);
			strcat(buff, buff1);
			SendMessage(GetDlgItem(hcwd, IDC_EDIT), MSG_SETTEXT, 1, (LPARAM)buff);
			break;
		case IDC_NUM4:
			SendMessage(GetDlgItem(hcwd, IDC_NUM4), MSG_GETTEXT, 1, (LPARAM)buff1);
			strcat(buff, buff1);
			SendMessage(GetDlgItem(hcwd, IDC_EDIT), MSG_SETTEXT, 1, (LPARAM)buff);
			break;
		case IDC_NUM5:
			SendMessage(GetDlgItem(hcwd, IDC_NUM5), MSG_GETTEXT, 1, (LPARAM)buff1);
			strcat(buff, buff1);
			SendMessage(GetDlgItem(hcwd, IDC_EDIT), MSG_SETTEXT, 1, (LPARAM)buff);
			break;
		case IDC_NUM6:
			SendMessage(GetDlgItem(hcwd, IDC_NUM6), MSG_GETTEXT, 1, (LPARAM)buff1);
			strcat(buff, buff1);
			SendMessage(GetDlgItem(hcwd, IDC_EDIT), MSG_SETTEXT, 1, (LPARAM)buff);
			break;
		case IDC_NUM7:
			SendMessage(GetDlgItem(hcwd, IDC_NUM7), MSG_GETTEXT, 1, (LPARAM)buff1);
			strcat(buff, buff1);
			SendMessage(GetDlgItem(hcwd, IDC_EDIT), MSG_SETTEXT, 1, (LPARAM)buff);
			break;
		case IDC_NUM8:
			SendMessage(GetDlgItem(hcwd, IDC_NUM8), MSG_GETTEXT, 1, (LPARAM)buff1);
			strcat(buff, buff1);
			SendMessage(GetDlgItem(hcwd, IDC_EDIT), MSG_SETTEXT, 1, (LPARAM)buff);
			break;
		case IDC_NUM9:
			SendMessage(GetDlgItem(hcwd, IDC_NUM9), MSG_GETTEXT, 1, (LPARAM)buff1);
			strcat(buff, buff1);
			SendMessage(GetDlgItem(hcwd, IDC_EDIT), MSG_SETTEXT, 1, (LPARAM)buff);
			break;
		case IDC_NUMX:
			SendMessage(GetDlgItem(hcwd, IDC_NUMX), MSG_GETTEXT, 1, (LPARAM)buff1);
			strcat(buff, buff1);
			SendMessage(GetDlgItem(hcwd, IDC_EDIT), MSG_SETTEXT, 1, (LPARAM)buff);
			break;
		case IDC_NUM0:
			SendMessage(GetDlgItem(hcwd, IDC_NUM0), MSG_GETTEXT, 1, (LPARAM)buff1);
			strcat(buff, buff1);
			SendMessage(GetDlgItem(hcwd, IDC_EDIT), MSG_SETTEXT, 1, (LPARAM)buff);
			break;
		case IDC_NUMY:
			SendMessage(GetDlgItem(hcwd, IDC_NUMY), MSG_GETTEXT, 1, (LPARAM)buff1);
			strcat(buff, buff1);
			SendMessage(GetDlgItem(hcwd, IDC_EDIT), MSG_SETTEXT, 1, (LPARAM)buff);
			break;

		case IDC_BOOK:
			Menu();
			break;

		case IDC_OK:
			flag = 1;
			if (flagcall == 1) {
				if (flag_call_ans == 1)	{
					gprs_ans();
					flagcall = 0;
				}
				if (buff[0] != '\0') {
					gprs_call(buff, strlen(buff));
					strcpy(buff, MSG_DIAL);
					SendMessage(GetDlgItem(hcwd, IDC_EDIT), MSG_SETTEXT, 0, (LPARAM)buff);
					flagcall = 0;
				}
			}
			break;
		case IDC_CANCEL:
			flag = 0;
			T    = 0;
			sprintf(buffer1, "%02d:%02d:%02d", 0, 0, 0);
			SetWindowText(GetDlgItem(hcwd, IDC_STAW), buffer1);
			fp = fopen(FILE_LAST_TIME_DAT, "w");
			fwrite(buffer, sizeof(buffer), 1, fp);
			fclose(fp);
			if (flagcall == 0) {
				gprs_hold();
				flagcall = 1;
				strcpy(buff, MSG_HUNG_UP);
				SendMessage(GetDlgItem(hcwd, IDC_EDIT), MSG_SETTEXT, 0, (LPARAM)buff);
			} else      {
				i           = strlen(buff);
				buff[i - 1] = '\0';
				SendMessage(GetDlgItem(hcwd, IDC_EDIT), MSG_SETTEXT, i - 1, (LPARAM)buff);
			}
			break;
		case IDC_NUMQ:
			flag = 0;
			T    = 0;
			KillTimer(hcwd, _IDC_TIMER);
			//DestroyMainWindow (hcwd);
			//PostQuitMessage (hcwd);
			ShowWindow(hcwd, SW_HIDE);
			break;

		/*  case IDC_NUMS:
				if(KBOn==0)
				      {
						      KBOn = 1;
						      CreateKeyBoard(hcwd);
				      }
				      else
				{
						      KBOn = 0;
					  Kb = GetFirstHosted(hcwd);
					  DestroyAllControls (Kb);
					  DestroyMainWindow (Kb);
			      PostQuitMessage (Kb);
				}

		   break;  */
		default: break;
		}
	}
	break;
	case MSG_TAG:
		ShowWindow(hcwd, SW_SHOWNORMAL);
		break;
	case MSG_RING:
		ShowWindow(hcwd, SW_SHOWNORMAL);
		if (IDYES == MessageBox(hcwd, MSG_PHONE_CALL, MSG_INDICATION, MB_YESNO)) {
			flag_call_ans = 1;
			flagcall == 1;
		} else   {
			gprs_hold();
		}
		return 0;
	case MSG_DESTROY:
		DestroyAllControls(hcwd);
		return 0;

	case MSG_CLOSE:
		flag = 0;
		T    = 0;
		KillTimer(hcwd, _IDC_TIMER);
		DestroyMainWindow(hcwd);
		PostQuitMessage(hcwd);
		return 0;
	}

	return DefaultMainWinProc(hcwd, message, wParam, lParam);
}

int CreateCallDialog (HWND hWnd)
{
	MSG Msg;
	//pthread_t th_message_read;
	MAINWINCREATE CreateInfo;
#ifdef _LITE_VERSION
	SetDesktopRect(0, 0, 1024, 768);
#endif

	CreateInfo.dwStyle        = WS_VISIBLE | WS_BORDER | WS_CAPTION;
	CreateInfo.dwExStyle      = WS_EX_NONE;
	CreateInfo.spCaption      = MSG_CALL;
	CreateInfo.hMenu          = 0;
	CreateInfo.hCursor        = GetSystemCursor(0);
	CreateInfo.hIcon          = 0;
	CreateInfo.MainWindowProc = CallWinProc;
	CreateInfo.lx             = 0;
	CreateInfo.ty             = 0;
	CreateInfo.rx             = 320;
	CreateInfo.by             = 240;
	CreateInfo.iBkColor       = COLOR_lightwhite;
	CreateInfo.dwAddData      = 0;
	CreateInfo.hHosting       = hWnd;

	hcwd = CreateMainWindow(&CreateInfo);


	//tty_init();
	//gprs_init();
	//pthread_create (&th_message_read, NULL, message_read_com, NULL);
	flagcall = 1;
	if (tag == 0) {
		ShowWindow(hcwd, SW_HIDE);
	}
	//else
	// ShowWindow(hcwd, SW_SHOWNORMAL);
	// tag = 2;
	while (GetMessage(&Msg, hcwd)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	// pthread_join (th_message_read, NULL);
	tty_end();
	MainWindowThreadCleanup(hcwd);

	return 0;
}

