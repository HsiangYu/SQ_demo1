#ifndef CALL_H
#define CALL_H

/*#include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <termios.h>
 #include <pthread.h>
 #include <time.h>
 #include <unistd.h>
 #include <fcntl.h>
 #include <minigui/common.h>
 #include <minigui/minigui.h>
 #include <minigui/gdi.h>
 #include <minigui/window.h>
 #include <minigui/mywindows.h>
 #include <minigui/control.h>
 #include <minigui/mgext.h>
 #include "gprs.h"
 #include "tty.h"*/
#define IDC_STA             0X300
#define IDC_EDIT            0X301
/*#define IDC_MAKE   0X301*/ //½s¿è«ö¯Ã
#define IDC_OK              0X302
#define IDC_BOOK            0X303  //¹q¸Ü¥»«ö¯Ã
#define IDC_CANCEL          0X304
#define IDC_NUM1            0X305
#define IDC_NUM2            0X306
#define IDC_NUM3            0X307
#define IDC_NUM4            0X308
#define IDC_NUM5            0X309
#define IDC_NUM6            0X310
#define IDC_NUM7            0X311
#define IDC_NUM8            0X312
#define IDC_NUM9            0X313
#define IDC_NUMX            0X314
#define IDC_NUM0            0X315
#define IDC_NUMY            0X316
#define IDC_NUMQ            0X317
#define IDC_NUMS            0X318
#define IDC_KB              100
#define IDK_CAPS            27
#define IDK_LSHIFT          40
#define IDK_RSHIFT          51
#define IDK_LCTRL           52
#define IDK_LALT            53
#define IDK_RALT            55
#define IDK_RCTRL           56
#define IDC_STAW            234
#define _IDC_TIMER          800
#define KBL1                13
#define KBL2                14
#define KBL3                13
#define KBL4                12
#define KBL5                6
#define MSG_RING            0X319
#define MSG_RING_HOLD       0X320
#define BAUDRATE            B9600
#define COM                 "/dev/ttyS0"




int  tty_init();
int  tty_end();
int  tty_read(char *buf, int nbytes);
int  tty_write(char *buf, int nbytes);
int  tty_writecmd(char *buf, int nbytes);
void gprs_init();
void gprs_call(char *number, int num);
void gprs_hold();
HWND            hedit;
HWND            hMainWnd;
char            buff[20];
char            buff1[20];
int             i;
static long int KState    = 0, CAPSState = 0;
static BOOL     ShiftFlag = 0;
HWND            hcwd;
int             tag;
static int      flag_call_ans;
#define MSG_TAG       901
#endif
