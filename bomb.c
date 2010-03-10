#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <popt.h>
#include <unistd.h>
#include <stdio.h>


#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
//#include <minigui/mywindows.h>
#include <minigui/control.h>
//#include <minigui/mgext.h>

#include "lang.h"


#define IDC_RET            201
#define IDC_CREATE         202

#define  MSG_REPAINT       200

#define  POSITIONX         10
#define  IDBUTTON          9


HWND        hcwd;
static int  numbers[81];
static char sign[5];

int sum = 81;

static int  iscontains();
static void drawmap();
static void aroundnumber();

void number(void)
{
	sum--;
	if (sum == 10) {
		MessageBox(0, MSG_SUCCESS, MSG_CONGRATULATION, MB_OK);
		memset(numbers, 0, 81);
		SendNotifyMessage(hcwd, MSG_REPAINT, 0, 0L);
	}

}

static void drawmap()
{
	int i;
	int j;
	int k;
	for (i = 0; i < 81; i++) { //初始化區域信息數組和狀態數組
		numbers [ i ] = 0;
	}
	for (j = 0; j < 10; j++) {
		k = (int)(80.0 * rand() / (RAND_MAX + 1.0));
		while (iscontains(k)) {
			k = (int)(80.0 * rand() / (RAND_MAX + 1.0));
		}
		numbers[k] = -1;
		aroundnumber(k);
	}

	/*numbers[23]=-1;
	   aroundnumber(23);
	   numbers[40]=-1;
	   aroundnumber(40);
	   numbers[49]=-1;
	   aroundnumber(49);
	 */
}

static int iscontains(n)
{
	if (!numbers[n]) {
		return 0;
	}
	return 1;
}

static void aroundnumber(int m)
{

	if  (m > 8 && m % 9 != 0 && -1 != numbers[m - 10]) {

		numbers[m - 10]++;
	}

	if (m > 8 && -1 != numbers[m - 9]) {
		numbers[m - 9]++;
	}

	if (m > 8 && m % 9 != 8 && -1 != numbers[m - 8]) {
		numbers[m - 8]++;
	}

	if (m < 72 && m % 9 != 8 && -1 != numbers[m + 10]) {
		numbers[m + 10]++;
	}

	if (m < 72 && -1 != numbers[m + 9]) {


		numbers[m + 9]++;
	}

	if (m < 72 && m % 9 != 0 && -1 != numbers[m + 8]) {
		numbers[m + 8]++;
	}

	if (m % 9 != 0 && -1 != numbers[m - 1]) {


		numbers[m - 1]++;
	}

	if (m % 9 != 8 && -1 != numbers[m + 1]) {

		numbers[m + 1]++;
	}

}

static int creatbutton(HWND hWnd)
{

	int i, j;
	for (i = 10, j = 0; i < 19; i++, j++) {
		CreateWindow(
			CTRL_BUTTON,
			"",
			WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			IDBUTTON * 0 + i,
			POSITIONX + j * 20, 0, 20, 20,
			hWnd,
			0


			);
		CreateWindow(
			CTRL_BUTTON,
			"",
			WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			IDBUTTON * 1 + i,
			POSITIONX + j * 20, 20, 20, 20,
			hWnd,
			0


			);
		CreateWindow(
			CTRL_BUTTON,
			"",
			WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			IDBUTTON * 2 + i,
			POSITIONX + j * 20, 40, 20, 20,
			hWnd,
			0


			);
		CreateWindow(
			CTRL_BUTTON,
			"",
			WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			IDBUTTON * 3 + i,
			POSITIONX + j * 20, 60, 20, 20,
			hWnd,
			0


			);
		CreateWindow(
			CTRL_BUTTON,
			"",
			WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			IDBUTTON * 4 + i,
			POSITIONX + j * 20, 80, 20, 20,
			hWnd,
			0


			);
		CreateWindow(
			CTRL_BUTTON,
			"",
			WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			IDBUTTON * 5 + i,
			POSITIONX + j * 20, 100, 20, 20,
			hWnd,
			0


			);
		CreateWindow(
			CTRL_BUTTON,
			"",
			WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			IDBUTTON * 6 + i,
			POSITIONX + j * 20, 120, 20, 20,
			hWnd,
			0


			);
		CreateWindow(
			CTRL_BUTTON,
			"",
			WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			IDBUTTON * 7 + i,
			POSITIONX + j * 20, 140, 20, 20,
			hWnd,
			0


			);
		CreateWindow(
			CTRL_BUTTON,
			"",
			WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			IDBUTTON * 8 + i,
			POSITIONX + j * 20, 160, 20, 20,
			hWnd,
			0


			);

	}

}

static int ListWinProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
	static RECT bombregion;
	int         i;
	switch (message) {
	case MSG_CREATE:

		drawmap();
		for (i = 0; i < 81; i++) {
			printf("%d", numbers[i]);
			if ((i + 1) % 9 == 0) {
				printf("\n");
			}
		}

		CreateWindow(CTRL_BUTTON,
			     MSG_NEW,
			     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			     IDC_CREATE,
			     0, 185, 70, 30,
			     hWnd,

			     0);
		CreateWindow(CTRL_BUTTON,
			     MSG_CANCEL,
			     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
			     IDC_RET,
			     170, 185, 70, 30,
			     hWnd,

			     0);

		creatbutton(hWnd);
		break;


	case MSG_REPAINT:
		DestroyAllControls(hWnd);
		SendNotifyMessage(hWnd, MSG_CREATE, 0, 0L);

		break;



	case MSG_COMMAND:
		switch (wParam)	{
		case 10:

			DestroyWindow(GetDlgItem(hWnd, 10));

			if (-1 == numbers[0]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[0]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     100,
				     10, 0, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 11:
			DestroyWindow(GetDlgItem(hWnd, 11));
			if (-1 == numbers[1]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[1]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     101,
				     30, 0, 20, 20,
				     hWnd,
				     0);
			number();

			break;
		case 12:
			DestroyWindow(GetDlgItem(hWnd, 12));
			if (-1 == numbers[2]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[2]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     102,
				     50, 0, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 13:
			DestroyWindow(GetDlgItem(hWnd, 13));
			if (-1 == numbers[3]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[3]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     103,
				     70, 0, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 14:
			DestroyWindow(GetDlgItem(hWnd, 14));
			if (-1 == numbers[4]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[4]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     104,
				     90, 0, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 15:
			DestroyWindow(GetDlgItem(hWnd, 15));
			if (-1 == numbers[5]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[5]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     105,
				     110, 0, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 16:
			DestroyWindow(GetDlgItem(hWnd, 16));
			if (-1 == numbers[6]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[6]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     106,
				     130, 0, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 17:
			DestroyWindow(GetDlgItem(hWnd, 17));
			if (-1 == numbers[7]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[7]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     107,
				     150, 0, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 18:
			DestroyWindow(GetDlgItem(hWnd, 18));
			if (-1 == numbers[8]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[8]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     108,
				     170, 0, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 19:
			DestroyWindow(GetDlgItem(hWnd, 19));
			if (-1 == numbers[9]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[9]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     109,
				     10, 20, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 20:
			DestroyWindow(GetDlgItem(hWnd, 20));
			if (-1 == numbers[10]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[10]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     110,
				     30, 20, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 21:
			DestroyWindow(GetDlgItem(hWnd, 21));
			if (-1 == numbers[11]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[11]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     111,
				     50, 20, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 22:
			DestroyWindow(GetDlgItem(hWnd, 22));
			if (-1 == numbers[12]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[12]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     112,
				     70, 20, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 23:
			DestroyWindow(GetDlgItem(hWnd, 23));
			if (-1 == numbers[13]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[13]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     113,
				     90, 20, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 24:
			DestroyWindow(GetDlgItem(hWnd, 24));
			if (-1 == numbers[14]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[14]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     114,
				     110, 20, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 25:
			DestroyWindow(GetDlgItem(hWnd, 25));
			if (-1 == numbers[15]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[15]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     115,
				     130, 20, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 26:
			DestroyWindow(GetDlgItem(hWnd, 26));
			if (-1 == numbers[16]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[16]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     116,
				     150, 20, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 27:
			DestroyWindow(GetDlgItem(hWnd, 27));
			if (-1 == numbers[17]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[17]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     117,
				     170, 20, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 28:
			DestroyWindow(GetDlgItem(hWnd, 28));
			if (-1 == numbers[18]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[18]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     118,
				     10, 40, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 29:
			DestroyWindow(GetDlgItem(hWnd, 29));
			if (-1 == numbers[19]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[19]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     119,
				     30, 40, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 30:
			DestroyWindow(GetDlgItem(hWnd, 30));
			if (-1 == numbers[20]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[20]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     120,
				     50, 40, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 31:
			DestroyWindow(GetDlgItem(hWnd, 31));
			if (-1 == numbers[21]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[21]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     121,
				     70, 40, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 32:
			DestroyWindow(GetDlgItem(hWnd, 32));
			if (-1 == numbers[22]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[22]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     122,
				     90, 40, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 33:
			DestroyWindow(GetDlgItem(hWnd, 33));
			if (-1 == numbers[23]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[23]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     123,
				     110, 40, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 34:
			DestroyWindow(GetDlgItem(hWnd, 34));
			if (-1 == numbers[24]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[24]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     124,
				     130, 40, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 35:
			DestroyWindow(GetDlgItem(hWnd, 35));
			if (-1 == numbers[25]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[25]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     125,
				     150, 40, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 36:
			DestroyWindow(GetDlgItem(hWnd, 36));
			if (-1 == numbers[26]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[26]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     126,
				     170, 40, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 37:
			DestroyWindow(GetDlgItem(hWnd, 37));
			if (-1 == numbers[27]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[27]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     127,
				     10, 60, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 38:
			DestroyWindow(GetDlgItem(hWnd, 38));
			if (-1 == numbers[28]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[28]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     128,
				     30, 60, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 39:
			DestroyWindow(GetDlgItem(hWnd, 39));
			if (-1 == numbers[29]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[29]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     129,
				     50, 60, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 40:
			DestroyWindow(GetDlgItem(hWnd, 40));
			if (-1 == numbers[30]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[30]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     130,
				     70, 60, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 41:
			DestroyWindow(GetDlgItem(hWnd, 41));
			if (-1 == numbers[31]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[31]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     131,
				     90, 60, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 42:
			DestroyWindow(GetDlgItem(hWnd, 42));
			if (-1 == numbers[32]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[32]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     132,
				     110, 60, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 43:
			DestroyWindow(GetDlgItem(hWnd, 43));
			if (-1 == numbers[33]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[33]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     133,
				     130, 60, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 44:
			DestroyWindow(GetDlgItem(hWnd, 44));
			if (-1 == numbers[34]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[34]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     134,
				     150, 60, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 45:
			DestroyWindow(GetDlgItem(hWnd, 45));
			if (-1 == numbers[35]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[35]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     135,
				     170, 60, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 46:
			DestroyWindow(GetDlgItem(hWnd, 46));
			if (-1 == numbers[36]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[36]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     136,
				     10, 80, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 47:
			DestroyWindow(GetDlgItem(hWnd, 47));
			if (-1 == numbers[37]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[37]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     137,
				     30, 80, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 48:
			DestroyWindow(GetDlgItem(hWnd, 48));
			if (-1 == numbers[38]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[38]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     138,
				     50, 80, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 49:
			DestroyWindow(GetDlgItem(hWnd, 49));
			if (-1 == numbers[39]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[39]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     139,
				     70, 80, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 50:
			DestroyWindow(GetDlgItem(hWnd, 50));
			if (-1 == numbers[40]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[40]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     140,
				     90, 80, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 51:
			DestroyWindow(GetDlgItem(hWnd, 51));
			if (-1 == numbers[41]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[41]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     141,
				     110, 80, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 52:
			DestroyWindow(GetDlgItem(hWnd, 52));
			if (-1 == numbers[42]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[42]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     142,
				     130, 80, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 53:
			DestroyWindow(GetDlgItem(hWnd, 53));
			if (-1 == numbers[43]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[43]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     143,
				     150, 80, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 54:
			DestroyWindow(GetDlgItem(hWnd, 54));
			if (-1 == numbers[44]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[44]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     144,
				     170, 80, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 55:
			DestroyWindow(GetDlgItem(hWnd, 55));
			if (-1 == numbers[45]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[45]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     145,
				     10, 100, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 56:
			DestroyWindow(GetDlgItem(hWnd, 56));
			if (-1 == numbers[46]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[46]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     146,
				     30, 100, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 57:
			DestroyWindow(GetDlgItem(hWnd, 57));
			if (-1 == numbers[47]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[47]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     147,
				     50, 100, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 58:
			DestroyWindow(GetDlgItem(hWnd, 58));
			if (-1 == numbers[48]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[48]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     148,
				     70, 100, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 59:
			DestroyWindow(GetDlgItem(hWnd, 59));
			if (-1 == numbers[49]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[49]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     149,
				     90, 100, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 60:
			DestroyWindow(GetDlgItem(hWnd, 60));
			if (-1 == numbers[50]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[50]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     150,
				     110, 100, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 61:
			DestroyWindow(GetDlgItem(hWnd, 61));
			if (-1 == numbers[51]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[51]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     151,
				     130, 100, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 62:
			DestroyWindow(GetDlgItem(hWnd, 62));
			if (-1 == numbers[52]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[52]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     152,
				     150, 100, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 63:
			DestroyWindow(GetDlgItem(hWnd, 63));
			if (-1 == numbers[53]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[53]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     153,
				     170, 100, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 64:
			DestroyWindow(GetDlgItem(hWnd, 64));
			if (-1 == numbers[54]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[54]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     154,
				     10, 120, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 65:
			DestroyWindow(GetDlgItem(hWnd, 65));
			if (-1 == numbers[55]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[55]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     155,
				     30, 120, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 66:
			DestroyWindow(GetDlgItem(hWnd, 66));
			if (-1 == numbers[56]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[56]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     156,
				     50, 120, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 67:
			DestroyWindow(GetDlgItem(hWnd, 67));
			if (-1 == numbers[57]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[57]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     167,
				     70, 120, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 68:
			DestroyWindow(GetDlgItem(hWnd, 68));
			if (-1 == numbers[58]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[58]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     158,
				     90, 120, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 69:
			DestroyWindow(GetDlgItem(hWnd, 69));
			if (-1 == numbers[59]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[59]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     159,
				     110, 120, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 70:
			DestroyWindow(GetDlgItem(hWnd, 70));
			if (-1 == numbers[60]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[60]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     160,
				     130, 120, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 71:
			DestroyWindow(GetDlgItem(hWnd, 71));
			if (-1 == numbers[61]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[61]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     161,
				     150, 120, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 72:
			DestroyWindow(GetDlgItem(hWnd, 72));
			if (-1 == numbers[62]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[62]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     162,
				     170, 120, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 73:
			DestroyWindow(GetDlgItem(hWnd, 73));
			if (-1 == numbers[63]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[63]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     163,
				     10, 140, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 74:
			DestroyWindow(GetDlgItem(hWnd, 74));
			if (-1 == numbers[64]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[64]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     164,
				     30, 140, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 75:
			DestroyWindow(GetDlgItem(hWnd, 75));
			if (-1 == numbers[65]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[65]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     165,
				     50, 140, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 76:
			DestroyWindow(GetDlgItem(hWnd, 76));
			if (-1 == numbers[66]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[66]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     166,
				     70, 140, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 77:
			DestroyWindow(GetDlgItem(hWnd, 77));
			if (-1 == numbers[67]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[67]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     167,
				     90, 140, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 78:
			DestroyWindow(GetDlgItem(hWnd, 78));
			if (-1 == numbers[68]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[68]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     168,
				     110, 140, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 79:
			DestroyWindow(GetDlgItem(hWnd, 79));
			if (-1 == numbers[69]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[69]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     169,
				     130, 140, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 80:
			DestroyWindow(GetDlgItem(hWnd, 80));
			if (-1 == numbers[70]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[70]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     170,
				     150, 140, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 81:
			DestroyWindow(GetDlgItem(hWnd, 81));
			if (-1 == numbers[71]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[71]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     171,
				     170, 140, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 82:
			DestroyWindow(GetDlgItem(hWnd, 82));
			if (-1 == numbers[72]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[72]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     172,
				     10, 160, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 83:
			DestroyWindow(GetDlgItem(hWnd, 83));
			if (-1 == numbers[73]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[73]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     173,
				     30, 160, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 84:
			DestroyWindow(GetDlgItem(hWnd, 84));
			if (-1 == numbers[74]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[74]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     174,
				     50, 160, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 85:
			DestroyWindow(GetDlgItem(hWnd, 85));
			if (-1 == numbers[75]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[75]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     175,
				     70, 160, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 86:
			DestroyWindow(GetDlgItem(hWnd, 86));
			if (-1 == numbers[76]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[76]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     176,
				     90, 160, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 87:
			DestroyWindow(GetDlgItem(hWnd, 87));
			if (-1 == numbers[77]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[77]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     177,
				     110, 160, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 88:
			DestroyWindow(GetDlgItem(hWnd, 88));
			if (-1 == numbers[78]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[78]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     178,
				     130, 160, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 89:
			DestroyWindow(GetDlgItem(hWnd, 89));
			if (-1 == numbers[79]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[79]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     179,
				     150, 160, 20, 20,
				     hWnd,
				     0);
			number();
			break;
		case 90:
			DestroyWindow(GetDlgItem(hWnd, 90));
			if (-1 == numbers[80]) {
				MessageBox(hWnd, MSG_STEPPED_ON, MSG_CONGRATULATION, MB_OK);
				memset(numbers, 0, 81);
				SendNotifyMessage(hWnd, MSG_REPAINT, 0, 0L);
			}
			sprintf(sign, "%d", numbers[80]);
			CreateWindow(CTRL_STATIC,
				     sign,
				     WS_TABSTOP | WS_VISIBLE | BS_DEFPUSHBUTTON,
				     180,
				     170, 160, 20, 20,
				     hWnd,
				     0);
			number();
			break;


		case IDC_CREATE:
			memset(numbers, 0, 81);
			drawmap();
			SendMessage(hcwd, MSG_REPAINT, 0, 0);
			break;
		case IDC_RET:
			DestroyMainWindow(hWnd);
			PostQuitMessage(hWnd);
			break;
		}
		break;


	case MSG_CLOSE:

		DestroyMainWindow(hWnd);
		PostQuitMessage(hWnd);
		return 0;
	}

	return DefaultMainWinProc(hWnd, message, wParam, lParam);
}

int CreateBombDialog (HWND hWnd)
{
	MSG           Msg;
	MAINWINCREATE CreateInfo;



	CreateInfo.dwStyle        = WS_VISIBLE | WS_BORDER | WS_CAPTION;
	CreateInfo.dwExStyle      = WS_EX_NONE;
	CreateInfo.spCaption      = "bomb";
	CreateInfo.hMenu          = 0;
	CreateInfo.hCursor        = GetSystemCursor(IDC_ARROW);
	CreateInfo.hIcon          = 0;
	CreateInfo.MainWindowProc = ListWinProc;
	CreateInfo.lx             = 0;
	CreateInfo.ty             = 0;
	CreateInfo.rx             = 320;
	CreateInfo.by             = 240;
	CreateInfo.iBkColor       = GetWindowElementColor(BKC_CONTROL_DEF);
	CreateInfo.dwAddData      = 0;
	CreateInfo.dwReserved     = 0;
	CreateInfo.hHosting       = hWnd;



	hcwd = CreateMainWindow(&CreateInfo);



	ShowWindow(hcwd, SW_SHOWNORMAL);

	while (GetMessage(&Msg, hcwd)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	MainWindowThreadCleanup(hcwd);

	return 0;
}

