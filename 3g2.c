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
#include "mini133.h"
#include "pdas.h"


#define USE_FTP	1
//#define CMD_USER

#define FTP_RM()\
	sprintf(str1, "rm %s",FILE_3G_FIN_DAT);	\
	system(str1);

#define FTP_TOUCH()\
	sprintf(str1, "touch %s",FILE_3G_FIN_DAT);\
	system(str1);

#define FTP_PROMPT()\
	sprintf(str1, "echo prompt >> %s",FILE_3G_FIN_DAT);\
	system(str1);

#define FTP_BI()\
	sprintf(str1, "echo bi >>  %s",FILE_3G_FIN_DAT);\
	system(str1);

#define FTP_CD()\
	sprintf(fn, "echo  cd %s >> %s",&dir[cur_sel][0],FILE_3G_FIN_DAT);\
        DEB("cmd=%s\n", fn);\
	system(fn);
	
#define FTP_LCD()\
	sprintf(str1, "echo lcd %s >> %s", MSG_TARGET_DIR,FILE_3G_FIN_DAT);\
	DEB("\ncmd=%s\n", str1);\
	system(str1);

#define FTP_MGET()\
	sprintf(str1, "echo mget %s >> %s",&filet[1],FILE_3G_FIN_DAT);\
	DEB("\ncmd=%s\n", str1);\
	system(str1);


#define FTP_LS()\
	sprintf(str1, "echo ls >>  %s",FILE_3G_FIN_DAT);\
	system(str1);
	
#define FTP_CAT()\
	sprintf(str1, "cat %s | ftp %s > %s",FILE_3G_FIN_DAT,NET_SERVER,FILE_3G_FOUT_DAT);\
        system(str1);

#ifdef CMD_USER
#define FTP_LOGIN()\
	sprintf(str1, "echo user %s %s >> %s",NET_USER,NET_PASSWORD,FILE_3G_FIN_DAT);\
	system(str1);
#else
#define FTP_LOGIN()	\
	sprintf(str1, "echo %s > %s",NET_USER,FILE_3G_FIN_DAT);	\
	system(str1);\
	sprintf(str1, "echo %s >> %s",NET_PASSWORD,FILE_3G_FIN_DAT);\
	system(str1);
#endif

extern char line[200];

static char fullpath2[PATH_MAX + 1];
HWND        hDir, hFile, hPath;

	char str1[50];

/*******************************************************************************
* File Name: ziyuanguanliqi.c
* Copy Right: GaoHaibo
* Author:  GaoHaibo
* Function discription:
*******************************************************************************/
#if 0
struct dirent
{
long d_ino; /* inode number索引節點號*/
off_t d_off; /* offset to this dirent在目錄文件中的偏移*/
unsigned short d_reclen; /* length of this d_name文件名長*/
unsigned char d_type; /* the type of d_name文件類型*/
char d_name [NAME_MAX+1]; /* file name (null-terminated)文件名，最長255字符*/
}
#endif


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

		//DEB("--fullpath = %s\n",fullpath);
		//DEB("--path = %s\n",path);
		strncpy(fullpath, path, PATH_MAX);
		//DEB("--fullpath = %s\n",fullpath);

		strcat(fullpath, "/");
		//DEB("--fullpath = %s\n",fullpath);


		strncpy(fullpath2, fullpath, PATH_MAX + 1);
		//DEB("--fullpath2 = %s\n",fullpath2);

		strcat(fullpath, dir_ent->d_name);
		DEB("--fullpath = %s\n",fullpath);

		if (stat(fullpath, &ftype) < 0) {
			continue;
		}

		if (S_ISDIR(ftype.st_mode)) {
			//DEB("--dr = %s\n",dir_ent->d_name);
			SendDlgItemMessage(hDlg, IDC_3G_DIR, LB_ADDSTRING, 0, (LPARAM)dir_ent->d_name);
		} else if (S_ISREG(ftype.st_mode)) {
			LISTBOXITEMINFO lbii;

			//DEB("--fn = %s\n",dir_ent->d_name);
			lbii.string = dir_ent->d_name;
			lbii.cmFlag = CMFLAG_BLANK;
			lbii.hIcon  = 0;
			SendDlgItemMessage(hDlg, IDC_3G_FILE, LB_ADDSTRING, 0, (LPARAM)&lbii);

		}
	}

	closedir(dir);

}

static int read_file(char *fn,int *p)
{
	FILE *fd;
	int  size;

	if ((fd = fopen(fn, "r")) == NULL) {
		MessageBox(0, fn, "error", MB_OK);
		return 0;
	}

	size = fread(p, 1, 1, fd);
	DEB("size = %d\n", size);
	DEB("%s\n", p);


	fclose(fd);

	return size;
}

void search_fn(char *p,char *fn)
{
	int i=0,flag=0;

	while(1){
		//DEB("%c", *p);
		if((char)*p++ == (char)' ') {
			if(flag == 0) {
				//DEB(".");

				flag=1;
				i++;
			}
		} else {
			flag = 0;
		}

		if(i == 8) {
			//DEB("+");
			while(1) {
				//DEB("%c", *p);
				if((char)*p != (char)0x0a) {
					*fn++ = *p++;
				} else {
					*fn++=0;
					break;
				}
			}
			break;
		}
	}



}


/*******************************************************************************
* File Name: ziyuanguanliqi.c
* Copy Right: GaoHaibo
* Author:  GaoHaibo
* Function discription:處理路徑
*******************************************************************************/

int dir[20][20];


static void fill_boxes2 (HWND hDlg)
{
	char command[2000],fn[255];
	int  dir_count=0,file_count=0,size,i,j,old_cur_sel=-1,c=0;
	FILE *fd;

	SendMessage(hDir, LB_RESETCONTENT, 0, (LPARAM)0);
	SendMessage(hFile, LB_RESETCONTENT, 0, (LPARAM)0);

	DEB("fill_boxes2\n");

		if ((fd = fopen("/tmp/fout.tmp", "r")) == NULL) {
			MessageBox(0, "/tmp/fout.tmp", "error", MB_OK);
			return;
		}
		size=fread(command, sizeof(command), 1, fd);
		fclose(fd);


		i=0;
		j=0;
		while(1){
			if(command[i]==0)
				break;

			if(command[i]==0x0a) {
				j=0;
				i++;
			}

			if(j==0) {
				j++;
				if(command[i] == 'd') {
					DEB("\nd ");
					search_fn(&command[i],&fn[0]);
					DEB("fn-%s\n", &fn[0]);
					strncpy((char *)&dir[dir_count], fn, 20);
					DEB("fn-%s", &fn[dir_count]);
					dir_count++;
					SendDlgItemMessage(hDlg, IDC_3G_DIR, LB_ADDSTRING, 0, (LPARAM)fn);
				} else if(command[i] == '-'){
					DEB("\nf ");
					search_fn(&command[i],&fn[0]);
					DEB("fn-%s", &fn[0]);
					LISTBOXITEMINFO lbii;

					lbii.string = fn;
					lbii.cmFlag = CMFLAG_BLANK;
					lbii.hIcon  = 0;
					SendDlgItemMessage(hDlg, IDC_3G_FILE, LB_ADDSTRING, 0, (LPARAM)&lbii);
				} else {
					break;
				}

			}
			//DEB("%c", command[i]);
			i++;
		}

}


static void dir_notif_proc2 (HWND hcwd, int id, int nc, DWORD add_data)
{
	FILE *fd;
	int  dir_count=0,file_count=0,size,i,j,old_cur_sel=-1,c=0;
	char command[2000],fn[255];

	int cur_sel;

	if(id == 0xf000){
		cur_sel = -1;
	} else {
		cur_sel = SendMessage(hcwd, LB_GETCURSEL, 0, 0L);
	}

	DEB("\ncur_sel=%d\n",cur_sel);


	//if(cur_sel >= 0)
	{

		//------------------------------
		SendMessage(hDir, LB_RESETCONTENT, 0, (LPARAM)0);
		SendMessage(hFile, LB_RESETCONTENT, 0, (LPARAM)0);

		if(cur_sel >= 0) {

			DEB("dir=%s\n",&dir[cur_sel][0]);

        		FTP_RM();
        		FTP_TOUCH();
 			FTP_LOGIN();
			FTP_BI();
        		FTP_CD();
 			FTP_LS();
			FTP_CAT();			
			
/*
			sprintf(str1, "rm %s",FILE_3G_FIN_DAT);
			system(str1);
			sprintf(str1, "touch %s",FILE_3G_FIN_DAT);
			system(str1);
#ifdef CMD_USER
			sprintf(str1, "echo user %s %s >> %s",NET_USER,NET_PASSWORD,FILE_3G_FIN_DAT);
			system(str1);
#else
			sprintf(str1, "echo %s > %s",NET_USER,FILE_3G_FIN_DAT);
			system(str1);
			sprintf(str1, "echo %s >> %s",NET_PASSWORD,FILE_3G_FIN_DAT);
			system(str1);
#endif
			sprintf(str1, "echo bi >>  %s",FILE_3G_FIN_DAT);
			system(str1);

			sprintf(fn, "echo  cd %s >> %s",&dir[cur_sel][0],FILE_3G_FIN_DAT);
        		DEB("cmd=%s\n", fn);
			system(fn);

			sprintf(str1, "echo ls >>  %s",FILE_3G_FIN_DAT);
			system(str1);

			sprintf(str1, "cat %s | ftp %s > %s",FILE_3G_FIN_DAT,NET_SERVER,FILE_3G_FOUT_DAT);
        		DEB("\ncmd=%s", str1);
			//system("cat fin.tmp | ftp -n 192.168.5.73 > fout.tmp");
			system(str1);
*/			
		}

		//memset(command, 0, sizeof(command));
		if ((fd = fopen(FILE_3G_FOUT_DAT, "r")) == NULL) {
			MessageBox(0, FILE_3G_FOUT_DAT, "error", MB_OK);
			return;
		}
		size=fread(command, sizeof(command), 1, fd);
		fclose(fd);


		//DEB("size = %d\n", size);
		//DEB("%s\n", command);

		DEB("dir_notif_proc2-");
		DEB("id=%d -",id);
		DEB("nc=%d -",nc);
		DEB("add_data=%d\n",add_data);

		i=0;
		j=0;
		while(1){
			if(command[i]==0)
				break;

			if(command[i]==0x0a) {
				j=0;
				i++;
			}

			if(j==0) {
				j++;
				if(command[i] == 'd') {
					DEB("\nd ");
					search_fn(&command[i],&fn[0]);
					//DEB("fn-%s\n", &fn[0]);
					strncpy((char *)&dir[dir_count], fn, 20);
					DEB("fn-%s", &fn[dir_count]);
					dir_count++;
					SendDlgItemMessage(GetParent(hcwd), IDC_3G_DIR, LB_ADDSTRING, 0, (LPARAM)fn);
				} else if(command[i] == '-'){
					DEB("\nf ");
					search_fn(&command[i],&fn[0]);
					DEB("fn-%s", &fn[0]);
					LISTBOXITEMINFO lbii;

					lbii.string = fn;
					lbii.cmFlag = CMFLAG_BLANK;
					lbii.hIcon  = 0;
					SendDlgItemMessage(GetParent(hcwd), IDC_3G_FILE, LB_ADDSTRING, 0, (LPARAM)&lbii);
				} else {
					break;
				}

			}
			//DEB("%c", command[i]);
			i++;
		}


	old_cur_sel = cur_sel;
	DEB("\ndir_notif_proc2 end\n");
	}
}


static void file_notif_proc2 (HWND hcwd, int id, int nc, DWORD add_data)
{
	DEB("--file_notif_proc2-");
	DEB("id=%d -",id);
	DEB("nc=%d -",nc);
	DEB("add_data=%d\n",add_data);
}




static void dir_notif_proc (HWND hcwd, int id, int nc, DWORD add_data)
{
	if (nc == LBN_CLICKED || nc == LBN_ENTER) {
		DEB("--dir_notif_proc\n");
		int cur_sel = SendMessage(hcwd, LB_GETCURSEL, 0, 0L);
		if (cur_sel >= 0) {
			char cwd [MAX_PATH + 1];
			char dir [MAX_NAME + 1];

			GetWindowText(GetDlgItem(GetParent(hcwd), IDC_3G_PATH), cwd, MAX_PATH);
			DEB("---cwd %s\n", cwd);
			SendMessage(hcwd, LB_GETTEXT, cur_sel, (LPARAM)dir);
			DEB("---dir %s\n", dir);
			if (strcmp(dir, ".") == 0) {
				return;
			}
			strcat(cwd, "/");
			strcat(cwd, dir);
			DEB("---cwd %s\n", cwd);
			fill_boxes(GetParent(hcwd), cwd);
		}
	}
}

static void file_notif_proc (HWND hcwd, int id, int nc, DWORD add_data)
{
	DEB("--dir_notif_proc\n");
	DEB("id=%d\n",id);
	DEB("nc=%d\n",nc);
	DEB("add_data=%d\n",add_data);
}

/*******************************************************************************
* Function DownLoad:
*******************************************************************************/
static void DownLoad(HWND hDlg)
{
     	int  i;
	char file [MAX_NAME + 1];
	char filet[MAX_NAME + 1];
	char files [512] = MSG_DOWNLOAD_FILE;

	int  status;

	for (i = 0; i < SendDlgItemMessage(hDlg, IDC_3G_FILE, LB_GETCOUNT, 0, 0L); i++) {

		status = SendDlgItemMessage(hDlg, IDC_3G_FILE, LB_GETCHECKMARK, i, 0);
		if (status == CMFLAG_CHECKED) {
			SendDlgItemMessage(hDlg, IDC_3G_FILE, LB_GETTEXT, i, (LPARAM)file);
			strcat(files, file);
			strcat(filet, file);
			strcat(filet, " ");
			strcat(files, "\n");
		}
	}
	if (IDOK == MessageBox(hDlg, files, "OK", MB_OK | MB_ICONINFORMATION)) {
		for (i = 0; i < SendDlgItemMessage(hDlg, IDC_3G_FILE, LB_GETCOUNT, 0, 0L); i++) {
			status = SendDlgItemMessage(hDlg, IDC_3G_FILE, LB_GETCHECKMARK, i, 0);
			if (status == CMFLAG_CHECKED) {
				SendMessage(GetDlgItem(hDlg, IDC_3G_FILE), LB_DELETESTRING, i, 0);
				i = 0;
			}

		}


        #if (USE_FTP == 1 )

        //FTP_RM();
        //FTP_TOUCH();
 	//FTP_LOGIN();
	//FTP_BI();
        //FTP_PROMPT();
 	//FTP_LCD();
 	//FTP_MGET(); 		
	sprintf(line, "mget %s\n",&filet[1]);
	cmdscanner(1);
	//FTP_CAT();

        #else
		//sprintf(str1, "rm -rf %s", filet);
		printf("filet=%s\n", &filet[3]);

		sprintf(str1, "cp  %s %s", &filet[3],MSG_TARGET_DIR);

		printf("nmove =%s", str1);
        	DEB("\ncmd=%s", str1);

		//system(str1);
		SYS_SERV_CALL(str1);
	#endif


	}
}

/*******************************************************************************
* File Name: ziyuanguanliqi.c
* Copy Right: GaoHaibo
* Author:  GaoHaibo
* Function discription:點擊主窗口資源管理器初始窗口
*******************************************************************************/
static int fn_3gProc(HWND hcwd, int message, WPARAM wParam, LPARAM lParam)
{
        //DEB("[3G]fn_3gProc \n ");
	{

		switch (message) {
		case MSG_CREATE:
		{
			char cwd [MAX_PATH + 1];
			loadbk(hcwd);
			DEB("-[3G]MSG_CREATE\n");

#if 1
			CreateWindow
				 (CTRL_STATIC, "File List Box", WS_VISIBLE | SS_SIMPLE, IDC_STATIC, 10, 2, 120, 25, hcwd, 0);

			hFile = CreateWindow
				 (CTRL_LISTBOX, "", WS_VISIBLE | WS_VSCROLL | WS_BORDER | LBS_SORT | LBS_AUTOCHECKBOX, IDC_3G_FILE, 10, 20, 280, 140, hcwd, 0);

#else
			CreateWindow
				 (CTRL_STATIC, "Directory List Box", WS_VISIBLE | SS_SIMPLE, IDC_STATIC, 10, 2, 120, 25, hcwd, 0);

			hDir = CreateWindow
				 (CTRL_LISTBOX, "", WS_VISIBLE | WS_VSCROLL | WS_BORDER | LBS_SORT | LBS_NOTIFY, IDC_3G_DIR, 10, 20, 140, 140, hcwd, 0);


			CreateWindow
				 (CTRL_STATIC, "File List Box", WS_VISIBLE | SS_SIMPLE, IDC_STATIC, 165, 2, 120, 25, hcwd, 0);

			hFile = CreateWindow
				 (CTRL_LISTBOX, "", WS_VISIBLE | WS_VSCROLL | WS_BORDER | LBS_SORT | LBS_AUTOCHECKBOX, IDC_3G_FILE, 165, 20, 140, 140, hcwd, 0);

			hPath = CreateWindow
				 (CTRL_STATIC, MSG_PATH, WS_VISIBLE | SS_SIMPLE, IDC_3G_PATH, 10, 150, 315, 0, hcwd, 0);
#endif
			CreateWindow
				 (CTRL_BUTTON, MSG_DOWNLOAD, WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP | WS_GROUP, IDC_3G_DOWNLOAD, 15, 165, 130, 25, hcwd, 0);


			CreateWindow
				 (CTRL_BUTTON, MSG_RETURN, WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP, IDC_3G_RETURN, 170, 165, 130, 25, hcwd, 0);

			#if (USE_FTP == 1 )
			SetNotificationCallback(hFile, file_notif_proc2);
			SetNotificationCallback(hDir, dir_notif_proc2);
			fill_boxes2(hcwd);
			#else
			SetNotificationCallback(hFile, file_notif_proc);
			SetNotificationCallback(hDir, dir_notif_proc);
			fill_boxes(hcwd, getcwd(cwd, MAX_PATH));
			#endif
		}
		break;


		case MSG_CLOSE:
		{
			DEB("-[3G]MSG_CLOSE\n");
			DestroyMainWindow(hcwd);
			PostQuitMessage(hcwd);
		}
			return 0;

		case MSG_COMMAND:
		{
			DEB("-[3G]MSG_COMMAND %d\n",wParam);
			switch (wParam) {
			case IDC_3G_DIR:
			        DEB("--[3G]IDC_3G_DIR \n ");
			        break;

			case IDC_3G_FILE:
			        DEB("--[3G]IDC_3G_FILE \n ");
			        break;

			case IDC_3G_PATH:
			        DEB("--[3G]IDC_3G_PATH \n ");
			        break;

			case IDC_3G_DOWNLOAD:    /*指定文件*/
			        DEB("--[3G]IDC_3G_DOWNLOAD \n ");
				DownLoad(hcwd);
				break;

			case IDC_3G_RETURN:     /*返回主界面*/
			        DEB("--[3G]IDC_3G_RETURN \n ");
				sprintf(line, "bye\n");
				cmdscanner(1);
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

int fn_3g2 (HWND hWnd)
{
	int           i = 99;
	MSG           Msg;
	HWND          hcwd;
	MAINWINCREATE CreateInfo;

        DEB("[3G]fn_3g2 \n ");
        #if (USE_FTP == 1 )
	miniftp();
	printf("miniftp down\n");
/*
	FTP_LOGIN();
	FTP_BI();
	FTP_LS();
	FTP_CAT();
*/
/*
#ifdef CMD_USER
	sprintf(str1, "echo user %s %s >> %s",NET_USER,NET_PASSWORD,FILE_3G_FIN_DAT);
	system(str1);
#else
	sprintf(str1, "echo %s > %s",NET_USER,FILE_3G_FIN_DAT);
	system(str1);
	sprintf(str1, "echo %s >> %s",NET_PASSWORD,FILE_3G_FIN_DAT);
	system(str1);
#endif
        DEB("\ncmd=%s", str1);

	sprintf(str1, "echo bi >>  %s",FILE_3G_FIN_DAT);
	system(str1);

	sprintf(str1, "echo ls >>  %s",FILE_3G_FIN_DAT);
	system(str1);


	sprintf(str1, "cat %s | ftp %s > %s",FILE_3G_FIN_DAT,NET_SERVER,FILE_3G_FOUT_DAT);
        system(str1);
*/
	#endif

#ifdef _LITE_VERSION
	SetDesktopRect(0, 0, 800, 600);
#endif

	CreateInfo.dwStyle        = WS_VISIBLE | WS_BORDER | WS_CAPTION;
	CreateInfo.dwExStyle      = WS_EX_NONE;
	CreateInfo.spCaption      = MSG_SERIVER;
	CreateInfo.hMenu          = 0;
	CreateInfo.hCursor        = GetSystemCursor(0);
	CreateInfo.hIcon          = 0;
	CreateInfo.MainWindowProc = fn_3gProc;
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

