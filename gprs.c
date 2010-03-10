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

//gprs��l��
//�]�m���W�q�D�B��X���W�H���W�q�B�ܵ��W�q
void gprs_init()
{
	tty_writecmd("at", strlen("at"));
	tty_writecmd("ate0", strlen("ate0"));

	//�]�m���W�q�D�G1�A�ƭ��W�q�D
	tty_writecmd("at+chfa=1", strlen("at+chfa=1"));

	//�]�m��X���W�H���W�q�G100�A�̤j���q
	tty_writecmd("at+clvl=100", strlen("at+clvl=100"));

	//�]�m�q�D1���ܵ��W�q�G10�A�̤j�W�q
	tty_writecmd("at+cmic=1,10", strlen("at+cmic=1,10"));

	//�o�e�ק�r�Ŷ��R�O:1,text�榡
	tty_writecmd("at+cmgf=1", strlen("at+cmgf=1"));

	//�ӹq���
	tty_writecmd("at+clip=1", strlen("at+clip=1"));

	//���TE�r�Ŷ��GGSM�q�{
	tty_writecmd("at+cscs=\"GSM\"", strlen("at+cscs=\"GSM\""));

	//�����s�u����
	tty_writecmd("at+cnmi=2,1,0,0,0", strlen("at+cnmi=2,1,0,0,0"));

}

//�����q��
void gprs_call(char *number, int num)
{
	tty_writecmd("at", strlen("at"));

	//�o�e�����R�OATD
	tty_write("atd", strlen("atd"));

	//�o�e�q�ܸ��X
	tty_write(number, num);

	//�o�e�����M�R�O�����лx
	tty_write(";\r", strlen(";\r"));
	usleep(200000);
}

//��{��ť�q��gprs_ans()���
void gprs_ans()
{
	tty_writecmd("at", strlen("at"));

	//�o�e��ť�R�OATA
	tty_writecmd("ata", strlen("ata"));
}

//�����N�X�G��{���_�q��gprs_hold()���
void gprs_hold()
{
	tty_writecmd("at", strlen("at"));
	//�o�e�����R�OATH
	tty_writecmd("ath", strlen("ath"));
	//tcflush(fd,TCIFLUCH);
}

//��{�o�e�u�H�����
void msg_send(char *number, char *text)
{
	char ctl[] = {26, 0};                              //ctl[0]=26,ctrl+z

	tty_writecmd("at", strlen("at"));

	//�o�e�ק�r�Ŷ��R�O:1,text�榡
	tty_writecmd("at+cmgf=1", strlen("at+cmgf=1"));

	//�o�e�u�H�R�O�G�R�O+���X+�H��+������
	tty_write("at+cmgs=", strlen("at+cmgs="));

	//�o�e�q�ܸ��X
	tty_writecmd(number, strlen(number));

	//�o�e�奻�H��
	tty_write(text, strlen(text));

	//�o�e������
	tty_write(ctl, 1);

	usleep(300000);
}

//�o�eŪ���u�H�R�O����o�u�H������
void msg_read(int index)
{
	char Cmd_Buffer[11] = "at+cmgr=";
	char buffer[3]      = {'\0'};
	gcvt((double)index, 2, buffer);     //index��Ƭ��r�Ŧ�
	strcat(Cmd_Buffer, buffer);
	printf("the string is %s\n", Cmd_Buffer);
	//tty_writecmd("at", strlen("at"));
	tty_writecmd(Cmd_Buffer, strlen(Cmd_Buffer));
}

//�R���u�H��
void msg_delete(int index)
{
	char Cmd_Buffer[11] = "at+cmgd=";
	char buffer[3]      = {'\0'};
	//tty_writecmd("at", strlen("at"));
	gcvt((double)index, 2, buffer);
	strcat(Cmd_Buffer, buffer);
	tty_writecmd(Cmd_Buffer, strlen(Cmd_Buffer));
}

