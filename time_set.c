#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include <minigui/mywindows.h>
#include <minigui/mgext.h>
#include "phoneseting.h"

#include "lang.h"

#define IDC_TIMEHOUR         160
#define IDC_TIMEMINUTE       161
#define IDC_TIMESTYLE        162
#define IDC_TIMEYEAR         163
#define IDC_TIMEMONTH        164
#define IDC_TIMEDATE         165
#define IDC_TIMEOK           166
#define IDC_TIMERET          167
#define IDC_TIMESTATIC       168

static DLGTEMPLATE TimeSetDate =
{
	WS_BORDER, //| WS_CAPTION,
	WS_EX_NONE,
	0, 40, 320, 200,
	MSG_TIME_SETTING,
	0, 0,
	16, NULL,
	0
};

static CTRLDATA timesetDate[] =
{
	{
		"static", WS_CHILD | SS_GROUPBOX | WS_VISIBLE, 5, 10, 305, 80, IDC_TIMESTATIC, MSG_TIME_SETTING, 0
	},
	{
		CTRL_COMBOBOX,
		WS_VISIBLE | CBS_DROPDOWNLIST | CBS_READONLY | CBS_NOTIFY,
		10, 30, 80, 20,
		IDC_TIMEHOUR,
		"",
		0
	},
	{
		"static", WS_CHILD | SS_CENTER | WS_VISIBLE, 80, 32, 40, 20, IDC_TIMESTATIC, MSG_HOUR, 0
	},
	{
		CTRL_COMBOBOX,
		WS_VISIBLE | CBS_DROPDOWNLIST | CBS_READONLY | CBS_NOTIFY,
		120, 30, 80, 20,
		IDC_TIMEMINUTE,
		"",
		0
	},
	{
		"static", WS_CHILD | SS_CENTER | WS_VISIBLE, 190, 32, 40, 20, IDC_TIMESTATIC, MSG_MINUTE, 0
	},
	{
		"static",
		WS_CHILD | SS_RIGHT | WS_VISIBLE,
		10, 65, 70, 70,
		IDC_TIMESTATIC,
		MSG_TIME_FORMAT,
		0
	},
	{
		CTRL_COMBOBOX,
		WS_VISIBLE | CBS_DROPDOWNLIST | CBS_READONLY | CBS_NOTIFY,
		100, 65, 100, 20,
		IDC_TIMESTYLE,
		"",
		0
	},
	{
		"static", WS_CHILD | SS_GROUPBOX | WS_VISIBLE, 5, 100, 305, 57, IDC_TIMESTATIC, MSG_DATE_SETTING, 0
	},
	{
		CTRL_COMBOBOX,
		WS_VISIBLE | CBS_DROPDOWNLIST | CBS_READONLY | CBS_NOTIFY,
		10, 130, 100, 20,
		IDC_TIMEYEAR,
		"",
		0
	},
	{
		"static", WS_CHILD | SS_CENTER | WS_VISIBLE, 95, 132, 50, 20, IDC_TIMESTATIC, MSG_YEAR, 0
	},
	{
		CTRL_COMBOBOX,
		WS_VISIBLE | CBS_DROPDOWNLIST | CBS_READONLY | CBS_NOTIFY,
		130, 130, 45, 20,
		IDC_TIMEMONTH,
		"",
		0
	},
	{
		"static",
		WS_CHILD | SS_CENTER | WS_VISIBLE,
		160, 132, 50, 20,
		IDC_TIMESTATIC,
		MSG_MONTH,
		0
	},
	{
		CTRL_COMBOBOX,
		WS_VISIBLE | CBS_DROPDOWNLIST | CBS_READONLY | CBS_NOTIFY,
		190, 130, 45, 20,
		IDC_TIMEDATE,
		"",
		0
	},
	{
		"static",
		WS_CHILD | SS_CENTER | WS_VISIBLE,
		220, 132, 50, 20,
		IDC_TIMESTATIC,
		MSG_DAY,
		0
	},
	{
		CTRL_BUTTON,
		WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP | WS_GROUP,
		10, 160, 70, 25,
		IDC_TIMEOK,
		MSG_OK,
		0
	},
	{
		CTRL_BUTTON,
		WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP | WS_GROUP,
		170, 160, 70, 25,
		IDC_TIMERET,
		MSG_RETURN,
		0
	},
};
static const char * p_hour [] =
{
	"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12",
	"13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24"
};
static const char * pp_hour [] =
{
	"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"
};
static const char * p_minute [] =
{
	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
	"10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
	"20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
	"30", "31", "32", "33", "34", "35", "36", "37", "38", "39",
	"40", "41", "42", "43", "44", "45", "46", "47", "48", "49",
	"50", "51", "52", "53", "54", "55", "56", "57", "58", "59"

};
static const char * p_style [] =
{
	"12",
	"24"
};
static const char * p_year [] =
{
	"2000", "2001", "2002", "2003", "2004", "2005", "2006", "2007", "2008", "2009",
	"2010", "2011", "2012", "2013", "2014", "2015", "2016", "2017", "2018", "2019",
	"2020", "2021", "2022", "2023", "2024", "2025", "2026", "2027", "2028", "2029"
};
static const char * p_month [] =
{
	"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"
};
static const char * p_day [] =
{
	"1", "2", "3", "4", "5", "6", "7", "8", "9", "10",
	"11", "12", "13", "14", "15", "16", "17", "18", "19", "20",
	"21", "22", "23", "24", "25", "26", "27", "27", "28", "29", "30",
	"31"
};

static int timesetProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
	int i;

	//用來保存不同組合框光標所在位置
	int t_hour, tt_hour, t_minute, t_style, t_year, t_month, t_day;

	//用來保存設定的系統時間
	TIME system_time;

	struct tm settime;
	time_t    T;
	switch (message) {
	case MSG_INITDIALOG:
		for (i = 0; i < 12; i++) {
			SendDlgItemMessage(hDlg, IDC_TIMEMONTH, CB_ADDSTRING, 0, (LPARAM)p_month[i]);
		}
		for (i = 0; i <= 31; i++) {
			SendDlgItemMessage(hDlg, IDC_TIMEDATE, CB_ADDSTRING, 0, (LPARAM)p_day[i]);
		}
		for (i = 0; i < 60; i++) {
			SendDlgItemMessage(hDlg, IDC_TIMEMINUTE, CB_ADDSTRING, 0, (LPARAM)p_minute[i]);
		}
		for (i = 0; i < 2; i++)	{
			SendDlgItemMessage(hDlg, IDC_TIMESTYLE, CB_ADDSTRING, 0, (LPARAM)p_style[i]);
		}
		for (i = 0; i < 24; i++) {
			SendDlgItemMessage(hDlg, IDC_TIMEHOUR, CB_ADDSTRING, 0, (LPARAM)p_hour[i]);
		}
		for (i = 0; i < 30; i++) {
			SendDlgItemMessage(hDlg, IDC_TIMEYEAR, CB_ADDSTRING, 0, (LPARAM)p_year[i]);
		}
		return 0;

	case MSG_COMMAND:
	{
		switch (wParam)	{
		//確定按鈕
		case IDC_TIMEOK:
			//獲取組合框中光標當前位置
			t_hour   = SendDlgItemMessage(hDlg, IDC_TIMEHOUR, CB_GETCURSEL, 0, 0);
			t_minute = SendDlgItemMessage(hDlg, IDC_TIMEMINUTE, CB_GETCURSEL, 0, 0);
			t_style  = SendDlgItemMessage(hDlg, IDC_TIMESTYLE, CB_GETCURSEL, 0, 0);
			t_year   = SendDlgItemMessage(hDlg, IDC_TIMEYEAR, CB_GETCURSEL, 0, 0);
			t_month  = SendDlgItemMessage(hDlg, IDC_TIMEMONTH, CB_GETCURSEL, 0, 0);
			t_day    = SendDlgItemMessage(hDlg, IDC_TIMEDATE, CB_GETCURSEL, 0, 0);

			system_time.year   = atoi(p_year[t_year]);
			system_time.month  = atoi(p_month[t_month]);
			system_time.day    = atoi(p_day[t_day]);
			system_time.hour   = atoi(p_hour[t_hour]);
			system_time.minute = atoi(p_minute[t_minute]);
			system_time.second = 0;

			settime.tm_sec  = system_time.minute;
			settime.tm_min  = system_time.minute;
			settime.tm_hour = system_time.hour;
			settime.tm_mday = system_time.day;
			settime.tm_mon  = system_time.month - 1;
			settime.tm_year = system_time.year - 1900;

			T = mktime(&settime);
			stime(&T);
			SendNotifyMessage(hDlg, MSG_CLOSE, 0, 0);
			return 0;
		case IDC_TIMERET:
			EndDialog(hDlg, 0);
			return 0;
		}
	}
	break;
	case MSG_CLOSE:
	{
		EndDialog(hDlg, wParam);
	}
		return 0;
	}
	return DefaultDialogProc(hDlg, message, wParam, lParam);

}

int timeset(HWND hWnd)
{


	TimeSetDate.controls = timesetDate;

	DialogBoxIndirectParam(&TimeSetDate, hWnd, timesetProc, 0L);

	return 0;
}

