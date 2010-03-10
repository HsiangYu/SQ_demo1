#include <stdio.h>
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include <string.h>
#include "pdas.h"
#include "sys_serv.h"
#include "mini133.h"


#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <net/if.h>

#include "network.h"

/*
int detect_network(void)
{
	int inet_sock;
	struct ifreq ifr;

	inet_sock = socket(AF_INET, SOCK_DGRAM, 0);
	strcpy(ifr.ifr_name, "ppp0"); 

	if (ioctl(inet_sock, SIOCGIFADDR, &ifr) < 0)
	{
		return 0;
	} else {
		return 1;
	}
}
*/

#define IDC_SD_CLOSE		2253

extern int net_3gadd(HWND Wnd);

struct cmdlist {
	char cmd[96];
};
int cmd_count;
	
static DLGTEMPLATE DlgBoxNonSD =
{
    WS_BORDER | WS_CAPTION, 
    WS_EX_NONE,
    90, 80, 140, 80, 
    "Non SD Card",
    0, 0,
    1, NULL,
    0
};

static CTRLDATA BoxNonSD [] =
{ 
    { 
        CTRL_BUTTON,
        WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 
        30, 10, 80, 30,
        IDC_SD_CLOSE,
        "OK",
        0
    }
};

static int NonSDDialogBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
	static int i;

	//DEB("--[3G]connect-box");
    switch (message) {
    case MSG_INITDIALOG:
	DEB("--[3G]connect-check--detect-init\n");
	return 1;
        
    case MSG_COMMAND:
        switch (wParam) {
        case IDC_SD_CLOSE:
        case IDCANCEL:
		DEB("--[conect]wvdial--");
		//system("kill %d",pid);
		EndDialog (hDlg, wParam);
		break;
        }
        break;
    }
    
    return DefaultDialogProc (hDlg, message, wParam, lParam);
}

static void nonSD(HWND hwnd)
{	
	DEB("[3G]nonSD");
        DlgBoxNonSD.controls = BoxNonSD;
        DialogBoxIndirectParam (&DlgBoxNonSD, hwnd, NonSDDialogBoxProc, (LPARAM)NULL);
}
void cmd_read(char* PATHNAME, struct cmdlist* logbuff)
{
	FILE *fd;
	int  i;
	cmd_count = 0;
	if ((fd = fopen(PATHNAME, "r")) == NULL) {
		MessageBox(0, PATHNAME, "error", MB_OK);
		return;
	}

	for (i = 0; ((i < 20) && (!feof(fd))); i++) {
		fread(&logbuff[i], sizeof(struct cmdlist), 1, fd);
		cmd_count++;
	}
	cmd_count = cmd_count - 1;

	fclose(fd);

}


static int Desktop(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
        //DEB("-Desktop -message=%d\n ",message);
	struct stat buf;

	struct cmdlist command[20];
	switch (message) {
	case MSG_CREATE:
	{
                DEB("--MSG_CREATE\n ");	
                loadbk(hWnd);
		CreateWindow(	CTRL_STATIC, 
				"Connect To Server", 
				WS_VISIBLE | SS_SIMPLE, 
				IDC_STATIC, 
				20, 20, 200, 25, 
				hWnd, 
				0);
				                
                //cmd_read(FILE_SERVER_DAT,command);
                
                //DEB("---%s\n ",command[0].cmd);	                

		CreateWindow(	CTRL_STATIC, 
				NET_SERVER/*command[0].cmd*/, 
				WS_VISIBLE | SS_SIMPLE, 
				IDC_STATIC, 
				20, 40, 200, 25, 
				hWnd, 
				0);

		CreateWindow(	CTRL_STATIC, 
				"Target Dir is ", 
				WS_VISIBLE | SS_SIMPLE, 
				IDC_STATIC, 
				20, 60, 200, 25, 
				hWnd, 
				0);
				
                DEB("---%s\n ",MSG_TARGET_DIR);	                

		CreateWindow(	CTRL_STATIC, 
				MSG_TARGET_DIR, 
				WS_VISIBLE | SS_SIMPLE, 
				IDC_STATIC, 
				20, 80, 200, 25, 
				hWnd, 
				0);				
				
				                
		CreateWindow(CTRL_BUTTON,
			     MSG_CONNECT,
			     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			     IDC_FUN_3G_BUTTON_CONNECT,
			     20, 150, 70, 25,
			     hWnd,
			     0);

		CreateWindow(CTRL_BUTTON,
			     MSG_MP_CLOSE,
			     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			     IDC_FUN_3G_BUTTON_CLOSE,
			     240, 150, 70, 25,
			     hWnd,
			     0);
			     
			     

	}
	break;

	case MSG_COMMAND:
	{
                DEB("--MSG_COMMAND hWnd=0x%x\n ",hWnd);	
		switch (wParam)	{
		case IDC_FUN_3G_BUTTON_CONNECT:
                DEB("---IDC_FUN_3G_BUTTON_CONNECT\n ");		
			
			//net_3gadd(hWnd);				
			
			if (lstat("/dev/mmcblk0p1", &buf)| !S_ISBLK(buf.st_mode)) {
				nonSD(hWnd);
			} else if (!detect_network()) {
			//} else if(0){
				nonconnect3G(hWnd);
			}else {
				fn_3g2(hWnd);
			}
	
			DestroyMainWindow(hWnd);
		        PostQuitMessage(hWnd);	
			//fn_3g2(hWnd);
			//FUN_3G(hWnd);
			break;

		case IDC_FUN_3G_BUTTON_CLOSE:
                DEB("---IDC_FUN_3G_BUTTON_CLOSE\n ");
			//system("killall mplayer");                		
			SYS_SERV_CALL("killall mplayer");
			DestroyMainWindow(hWnd);
			PostQuitMessage(hWnd);
			break;
		}
	}
	break;

	case MSG_MUSIC_ADD:
                DEB("--IDC_FUN_3G_BUTTON_CONNECT\n ");	
		//SendMessage(GetDlgItem(hWnd, IDC_FUN_3G_LISTBOX_NAME), LB_RESETCONTENT, 0, 0);
		//SendMessage(GetDlgItem(hWnd, IDC_FUN_3G_LISTBOX_SINGER), LB_RESETCONTENT, 0, 0);

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



int FUN_3G(HWND hwnd)
{
	MSG           Msg;
	MAINWINCREATE CreateInfo;
	HWND          FUN_3GWnd;

        DEB("[3G]CreateMainWindow \n ");

	CreateInfo.dwStyle        = WS_CAPTION | WS_BORDER | WS_VISIBLE;
	CreateInfo.dwExStyle      = WS_EX_NONE;
	CreateInfo.spCaption      = MSG_3G;
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

	FUN_3GWnd = CreateMainWindow(&CreateInfo);
	if (FUN_3GWnd == HWND_INVALID) {
		return -1;
	}

	ShowWindow(FUN_3GWnd, SW_SHOWNORMAL);
        DEB("GetMessage \n ");
	while (GetMessage(&Msg, FUN_3GWnd)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
        DEB("MainWindowThreadCleanup \n ");
	MainWindowThreadCleanup(FUN_3GWnd);
	return 0;
}

