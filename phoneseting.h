#ifndef COMMON_H
#define COMMON_H

#define MSG_USR1       1550
#define MSG_USR2       1551

//定義鬧鐘結構體
typedef struct ALARMCLOCK {

	int h;
	int m;
	int s;
	int status;
} AT;

//定義時間結構體
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

