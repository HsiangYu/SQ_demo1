#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include "ecpda.h"
#include "gprs.h"
#include "tty.h"
char        temp[10] = {0};
int         Mes_index;
extern HWND hwnd_l;
extern int  Mon_flag1;
int         Count_Tel = 0, Count = 0;
FILE        *fe;
void * lisen1(void * data)
{
	int  i;
	char ch[10];
	char c;
	char respond_code[4];
	char Date[20];

	// for(i=0;i<1000;i++)

	//tty_writecmd("AT+CMGL=\"ALL\"",13);

	gprs_init();
	//循環讀取gprs串口數據，並輸出
	//  while (STOP==FALSE)
	while (Mon_flag1) {


		tty_read(&c, 1);

		// printf("%c",c);
		if (c == '+') {
			tty_read(respond_code, 4);
			respond_code[4] = '\0';

			if (strcmp(respond_code, "CMGL") == 0) {
				ind++;
			} else if (strcmp(respond_code, "CMTI") == 0) {

				tty_read(temp, 7);
				tty_read(temp, 2);
				temp[3] = '\0';
				//printf(" msg index= %s ",temp);
				Mes_index = atoi(temp);
				//printf(" Mes_index= %d",Mes_index);
				msg_read(Mes_index);
				SendNotifyMessage(hwnd_l, MSG_NEWMSG, 0, 0L);
			} else if (strcmp(respond_code, "CMGR") == 0) {

				tty_read(&c, 1);
				while (c != ',') {
					tty_read(&c, 1);
				}
				tty_read(&c, 1);
				tty_read(&c, 1);

				while (c != '\"') {
					buff1[Count_Tel++] = c;
					tty_read(&c, 1);
				}
				buff1[Count_Tel] = '\0';
				printf("the sms number is %s\n", buff1);

				tty_read(&c, 1);
				tty_read(&c, 1);
				tty_read(&c, 1);

				tty_read(Date, 17);
				Date[17] = '\0';
				printf("the sms date is %s\n", Date);

				tty_read(&c, 1);
				while (c != '\n') {
					tty_read(&c, 1);
				}

				tty_read(&c, 1);
				tty_read(&c, 1);
				while (c != '\n') {
					buff2[Count++] = c;
					tty_read(&c, 1);
				}
				buff2[Count] = '\0';
				printf("the sms context is %s\n", buff2);

				tty_read(&c, 1);
				while (c != 'K') {
					tty_read(&c, 1);
				}

				if (MessageBox(hMainWnd, MSG_NEW_MESSAGE1, MSG_NEW_MESSAGE, MB_YESNO | MB_ICONINFORMATION) == IDYES) {
					SendNotifyMessage(hMainWnd, MSG_READOK, 0, 0L);
				}

				//將讀到的短信內容保存到文件
				fe = fopen(FILE_READ_MSG_DAT, "a+");
				fwrite(&buff1, sizeof(buff1), 1, fe);
				fwrite(&buff2, sizeof(buff2), 1, fe);
				fclose(fe);
			}
		}

	}
}

