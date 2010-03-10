#ifndef __GPRS_H__
#define __GPRS_H__

extern char * cmd[];
void gprs_init();
void gprs_msg(char *number, int num);
void gprs_call(char *number, int num);
void gprs_hold();
void gprs_ans();
void gprs_call(char *number, int num);
#endif
