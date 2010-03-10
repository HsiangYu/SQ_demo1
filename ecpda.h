#define TURE                    1
#define FALSE                   0
#define IDC_static              101
#define IDC_Start               102
#define IDC_Change              103
#define IDC_KB                  104
#define IDC_Quit                105
#define IDC_button1             106
#define IDC_button2             107
#define IDC_button3             108
#define IDC_button4             109
#define IDC_button5             110
#define IDC_button6             111
#define IDC_button7             112
#define IDC_button8             113
#define IDC_button9             114
#define IDC_button10            115
#define IDC_button11            116
#define IDC_button12            117
#define IDC_button13            118
#define IDC_button14            119
#define IDC_button15            120
#define IDC_button16            121
#define IDC_button17            122
#define IDC_static1             123
#define IDC_static2             124
#define IDC_static3             125
#define IDC_static4             126
#define IDC_edit1               127
#define IDC_edit2               128
#define IDC_edit3               129
#define IDC_button18            130
#define IDC_button19            131
#define IDC_button20            132
#define IDC_button21            133
#define IDC_button22            134
#define IDC_edit4               135
#define IDC_list                136
#define IDC_edit5               137
#define IDC_button23            138
#define IDC_button24            139
#define IDC_button25            140
#define IDC_button26            141
#define IDC_button27            142
#define IDC_button28            143
#define IDC_CB                  144

//鍵盤功能鍵鍵值
//#define IDC_KB 100
#define IDK_CAPS                145
#define IDK_LSHIFT              146
#define IDK_RSHIFT              147
#define IDK_LCTRL               148
#define IDK_LALT                149
#define IDK_RALT                150
#define IDK_RCTRL               151

//記錄鍵盤各行按鍵個數
#define KBL1                    13
#define KBL2                    14
#define KBL3                    13
#define KBL4                    12
#define KBL5                    6

#define MSG_TASKBAR_CLOSE       500










HWND hwindowDlg;                  //記事本窗口句柄

char buffA[1000];                       //addnote.c中用到的
char buffN[1000];                       //notes.c中用到的
char buffW[1000];                       //writemsg.c中用到的
char buffP[1000];                       //phonenumber.c中用到的
char buffE[1000];                       //edit_note.c中用到的
char buffB[1000];                       //臨時存放記事本編輯框中數據

char buff1[100];                        //send_msg中用到的 存放發送號碼的
char buff2[1000];                       //send_msg中用到的 存放發送內容的

static int ind;                         //pthread.c中的
#define MSG_NEWMSG       501            //新信息
#define MSG_READOK       502            //收件箱
FILE *fp;
int  i;                          //做刪除時用到的

int indexV;                       //記事本列表框索引

pthread_t th_a;
pthread_t th_b;

//所有ID號列表


//信息功能messaging.c下控件ID號
#define IDM_BXXXX        500
#define IDM_SJX          501
#define IDM_CG           502
#define IDM_YFXX         503
#define IDM1_FH          504

//編寫新信息writemsg.c下控件ID號
#define IDW_WCHAR        507
#define IDW_JX           508
#define IDW_GD           509
#define IDW_FH           510
#define IDW_SC           511
#define IDW_BC           512


//收件箱inbox.c下控件ID號
#define IDI_ICHAR        515
#define IDI_CK           516
#define IDI_GD           517
#define IDI_FH           518
#define IDI_SC           519

//草稿箱drafts.c下控件ID號
#define IDD_DCHAR        525
#define IDD_BJ           526
#define IDD_GD           527
#define IDD_FH           528
#define IDD_SC           529

//已發信息sentmsg.c下控件ID號
#define IDS1_SCHAR       532
#define IDS_CK           533
#define IDS_GD           534
#define IDS1_FH          535
#define IDS_SC           536

//選擇發送方式sendto.c下控件ID號
#define IDS_DHHM         540
#define IDS_CZTXL        541
#define IDS2_FH          542

//輸入接受人電話號phonenumber.c下控件ID號
#define IDP_HM           545
#define IDP_PCHAR        546
#define IDP_QD           547
#define IDP_FH           548
#define IDP_SC           549

//確定發送界面send_msg.c下控件ID號
#define IDS_HM           552
#define IDS2_SCHAR       553
#define IDS_FS           554
#define IDS3_FH          555







//記事本notes.c下控件ID號
#define IDN_NCHAR        700
#define IDN_TJ           701
#define IDN_CK           702
#define IDN_GD           703
#define IDN_SC           704
#define IDN_FH           705


//添加記事addnote.c下控件ID號
#define IDA_ACHAR        708
#define IDA_BC           709
#define IDA_SC           710
#define IDA_FH           711


//查看記事內容viewnote.v下控件ID號
#define IDV_VCHAR        715
#define IDV_BJ           716
#define IDV_FS           717
#define IDV_SC           718
#define IDV_FH           719



//記事本中點「更多」顯示出的more_note.c下控件ID號
#define IDM_BJ           720
#define IDM_FS           721
#define IDM_SC           722
#define IDM2_FH          723



//查看中點「編輯」顯示出的edit_note.c下控件ID號
#define IDE_ECHAR        725
#define IDE_BC           726
#define IDE_SC           727
#define IDE_FH           728





//taskbar 窗口句柄
HWND        TaskBarWindow;
HWND        InputEdit;
BOOL        GPRSSTOP;
BOOL        STOP;
BOOL        CLOCKSTOP;
BOOL        DATESTOP;
static BOOL KBON;
char        buff[50];
static HWND hMainWnd;
//static HWND hKB;

void * TaskBar(void *);
int    menu(HWND hWnd);
int    sysset(HWND hwnd);
void * alarm_proc(void *);

void * OpenPhone(void *);
struct alarmclock {
	int flag;
	char alarm_time[20];
} alarm1;

#include "lang.h"



