#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
//#include <minigui/mgext.h>

#include "call.h"

static BOOL RCOM;

void *message_read_com(void *age)
{

	int        Tel_Num;
	int        date;
	int        index;
	static int index1;
	int        i;
	int        k;
	char       c;
	char       temp[10];
	char       PhoneString[20];
	char       *PhoneNum;
	int        record = 1;

	// RCOM=READTURE;


	while (RCOM == 1) {
		tty_read(&c, 1);
		if (c == 'R') {
			tty_read(temp, 3);
			temp[3] = '\0';
			if (strcmp(temp, "ING") == 0) {
				SendNotifyMessage(hMainWnd, MSG_RING, 0, 0L);
			}
		}
		if (c == 'N') {
			tty_read(temp, 9);
			temp[9] = '\0';
			if (strcmp(temp, "O CARRIER") == 0) {
				/*	if(call_NOCARRIER==1)
				    {
					    SendNotifyMessage (CALLhcwd,MSG_RINGING_HOLD1,0,0L);//打電話
					    call_NOCARRIER=0;
				    }
				    else if(call_NOCARRIER==2)
					    {
					    SendNotifyMessage (CALLhcwd,MSG_RINGING_HOLD2,0,0L);//接電話
					    call_NOCARRIER=0;
				    }
				    else
					    {*/
				SendNotifyMessage(hMainWnd, MSG_RING_HOLD, 0, 0L);
				// }
			}
		}
		if (c == '+') {
			tty_read(temp, 4);
			if (strcmp(temp, "CLIP") == 0) {
				for (k = 0; k < 20; k++) {
					tty_read(&c, 1);
					PhoneString[k] = c;
				}
				PhoneString[k] = '\0';
				PhoneNum       = (char *)strtok(PhoneString, "\"");
				PhoneNum       = (char *)strtok(NULL, "\"");
				//strcpy(telephone_number,PhoneNum);
				// printf("the telnum is%s\n",telephone_number);
				printf("the telnum is%s\n", PhoneNum);
			}


		}
	}

}

