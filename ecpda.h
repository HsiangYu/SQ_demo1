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

//��L�\�������
//#define IDC_KB 100
#define IDK_CAPS                145
#define IDK_LSHIFT              146
#define IDK_RSHIFT              147
#define IDK_LCTRL               148
#define IDK_LALT                149
#define IDK_RALT                150
#define IDK_RCTRL               151

//�O����L�U�����Ӽ�
#define KBL1                    13
#define KBL2                    14
#define KBL3                    13
#define KBL4                    12
#define KBL5                    6

#define MSG_TASKBAR_CLOSE       500










HWND hwindowDlg;                  //�O�ƥ����f�y�`

char buffA[1000];                       //addnote.c���Ψ쪺
char buffN[1000];                       //notes.c���Ψ쪺
char buffW[1000];                       //writemsg.c���Ψ쪺
char buffP[1000];                       //phonenumber.c���Ψ쪺
char buffE[1000];                       //edit_note.c���Ψ쪺
char buffB[1000];                       //�{�ɦs��O�ƥ��s��ؤ��ƾ�

char buff1[100];                        //send_msg���Ψ쪺 �s��o�e���X��
char buff2[1000];                       //send_msg���Ψ쪺 �s��o�e���e��

static int ind;                         //pthread.c����
#define MSG_NEWMSG       501            //�s�H��
#define MSG_READOK       502            //����c
FILE *fp;
int  i;                          //���R���ɥΨ쪺

int indexV;                       //�O�ƥ��C��د���

pthread_t th_a;
pthread_t th_b;

//�Ҧ�ID���C��


//�H���\��messaging.c�U����ID��
#define IDM_BXXXX        500
#define IDM_SJX          501
#define IDM_CG           502
#define IDM_YFXX         503
#define IDM1_FH          504

//�s�g�s�H��writemsg.c�U����ID��
#define IDW_WCHAR        507
#define IDW_JX           508
#define IDW_GD           509
#define IDW_FH           510
#define IDW_SC           511
#define IDW_BC           512


//����cinbox.c�U����ID��
#define IDI_ICHAR        515
#define IDI_CK           516
#define IDI_GD           517
#define IDI_FH           518
#define IDI_SC           519

//��Z�cdrafts.c�U����ID��
#define IDD_DCHAR        525
#define IDD_BJ           526
#define IDD_GD           527
#define IDD_FH           528
#define IDD_SC           529

//�w�o�H��sentmsg.c�U����ID��
#define IDS1_SCHAR       532
#define IDS_CK           533
#define IDS_GD           534
#define IDS1_FH          535
#define IDS_SC           536

//��ܵo�e�覡sendto.c�U����ID��
#define IDS_DHHM         540
#define IDS_CZTXL        541
#define IDS2_FH          542

//��J�����H�q�ܸ�phonenumber.c�U����ID��
#define IDP_HM           545
#define IDP_PCHAR        546
#define IDP_QD           547
#define IDP_FH           548
#define IDP_SC           549

//�T�w�o�e�ɭ�send_msg.c�U����ID��
#define IDS_HM           552
#define IDS2_SCHAR       553
#define IDS_FS           554
#define IDS3_FH          555







//�O�ƥ�notes.c�U����ID��
#define IDN_NCHAR        700
#define IDN_TJ           701
#define IDN_CK           702
#define IDN_GD           703
#define IDN_SC           704
#define IDN_FH           705


//�K�[�O��addnote.c�U����ID��
#define IDA_ACHAR        708
#define IDA_BC           709
#define IDA_SC           710
#define IDA_FH           711


//�d�ݰO�Ƥ��eviewnote.v�U����ID��
#define IDV_VCHAR        715
#define IDV_BJ           716
#define IDV_FS           717
#define IDV_SC           718
#define IDV_FH           719



//�O�ƥ����I�u��h�v��ܥX��more_note.c�U����ID��
#define IDM_BJ           720
#define IDM_FS           721
#define IDM_SC           722
#define IDM2_FH          723



//�d�ݤ��I�u�s��v��ܥX��edit_note.c�U����ID��
#define IDE_ECHAR        725
#define IDE_BC           726
#define IDE_SC           727
#define IDE_FH           728





//taskbar ���f�y�`
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



