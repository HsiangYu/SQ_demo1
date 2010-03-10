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
        IDC_XZ_CONNECT_CANCEL,
        "Cancel",
        0
    }
};

static int flag_detect_network;

static int ConnectDialogBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
	static int i;

	//DEB("--[3G]connect-box");
	if (flag_detect_network) {
	if(detect_network()) {
	//if (++i>100) {
		
		//SYS_SERV_CALL("/etc/pda/net_config connected");
			//printf("detect/n");
			flag_detect_network=0;
		EndDialog(hDlg, wParam);
		}else {
		}
	}
    switch (message) {
    case MSG_INITDIALOG:
	DEB("--[3G]connect-check--detect-init\n");
	return 1;
        
    case MSG_COMMAND:
        switch (wParam) {
        case IDC_XZ_CONNECT_CANCEL:
        case IDCANCEL:
		DEB("--[conect]wvdial--");
		//system("killall wvdial");
		//system("kill -9 %d",pid);
		SYS_SERV_CALL("killall wvdial");
		EndDialog (hDlg, wParam);
		break;
        }
        break;
    }
    
    return DefaultDialogProc (hDlg, message, wParam, lParam);
}

int detect_network(void)
{
	struct stat buf;
	
#if 0
	if(lstat("/sys/class/net/ppp0", &buf))
		return 0;
	else
		return 1;
#else
	int inet_sock;
	struct ifreq ifr;

	inet_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(inet_sock<0)
		printf("cann't build socket\n");
	strcpy(ifr.ifr_name, "ppp0"); 

	if (ioctl(inet_sock, SIOCGIFADDR, &ifr) < 0)
	{
		close(inet_sock);
		return 0;
	} else {
		close(inet_sock);
		return 1;
	}
#endif
}


void connect3G(HWND hwnd)
{	
	//system("killall wvdial");
        //system("/etc/pda/net_config wvdial");
	SYS_SERV_CALL("killall wvdial");
	SYS_SERV_CALL("/etc/pda/net_config wvdial");
	flag_detect_network=1;

	DEB("[3G]connect3G fun");
        DlgBoxConnect.controls = BoxConnect;
        
        DialogBoxIndirectParam (&DlgBoxConnect, hwnd, ConnectDialogBoxProc, (LPARAM)NULL);


/*
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
*/

}
