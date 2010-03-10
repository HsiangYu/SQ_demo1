#define FALSE       0
#define TURE        1

//獲得焦點的編輯框句柄
HWND InputEdit;
//主窗口句柄
HWND MainWindow;
//taskbar 窗口句柄
HWND TaskBarWindow;

//HWND hDlg;

typedef struct ALARM {
	char hour[5];
	char minute[5];
	char second[5];
	char change[5];
} S;

#define IDC_TASKBAR_CLOSEOUT       0x0808

#include "lang.h"

