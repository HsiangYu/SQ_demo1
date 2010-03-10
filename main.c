#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include "minigui/common.h"
#include "minigui/minigui.h"
#include "minigui/gdi.h"
#include "minigui/window.h"
#include "minigui/control.h"
#include "minigui/dti.c"
#include <time.h>
#include "pda.h"
#include "call.h"

#include "lang.h"

#define TRUE            1
#define FALSE           0
#define DEB //printf


#define _ID_TIMER       154
HWND          hwnd_l;
int           Mon_flag  = 1;
int           Mon_flag1 = 1;
static BITMAP bmp;
S             s1;
int           maintime = 0;

int		fd_sys_call[2];
int		fd_sys_ret[2];

HWND hwnd;
extern void * TaskBar();
extern void * lisen();
extern void * lisen1(void * data);


struct M2{
    /**
     * type of menu item, can be one of the following values:
     *      - MFT_STRING\n
     *        A normal string menu item.
     *      - MFT_BITMAP\n
     *        A bitmap menu item.
     *      - MFT_BMPSTRING\n
     *        A bitmap menu item followed by a string.
     *      - MFT_SEPARATOR
     *        A separator in menu.
     *      - MFT_RADIOCHECK\n
     *        A normal string with a radio check mark.
     */
    UINT                type;
    /**
     * state of the menu item, can be one of the following values:
     *      - MFS_GRAYED\n
     *        The menu item is disabled.
     *      - MFS_DISABLED\n
     *        The menu item is disabled.
     *      - MFS_CHECKED\n
     *        The menu item is checked.
     *      - MFS_ENABLED\n
     *        The menu item is enabled.
     *      - MFS_UNCHECKED\n
     *        The menu item is unchecked.
     */
    UINT                state;    
    /** the identifier of the menu item */
    int                 id;    
    /** the data of this menu item, used to pass the string of the menu item */
    DWORD               typedata;    
};

//tool menu
#define ID_TOOL			100
#define ID_PHONEBOOK		101		      
#define ID_ALARM_CLOCK          102
#define ID_CALCULATION          103
#define ID_GAME                 104
#define ID_CALENDAR             105
#define ID_MUTIMEDIA_PLAYER     106

#define ID_TALK_TIME            108
#define	ID_3G_CONNECT		109
#define ID_MINIFTP		110

//pda menu
#define ID_PDA			200
#define ID_AUDIO_COMMMUNICATION	201
#define ID_MESSAGE          	202
#define ID_SYSTEM_SETTING    	203
#define ID_NOTE              	204
#define ID_DATA              	205
#define ID_MEMO              	206
#define ID_RESOURCE_MANAGE  	207


struct M2 tool_memu[]={
//{MFT_STRING,0,ID_PHONEBOOK		,(DWORD)MSG_PHONEBOOK},
//{MFT_STRING,0,ID_ALARM_CLOCK          ,(DWORD)MSG_ALARM_CLOCK},
//{MFT_STRING,0,ID_CALCULATION          ,(DWORD)MSG_CALCULATION},
//{MFT_STRING,0,ID_GAME                 ,(DWORD)MSG_GAME},
//{MFT_STRING,0,ID_CALENDAR             ,(DWORD)MSG_CALENDAR},
{MFT_STRING,0,ID_MUTIMEDIA_PLAYER     ,(DWORD)MSG_MUTIMEDIA_PLAYER},
{MFT_STRING,0,ID_MINIFTP		,(DWORD)MSG_MINIFTP},
{MFT_STRING,0,ID_3G_CONNECT           ,(DWORD)MSG_3G_CONNECT},
//{MFT_STRING,0,ID_TALK_TIME            ,(DWORD)MSG_TALK_TIME},
};



static HMENU createpmenufile2(void)
{
	HMENU        hmnu;
	MENUITEMINFO mii;
	int           i;

	memset(&mii, 0, sizeof(MENUITEMINFO));
	mii.type     = MFT_STRING;
	mii.id       = ID_TOOL;
	mii.typedata = (DWORD)"";
	hmnu         = CreatePopupMenu(&mii);

        for(i=0;i<(sizeof(tool_memu)/sizeof(struct M2));i++){
	memset(&mii, 0, sizeof(MENUITEMINFO));
	mii.type     = tool_memu[i].type;
	mii.state    = tool_memu[i].state;
	mii.id       = tool_memu[i].id;
	mii.typedata = tool_memu[i].typedata;
	InsertMenuItem(hmnu, i, TRUE, &mii);
	}

	return hmnu;
}






struct M2 pda_menu[]={
//{MFT_STRING,0,ID_AUDIO_COMMMUNICATION	,(DWORD)MSG_AUDIO_COMMMUNICATION},
//{MFT_STRING,0,ID_MESSAGE          	,(DWORD)MSG_MESSAGE},
//{MFT_STRING,0,ID_SYSTEM_SETTING    	,(DWORD)MSG_SYSTEM_SETTING},
//{MFT_STRING,0,ID_NOTE              	,(DWORD)MSG_NOTE},
//{MFT_STRING,0,ID_DATA              	,(DWORD)MSG_DATA},
//{MFT_STRING,0,ID_MEMO              	,(DWORD)MSG_MEMO},
{MFT_STRING,0,ID_RESOURCE_MANAGE  	,(DWORD)MSG_RESOURCE_MANAGE},
{MFT_STRING,0,ID_MUTIMEDIA_PLAYER     ,(DWORD)MSG_MUTIMEDIA_PLAYER},
{MFT_STRING,0,ID_MINIFTP		,(DWORD)MSG_MINIFTP},
{MFT_STRING,0,ID_3G_CONNECT           ,(DWORD)MSG_3G_CONNECT},
};

static HMENU createpmenufile(void)
{
	HMENU        hmnu;
	MENUITEMINFO mii;

	memset(&mii, 0, sizeof(MENUITEMINFO));
	mii.type     = MFT_STRING;
	mii.id       = ID_PDA;
	mii.typedata = (DWORD)"";
	hmnu         = CreatePopupMenu(&mii);

        for(i=0;i<(sizeof(pda_menu)/sizeof(struct M2));i++){
	memset(&mii, 0, sizeof(MENUITEMINFO));
	mii.type     = pda_menu[i].type;
	mii.state    = pda_menu[i].state;
	mii.id       = pda_menu[i].id;
	mii.typedata = pda_menu[i].typedata;
	InsertMenuItem(hmnu, i, TRUE, &mii);
	}

	return hmnu;
}

static HMENU createmenu(void)
{
	HMENU        hmnu;
	MENUITEMINFO mii;
	int           i;	
	
	hmnu = CreateMenu();

	memset(&mii, 0, sizeof(MENUITEMINFO));
	mii.type     = MFT_STRING;
	mii.id       = ID_PDA;
	mii.typedata = (DWORD)MSG_PDA;
	mii.hsubmenu = createpmenufile();
	InsertMenuItem(hmnu, 0, TRUE, &mii);
/*
	memset(&mii, 0, sizeof(MENUITEMINFO));
	mii.type     = MFT_STRING;
	mii.id       = ID_TOOL;
	mii.typedata = (DWORD)MSG_TOOL;
	mii.hsubmenu = createpmenufile2();
	InsertMenuItem(hmnu, 1, TRUE, &mii);
*/
	return hmnu;
}

#define USE_BG_BMP	1

int loadbk(HWND hWnd)
{
	static BITMAP bmp2;	
	HDC        hdc;
		
	if (LoadBitmap(HDC_SCREEN, &bmp2, FILE_BACKGROUND_BMP)) {
		return 0;
	}
	hdc = BeginPaint(hWnd);	
	FillBoxWithBitmap(hdc, 0, 0, 320, 240, &bmp2);	
	EndPaint(hWnd, hdc);	
}





static int HelloWinProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
	FILE       *fp;
	HDC        hdc;
	RECT       rc;
	static int num1, num2, num3;
	struct tm  *ptime;
	time_t     now;
	char       buffer1[100];
	int	   ret;
	
	DEB("*OPEN message=0x%x wParam 0x%x lParam 0x%x\n",message,wParam,lParam);	
	
	switch (message) {
	case MSG_CREATE:
		DEB("*MSG_CREATE\n");
		if ((fp = fopen("wenhouyu", "r")) != NULL) {
			fread(buffer1, 100, 1, fp);
			MessageBox(hWnd, buffer1, MSG_HELLO, MB_OK);
			fclose(fp);
		}

		if ((fp = fopen("clockset", "r")) != NULL) {
			fread(&s1, sizeof(S), 1, fp);
			SetTimer(hWnd, _ID_TIMER, 100);
			fclose(fp);
		}
		#if (USE_BG_BMP == 1)
		if (LoadBitmap(HDC_SCREEN, &bmp, FILE_BACKGROUND_BMP)) {
			break;
		}						
		#endif

	case MSG_PAINT:
		hdc = BeginPaint(hWnd);
		#if (USE_BG_BMP == 1)		
		FillBoxWithBitmap(hdc, 0, 0, 320, 240, &bmp);
		#endif		
		EndPaint(hWnd, hdc);	
		return 0;

	case MSG_TIMER:		
		if (wParam == _ID_TIMER) {

			time(&now);
			ptime = localtime(&now);
			num1  = atoi(s1.hour);
			num2  = atoi(s1.minute);
			num3  = atoi(s1.second);
			if (!strcmp(s1.change, MSG_OPEN)) {
				if (ptime->tm_hour == num1 && ptime->tm_min == num2 && ptime->tm_sec == num3) {

					MessageBox(hWnd, MSG_TIME_OUT, MSG_INDICATION, MB_OK);
				}
			}
		}
		return 0;
	case MSG_COMMAND:
		DEB("*MSG_COMMAND 0x%x\n",wParam);	
		switch (wParam) {
			/*
		case ID_CALCULATION: CreateCounterDialog(hWnd);
			return 0;
		case ID_ALARM_CLOCK: CreateAlarmDialog(hWnd);
			return 0;
		case ID_MEMO: CreateMemoireDialog(hWnd);
			return 0;
			*/
		case ID_MUTIMEDIA_PLAYER: MPlayer(hWnd);
			return 0;
		case ID_MINIFTP:	FUN_3G(hWnd);
					//fn_3g2(hWnd);
			return 0;
			
		case ID_3G_CONNECT: Network_connect(hWnd);
			return 0;
		/*				
		case ID_AUDIO_COMMMUNICATION:
			//if(tag == 2)
			SendMessage(hcwd, MSG_TAG, 0, 0);
			//tag=1;
			//CreateCallDialog(hWnd);
			return 0;
		case ID_CALENDAR: CreateMonthcalDialog(hWnd);
			return 0;
		case ID_NOTE: notes(hWnd);
			return 0;
		case ID_MESSAGE: messaging(hWnd);
			return 0;
			
		case ID_TALK_TIME: Callrecords(hWnd);
			return 0;
		case ID_PHONEBOOK: Menu(hWnd);
			return 0;
		case ID_GAME:   CreateBombDialog(hWnd);
			return 0;
		case ID_SYSTEM_SETTING: phone_set(hWnd);
			return 0;
			*/
		case ID_RESOURCE_MANAGE:   Ziyuanguanli(hWnd);
			return 0;
		}
		break;
	case MSG_DESTROY:
		DEB("*MSG_DESTROY\n");	
		DestroyAllControls(hWnd);
		break;
	case MSG_CLOSE:
		DEB("*MSG_CLOSE\n");	
		
		#if 0
		KillTimer(hWnd, _ID_TIMER);
		#if (USE_BG_BMP == 1)
		UnloadBitmap(&bmp);
		#endif
		
		SendMessage(TaskBarWindow, MSG_CLOSE, 0, 0);
		DestroyMainWindow(hWnd);
		PostQuitMessage(hWnd);
		#endif
		return 0;
	}
	
	ret = DefaultMainWinProc(hWnd, message, wParam, lParam);
	DEB("*CLOSE ret=0x%x\n",ret);	
	return ret;
}

int sys_serv(void)
{
	int n;
	char cmdline[200];

	close(fd_sys_call[1]);
	close(fd_sys_ret[0]);
	while(1){
		n=read(fd_sys_call[0], cmdline, 200);
		if(n>0) {
			cmdline[n]='\0';
			system(cmdline);
			sprintf(cmdline, "1\n");
			write(fd_sys_ret[1], cmdline, 2);
		}

	}
}

int MiniGUIMain(int argc, const char* argv[])
{
	//	pthread_t     th_task, th_pth, th_pth1;
	MSG           Msg;
	HWND          hMainWnd;
	MAINWINCREATE CreateInfo;
	int ret;

	int pid;
	if(pipe(fd_sys_call)<0)
		printf("system pipe fail");
	if(pipe(fd_sys_ret)<0)
		printf("system pipe ret fail");

	pid=fork();
	if(0==pid) {
		sys_serv();
	}else if(pid>0) {
		close(fd_sys_call[0]);
		close(fd_sys_ret[1]);
#ifdef _LITE_VERSION
		SetDesktopRect(0, 0, 1024, 768);
#endif

		CreateInfo.dwStyle        = WS_VISIBLE | WS_BORDER | WS_CAPTION;
		CreateInfo.dwExStyle      = WS_EX_NONE;
		CreateInfo.spCaption      = MSG_SQ_PDA;
		CreateInfo.hMenu          = createmenu();
		CreateInfo.hCursor        = GetSystemCursor(0);
		CreateInfo.hIcon          = 0;
		CreateInfo.MainWindowProc = HelloWinProc;
		CreateInfo.lx             = 0;
		CreateInfo.ty             = 0;
		CreateInfo.rx             = 320;
		CreateInfo.by             = 240;
		CreateInfo.iBkColor       = COLOR_lightwhite;
		CreateInfo.dwAddData      = 0;
		CreateInfo.hHosting       = HWND_DESKTOP;

		hMainWnd = CreateMainWindow(&CreateInfo);
		hwnd_l   = hMainWnd;
		//	pthread_create(&th_task, NULL, TaskBar, (void*)(&hMainWnd));
		//	pthread_create(&th_pth, NULL, (void*)lisen, NULL);
		//	pthread_create(&th_pth1, NULL, (void*)lisen1, NULL);
		if (hMainWnd == HWND_INVALID) {
			return -1;
		}

		ShowWindow(hMainWnd, SW_SHOWNORMAL);

		tag = 0;
		//	CreateCallDialog(hMainWnd);


		while (GetMessage(&Msg, hMainWnd)) {
			TranslateMessage(&Msg);		
			DispatchMessage(&Msg);		
		}
		Mon_flag1 = 0;
		//	pthread_join(th_pth1, NULL);
		Mon_flag = 0;
		//	pthread_join(th_pth, NULL);
		//	pthread_join(th_task, NULL);
		MainWindowThreadCleanup(hMainWnd);
		return 0;
	} else if(pid<0){
		printf("fork sub failure");
	}
}

