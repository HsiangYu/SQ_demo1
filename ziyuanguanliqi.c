#include <stdio.h>
#include <stdlib.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <stdarg.h>
#include <errno.h>
#include "lang.h"
#include "sys_serv.h"

#define IDC_XZ_DIR          1470
#define IDC_XZ_FILE         1471
#define IDC_XZ_PATH         1472
#define IDC_XZ_DELETE       1473
#define IDC_XZ_RETURN       1474
//#define IDC_XZ_VIEW       1475

static char fullpath2[PATH_MAX + 1];
HWND        hDir, hFile, hPath;

/*******************************************************************************
* File Name: ziyuanguanliqi.c
* Copy Right: GaoHaibo
* Author:  GaoHaibo
* Function discription:
*******************************************************************************/
static void fill_boxes (HWND hDlg, const char* path)
{

	struct dirent * dir_ent;
	DIR           * dir;

	struct stat ftype;
	char        fullpath [PATH_MAX + 1];

	SendMessage(hDir, LB_RESETCONTENT, 0, (LPARAM)0);
	SendMessage(hFile, LB_RESETCONTENT, 0, (LPARAM)0);
	SetWindowText(hPath, path);

	if ((dir = opendir(path)) == NULL) {
		return;
	}

	while ((dir_ent = readdir( dir )) != NULL) {
		strncpy(fullpath, path, PATH_MAX);
		strcat(fullpath, "/");
		strncpy(fullpath2, fullpath, PATH_MAX + 1);
		strcat(fullpath, dir_ent->d_name);

		if (stat(fullpath, &ftype) < 0) {
			continue;
		}

		if (S_ISDIR(ftype.st_mode)) {
			SendDlgItemMessage(hDlg, IDC_XZ_DIR, LB_ADDSTRING, 0, (LPARAM)dir_ent->d_name);
		} else if (S_ISREG(ftype.st_mode)) {
			LISTBOXITEMINFO lbii;


			lbii.string = dir_ent->d_name;
			lbii.cmFlag = CMFLAG_BLANK;
			lbii.hIcon  = 0;
			SendDlgItemMessage(hDlg, IDC_XZ_FILE, LB_ADDSTRING, 0, (LPARAM)&lbii);

		}
	}

	closedir(dir);

}

/*******************************************************************************
* File Name: ziyuanguanliqi.c
* Copy Right: GaoHaibo
* Author:  GaoHaibo
* Function discription:處理路徑
*******************************************************************************/
static void dir_notif_proc (HWND hcwd, int id, int nc, DWORD add_data)
{
	if (nc == LBN_CLICKED || nc == LBN_ENTER) {
		int cur_sel = SendMessage(hcwd, LB_GETCURSEL, 0, 0L);
		if (cur_sel >= 0) {
			char cwd [MAX_PATH + 1];
			char dir [MAX_NAME + 1];
			GetWindowText(GetDlgItem(GetParent(hcwd), IDC_XZ_PATH), cwd, MAX_PATH);
			SendMessage(hcwd, LB_GETTEXT, cur_sel, (LPARAM)dir);

			if (strcmp(dir, ".") == 0) {
				return;
			}
			strcat(cwd, "/");			
			strcat(cwd, dir);
			fill_boxes(GetParent(hcwd), cwd);
		}
	}
}

static void file_notif_proc (HWND hcwd, int id, int nc, DWORD add_data)
{
}

/*******************************************************************************
* File Name: ziyuanguanliqi.c
* Copy Right: GaoHaibo
* Author:  GaoHaibo
* Function discription:選擇要刪除的文件
*******************************************************************************/
static void DeleteFile(HWND hDlg)
{
	int  i;
	char file [MAX_NAME + 1];
	char filet[MAX_NAME + 1];
	char files [1024] = MSG_DEL_FILE;
	char str1[50];
	int  status;

	for (i = 0; i < SendDlgItemMessage(hDlg, IDC_XZ_FILE, LB_GETCOUNT, 0, 0L); i++) {

		status = SendDlgItemMessage(hDlg, IDC_XZ_FILE, LB_GETCHECKMARK, i, 0);
		if (status == CMFLAG_CHECKED) {
			SendDlgItemMessage(hDlg, IDC_XZ_FILE, LB_GETTEXT, i, (LPARAM)file);
			strcat(files, file);
			strcat(filet, file);
			strcat(filet, " ");
			strcat(files, "\n");
		}
	}
	if (IDOK == MessageBox(hDlg, files, "OK", MB_OK | MB_ICONINFORMATION)) {
		for (i = 0; i < SendDlgItemMessage(hDlg, IDC_XZ_FILE, LB_GETCOUNT, 0, 0L); i++) {
			status = SendDlgItemMessage(hDlg, IDC_XZ_FILE, LB_GETCHECKMARK, i, 0);
			if (status == CMFLAG_CHECKED) {
				SendMessage(GetDlgItem(hDlg, IDC_XZ_FILE), LB_DELETESTRING, i, 0);
				i = 0;
			}

		}
		sprintf(str1, "rm -rf /mnt/sd/demo/%s", filet);
		printf("s =%s", filet);
		//system(str1);
		SYS_SERV_CALL(str1);
	}
}


/*******************************************************************************
* File Name: ziyuanguanliqi.c
* Copy Right: GaoHaibo
* Author:  GaoHaibo
* Function discription:點擊主窗口資源管理器初始窗口
*******************************************************************************/



static int ZiYuanguanliqiProc(HWND hcwd, int message, WPARAM wParam, LPARAM lParam)
{
	{

		switch (message) {
		case MSG_CREATE:
		{

			char cwd [MAX_PATH + 1];
			loadbk(hcwd);	
#if 1

			CreateWindow(CTRL_STATIC, MSG_TARGET_DIR, WS_VISIBLE | SS_SIMPLE, IDC_STATIC, 10, 2, 120, 25, hcwd, 0);				     	 
			hFile = CreateWindow(CTRL_LISTBOX, "", WS_VISIBLE | WS_VSCROLL | WS_BORDER | LBS_SORT | LBS_AUTOCHECKBOX, IDC_XZ_FILE, 10, 20, 280, 140, hcwd, 0);			     
			     
#else
			CreateWindow(CTRL_STATIC, "Directory List Box", WS_VISIBLE | SS_SIMPLE, IDC_STATIC, 10, 2, 120, 25, hcwd, 0);			
				 
			hDir = CreateWindow(CTRL_LISTBOX, "", WS_VISIBLE | WS_VSCROLL | WS_BORDER | LBS_SORT | LBS_NOTIFY, IDC_XZ_DIR, 10, 20, 140, 140, hcwd, 0);

			CreateWindow(CTRL_STATIC, "File List Box", WS_VISIBLE | SS_SIMPLE, IDC_STATIC, 165, 2, 120, 25, hcwd, 0);

			hFile = CreateWindow(CTRL_LISTBOX, "", WS_VISIBLE | WS_VSCROLL | WS_BORDER | LBS_SORT | LBS_AUTOCHECKBOX, IDC_XZ_FILE, 165, 20, 140, 140, hcwd, 0);

			hPath = CreateWindow(CTRL_STATIC, MSG_PATH, WS_VISIBLE | SS_SIMPLE, IDC_XZ_PATH, 10, 150, 315, 0, hcwd, 0);

#endif

			CreateWindow
				 (CTRL_BUTTON, MSG_DELECT, WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP | WS_GROUP, IDC_XZ_DELETE, 15, 165, 130, 25, hcwd, 0);

//			CreateWindow
//				 (CTRL_BUTTON, MSG_VIEW, WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP | WS_GROUP, IDC_XZ_VIEW, 15, 185, 130, 25, hcwd, 0);


			CreateWindow
				 (CTRL_BUTTON, MSG_RETURN, WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, IDC_XZ_RETURN, 170, 165, 130, 25, hcwd, 0);

			SetNotificationCallback(hFile, file_notif_proc);
			SetNotificationCallback(hDir, dir_notif_proc);
			//fill_boxes(hcwd, getcwd(cwd, MAX_PATH));
			fill_boxes(hcwd, MSG_TARGET_DIR);			
		}
		break;


		case MSG_CLOSE:
		{
			DestroyMainWindow(hcwd);
			PostQuitMessage(hcwd);
		}
			return 0;

		case MSG_COMMAND:
		{
			switch (wParam) {
			case IDC_XZ_DELETE:    /*刪除指定文件*/
				DeleteFile(hcwd);
				break;

			//case IDC_XZ_VIEW:
			//	View(hcwd);
			case IDC_XZ_RETURN:     /*返回主界面*/
				DestroyMainWindow(hcwd);
				PostQuitMessage(hcwd);
				break;

			}
		}
			return 0;
		}
		return DefaultMainWinProc(hcwd, message, wParam, lParam);
	}
}

int Ziyuanguanli (HWND hWnd)
{
	int           i = 99;
	MSG           Msg;
	HWND          hcwd;
	MAINWINCREATE CreateInfo;

#ifdef _LITE_VERSION
	SetDesktopRect(0, 0, 800, 600);
#endif

	CreateInfo.dwStyle        = WS_VISIBLE | WS_BORDER | WS_CAPTION;
	CreateInfo.dwExStyle      = WS_EX_NONE;
	CreateInfo.spCaption      = "Explorer";
	CreateInfo.hMenu          = 0;
	CreateInfo.hCursor        = GetSystemCursor(0);
	CreateInfo.hIcon          = 0;
	CreateInfo.MainWindowProc = ZiYuanguanliqiProc;
	CreateInfo.lx             = 0;
	CreateInfo.ty             = 0;
	CreateInfo.rx             = 320;
	CreateInfo.by             = 240;
	CreateInfo.iBkColor       = COLOR_lightgray;
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

