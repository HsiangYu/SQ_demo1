#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <errno.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include "pdas.h"
#include "mplayer.h"
#include "mini133.h"
struct musiclist list;
static HWND             fWnd;


typedef struct _MAINWIN
{
    /*
     * These fields are similiar with CONTROL struct.
     */
    short DataType;		// the data type.
    short WinType;		// the window type.
}MAINWIN2;
typedef MAINWIN2* PMAINWIN2;
PMAINWIN2 pWin2;  //channing	

static void fill_boxes (HWND hWnd, const char* path)
{
	struct dirent * dir_ent;
	DIR           * dir;
	struct stat   ftype;
	char          fullpath [PATH_MAX + 1];

        DEB("-fill_boxes: path=%s\n ",path);

	SendDlgItemMessage(hWnd, IDC_FUN_3G_NOW_LISTBOX_FILE, LB_RESETCONTENT, 0, (LPARAM)0);
	SendDlgItemMessage(hWnd, IDC_FUN_3G_ADD_LISTBOX_FILE, LB_RESETCONTENT, 0, (LPARAM)0);
	SetWindowText(GetDlgItem(hWnd, IDC_FUN_MPLAYER_MUSICADD_STATIC_PATH), path);

	if ((dir = opendir(path)) == NULL) {
		DEB("--return\n "); 	
		return;
	}
        DEB("--path open ok\n ");
	while ((dir_ent = readdir( dir )) != NULL) {
		strncpy(fullpath, path, PATH_MAX);
		strcat(fullpath, "/");
		strcat(fullpath, dir_ent->d_name);

		if (stat(fullpath, &ftype) < 0)	{
			continue;
		}

		if (S_ISDIR(ftype.st_mode)) {
			SendDlgItemMessage(hWnd, IDC_FUN_3G_NOW_LISTBOX_FILE, LB_ADDSTRING, 0, (LPARAM)dir_ent->d_name);
		}	else if (S_ISREG(ftype.st_mode)) {
			SendDlgItemMessage(hWnd, IDC_FUN_3G_ADD_LISTBOX_FILE, LB_ADDSTRING, 0, (LPARAM)dir_ent->d_name);
		}
	}

	closedir(dir);
        DEB("--path close\n ");	
}

static void now_notif_proc (HWND hwnd, int id, int nc, DWORD add_data)
{
	int index;

        DEB("-now_notif_proc: \n ");
        
	if (nc == LBN_CLICKED || nc == LBN_ENTER) {
		index = SendMessage(hwnd, LB_GETCURSEL, 0, 0);

		SendMessage(hwnd, LB_GETTEXT, index, (LPARAM)list.name);
		strtok(list.name, ".");
		SetWindowText(GetDlgItem(GetParent(hwnd), IDC_FUN_MPLAYER_MUSICADD_SLEDIT_NAME), list.name);
	}
}

static void file_notif_proc (HWND hwnd, int id, int nc, DWORD add_data)
{
	int index;

        DEB("-file_notif_proc: \n ");
        
	if (nc == LBN_CLICKED || nc == LBN_ENTER) {
		index = SendMessage(hwnd, LB_GETCURSEL, 0, 0);

		SendMessage(hwnd, LB_GETTEXT, index, (LPARAM)list.name);
		strtok(list.name, ".");
		SetWindowText(GetDlgItem(GetParent(hwnd), IDC_FUN_MPLAYER_MUSICADD_SLEDIT_NAME), list.name);
	}
}

int fn_3gFileSave(HWND hWnd)
{
	FILE *fp_music;
	char cwd[MAX_PATH + 1];
	int  index;
	char name[MAX_PATH + 1];

        DEB("-fn_3gFileSave: \n ");

	if ((fp_music = fopen(FILE_MUSIC_TMP_FILE, "a+")) == NULL) {
		MessageBox(hWnd, FILE_FILE_ERROR, "", MB_OK | MB_ICONINFORMATION);
		DEB("--return\n "); 		
		return;
	}
        DEB("--fopen %s\n ",FILE_MUSIC_TMP_FILE);

	index = SendMessage(GetDlgItem(hWnd, IDC_FUN_3G_ADD_LISTBOX_FILE), LB_GETCURSEL, 0, 0);
	SendMessage(GetDlgItem(hWnd, IDC_FUN_3G_ADD_LISTBOX_FILE), LB_GETTEXT, index, (LPARAM)name);
	GetWindowText(GetDlgItem(hWnd, IDC_FUN_MPLAYER_MUSICADD_SLEDIT_NAME), list.name, sizeof(list.name));
	GetWindowText(GetDlgItem(hWnd, IDC_FUN_MPLAYER_MUSICADD_SLEDIT_SINGER), list.singer, sizeof(list.singer));

        DEB("--cwd=%s\n ",cwd);
        
	getcwd(cwd, MAX_PATH);	
        DEB("--cwd=%s\n ",cwd);	
        
	strcat(cwd, FILE_MPLAYER_DIR);	
        DEB("--cwd=%s\n ",cwd);	
        
	strcat(cwd, name);
        DEB("--cwd=%s\n ",cwd);
        	
	strcpy(list.path, cwd);
        DEB("--list.path=%s\n ",list.path);
        
	fwrite(&list, sizeof(struct musiclist), 1, fp_music);
        DEB("--fwrite \n ");	
	
	fclose(fp_music);
        DEB("--fclose ok\n ");	
}

static int Desktop(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
	char cwd[MAX_PATH + 1];

        //DEB("-Desktop: \n ");

	switch (message) {
	case MSG_CREATE:
	{
                DEB("--MSG_CREATE\n ");	
                /*	
		CreateWindow(CTRL_LISTBOX,
			     "",
			     LBS_NOTIFY  | WS_VSCROLL | WS_BORDER | WS_VISIBLE,
			     IDC_FUN_3G_NOW_LISTBOX_FILE,
			     10, 30, 100, 100,
			     hWnd,
			     0);
*/
		CreateWindow(CTRL_LISTBOX,
			     "",
			     LBS_NOTIFY  | WS_VSCROLL | WS_BORDER | WS_VISIBLE,
			     IDC_FUN_3G_NOW_LISTBOX_FILE,
			     10, 30, 100, 100,
			     hWnd,
			     0);
			     
		CreateWindow(CTRL_LISTBOX,
			     "",
			     LBS_NOTIFY  | WS_VSCROLL | WS_BORDER | WS_VISIBLE,
			     IDC_FUN_3G_ADD_LISTBOX_FILE,
			     110, 30, 100, 100,
			     hWnd,
			     0);

		CreateWindow(CTRL_STATIC,
			     MSG_PATH,
			     WS_VISIBLE | SS_SIMPLE,
			     IDC_FUN_MPLAYER_MUSICADD_STATIC_PATH,
			     10, 10, 130, 15,
			     hWnd,
			     0);

		CreateWindow(CTRL_BUTTON,
			     MSG_DOWNLOAD,
			     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			     IDC_FUN_MPLAYER_MUSICADD_BUTTON_CHOOSE,
			     230, 50, 70, 25,
			     hWnd,
			     0);

		CreateWindow(CTRL_BUTTON,
			     MSG_CANCEL,
			     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			     IDC_FUN_MPLAYER_MUSICADD_BUTTON_CANCEL,
			     230, 100, 50, 25,
			     hWnd,
			     0);

		SetNotificationCallback(GetDlgItem(hWnd, IDC_FUN_3G_NOW_LISTBOX_FILE), now_notif_proc);
		SetNotificationCallback(GetDlgItem(hWnd, IDC_FUN_3G_ADD_LISTBOX_FILE), file_notif_proc);
		fill_boxes(hWnd, getcwd(cwd, MAX_PATH));
	}
	break;

	case MSG_COMMAND:
	{
                DEB("--MSG_COMMAND hWnd=%d\n ,hWnd");	
		switch (wParam)	{
		case IDC_FUN_MPLAYER_MUSICADD_BUTTON_CHOOSE:
                        DEB("---IDC_FUN_MPLAYER_MUSICADD_BUTTON_CHOOSE\n ");		
			fn_3gFileSave(hWnd);
                                     	
			DEB("---SendNotifyMessage fWnd=%d\n ",fWnd);
			SendNotifyMessage(fWnd, MSG_MUSIC_ADD, 0, 0L);
			DEB("---SendNotifyMessage end\n ");			
			break;

		case IDC_FUN_MPLAYER_MUSICADD_BUTTON_CANCEL:
                        DEB("---IDC_FUN_MPLAYER_MUSICADD_BUTTON_CANCEL\n ");		
			DestroyMainWindow(hWnd);
			PostQuitMessage(hWnd);
			return 0;
		}
                DEB("--MSG_COMMAND END\n ");		
	}
	break;

	case MSG_CLOSE:
	{
                DEB("--MSG_CLOSE\n ");	
		DestroyMainWindow(hWnd);
		PostQuitMessage(hWnd);
		return 0;
	}
	}
	
	
	return DefaultMainWinProc(hWnd, message, wParam, lParam);
}



int net_3gadd(HWND Wnd)
{
	MSG           Msg;
	MAINWINCREATE CreateInfo;
	HWND          MPlayerWnd;
        PMAINWIN2 pWin;  //channing	
	
	
	fWnd = Wnd;

    
#if _DEBUG
        pWin2 = (PMAINWIN2)Wnd;
        printf ("net_3gadd\n");        
        printf ("pWin=0x%p \n",pWin2);
        printf ("fWnd=0x%p \n",fWnd);        
        printf ("pWin->WinType=0x%x\n",pWin2->DataType);        
        printf ("pWin->WinType=0x%x\n",pWin2->WinType);
#endif 
        


	CreateInfo.dwStyle        = WS_CAPTION | WS_BORDER | WS_VISIBLE;
	CreateInfo.dwExStyle      = WS_EX_NONE;
	CreateInfo.spCaption      = MSG_ADD_FILE;
	CreateInfo.hMenu          = 0;
	CreateInfo.hCursor        = GetSystemCursor(IDC_ARROW);
	CreateInfo.hIcon          = 0;
	CreateInfo.MainWindowProc = Desktop;
	CreateInfo.lx             = 0;
	CreateInfo.ty             = 0;
	CreateInfo.rx             = 320;
	CreateInfo.by             = 210;
	CreateInfo.iBkColor       = GetWindowElementColor(BKC_CONTROL_DEF);
	CreateInfo.dwAddData      = 0;
	CreateInfo.dwReserved     = 0;
	CreateInfo.hHosting       = 0;

	MPlayerWnd = CreateMainWindow(&CreateInfo);
	if (MPlayerWnd == HWND_INVALID) {
		return -1;
	}

	ShowWindow(MPlayerWnd, SW_SHOWNORMAL);

	while (GetMessage(&Msg, MPlayerWnd)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	MainWindowThreadCleanup(MPlayerWnd);
	return 0;
}

