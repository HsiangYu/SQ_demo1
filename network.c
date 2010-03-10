#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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

#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include "lang.h"
#include "sys_serv.h"
#include "mini133.h"
#include "network.h"
#include "pdas.h"



#define	CONFIG_ELEMENT_H	30
#define CONFIG_ELEMENT_W	0
#define	CONFIG_ELEMENT_DY	30
#define CONFIG_STATIC_X		10
#define CONFIG_STATIC_Y		10
#define	CONFIG_STATIC_W		60
#define CONFIG_EDIT_X		CONFIG_STATIC_X+CONFIG_STATIC_W+10
#define	CONFIG_EDIT_Y		CONFIG_STATIC_Y
#define	CONFIG_EDIT_W		100

static DLGTEMPLATE DlgBoxNonDongle =
{
    WS_BORDER | WS_CAPTION, 
    WS_EX_NONE,
    90, 80, 140, 80, 
    "Non USB Dongle",
    0, 0,
    1, NULL,
    0
};

static CTRLDATA BoxNonDongle [] =
{ 
    { 
        CTRL_BUTTON,
        WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 
        30, 10, 80, 30,
        IDC_DONGLE_CLOSE,
        "OK",
        0
    }
};

static int NonDongleDialogBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
	static int i;

	//DEB("--[3G]connect-box");
    switch (message) {
    case MSG_INITDIALOG:
	return 1;
        
    case MSG_COMMAND:
        switch (wParam) {
        case IDC_DONGLE_CLOSE:
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

static void nonDongle(HWND hwnd)
{	
	DEB("[3G]nonSD");
        DlgBoxNonDongle.controls = BoxNonDongle;
        DialogBoxIndirectParam (&DlgBoxNonDongle, hwnd, NonDongleDialogBoxProc, (LPARAM)NULL);
}



static DLGTEMPLATE DlgBoxConfig =
{
    WS_BORDER | WS_CAPTION, 
    WS_EX_NONE,
    65, 20, 190, 200, 
    "Configuration",
    0, 0,
    10, NULL,
    0
};

static CTRLDATA CtrlInputConfig [] =
{ 
    {
        CTRL_STATIC,
        WS_VISIBLE | SS_SIMPLE,
        CONFIG_STATIC_X, CONFIG_STATIC_Y, CONFIG_STATIC_W,CONFIG_ELEMENT_H,
        IDC_STATIC, 
        "APN",
        0
    },
    {
        CTRL_EDIT,
        WS_VISIBLE | WS_TABSTOP | WS_BORDER,
        CONFIG_EDIT_X, CONFIG_EDIT_Y+CONFIG_ELEMENT_DY*0, CONFIG_EDIT_W, CONFIG_ELEMENT_H,
        IDC_NETWORK_APN,
        NULL,
        0
    },
    {
        CTRL_STATIC,
        WS_VISIBLE | SS_SIMPLE,
        CONFIG_STATIC_X, CONFIG_STATIC_Y+CONFIG_ELEMENT_DY, CONFIG_STATIC_W, CONFIG_ELEMENT_H,
        IDC_STATIC, 
        "Username",
        0
    },
    {
        CTRL_EDIT,
        WS_VISIBLE | WS_TABSTOP | WS_BORDER,
        CONFIG_EDIT_X, CONFIG_EDIT_Y+CONFIG_ELEMENT_DY*1, CONFIG_EDIT_W, CONFIG_ELEMENT_H,
        IDC_NETWORK_USR,
        NULL,
        0
    },
    {
        CTRL_STATIC,
        WS_VISIBLE | SS_SIMPLE,
        CONFIG_STATIC_X, CONFIG_STATIC_Y+CONFIG_ELEMENT_DY*2, CONFIG_STATIC_W, CONFIG_ELEMENT_H,
        IDC_STATIC, 
        "Password",
        0
    },
    {
        CTRL_EDIT,
        WS_VISIBLE | WS_TABSTOP | WS_BORDER,
        CONFIG_EDIT_X, CONFIG_EDIT_Y+CONFIG_ELEMENT_DY*2, CONFIG_EDIT_W, CONFIG_ELEMENT_H,
        IDC_NETWORK_PWD,
        NULL,
        0
    },
    {
        CTRL_STATIC,
        WS_VISIBLE | SS_SIMPLE,
        CONFIG_STATIC_X, CONFIG_STATIC_Y+CONFIG_ELEMENT_DY*3, CONFIG_STATIC_W, CONFIG_ELEMENT_H,
        IDC_STATIC, 
        "Phone",
        0
    },
    {
        CTRL_EDIT,
        WS_VISIBLE | WS_TABSTOP | WS_BORDER,
        CONFIG_EDIT_X, CONFIG_EDIT_Y+CONFIG_ELEMENT_DY*3, CONFIG_EDIT_W, CONFIG_ELEMENT_H,
        IDC_NETWORK_PHONE,
        NULL,
        0
    },
    {
        CTRL_BUTTON,
        WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 
        10, CONFIG_EDIT_Y+CONFIG_ELEMENT_DY*4+10, 60, CONFIG_ELEMENT_H,
        IDC_NETWORK_OK,
        "OK",
        0
    },
    {
        CTRL_BUTTON,
        WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 
        120, CONFIG_EDIT_Y+CONFIG_ELEMENT_DY*4+10, 60, CONFIG_ELEMENT_H,
        IDC_NETWORK_CANCEL,
        "Cancel",
        0
    }
};

/*
static DLGTEMPLATE DlgBoxConnect =
{
    WS_BORDER | WS_CAPTION, 
    WS_EX_NONE,
    90, 80, 140, 80, 
    "Connecting.....",
    0, 0,
    1, NULL,
    0
};


static CTRLDATA BoxConnect [] =
{ 
    { 
        CTRL_BUTTON,
        WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 
        30, 10, 80, CONFIG_ELEMENT_H,
        IDC_NETWORK_CONNECT_CANCEL,
        "Cancel",
        0
    }
};
*/
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
static void init_config(HWND hWnd)
{
	int i;
	char buff[100];
	FILE *fp;
	//system("/etc/pda/net_config init");
	SYS_SERV_CALL("/etc/pda/net_config init");

	fp=fopen("/tmp/minigui_pda_network.tmp", "r");

	fgets(buff, 100, fp);
	buff[strlen(buff)-1]='\0';
	SetWindowText(GetDlgItem(hWnd, IDC_NETWORK_APN), buff);
	fgets(buff, 100, fp);
	buff[strlen(buff)-1]='\0';
	SetWindowText(GetDlgItem(hWnd, IDC_NETWORK_USR), buff);
	fgets(buff, 100, fp);
	buff[strlen(buff)-1]='\0';
	SetWindowText(GetDlgItem(hWnd, IDC_NETWORK_PWD), buff);
	fgets(buff, 100, fp);
	buff[strlen(buff)-1]='\0';
	SetWindowText(GetDlgItem(hWnd, IDC_NETWORK_PHONE), buff);

	fclose(fp);
	//system("rm /var/tmp/minigui_pda_network.tmp");
	SYS_SERV_CALL("rm /tmp/minigui_pda_network.tmp");
}

static void ok(HWND hWnd)
{	
	char p[100];
	int fd;
	char tittle[] = "[MiniGUI]";
	char apn_buf[] = "\nAPN = ";
	char usr_buf[] = "\nUsername = ";
	char pwd_buf[] = "\nPassword = ";
	char phone_buf[] = "\nPhone = ";

	//system("/etc/pda/net_config ok");
	SYS_SERV_CALL("/etc/pda/net_config ok");
	fd=open("/etc/wvdial.conf", O_WRONLY|O_APPEND);
	
	write(fd, tittle, strlen(tittle));

	write(fd, apn_buf, strlen(apn_buf));
	GetWindowText(GetDlgItem(hWnd, IDC_NETWORK_APN), p, 100);
	write(fd, p, strlen(p));
	
	write(fd, usr_buf, strlen(usr_buf));
	GetWindowText(GetDlgItem(hWnd, IDC_NETWORK_USR), p, 100);
	write(fd, p, strlen(p));

	write(fd, pwd_buf, strlen(pwd_buf));
	GetWindowText(GetDlgItem(hWnd, IDC_NETWORK_PWD), p, 100);
	write(fd, p, strlen(p));

	write(fd, phone_buf, strlen(phone_buf));
	GetWindowText(GetDlgItem(hWnd, IDC_NETWORK_PHONE), p, 100);
	write(fd, p, strlen(p));

	write(fd, "\n", 1);

	close(fd);
}

static int ConfigDialogBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case MSG_INITDIALOG:
	init_config(hDlg);
	return 1;
        
    case MSG_COMMAND:
        switch (wParam) {
        case IDC_NETWORK_OK:
		ok(hDlg);
	case IDC_NETWORK_CANCEL:
        case IDCANCEL:
		EndDialog (hDlg, wParam);
		break;
        }
        break;
    }
    
    return DefaultDialogProc (hDlg, message, wParam, lParam);
}

/*
static int ConnectDialogBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
	static int i;

	//DEB("--[3G]connect-box");
	if(detect_network()) {
	//if (++i>100) {
		EndDialog(hDlg, wParam);
	}
    switch (message) {
    case MSG_INITDIALOG:
	DEB("--[3G]connect-check--detect-init\n");
	return 1;
        
    case MSG_COMMAND:
        switch (wParam) {
        case IDC_NETWORK_CONNECT_CANCEL:
        case IDCANCEL:
		system("killall wvdail");
		//system("kill %d",pid);
		EndDialog (hDlg, wParam);
		break;
        }
        break;
    }
    
    return DefaultDialogProc (hDlg, message, wParam, lParam);
}
*/
/*
static void ConfigDialogBox (HWND hWnd, double* length)
{
    DlgBoxInputLen.controls = CtrlInputLen;
    
    DialogBoxIndirectParam (&DlgBoxInputLen, hWnd, InputLenDialogBoxProc, (LPARAM)null);
}
*/
static void setting(HWND hwnd)
{
	DlgBoxConfig.controls = CtrlInputConfig;
    
	DialogBoxIndirectParam (&DlgBoxConfig, hwnd, ConfigDialogBoxProc, (LPARAM)NULL);
}
/*
static void connect3G(HWND hwnd)
{	
	system("killall wvdial");
        system("wvdial& MiniGUI");

	DEB("[3G]connect3G fun");
        DlgBoxConnect.controls = BoxConnect;
        DialogBoxIndirectParam (&DlgBoxConnect, hwnd, ConnectDialogBoxProc, (LPARAM)NULL);



	int pid;
	if(pid=fork()){
		DEB("[3G]connect3G fun");
		DlgBoxConnect.controls = BoxConnect;
        	DialogBoxIndirectParam (&DlgBoxConnect, hwnd, ConnectDialogBoxProc, (LPARAM)NULL);

	} else {
		system("killall wvdial");
		system("wvdial MiniGUI");
		printf("Children Process\n");
		exit(0);
	}


}
*/
static int MessageSendProc(HWND hwnd, int id, int nc, DWORD add_data)
{
}
/*******************************************************************************
* File Name: ziyuanguanliqi.c
* Copy Right: GaoHaibo
* Author:  GaoHaibo
* Function discription:點擊主窗口資源管理器初始窗口
*******************************************************************************/
static int networkProc(HWND hcwd, int message, WPARAM wParam, LPARAM lParam)
{
        //DEB("[3G]fn_3gProc \n ");
	{

		switch (message) {
		case MSG_CREATE:
		{
			char cwd [MAX_PATH + 1];
			loadbk(hcwd);
			DEB("-[Network]MSG_CREATE\n");
			if(!detect_network()) {
				//CreateWindow (CTRL_BUTTON, "Setting", WS_CHILD | BS_PUSHBUTTON | BS_MULTLINE | WS_VISIBLE, IDC_NETWORK_SET, 10, 100, 100, 30, hcwd, 0);
				CreateWindow (CTRL_BUTTON, "Connect 3G", WS_CHILD | BS_PUSHBUTTON | BS_MULTLINE | WS_VISIBLE, IDC_NETWORK_CONNECT, 120, 100, 100, 30, hcwd, 0);
			} else {
				CreateWindow (CTRL_BUTTON, "disconnect 3G", WS_CHILD | BS_PUSHBUTTON | BS_MULTLINE | WS_VISIBLE, IDC_NETWORK_DISCONNECT, 80, 90, 120, 30, hcwd, 0);
			}
				CreateWindow (CTRL_BUTTON, "Close", WS_CHILD | BS_PUSHBUTTON | BS_MULTLINE | WS_VISIBLE, IDC_NETWORK_CLOSE, 120, 160, 120, 30, hcwd, 0);

			
		}
		break;


		case MSG_CLOSE:
		{
			DEB("-[network]MSG_CLOSE\n");			
			DestroyMainWindow(hcwd);
			PostQuitMessage(hcwd);
		}
			return 0;

		case MSG_COMMAND:
		{
			DEB("-[network]MSG_COMMAND\n");				
			switch (wParam) {
			case IDC_NETWORK_SET:
				DEB("--[Network]IDC_NETWORK_SET\n");
				setting(hcwd);
				break;
			case IDC_NETWORK_CONNECT:
			        DEB("--[network]IDC_NETWORK_CONNECT \n ");
				struct stat buf;
				if(lstat("/dev/sr0", &buf) && lstat("/dev/ttyUSB0", &buf)) {
					nonDongle(hcwd);
				} else {
					connect3G(hcwd);
					//system("/etc/pda/net_config connected");
					SYS_SERV_CALL("/etc/pda/net_config connected");
				}
				DestroyMainWindow(hcwd);
                                PostQuitMessage(hcwd);

				break;

			case IDC_NETWORK_DISCONNECT:
				//system("killall wvdial");
				//system("/etc/pda/net_config disconnect");
				SYS_SERV_CALL("killall wvdial");
				SYS_SERV_CALL("/etc/pda/net_config disconnect");
				DestroyMainWindow(hcwd);
                                PostQuitMessage(hcwd);
                                break;

			case IDC_NETWORK_RETURN:
			        DEB("--[network]IDC_NETWORK_RETURN \n ");

			case IDC_NETWORK_CLOSE:
			        DEB("--[network]IDC_NETWORK_CLOSE \n ");
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


int Network_connect (HWND hWnd)
{
	int           i = 99;
	MSG           Msg;
	HWND          hcwd;
	MAINWINCREATE CreateInfo;

        DEB("[network]Network_connect\n ");

#ifdef _LITE_VERSION
	SetDesktopRect(0, 0, 800, 600);
#endif

	CreateInfo.dwStyle        = WS_VISIBLE | WS_BORDER | WS_CAPTION;
	CreateInfo.dwExStyle      = WS_EX_NONE;
	CreateInfo.spCaption      = MSG_3G_CONNECT;
	CreateInfo.hMenu          = 0;
	CreateInfo.hCursor        = GetSystemCursor(0);
	CreateInfo.hIcon          = 0;
	CreateInfo.MainWindowProc = networkProc;
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

