#include <stdio.h>
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
//#include <minigui/mgext.h>
#include "gprs.h"
#include "tty.h"



#include "common.h"
#include "call.h"

extern int Mon_flag;

void * lisen()
{

	char    c;
	char    respond_code[20]  = {0};
	char    respond_code1[20] = {0};
	char    temp[20]          = {0};
	Message inbox;
	CL      r;
	char    *Num;
	int     i;
	int     tel_count;
	int     msg_count;
	FILE    *fp1;
	tty_init();
	gprs_init();  // 初識化GPRS模塊
	while (Mon_flag) {
		// memset(respond_code,0,20);
		tty_read(&c, 1);
		//printf("dds\n");
		if (c == 'R') {
			tty_read(respond_code, 3);
			respond_code[3] = '\0';
			if (strcmp(respond_code, "ING") == 0) {
				//printf("%s",respond_code);
				calltype = 2;
				SendNotifyMessage(hcwd, MSG_RING, 0, 0L);
				printf("call call ....");
			}
		}

		if (c == 'N') {   //收到掛電話
			tty_read(respond_code1, 9);
			//respond_code1[9]='\0';
			if (strcmp(respond_code1, "O CARRIER") == 0) {
				//發送消息到通話界面，結束正在通話界面，返回主界面。
				if (calltype == 1) {
					SendNotifyMessage(h_calling, MSG_USRHOLD, 0, 0L);
				} else if (calltype == 2)    {
					strcpy(r.Phone_num, PhoneNum);
					//records_write(FILE_MISSED_CALL_DAT,&r);
					SendMessage(c_holding, MSG_MISSED, 0, 0L);
				}
			}
		}

		if (c == '+') {
			tty_read(respond_code, 4);
			respond_code[4] = '\0';
			if (strcmp(respond_code, "CLIP") == 0) {
				printf("CLIP");
				for (i = 0; i < 20; i++) {
					tty_read(&c, 1);
					PhoneNum[i] = c;
				}
				PhoneNum[i] = '\0';
				Num         = (char*)strtok(PhoneNum, "\"");
				Num         = (char*)strtok(NULL, "\"");
				strcpy(temp, Num);
				strcpy(PhoneNum, temp);
				//printf("%s",Num);
			} else if (strcmp(respond_code, "CMTI") == 0)	   {
				//msg_read(Mes_index);

				tty_read(temp, 7);
				tty_read(temp, 2);
				temp[3] = '\0';
				printf(" msg index= %s ", temp);
				Mes_index = atoi(temp);
				printf(" Mes_index= %d", Mes_index);
				msg_read(Mes_index);
				SendNotifyMessage(hMainWnd, MSG_NEWMSG, 0, 0L);
			} else if (strcmp(respond_code, "CMGR") == 0)	   {
				tty_read(&c, 1);
				while (c != ',') {
					tty_read(&c, 1);
				}
				tty_read(&c, 1);
				tty_read(&c, 1);
				while (c != '\"') {
					Tel_Num[tel_count++] = c;
					tty_read(&c, 1);
				}
				Tel_Num[tel_count] = '\0';
				printf("\n- %s \n", Tel_Num);
				tty_read(temp, 3);

				tty_read(Data, 17);
				Data[17] = '\0';
				printf("\n %s\n ", Data);

				tty_read(&c, 1);
				while (c != '\n') {
					tty_read(&c, 1);
				}

				tty_read(&c, 1);
				tty_read(&c, 1);
				while (c != '\n') {
					Msg_text[msg_count++] = c;
					tty_read(&c, 1);
				}
				Msg_text[msg_count] = '\0';
				printf("\n %s ", Msg_text);
				tty_read(&c, 1);
				while (c != 'K') {
					tty_read(&c, 1);
				}

				if ((fp1 = fopen("./message/inbox.dat", "a+")) == NULL)	{
					printf("open file inbox.dat error, program ending !");
				}


				//  printf("now find the file\n");
//                                fprintf(fp1,"%d",Mes_index);


				inbox.index = Mes_index;
				memset(inbox.name, 20, 0);
				strcpy(inbox.PhoneNumber, Tel_Num);
				strcpy(inbox.Msgtime, Data);
				strcpy(inbox.Msgtext, Msg_text);

				fwrite(&inbox, sizeof(Message), 1, fp1);


				fclose(fp1);

			}



		}

	}
}

