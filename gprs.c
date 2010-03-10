#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "tty.h"
#include "gprs.h"

//gprs初始化
//設置音頻通道、輸出音頻信號增益、話筒增益
void gprs_init()
{
	tty_writecmd("at", strlen("at"));
	tty_writecmd("ate0", strlen("ate0"));

	//設置音頻通道：1，副音頻通道
	tty_writecmd("at+chfa=1", strlen("at+chfa=1"));

	//設置輸出音頻信號增益：100，最大音量
	tty_writecmd("at+clvl=100", strlen("at+clvl=100"));

	//設置通道1的話筒增益：10，最大增益
	tty_writecmd("at+cmic=1,10", strlen("at+cmic=1,10"));

	//發送修改字符集命令:1,text格式
	tty_writecmd("at+cmgf=1", strlen("at+cmgf=1"));

	//來電顯示
	tty_writecmd("at+clip=1", strlen("at+clip=1"));

	//選擇TE字符集：GSM默認
	tty_writecmd("at+cscs=\"GSM\"", strlen("at+cscs=\"GSM\""));

	//接收新短消息
	tty_writecmd("at+cnmi=2,1,0,0,0", strlen("at+cnmi=2,1,0,0,0"));

}

//撥打電話
void gprs_call(char *number, int num)
{
	tty_writecmd("at", strlen("at"));

	//發送撥打命令ATD
	tty_write("atd", strlen("atd"));

	//發送電話號碼
	tty_write(number, num);

	//發送分號和命令結束標誌
	tty_write(";\r", strlen(";\r"));
	usleep(200000);
}

//實現接聽電話gprs_ans()函數
void gprs_ans()
{
	tty_writecmd("at", strlen("at"));

	//發送接聽命令ATA
	tty_writecmd("ata", strlen("ata"));
}

//完善代碼：實現掛斷電話gprs_hold()函數
void gprs_hold()
{
	tty_writecmd("at", strlen("at"));
	//發送掛機命令ATH
	tty_writecmd("ath", strlen("ath"));
	//tcflush(fd,TCIFLUCH);
}

//實現發送短信的函數
void msg_send(char *number, char *text)
{
	char ctl[] = {26, 0};                              //ctl[0]=26,ctrl+z

	tty_writecmd("at", strlen("at"));

	//發送修改字符集命令:1,text格式
	tty_writecmd("at+cmgf=1", strlen("at+cmgf=1"));

	//發送短信命令：命令+號碼+信息+結束符
	tty_write("at+cmgs=", strlen("at+cmgs="));

	//發送電話號碼
	tty_writecmd(number, strlen(number));

	//發送文本信息
	tty_write(text, strlen(text));

	//發送結束符
	tty_write(ctl, 1);

	usleep(300000);
}

//發送讀取短信命令並獲得短信的索引
void msg_read(int index)
{
	char Cmd_Buffer[11] = "at+cmgr=";
	char buffer[3]      = {'\0'};
	gcvt((double)index, 2, buffer);     //index轉化為字符串
	strcat(Cmd_Buffer, buffer);
	printf("the string is %s\n", Cmd_Buffer);
	//tty_writecmd("at", strlen("at"));
	tty_writecmd(Cmd_Buffer, strlen(Cmd_Buffer));
}

//刪除短信息
void msg_delete(int index)
{
	char Cmd_Buffer[11] = "at+cmgd=";
	char buffer[3]      = {'\0'};
	//tty_writecmd("at", strlen("at"));
	gcvt((double)index, 2, buffer);
	strcat(Cmd_Buffer, buffer);
	tty_writecmd(Cmd_Buffer, strlen(Cmd_Buffer));
}

