#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BAUDRATE       B9600          //默認波特率
#define COM3           "/dev/ttyS2"
static int            fd;
static struct termios oldtio, newtio;
//==初始化串口==================================================
int tty_init()
{
	fd = open(COM3, O_RDWR );
	if (fd < 0) {
		perror(COM3);
		exit(-1);
	}

	tcgetattr(fd, &oldtio);                //保存當前設置
	bzero(&newtio, sizeof(newtio));
	newtio.c_cflag        = BAUDRATE | /*CRTSCTS |*/ CS8 /*| CLOCAL | CREAD */;
	newtio.c_iflag        = IGNPAR | ICRNL;
	newtio.c_oflag        = 0;
	newtio.c_lflag        = ICANON;
	newtio.c_cc[VINTR]    = 0;      /* Ctrl-c */
	newtio.c_cc[VQUIT]    = 0;      /* Ctrl-\ */
	newtio.c_cc[VERASE]   = 0;      /* del */
	newtio.c_cc[VKILL]    = 0;      /* @ */
	newtio.c_cc[VEOF]     = 4;      /* Ctrl-d */
	newtio.c_cc[VTIME]    = 0;      /* 不使用分割字元組的計時器 */
	newtio.c_cc[VMIN]     = 1;      /* 在讀取到 1 個字元前先停止 */
	newtio.c_cc[VSWTC]    = 0;      /* '\0' */
	newtio.c_cc[VSTART]   = 0;      /* Ctrl-q */
	newtio.c_cc[VSTOP]    = 0;      /* Ctrl-s */
	newtio.c_cc[VSUSP]    = 0;      /* Ctrl-z */
	newtio.c_cc[VEOL]     = 0;      /* '\0' */
	newtio.c_cc[VREPRINT] = 0;      /* Ctrl-r */
	newtio.c_cc[VDISCARD] = 0;      /* Ctrl-u */
	newtio.c_cc[VWERASE]  = 0;      /* Ctrl-w */
	newtio.c_cc[VLNEXT]   = 0;      /* Ctrl-v */
	newtio.c_cc[VEOL2]    = 0;      /* '\0' */
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &newtio);  //設置新參數
	return 0;
}

//==============================================================
//讀gprs串口數據
int tty_read(char *buf, int nbytes)
{
	int i, num;
	num = read(fd, buf, nbytes);
	for (i = 0; i < num; i++) {
		printf("%c", buf[i]);
	}
	return num;
}

//==============================================================
//寫gprs串口數據
int tty_write(char *buf, int nbytes)
{
	int i;
	for (i = 0; i < nbytes; i++) {
		write(fd, &buf[i], 1);
		usleep(100);
	}
	//等待所有輸出都被發送
	return tcdrain(fd);
}

//==============================================================
//寫gprs串口命令
int tty_writecmd(char *buf, int nbytes)
{
	int i;
	for (i = 0; i < nbytes; i++) {
		write(fd, &buf[i], 1);
		usleep(100);
	}
	write(fd, "\r", 1);
	usleep(300000);
	//等待所有輸出都被發送
	return tcdrain(fd);
}

//==============================================================
//恢復並關閉gprs串口
int tty_end()
{
	//恢復舊設置
	tcsetattr(fd, TCSANOW, &oldtio);

	//關閉串口
	close(fd);
}

