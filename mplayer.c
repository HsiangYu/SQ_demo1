#include <stdio.h>
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include <string.h>
#include "pdas.h"
#include "sys_serv.h"
#include "mplayer.h"
#include "mini133.h"
//#define DEB printf

static void fill_box(HWND hWnd)
{
	int              i;
	FILE             *fp;
	int              size;
	struct musiclist list[MAX_FILE_LIST];

        DEB("-fill_box \n ");

	if ((fp = fopen(FILE_MUSIC_TMP_FILE, "r")) == NULL) {
		MessageBox(hWnd, FILE_FILE_ERROR, "", MB_OK | MB_ICONINFORMATION);
		return;
	}

	size = fread(list, sizeof(struct musiclist), MAX_FILE_LIST, fp);
        DEB("--fread ok size=%d\n",size);
        
	for (i = 0; i < size; i++) {
		SendMessage(GetDlgItem(hWnd, IDC_FUN_MPLAYER_LISTBOX_NAME), LB_ADDSTRING, i, (LPARAM)list[i].name);
//		SendMessage(GetDlgItem(hWnd, IDC_FUN_MPLAYER_LISTBOX_SINGER), LB_ADDSTRING, i, (LPARAM)list[i].name);	
	}
	fclose(fp);
        DEB("--fclose ok\n ");	
}

static void WriteBack(HWND hWnd)
{
	int              count = 0;
	int              i     = 0;
	FILE             *fp;
	int              size;
	struct musiclist list[MAX_FILE_LIST];

        DEB("-WriteBack \n ");

	if ((fp = fopen(FILE_MUSIC_TMP_FILE, "r")) == NULL) {
		MessageBox(hWnd, FILE_FILE_ERROR, "", MB_OK | MB_ICONINFORMATION);
		return;
	}

	size = fread(list, sizeof(struct musiclist), MAX_FILE_LIST, fp);
        DEB("--fread ok\n size=%d",size);	
	
	fclose(fp);
        DEB("--fclose ok\n ");
        
	if ((fp = fopen(FILE_MUSIC_TMP_FILE, "w")) == NULL) {
		MessageBox(hWnd, FILE_FILE_ERROR, "", MB_OK | MB_ICONINFORMATION);
		return;
	}

	count = SendMessage(GetDlgItem(hWnd, IDC_FUN_MPLAYER_LISTBOX_NAME), LB_GETCOUNT, 0, 0);

	for (i = 0; i < size; i++) {
		fwrite(list, sizeof(struct musiclist), size, fp);
	}
	fclose(fp);
        DEB("--fclose ok\n ");	
}

static void Music_List_And(HWND hwnd, int id, int nc, DWORD add_data)
{
	int index;

        DEB("-Music_List_And \n ");

	index = SendMessage(hwnd, LB_GETCURSEL, 0, 0);
	SendMessage(GetDlgItem(GetParent(hwnd), IDC_FUN_MPLAYER_LISTBOX_NAME), LB_SETCURSEL, index, 0);
//	SendMessage(GetDlgItem(GetParent(hwnd), IDC_FUN_MPLAYER_LISTBOX_SINGER), LB_SETCURSEL, index, 0);
}

int MusicDel(HWND hWnd)
{
	int              index;
	int              i = 0;
	FILE             *fp;
	int              size;
	int              save;
	struct musiclist list[MAX_FILE_LIST];

        DEB("-MusicDel \n ");
        
	save = MessageBox(hWnd, MSG_WANT_DELECT, MSG_YES, MB_OKCANCEL);
	

	if (save == IDOK) {
		index = SendMessage(GetDlgItem(hWnd, IDC_FUN_MPLAYER_LISTBOX_NAME), LB_GETCURSEL, 0, 0);
		SendMessage(GetDlgItem(hWnd, IDC_FUN_MPLAYER_LISTBOX_NAME), LB_DELETESTRING, index, 0);
//		SendMessage(GetDlgItem(hWnd, IDC_FUN_MPLAYER_LISTBOX_SINGER), LB_DELETESTRING, index, 0);

		if ((fp = fopen(FILE_MUSIC_TMP_FILE, "r")) == NULL) {
			MessageBox(hWnd, FILE_FILE_ERROR, "", MB_OK | MB_ICONINFORMATION);
			return;
		}

		size = fread(list, sizeof(struct musiclist), MAX_FILE_LIST, fp);
		fclose(fp);

		for (i = index; i < size; i++) {
			strcpy(list[index].name, list[index + 1].name);
			strcpy(list[index].singer, list[index + 1].singer);
			strcpy(list[index].path, list[index + 1].path);
			index++;
		}

		if ((fp = fopen(FILE_MUSIC_TMP_FILE, "w")) == NULL) {
			MessageBox(hWnd, FILE_FILE_ERROR, "", MB_OK | MB_ICONINFORMATION);
			return;
		}
		fwrite(list, sizeof(struct musiclist), size - 1, fp);
		fclose(fp);
	}
}

int MusicPlay(hWnd)
{
	static int       index;
	static FILE      *fp;
	int              size;
	struct musiclist list[MAX_FILE_LIST];
//	char             path[50];
//	char             temp[20];
	static char      *pname;
#if 0	
	char             name[40]     = {0};
	char             name1[40]    = {0};
#endif	
	char             command[100] = {0};
	
        DEB("-MusicPlay \n ");	
	
	index = SendMessage(GetDlgItem(hWnd, IDC_FUN_MPLAYER_LISTBOX_NAME), LB_GETCURSEL, 0, 0);
        DEB("--index=0x%x\n ",index);	
	
	//SendMessage(GetDlgItem(hWnd, IDC_FUN_MPLAYER_LISTBOX_NAME), LB_GETTEXT, index, (LPARAM)name);	
	
#if 0
	system("./x86/mplayer ./MPEG4.avi");
	SYS_SERV_CALL("./x86/mplayer ./MPEG4.avi");
#else	
        DEB("--fopen %s\n ",FILE_MUSIC_TMP_FILE);
	if ((fp = fopen(FILE_MUSIC_TMP_FILE, "r")) == NULL) {
		MessageBox(hWnd, FILE_FILE_ERROR, "", MB_OK | MB_ICONINFORMATION);
		return;
	}
	
        DEB("--list=%s\n",fp);	
	size = fread(list, sizeof(struct musiclist), MAX_FILE_LIST, fp);
        DEB("--fread size=%d \n",size);	
        DEB("--list=%s\n",fp);	
	fclose(fp);
        DEB("--fclose ok\n ");

        DEB("-index=0x%x \n ",index);    
        DEB("--name=%s \n ",list[index].name);                   
        DEB("--singer=%s \n ",list[index].singer);      
        DEB("--path=%s \n ",list[index].path);                                                
       
	//system("killall mplayer");
	SYS_SERV_CALL("killall mplayer");

	strcpy(command, list[index].path);
        DEB("--command=%s\n ",command);
               
	strtok(command, ".");

	pname = strtok(NULL, ".");	
        DEB("--pname=%s\n ",pname);
        	
	strcpy(command, FILE_MPLAYER_AP);
        DEB("--command=%s\n ",command);

	//strcpy(name1, FILE_MPLAYER_DIR);
        //DEB("--dir=%s\n ",name1);
        	
        //DEB("--pname=%s\n ",pname);
        	
        	
        	
#if 0        	
	if (strcmp(pname, "mp3") == 0) {
                DEB("--<mp3>\n");
		strcat(name1, name);
		strcat(name1, ".mp3");
		strcat(command, name1);
		strcat(command, " &");
                DEB("---command=%s\n ",command);		
		system(command);
	} else if (strcmp(pname, "wma") == 0)	    {
                DEB("--<wma>\n");	
		strcat(name1, name);
		strcat(name1, ".wma");
		strcat(command, name1);
		strcat(command, " &");
                DEB("---command=%s\n ",command);		
		system(command);		
	}
#else
/*
#mplayer -fps 30 -vf rotate=2 tv:// -tv driver=v4l2:width=320:height=240:device=/dev/video0
#mplayer MPEG4.mp4 -vo soclefb -ao alsa -vfm ffmpeg -quiet -loop 0
#mpilayer panda.mpg -vf rotate=2 -vfm ffmpeg -afm libmad -quiet -loop 0
#mplayer MPEG4.rmvb -vf rotate=2  -afm libmad -quiet -loop 0
#mplayer -zoom -x 240 -y 320 mf://\*.jpg -loop 0
#mplayer -zoom -x 320 -y 240 -fps 30 -vf rotate=2 -vo fbdev2 MPEG4.vob
#mplayer untitled.gif

To use it add: 
-softvol ?softvol-max <10.0?10000.0> 
To set the maximum amplification level in percent (default: 110). A value of 200 will allow you to adjust the volume up to a maximum of double the current level. With values below 100 the initial volume (which is 100%) will be above the maximum, which e.g. the OSD cannot display correctly. 
Example 
mplayer -softvol -softvol-max 200 media.avi

To use it add : 
-af volume=<v>:<sc> 
Where 
<v> is the desired gain in dB for all channels in the stream from -200dB to +60dB, where -200dB mutes the sound completely and +60dB equals a gain of 1000 (default: 0). 
<sc> Turns soft clipping on (1) or off (0). Soft-clipping can make the sound more smooth if very high volume levels are used. Enable this option if the dynamic range of the loudspeakers is very low. 
Example: 
mplayer -af volume=1000.1:0 media.avi

*/
	if ( 	(strcmp(pname, "jpg") == 0)|(strcmp(pname, "JPG") == 0)|
		(strcmp(pname, "bmp") == 0)|(strcmp(pname, "BMP") == 0)|
		(strcmp(pname, "png") == 0)|(strcmp(pname, "PNG") == 0))  {
		#if 1
		//mplayer mf://\*.jpg -loop 0
		//strcat(command, " mf://"); 
		//#mplayer -zoom -x 320 -y 240 mf://\*.jpg -loop 0
		strcat(command, " -zoom -x 320 -y 240 mf://");
		strcat(command, list[index].path);                                
		strcat(command, " &");
		//strcat(command, " -loop 0 &");				
		#else
		DEB("--show=%s\n ",list[index].path);	
		static BITMAP bmp2;	
		HDC        hdc;
				
		if (LoadBitmap(HDC_SCREEN, &bmp2, list[index].path)) {
			return 1;
		}
		DEB("--FillBoxWithBitmap\n ");			
		hdc = BeginPaint(hWnd);	
		FillBoxWithBitmap(hdc, 0, 0, 320, 240, &bmp2);	
		EndPaint(hWnd, hdc);
		return 0;		
		#endif
	} else if ((strcmp(pname, "gif") == 0)|(strcmp(pname, "GIF") == 0)) { 
		strcat(command, " -zoom -x 320 -y 240 ");		
		strcat(command, list[index].path);                                
		strcat(command, " &");				
	} else if ((strcmp(pname, "rmvb") == 0)|(strcmp(pname, "RMVB") == 0)) {
		strcat(command, " -vo soclefb -vf rotate=2  -afm libmad -quiet -loop 0 -softvol -af volume=1000.1:0 -quiet "); 
		strcat(command, list[index].path);                                
		strcat(command, " &");
	} else if((strcmp(pname, "vob") == 0)|(strcmp(pname, "VOB") == 0)) {
		strcat(command, " -vo soclefb -zoom -x 320 -y 240 -fps 30 -vf rotate=2 -af volume=1000.1:0 -quiet "); 
		strcat(command, list[index].path);                                
		strcat(command, " &");
	} else if((strcmp(pname, "mpg") == 0)|(strcmp(pname, "MPG") == 0)) {
		strcat(command, " -vo soclefb -vf rotate=2 -vfm ffmpeg -afm libmad -loop 0 -af volume=1000.1:0 -quiet "); 
		strcat(command, list[index].path);                                
		strcat(command, " &");					
	} else {			
		//strcat(command, " -vo soclefb -ao alsa -vfm ffmpeg -quiet -loop 0 "); 
		strcat(command, " -vo soclefb -quiet "); 		
		strcat(command, list[index].path);                                
		strcat(command, " &");
	}	
                DEB("--command=%s\n ",command);		
		//system(command);		
		SYS_SERV_CALL(command);
#endif 	
#endif 
        	
        DEB("-MusicPlay End \n ");
}

#define MSG_FIRSTPOSTMSG    0x0020	

extern int loadbk(HWND hWnd);


static int Desktop(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
 //       DEB("-Desktop -message=%d wParam=%d lParam=%d\n ",message,wParam,lParam);
	static int mpalyer_flag = 0;
	static int reload_flag = 0;

	switch (message) {
	case MSG_IDLE:
                DEB("^");			
	break;

	case MSG_FIRSTPOSTMSG:
                DEB("<%d",mpalyer_flag);	
                if(mpalyer_flag == 1) {
                	//system("killall mplayer");
			SYS_SERV_CALL("killall mplayer");
                	mpalyer_flag = 0;
                	reload_flag = 1;                	               		
			//DestroyMainWindow(hWnd);
			//PostQuitMessage(hWnd);
                	DEB("---KILL MPLAY\n ");
			//return 0;
			//break;		
                	goto msg_recreate;
                }
                			
	break;

	case MSG_CREATE:
	{
msg_recreate:	
		loadbk(hWnd);	
                DEB("--MSG_CREATE\n ");	
                
/*
		CreateWindow(CTRL_LISTBOX,
			     "",
			     LBS_NOTIFY  | WS_VSCROLL | WS_BORDER | WS_VISIBLE,
			     IDC_FUN_MPLAYER_LISTBOX_SINGER,
			     140, 20, 80, 120,
			     hWnd,
			     0);
*/                
             
		CreateWindow(CTRL_LISTBOX,
			     "",
			     LBS_NOTIFY  | WS_VSCROLL | WS_BORDER | WS_VISIBLE,
			     IDC_FUN_MPLAYER_LISTBOX_NAME,
			     20, 20, 280, 140,
			     hWnd,
			     0);

		CreateWindow(CTRL_BUTTON,
			     MSG_ADD,
			     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			     IDC_FUN_MPLAYER_BUTTON_ADD,
			     20, 180, 55, 25,
			     hWnd,
			     0);

		CreateWindow(CTRL_BUTTON,
			     MSG_DELECT,
			     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			     IDC_FUN_MPLAYER_BUTTON_DEL,
			     80, 180, 55, 25,
			     hWnd,
			     0);

		CreateWindow(CTRL_BUTTON,
			     MSG_PLAY,
			     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			     IDC_FUN_MPLAYER_BUTTON_PLAY,
			     140, 180, 55, 25,
			     hWnd,
			     0);
/*
		CreateWindow(CTRL_BUTTON,
			     MSG_STOP,
			     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			     IDC_FUN_MPLAYER_BUTTON_STAY,
			     240, 50, 50, 25,
			     hWnd,
			     0);


		CreateWindow(CTRL_BUTTON,
			     MSG_PAUSE,
			     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			     IDC_FUN_MPLAYER_BUTTON_STOP,
			     240, 80, 50, 25,
			     hWnd,
			     0);
*/
		CreateWindow(CTRL_BUTTON,
			     MSG_MP_CLOSE,
			     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			     IDC_FUN_MPLAYER_BUTTON_CLOSE,
			     200, 180, 55, 25,
			     hWnd,
			     0);
			     
		if (reload_flag == 0) {	     
			SetNotificationCallback(GetDlgItem(hWnd, IDC_FUN_MPLAYER_LISTBOX_NAME), Music_List_And);
			fill_box(hWnd);
		}
		reload_flag = 0;
	}
	break;

	case MSG_COMMAND:
	{
                DEB("--MSG_COMMAND hWnd=0x%x\n ",hWnd);	
		switch (wParam)	{		
		case IDC_FUN_MPLAYER_BUTTON_ADD:
		DEB("---IDC_FUN_MPLAYER_BUTTON_ADD\n ");		
			musicadd(hWnd);
			loadbk(hWnd);
			//SetNotificationCallback(GetDlgItem(hWnd, IDC_FUN_MPLAYER_LISTBOX_NAME), Music_List_And);//0310
			fill_box(hWnd);			
			//goto msg_recreate;
			break;

		case IDC_FUN_MPLAYER_BUTTON_DEL:
                DEB("---IDC_FUN_MPLAYER_BUTTON_DEL\n ");		
			MusicDel(hWnd);			
			break;

		case IDC_FUN_MPLAYER_BUTTON_PLAY:
                DEB("---IDC_FUN_MPLAYER_BUTTON_PLAY\n ");
                	mpalyer_flag = 1;	
			MusicPlay(hWnd);
			break;

		case IDC_FUN_MPLAYER_BUTTON_STAY:
                DEB("---IDC_FUN_MPLAYER_BUTTON_STAY\n ");		
			//system("killall mplayer");
			SYS_SERV_CALL("killall mplayer");
			break;

		case IDC_FUN_MPLAYER_BUTTON_STOP:
                DEB("---IDC_FUN_MPLAYER_BUTTON_STOP\n ");
			break;

		case IDC_FUN_MPLAYER_BUTTON_CLOSE:
                DEB("---IDC_FUN_MPLAYER_BUTTON_CLOSE\n ");
			//system("killall mplayer");                		
			SYS_SERV_CALL("killall mplayer");                		
			DestroyMainWindow(hWnd);
			PostQuitMessage(hWnd);
			break;
		}
	}
	break;

	case MSG_MUSIC_ADD:
                DEB("--MSG_MUSIC_ADD\n ");	
		SendMessage(GetDlgItem(hWnd, IDC_FUN_MPLAYER_LISTBOX_NAME), LB_RESETCONTENT, 0, 0);
//		SendMessage(GetDlgItem(hWnd, IDC_FUN_MPLAYER_LISTBOX_SINGER), LB_RESETCONTENT, 0, 0);
		fill_box(hWnd);		
		break;

	case MSG_CLOSE:
	{
                DEB("--MSG_CLOSE\n ");	
		DestroyMainWindow(hWnd);
		PostQuitMessage(hWnd);
		return 0;
	}
	default:
        //DEB("-Desktop -message=0x%x wParam=%d lParam=%d\n ",message,wParam,lParam);	
	break;
	}
	return DefaultMainWinProc(hWnd, message, wParam, lParam);
}
	

int MPlayer()
{
	MSG           Msg;
	MAINWINCREATE CreateInfo;
	HWND          MPlayerWnd;
        DEB("[MPlayer]CreateMainWindow \n ");

	CreateInfo.dwStyle        = WS_CAPTION | WS_BORDER | WS_VISIBLE;
	CreateInfo.dwExStyle      = WS_EX_NONE;
	CreateInfo.spCaption      = MSG_MPLAYER;
	CreateInfo.hMenu          = 0;
	CreateInfo.hCursor        = GetSystemCursor(IDC_ARROW);
	CreateInfo.hIcon          = 0;
	CreateInfo.MainWindowProc = Desktop;
	CreateInfo.lx             = 0;
	CreateInfo.ty             = 0;
	CreateInfo.rx             = 320;
	CreateInfo.by             = 240;
	CreateInfo.iBkColor       = GetWindowElementColor(BKC_CONTROL_DEF);
	CreateInfo.dwAddData      = 0;
	CreateInfo.dwReserved     = 0;
	CreateInfo.hHosting       = 0;

	MPlayerWnd = CreateMainWindow(&CreateInfo);
	if (MPlayerWnd == HWND_INVALID) {
		return -1;
	}

	ShowWindow(MPlayerWnd, SW_SHOWNORMAL);
	
        DEB("GetMessage \n ");
	while (GetMessage(&Msg, MPlayerWnd)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
        DEB("MainWindowThreadCleanup \n ");
	MainWindowThreadCleanup(MPlayerWnd);
        DEB("MainWindowThreadCleanup end\n ");	
	return 0;
}

