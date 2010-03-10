
#ifndef _SYS_SERV_H_
#define _SYS_SERV_H_

extern int fd_sys_call[2];
extern int fd_sys_ret[2];
static char cmdline[200];


#define SYS_SERV_CALL(cmd) {                                    \
              sprintf(cmdline, cmd);                              \
              write(fd_sys_call[1], cmdline, strlen(cmdline));   \
              cmdline[0]='0';                                  \
              do {                                              \
                read(fd_sys_ret[0], cmdline, 5);              \
              } while(cmdline[0]!='1');                           \
        }


#endif /* _LANG_H_ */

