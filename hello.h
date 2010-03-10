#ifndef _HELLO_H
#define _HELLO_H

HWND hwindowDlg;
HWND MainWindow;
HWND Input;
HWND hwnd2;
HWND hwcd;

//int KeyBoard (HWND hWnd)
char PhoneNum[20];
char buff1[100];
char buff2[100];
FILE *fp;
char buffer[20];
#define MSG_RING           400

#define IDM_MENU           100
#define IDM_QUIT           101
#define IDM_START          102

#define IDC_OPTIONS        103
#define IDC_NEW            105
#define IDC_CALL           106
#define IDC_MORE           107
#define IDC_RETURN         108
#define IDC_CLEAN          109
#define IDC_SAVE           110
#define IDC_DEL            111
#define IDC_KEYBOARD       112


#define IDC_LISTBOX        130
#define IDC_ADD            131
#define IDC_DEL1           132
#define IDC_NAME           133
#define IDC_NUMBER         134
#define IDC_RETURN1        135

#define IDC_CHAR           120
#define IDC_CHAR1          121
#define IDC_CHAR2          122
#define IDC_YES            123
#define IDC_NO             124

#define IDC_K1             140
#define IDC_K2             141
#define IDC_K3             142
#define IDC_K4             143
#define IDC_K5             144
#define IDC_K6             145
#define IDC_K7             146
#define IDC_K8             147
#define IDC_K9             148
#define IDC_KMI            149
#define IDC_K0             150
#define IDC_KJING          151
#define IDC_CALL2          152
#define IDC_MORE2          153
#define IDC_RETURN3        154
#define IDC_DEL3           155
#define IDC_NUMBER1        156
#define IDC_CHAR3          157
#define IDC_HOLD           158


#define IDC_COOLBAR        170
#define IDC_CB             171


#define IDC_Edit           175
#define IDC_Ans            176
#define IDC_Refuse         177
//#define IDC_K1

#endif
