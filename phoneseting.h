#ifndef COMMON_H
#define COMMON_H

#define MSG_USR1       1550
#define MSG_USR2       1551

//�w�q�x�����c��
typedef struct ALARMCLOCK {

	int h;
	int m;
	int s;
	int status;
} AT;

//�w�q�ɶ����c��
typedef struct time {
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
} TIME;

AT alarmsave;

#endif

