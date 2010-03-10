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


#include "lang.h"
#include "mini133.h"

#define	IDC_XC_NONCONNECT	2156
#define	IDC_XC_CLOSE         	IDC_XC_NONCONNECT+15

#define	CONFIG_ELEMENT_H	30
#define CONFIG_ELEMENT_W	0
#define	CONFIG_ELEMENT_DY	30

static DLGTEMPLATE DlgBoxNonConnect =
{
    WS_BORDER | WS_CAPTION, 
    WS_EX_NONE,
    90, 80, 140, 80, 
    "Non Connected",
    0, 0,
    1, NULL,
    0
};

static CTRLDATA BoxNonConnect [] =
{ 
    { 
        CTRL_BUTTON,
        WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON, 
        30, 10, 80, CONFIG_ELEMENT_H,
        IDC_XC_CLOSE,
        "OK",
        0
    }
};

static int NonConnectDialogBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
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
        case IDC_XC_CLOSE:
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

void nonconnect3G(HWND hwnd)
{	
	DEB("[3G]nonconnect3G fun");
        DlgBoxNonConnect.controls = BoxNonConnect;
        DialogBoxIndirectParam (&DlgBoxNonConnect, hwnd, NonConnectDialogBoxProc, (LPARAM)NULL);
}
