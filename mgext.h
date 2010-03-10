/**
 * \file mgext.h
 * \author Wei Yongming <ymwei@minigui.org>
 * \date 2002/01/06
 *
 * The header file of MiniGUI extension library.
 *
   \verbatim
    Copyright (C) 1998-2002 Wei Yongming and others
    Copyright (C) 2003 Feynman Software

    This file is part of MiniGUI, a lightweight Graphics User Interface
    support library for real-time embedded Linux.

    This file is part of MiniGUI, a lightweight Graphics User Interface
    support library for real-time embedded Linux.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

   \endverbatim
 */

/*
 * $Id: mgext.h,v 1.74 2003/12/02 02:18:21 tangxf Exp $
 *
 *             MiniGUIExt for Linux Version 1.3.x
 *             Copyright (C) 2002 ~ 2003 Feynman Software.
 *             Copyright (C) 2001 ~ 2002 Wei Yongming and others.
 *
 *             Create date: 2001/01/15, by Zhang Yunfan.
 */

#ifndef MGEXT_H
#define MGEXT_H

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * \defgroup mgext_fns Interfaces of the MiniGUI extension library (libmgext)
 * @{
 */

/**
 * \fn BOOL InitMiniGUIExt (void)
 * \brief Initializes MiniGUI extension library.
 *
 * This function initializes MiniGUI extension library. You should call
 * this function before using any API provided by MiniGUIExt library.
 *
 * \return This function returns TRUE when success, otherwise FALSE.
 *
 * \sa MiniGUIExtCleanUp
 */
BOOL InitMiniGUIExt(void);

/**
 * \fn MiniGUIExtCleanUp
 * \brief Cleans up the MiniGUI extension library.
 *
 * This function cleans up the MiniGUI extension library. You should call
 * this function when you no longer use APIs provided by MiniGUIExt library.
 *
 * \sa MiniGUIExtCleanUp
 */
void MiniGUIExtCleanUp(void);

/****** Full GIF support *************************************************/
#ifdef _EXT_FULLGIF

/**
 * \defgroup mgext_gif_fns GIF image file operations
 * @{
 */

typedef struct tagGIFBITMAPELEMENT {
	struct tagGIFBITMAPELEMENT *prev;
	struct tagGIFBITMAPELEMENT *next;
	BITMAP Bitmap;
	int top;
	int left;
} GIFBITMAPELEMENT;

typedef struct tagGIFBITMAP {
	int delaytime;
	int count;
	GIFBITMAPELEMENT *first;
	GIFBITMAPELEMENT *current;
} GIFBITMAP;

int     ReadGIF(FILE * src, GIFBITMAP * gifbmp, HDC hdc);
void    CleanGIF(GIFBITMAP * gifbmp);
void    RewindGIF(GIFBITMAP * gifbmp);
PBITMAP GetCurrentGIFBmp(GIFBITMAP * gifbmp);
PBITMAP GetNextGIFBmp(GIFBITMAP * gifbmp);
void    InitGIF(GIFBITMAP * gifbmp);

/** @} end of mgext_gif_fns */

#endif /* _EXT_FULLGIF */

/**
 * \defgroup mgext_controls Controls defined in libmgext
 * @{
 */

/****** TreeView Control *************************************************/
#ifdef _EXT_CTRL_TREEVIEW

/**
 * \defgroup mgext_ctrl_treeview TreeView control
 *
 * \note You can pass the root item information through \a dwAddData
 * argument of CreateWindowEx function.
 *
 * \code
 * HICON folded, unfolded;
 * TVITEMINFO tvii = {"/proc", 0, folded, unfolded};
 *
 * CreateWindowEx (CTRL_TREEVIEW, ..., (DWORD)&tvii);
 * \endcode
 *
 * @{
 */

/**
 * \def CTRL_TREEVIEW
 * \brief The class name of treeview control.
 */
#define CTRL_TREEVIEW       ("TreeView")

#define TVIF_ROOT           0x0001L
#define TVIF_FOLD           0x0004L
#define TVIF_SELECTED       0x0008L

/** TreeView item info structure */
typedef struct _TVITEMINFO {
	/** text of the item */
	char *text;

	/**
	 * State flags of the item, can be OR'ed by the following values:
	 *
	 * - TVIF_ROOT\n
	 *   The item is a root item.
	 * - TVIF_SELECTED\n
	 *   The item is a selected item.
	 * - TVIF_FOLD\n
	 *   The item is folded.
	 *
	 * When adding an item to the TreeView control, only TVIF_FOLD
	 * flag is valid.
	 */
	DWORD dwFlags;

	/** Handle to the icon of the folded item. */
	HICON hIconFold;
	/** Handle to the icon of the unfolded item. */
	HICON hIconUnfold;

	/** Additional data associated with the item. */
	DWORD dwAddData;
} TVITEMINFO;

/**
 * \var typedef TVITEMINFO *PTVITEMINFO;
 * \brief Data type of the pointer to a TVITEMINFO.
 */
typedef TVITEMINFO *PTVITEMINFO;

/**
 * \defgroup mgext_ctrl_treeview_styles Styles of treeview control
 * @{
 */

/**
 * \def TVS_NOTIFY
 * \brief Sends the parent window notification messages when the user
 *        clicks or double-clicks the control.
 */
#define TVS_NOTIFY               0x0001L

/**
 * \def TVS_WITHICON
 * \brief The treeview item will use icons to indicate folded or unfolded status.
 */
#define TVS_WITHICON             0x0002L

/**
 * \def TVS_ICONFORSELECT
 * \brief The fold icon is used to indicate selected item.
 *
 * For TreeView control with TVS_ICONFORSELECT style, the item icons
 * will be used to indicate selected or unselected status of the item.
 *
 */
#define TVS_ICONFORSELECT        0x0004L

/* Internally used style */
#define TVS_FOCUS                0x0008L

/**
 * \def TVS_SORT
 * \brief Enables sorting in the treeview.
 */
#define TVS_SORT                 0x0010L

/** @} end of mgext_ctrl_treeview_styles */

/**
 * \defgroup mgext_ctrl_treeview_msgs Messages of treeview control
 * @{
 */

/**
 * \def TVM_ADDITEM
 * \brief Adds a new item in a treeview control.
 *
 * \code
 * TVM_ADDITEM
 * GHANDLE parent;
 * PTVITEMINFO newIteminfo;
 *
 * wParam = (WPARAM)parent;
 * lParam = (LPARAM)newIteminfo;
 * \endcode
 *
 * \param parent Handle to the item who is the parent of the new item.
 * \param newIteminfo Pointer to the item info structure of the new item
 *        to be added.
 *
 * \return The handle to the new item on success, otherwise return 0.
 */
#define TVM_ADDITEM              0xF110

/**
 * \def TVM_INSERTITEM
 * \brief The same as TVM_ADDITEM message.
 */
#define TVM_INSERTITEM           0xF111

/**
 * \def TVM_GETROOT
 * \brief Gets the root item of a treeview control.
 *
 * \code
 * TVM_GETROOT
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return The handle to the root item.
 */
#define TVM_GETROOT              0xF112

/**
 * \def TVM_DELTREE
 * \brief Removes an item and its descendant items for the TreeView control.
 *
 * \code
 * TVM_DELTREE
 * GHANDLE item;
 *
 * wParam = (WPARAM)item;
 * lParam = 0;
 * \endcode
 *
 * \return Zero on success, otherwise -1.
 */
#define TVM_DELTREE              0xF113

/**
 * \def TVM_SEARCHITEM
 * \brief Searches an item matching a specified string in a subtree rooted by a specific item.
 *
 * \note This is a depth first search.
 *
 * \code
 * TVM_SEARCHITEM
 * GHNADLE item;
 * char* string;
 *
 * wParam = (WPARAM)item;
 * lParam = (LPARAM)string;
 * \endcode
 *
 * \param found The handle to the item which is the root item of the subtree.
 *        Zero means the root item.
 * \param string The specified string.
 *
 * \return The handle to the item whose text matches the specified string
 *         on success, otherwise zero for not found or invalid parameters.
 */
#define TVM_SEARCHITEM           0xF114

/**
 * \def TVM_FINDCHILD
 * \brief Finds a child item matching a specified string in children of a specific item.
 *
 * \code
 * TVM_FINDCHILD
 * GHNADLE item;
 * char* string;
 *
 * wParam = (WPARAM)item;
 * lParam = (LPARAM)string;
 * \endcode
 *
 * \param item The handle to the item. Zero means the root item.
 * \param string The specified string.
 *
 * \return The handle to the item whose text matches the specified string
 *         on success, otherwise zero for not found or invalid parameters.
 */
#define TVM_FINDCHILD            0xF115

/**
 * \def TVM_GETSELITEM
 * \brief Gets the selected item.
 *
 * \code
 * TVM_GETSELITEM
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return Handle to the selected item.
 */
#define TVM_GETSELITEM           0xF116

/**
 * \def TVM_SETSELITEM
 * \brief Sets the selected item.
 *
 * \code
 * TVM_SETSELITEM
 * GHANDLE item;
 *
 * wParam = (WPARAM)item;
 * lParam = 0;
 * \endcode
 *
 * \param item The handle to candicate item.
 *
 * \return The handle to the old selected item on success, otherwise -1.
 */
#define TVM_SETSELITEM           0xF117

/**
 * \def TVM_GETITEMTEXTLEN
 * \brief Retrives the text length of the specified item in TreeView control.
 *
 * \code
 * TVM_GETITEMTEXTLEN
 *
 * GHANDLE item;
 *
 * wParam = (WPARAM)item;
 * lParam = (LPARAM)0;
 * \endcode
 *
 * \param item The handle to the item which we want to retrive.
 *
 * \return The length of the item text on success, otherwise -1.
 */
#define TVM_GETITEMTEXTLEN       0xF118

/**
 * \def TVM_GETITEMTEXT
 * \brief Retrives the text of the specified item in TreeView control.
 *
 * \code
 * TVM_GETITEMTEXT
 *
 * GHANDLE item;
 * char* buffer;
 *
 * wParam = (WPARAM)item;
 * lParam = (LPARAM)buffer;
 * \endcode
 *
 * \param item The handle to the item which we want to retrive.
 * \param buffer The pointer to a buffer to save the text of the item.
 *
 * \return The length of the item text on success, otherwise -1.
 */
#define TVM_GETITEMTEXT          0xF119

/**
 * \def TVM_GETITEMINFO
 * \brief Retrives the information of an item in TreeView control.
 *
 * \code
 * TVM_GETITEMINFO
 *
 * GHANDLE item;
 * TVITEMINFO* tvii;
 *
 * wParam = (WPARAM)item;
 * lParam = (LPARAM)tvii;
 * \endcode
 *
 * \param item The handle to the item which we want to retrive.
 * \param tvii A pointer to a TVITEMINFO structure to receive the item information.
 *        Note that the \a text field of this structure should be large enough to
 *        get the item text.
 *
 * \return Zero on success, otherwise -1.
 *
 * \sa TVM_GETITEMTEXTLEN
 */
#define TVM_GETITEMINFO          0xF11A

/**
 * \def TVM_SETITEMINFO
 * \brief Changes the information of an item.
 *
 * \code
 * TVM_SETITEMTEXT
 * GHANDLE item;
 * TVITEMINFO* tvii;
 *
 * wParam = (WPARAM)id;
 * lParam = (LPARAM)tvii;
 * \endcode
 *
 * \param item The handle of the item.
 * \param newText Pointer to a TVITEMINFO structure which include the new information
 *        of the item.
 *
 * \return Zero on success, otherwise -1.
 */
#define TVM_SETITEMINFO          0xF11B

#define TVIR_PARENT              1
#define TVIR_FIRSTCHILD          2
#define TVIR_NEXTSIBLING         3
#define TVIR_PREVSIBLING         4

/**
 * \def TVM_GETRELATEDITEM
 * \brief Retrives related item of specific item.
 *
 * \code
 * TVM_GETRELATEDITEM
 * int related;
 * GHANDLE item;
 *
 * wParam = (WPARAM)related;
 * lParam = (LPARAM)item;
 * \endcode
 *
 * \param related A integer which indicates the relationship between
 *        the item to retrive and the specified item, can be one of the following values:
 *          - TVIR_PARENT\n
 *              To retrive the parent item of the specified item.
 *          - TVIR_FIRSTCHILD\n
 *              To retrive the first child item of the specified item.
 *          - TVIR_NEXTSIBLING\n
 *              To retrive the next sibling item of the specified item.
 *          - TVIR_PREVSIBLING\n
 *              To retrive the previous sibling item of the specified item.
 *
 * \param item The handle to the known item.
 *
 * \return The handle to the related item on success, otherwise 0.
 */
#define TVM_GETRELATEDITEM       0xF11C

/**
 * \def TVM_SETSTRCMPFUNC
 * \brief Sets the STRCMP function used to sort items.
 *
 * An application sends a TVM_SETSTRCMPFUNC message to set a
 * new STRCMP function to sort items in the TreeView control.
 *
 * Note that you should send this message before adding
 * any item to the TreeView control.
 *
 * \code
 * static int my_strcmp (const char* s1, const char* s2, size_t n)
 * {
 *      ...
 *      return 0;
 * }
 *
 * TVM_SETSTRCMPFUNC
 *
 * wParam = 0;
 * lParam = (LPARAM) my_strcmp;
 * \endcode
 *
 * \param my_strcmp Your own function to compare two strings.
 *
 * \return One of the following values:
 *          - 0\n     Success
 *          - -1\n    Not an empty TreeView control
 */
#define TVM_SETSTRCMPFUNC        0xF11D

#define TVM_MSGMAX               0xF120

/** @} end of mgext_ctrl_treeview_msgs */

/**
 * \defgroup mgext_ctrl_treeview_ncs Notification codes of treeview control
 * @{
 */

/**
 * \def TVN_ERRSPACE
 * \brief Indicates that memory is not enough.
 *
 * A list box sends an TVN_ERRSPACE notification message to its parent window
 * when it cannot allocate enough memory to complete the current operation.
 */
#define TVN_ERRSPACE             255

/**
 * \def TVN_SELCHANGE
 * \brief Notifies the change of selection.
 */
#define TVN_SELCHANGE            1

/**
 * \def TVN_DBLCLK
 * \brief Notifies the user has double-clicked an item.
 */
#define TVN_DBLCLK               2

/**
 * \def TVN_SETFOCUS
 * \brief Indicates gain of input focus.
 *
 * A TreeView control sends an TVN_SETFOCUS notification message to its parent window
 * when the list box gains the input focus.
 */
#define TVN_SETFOCUS             4

/**
 * \def TVN_KILLFOCUS
 * \brief Indicates loss of input focus.
 *
 * A TreeView control sends an TVN_KILLFOCUS notification message to its parent window
 * when the list box loses the input focus.
 */
#define TVN_KILLFOCUS            5

/**
 * \def TVN_CLICKED
 * \brief Indicates the user has clicked an item.
 */
#define TVN_CLICKED              7

/**
 * \def TVN_ENTER
 * \brief Indicates the user has pressed the ENTER key.
 */
#define TVN_ENTER                8

/**
 * \def TVN_FOLDED
 * \brief Indicates a sub-tree has folded.
 *
 * \note This is an extended notification, the control calls \a NotifyParentEx function
 *       to notify the parent, and passes the handle to the folded item through
 *       \a add_data argument of \a NotifyParentEx function. You should define and
 *       set Notificaton Callback Procedure for the control in order to
 *       get the handle to the folded item.
 *
 * \sa SetNotificationCallback, NotifyParentEx
 */
#define TVN_FOLDED               9

/**
 * \def TVN_UNFOLDED
 * \brief Indicates a sub-tree has unfolded.
 *
 * \note This is an extended notification, the control calls \a NotifyParentEx function
 *       to nofity the parent, and passes the handle to the unfolded item through
 *       \a add_data argument of \a NotifyParentEx function. You should define and
 *       set Notificaton Callback Procedure for the control in order to
 *       get the handle to the unfolded item.
 *
 * \sa SetNotificationCallback, NotifyParentEx
 */
#define TVN_UNFOLDED             10

/** @} end of mgext_ctrl_treeview_ncs */

/** @} end of mgext_ctrl_treeview */

#endif /* _EXT_CTRL_TREEVIEW */

/******************************** MonthCalendar Control ****************************/
#ifdef _EXT_CTRL_MONTHCAL

/**
 * \defgroup mgext_ctrl_monthcal MonthCalendar control
 * @{
 */

/**
 * \def CTRL_MONTHCALENDAR
 * \brief The class name of monthcalendar control.
 */
#define CTRL_MONTHCALENDAR       ("MonthCalendar")

/** Structure of the system time */
typedef struct _SYSTEMTIME {
	/** Year number of the date */
	int year;
	/** Month number of the date */
	int month;
	/** Day number of the date */
	int day;
	/** Weekday number of the date */
	int weekday;
} SYSTEMTIME;

/**
 * \var typedef SYSTEMTIME *PSYSTEMTIME;
 * \brief Data type of the pointer to a SYSTEMTIME.
 */
typedef SYSTEMTIME *PSYSTEMTIME;

/** Struture of the color info of the monthcalendar control */
typedef struct _MCCOLORINFO {
	/** Color of the titile background */
	int clr_titlebk;
	/** Color of the titile text */
	int clr_titletext;
	/** Color of the arrow */
	int clr_arrow;
	/** Color of the hilighted arrow background*/
	int clr_arrowHibk;

	/** Color of the week caption background */
	int clr_weekcaptbk;
	/** Color of the week caption text */
	int clr_weekcapttext;

	/** Color of the day text background */
	int clr_daybk;
	/** Color of the hilighted day text background */
	int clr_dayHibk;
	/** Color of the day text */
	int clr_daytext;
	/** Color of the trailing day text */
	int clr_trailingtext;
	/** Color of the hilighted day text */
	int clr_dayHitext;
} MCCOLORINFO;

/**
 * \var typedef MCCOLORINFO *PMCCOLORINFO;
 * \brief Data type of the pointer to a MCCOLORINFO.
 */
typedef MCCOLORINFO *PMCCOLORINFO;

/**
 * \defgroup mgext_ctrl_monthcal_styles Styles of monthcalendar control
 * @{
 */

/**
 * \def MCS_CHN
 * \brief Displays chinese label.
 */
#define MCS_CHN                   0x0001L

/**
 * \def MCS_ENG_L
 * \brief Displays long english label.
 */
#define MCS_ENG_L                 0x0002L

/**
 * \def MCS_ENG_S
 * \brief Displays short english label.
 */
#define MCS_ENG_S                 0x0003L

/**
 * \def MCS_NOTIFY
 * \brief Notifies the parent window when something happens.
 */
#define MCS_NOTIFY                0x0004L

/** @} end of mgext_ctrl_monthcal_styles */

/**
 * \defgroup mgext_ctrl_monthcal_msgs Messages of monthcalendar control
 * @{
 */

/**
 * \def MCM_GETCURDAY
 * \brief Gets the day number of the current selected date.
 *
 * \code
 * MCM_GETCURDAY
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return The day number of the current selected date.
 */
#define MCM_GETCURDAY             0xF300

/**
 * \def MCM_GETCURMONTH
 * \brief Gets the month number of the current selected date.
 *
 * \code
 * MCM_GETCURMONTH
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return The month number of the current selected date.
 */
#define MCM_GETCURMONTH           0xF301

/**
 * \def MCM_GETCURYEAR
 * \brief Gets the year number of the current selected date.
 *
 * \code
 * MCM_GETCURYEAR
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return The year number of the current selected date.
 */
#define MCM_GETCURYEAR            0xF302

/**
 * \def MCM_GETCURWEEKDAY
 * \brief Gets the weekday number of the current selected date.
 *
 * \code
 * MCM_GETCURWEEKDAY
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return The weekday number of the current selected date.
 */
#define MCM_GETCURWEEKDAY         0xF303

/**
 * \def MCM_GETCURMONLEN
 * \brief Gets the month length of the current selected date.
 *
 * \code
 * MCM_GETCURMONLEN
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return The month length of the current selected date.
 */
#define MCM_GETCURMONLEN          0xF304

/**
 * \def MCM_SETCURDAY
 * \brief Changes the day of the currently selected date.
 *
 * \code
 * MCM_SETCURDAY
 * int newday;
 *
 * wParam = (WPARAM)newday;
 * lParam = 0;
 * \endcode
 *
 * \param newday The new day number of the currently selected date.
 */
#define MCM_SETCURDAY             0xF305

/**
 * \def MCM_SETCURMONTH
 * \brief Changes the month of the currently selected date.
 *
 * \code
 * MCM_SETCURMONTH
 * int newmonth;
 *
 * wParam = (WPARAM)newmonth;
 * lParam = 0;
 * \endcode
 *
 * \param newmonth The new month number of the currently selected date.
 */
#define MCM_SETCURMONTH           0xF306

/**
 * \def MCM_SETCURYEAR
 * \brief Changes the year of the currently selected date.
 *
 * \code
 * MCM_SETCURYEAR
 * int newyear;
 *
 * wParam = (WPARAM)newyear;
 * lParam = 0;
 * \endcode
 *
 * \param newyear The new year number of the currently selected date.
 */
#define MCM_SETCURYEAR            0xF307

/**
 * \def MCM_SETTODAY
 * \brief Sets the currently selected date as the date of "today".
 *
 * \code
 * MCM_SETTODAY
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 */
#define MCM_SETTODAY              0xF308

/**
 * \def MCM_GETFIRSTWEEKDAY
 * \brief Gets the first day of the week.
 *
 * \code
 * MCM_GETFIRSTWEEKDAY
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return The first day of the week.
 */
#define MCM_GETFIRSTWEEKDAY       0xF309

/**
 * \def MCM_GETCURDATE
 * \brief Gets the currently selected date.
 *
 * \code
 * MCM_GETCURDATE
 * PSYSTEMTIME pcurdate;
 *
 * wParam = 0;
 * lParam = (LPARAM)pcurdate;
 * \endcode
 *
 * \param pcurdate Pointer to the SYSTEMTIME structure to retreive the date.
 */
#define MCM_GETCURDATE            0xF310

/**
 * \def MCM_GETTODAY
 * \brief Gets the date of "today".
 *
 * \code
 * MCM_GETTODAY
 * PSYSTEMTIME pcurdate;
 *
 * wParam = 0;
 * lParam = (LPARAM)pcurdate;
 * \endcode
 *
 * \param pcurdate Pointer to the SYSTEMTIME structure to retreive the
 *             date of "today".
 */
#define MCM_GETTODAY              0xF311

/**
 * \def MCM_GETMINREQRECTW
 * \brief Gets the minimum width required to display a full month in a month
 *         calendar control.
 *
 * \code
 * MCM_GETMINREQRECTW
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return The minimum width required to dispaly a full month.
 */
#define MCM_GETMINREQRECTW        0xF312

/**
 * \def MCM_GETMINREQRECTH
 * \brief Gets the minimum height required to display a full month in a month
 *         calendar control.
 *
 * \code
 * MCM_GETMINREQRECTH
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return The minimum height required to dispaly a full month.
 */
#define MCM_GETMINREQRECTH        0xF313

/**
 * \def MCM_SETCURDATE
 * \brief Sets the currently selected date.
 *
 * \code
 * MCM_SETCURDATE
 * PSYSTEMTIME pcurdate;
 *
 * wParam = 0;
 * lParam = (LPARAM)pcurdate;
 * \endcode
 *
 * \param pcurdate Pointer to the SYSTEMTIME structure storing the values of
 *             the current selected date.
 */
#define MCM_SETCURDATE            0xF314

/**
 * \def MCM_SETCOLOR
 * \brief Sets the color of the monthcalendar control.
 *
 * \code
 * MCM_SETCOLOR
 * PMCCOLORINFO newcolor;
 *
 * wParam = 0;
 * lParam = (LPARAM)newcolor;
 * \endcode
 *
 * \param newcolor Pointer to the MCCOLORINFO structure storing the vaules of
 *             the new color info.
 */
#define MCM_SETCOLOR              0xF315

/**
 * \def MCM_GETCOLOR
 * \brief Gets the color of the monthcalendar control.
 *
 * \code
 * MCM_GETCOLOR
 * PMCCOLORINFO color;
 *
 * wParam = 0;
 * lParam = (LPARAM)color;
 * \endcode
 *
 * \param color Pointer to the MCCOLORINFO structure retreiving the color info.
 */
#define MCM_GETCOLOR              0xF316

/** @} end of mgext_ctrl_monthcal_msgs */

/**
 * \defgroup mgext_ctrl_monthcal_ncs Notification codes of monthcalendar control
 * @{
 */

/**
 * \def MCN_DATECHANGE
 * \brief Notifies that the currently selected date is changed.
 */
#define MCN_DATECHANGE            1
#define MCN_DAYCHANGE             2

/** @} end of mgext_ctrl_monthcal_ncs */

/** @} end of mgext_ctrl_monthcal */

#endif /* _EXT_CTRL_MONTHCAL */

/********************** Spin Control *****************************************/
#ifdef _EXT_CTRL_SPINBOX

/**
 * \defgroup mgext_ctrl_spinbox SpinBox control
 * @{
 */

/**
 * \def CTRL_SPINBOX
 * \brief The class name of spinbox control.
 */
#define CTRL_SPINBOX         ("SpinBox")

#define SPINBOX_WIDTH        13
#define SPINBOX_HEIGHT       16

/** Structure of the spinbox info */
typedef struct _SPININFO {
	/** Maximum position value */
	int max;
	/** Minimum position value */
	int min;
	/** Current position value */
	int cur;
} SPININFO;

/**
 * \var typedef SPININFO *PSPININFO;
 * \brief Data type of the pointer to a SPININFO.
 */
typedef SPININFO *PSPININFO;


/**
 * \defgroup mgext_ctrl_spinbox_styles Styles of spinbox control
 * @{
 */

/**
 * \def SPS_AUTOSCROLL
 * \brief The spinbox control can automatically scroll,
 *        and disable itself when reach maximal or minimal value.
 */
#define SPS_AUTOSCROLL        0x00000001L

/** @} end of mgext_ctrl_spinbox_styles */

/**
 * \defgroup mgext_ctrl_spinbox_msgs Messages of spinbox control
 * @{
 */

#define KS_SPINPOST           0x00010000

/**
 * \def SPM_SETTARGET
 * \brief Sets the target window of the spinbox.
 *
 * When the user click the up or down arrow of the spin box, it will
 * emulate the down and up of the key SCANCODE_CURSORBLOCKUP or
 * SCANCODE_CURSORBLOCKDOWN, and post MSG_KEYDOWN and MSG_KEYUP
 * message to the target window. Note that the shifit key status of the
 * message will have the flag KS_SPINPOST set.
 *
 * \code
 * SPM_SETTARGET
 * HWND hTarget;
 *
 * wParam = 0;
 * lParam = (LPARAM)hTarget;
 * \endcode
 *
 * \param hTarget Handle of the target window.
 * \return Always be zero.
 */
#define SPM_SETTARGET         0xF300

/**
 * \def SPM_GETTARGET
 * \brief Gets the target window of the spinbox.
 *
 * \code
 * SPM_GETTARGET
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return The handle to the target window.
 */
#define SPM_GETTARGET         0xF301

/**
 * \def SPM_SETINFO
 * \brief Sets the parameter information of the spinbox.
 *
 * \code
 * SPM_SETINFO
 * PSPININFO newinfo;
 *
 * wParam = 0;
 * lParam = (LPARAM)newinfo;
 * \endcode
 *
 * \param newinfo Pointer to the SPININFO structure storing the new spinbox info.
 *
 * \return Zero on success, -1 to indicate invalid parameter.
 *
 * \sa SPININFO
 */
#define SPM_SETINFO           0xF302

/**
 * \def SPM_GETINFO
 * \brief Gets the parameter infos of the spinbox.
 *
 * \code
 * SPM_GETINFO
 * PSPININFO info;
 *
 * wParam = 0;
 * lParam = (LPARAM)info;
 * \endcode
 *
 * \param info Pointer to the SPININFO structure retreiving the spinbox info.
 *
 * \return Zero on success, -1 to indicate invalid parameter.
 *
 * \sa SPININFO
 */
#define SPM_GETINFO           0xF303

/**
 * \def SPM_DISABLEUP
 * \brief Disable the ability to scroll up.
 *
 * \code
 * SPM_DISABLEUP
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return Always be zero.
 */
#define SPM_DISABLEUP         0xF304

/**
 * \def SPM_DISABLEDOWN
 * \brief Disable the ability to scroll down.
 *
 * \code
 * SPM_DISABLEDOWN
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return Always be zero.
 */
#define SPM_DISABLEDOWN       0xF305

/**
 * \def SPM_ENABLEUP
 * \brief Enable the ability to scroll up.
 *
 * \code
 * SPM_ENABLEUP
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return Always be zero.
 */
#define SPM_ENABLEUP          0xF306

/**
 * \def SPM_ENABLEDOWN
 * \brief Enable the ability to scroll down.
 *
 * \code
 * SPM_ENABLEDOWN
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return Always be zero.
 */
#define SPM_ENABLEDOWN        0xF307

/**
 * \def SPM_SETCUR
 * \brief Sets the current position in the range of the spinbox.
 *
 * \code
 * SPM_SETCUR
 * int pos;
 *
 * wParam = (WPARAM)pos;
 * lParam = 0;
 * \endcode
 *
 * \param pos The current position to set.
 *
 * \return Zero on success, -1 to indicate invalid parameter.
 */
#define SPM_SETCUR            0xF308

/**
 * \def SPM_GETCUR
 * \brief Gets the current position in the range of the spinbox.
 *
 * \code
 * SPM_GETCUR
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return The current position in the range of the spinbox.
 */
#define SPM_GETCUR            0xF309

/** @} end of mgext_ctrl_spinbox_msgs */

/**
 * \defgroup mgext_ctrl_spinbox_ncs Notification codes of spinbox control
 * @{
 */

/**
 * \def SPN_REACHMIN
 * \brief Notifies that the spin box has reached the minimum limit.
 */
#define SPN_REACHMIN          1

/**
 * \def SPN_REACHMAX
 * \brief Notifies that the spin box has reached the maximum limit.
 */
#define SPN_REACHMAX          2

/** @} end of mgext_ctrl_spinbox_ncs */

/** @} end of mgext_ctrl_spinbox */

#endif /* _EXT_CTRL_SPINBOX */

/************************** Cool Bar control **********************************/
#ifdef _EXT_CTRL_COOLBAR

/**
 * \defgroup mgext_ctrl_coolbar CoolBar control
 * @{
 */

/**
 * \def CTRL_COOLBAR
 * \brief The class name of coolbar control.
 */
#define CTRL_COOLBAR        ("CoolBar")

#define TYPE_BARITEM        1
#define TYPE_BMPITEM        2
#define TYPE_TEXTITEM       3

/** Structure of the coolbar item info */
typedef struct _COOLBARITEMINFO {
	/** Reserved, do not use. */
	int insPos;

	/**
	 * Identifier of the item. When the user clicked the item, this control
	 * will send a notification message to the parent window
	 * with the notification code to be equal to this identifier.
	 */
	int id;

	/**
	 * Type of the item, can be one of the following values:
	 * - TYPE_BARITEM
	 *   The item is a separator (a vertical line).
	 * - TYPE_BMPITEM
	 *   The item is a bitmap.
	 * - TYPE_TEXTITEM
	 *   The item is text.
	 */
	int ItemType;

	/**
	 * Pointer to the bitmap of the item, valid when the type is TYPE_BMPITEM.
	 */
	PBITMAP Bmp;

	/**
	 * Hint text of the item, will be displayed in the tooltip window.
	 */
	const char *ItemHint;

	/**
	 * Caption of the item, valid when the type is TPYE_TEXTITEM.
	 */
	const char *Caption;

	/** Additional data of the item */
	DWORD dwAddData;
} COOLBARITEMINFO;

/**
 * \var typedef struct COOLBARITEMINFO *PCOOLBARITEMINFO;
 * \brief Data type of the pointer to a COOLBARITEMINFO.
 */
typedef COOLBARITEMINFO *PCOOLBARITEMINFO;

/**
 * \defgroup mgext_ctrl_coolbar_styles Styles of coolbar control
 * @{
 */

/**
 * \def CBS_BMP_16X16
 * \brief The size of the item bitmap is 16x16.
 */
#define CBS_BMP_16X16        0x0000

/**
 * \def CBS_BMP_32X32
 * \brief The size of the item bitmap is 32x32.
 */
#define CBS_BMP_32X32        0x0001

/**
 * \def CBS_BMP_CUSTOM
 * \brief The item bitmap has customized size.
 *
 * \note For the control with this style, you should pass
 *       the width and the height of the item bitmap by
 *       the argument \a dwAddData of \a CreateWindowEx function.
 *
 * \code
 * int item_width = 20;
 * int item_height = 20;
 *
 * CreateWindowEx (CTRL_COOLBAR, ..., MAKELONG (item_width, item_height)));
 * \endcode
 */
#define CBS_BMP_CUSTOM       0x0002

/**
 * \def CBS_USEBKBMP
 * \brief The control has a background bitmap.
 *
 * \note For a CoolBar control with this style, you should pass the bitmap file name
 *       by the argument \a spCaption of \a CreateWindowEx function.
 *
 * \code
 * const char* file_bkgnd = "res/my_bkgnd.gif";
 *
 * CreateWindowEx (CTRL_COOLBAR, file_bkgnd, ...);
 * \endcode
 */
#define CBS_USEBKBMP         0x0004

/** @} end of mgext_ctrl_coolbar_styles */

/**
 * \defgroup mgext_ctrl_coolbar_msgs Messages of coolbar control
 * @{
 */

/**
 * \def CBM_ADDITEM
 * \brief Adds a new item in a coolbar control.
 *
 * \code
 * CBM_ADDITEM
 * COOLBARITEMINFO *newIteminfo;
 *
 * wParam = 0;
 * lParam = (LPARAM)newIteminfo;
 * \endcode
 *
 * \param newIteminfo Pointer to the item info structure of the new item
 *             to be added.
 *
 * \return Zero when success, otherwise less than 0;
 */
#define CBM_ADDITEM          0xFE00

/**
 * \def CBM_ENABLE
 * \brief Sets an item to be enabled or disabled.
 *
 * \code
 * CBM_ENABLE
 * int id;
 * BOOL enabled;
 *
 * wParam = (WPARAM)id;
 * lParam = (LPARAM)enabled;
 * \endcode
 *
 * \param id The identifier of the item to change.
 * \param enabled TRUE to enable the item, FALSE to disable the item.
 *
 * \return Zero when success, otherwise less than 0.
 */
#define CBM_ENABLE           0xFE01

/** @} end of mgext_ctrl_coolbar_msgs */

/** @} end of mgext_ctrl_coolbar */

#endif /* _CTRL_COOLBAR */

/************************** List View control ********************************/
#ifdef _EXT_CTRL_LISTVIEW

/**
 * \defgroup mgext_ctrl_listview ListView control
 * @{
 */

#define CTRL_LISTVIEW       ("ListView")

/** Listview return value */
#define LV_OKAY             0
#define LV_ERR              (-1)
#define LV_ERRSPACE         (-2)

/**
 * Structure of the listview item info, contains information about an item.
 * This structure is used for creating or retrieving an item.
 */
typedef struct _LVITEM {
	/** the rows of the item */
	int nItem;
	/** attached additional data of this item */
	DWORD itemData;
} LVITEM;
typedef LVITEM *PLVITEM;

/** listview icon flags */
#define LVFLAG_BITMAP	    0x0001
#define LVFLAG_ICON	    0x0002

/**
 * Struct of the listview subitem info, contains information about a subitem.
 * This structure is used for creating or retrieving a subitem.
 */
typedef struct _LVSUBITEM {
	/** subitem flags */
	DWORD flags;
	/** the Subitem vertical position(rows) */
	int nItem;
	/** the Subitem horizontal position(columns) */
	int subItem;
	/** text content of this subitem */
	char *pszText;
	/** max text len */
	int nTextMax;
	/** text color of the subitem */
	int nTextColor;
	/** image of the subitem, can be bitmap or icon */
	DWORD image;
} LVSUBITEM;
typedef LVSUBITEM *PLVSUBITEM;

//FIXME
//TODO
/** Contains information for sorting listview */
typedef struct _LVSORTDATA {
	/** Sorting column index */
	int ncol;
	/** low sorted or high sorted */
	int losorted;
} LVSORTDATA;
typedef LVSORTDATA *PLVSORTDATA;

typedef int (*PFNLVCOMPARE)(int nItem1, int nItem2, PLVSORTDATA sortData);


/** Column and header flags */
#define LVCF_LEFTALIGN	       0x0000           // column text left align, default
#define LVCF_RIGHTALIGN	       0x0001           // column text right align
#define LVCF_CENTERALIGN       0x0002           // column text center align

#define LVHF_LEFTALIGN	       0x0000           // header text left align, default
#define LVHF_RIGHTALIGN	       0x0004           // header text right align
#define LVHF_CENTERALIGN       0x0008           // header text center align

/**
 * Struct of the listview column info, contains information about a column.
 * This structure is used for creating or retrieving a column.
 */
typedef struct _LVCOLUMN {
	/** the horizontal position */
	int nCols;
	/** column's width */
	int width;
	/** the title of this column */
	char *pszHeadText;
	/** max text len */
	int nTextMax;
	/** image of the column header, can be bitmap or icon */
	DWORD image;
	/** Comparision function associated with the column */
	PFNLVCOMPARE pfnCompare;
	/** Column and header flags */
	DWORD colFlags;
} LVCOLUMN;
typedef LVCOLUMN *PLVCOLUMN;

/** listview search flags */
#define LVFF_TEXT	   0x0001
#define LVFF_ADDDATA	   0x0002

/** Contains information for finding a certain item info */
typedef struct _LVFINDINFO {
	/**
	 * Type of search to perform.
	 * This member can be set to one or more of the following values:
	 * - LVFF_TEXT
	 *   Searches based on the item(subitems) text.
	 * - LVFF_ADDDATA
	 *   Searches based on the attached additional item data.
	 */
	DWORD flags;
	/** Search index to begin with, 0 from the beginning */
	int iStart;
	/** pszInfo containing nCols columns' text */
	int nCols;
	/** all the subitem's content of this item */
	char **pszInfo;
	/** the additional item data */
	DWORD addData;

	/** The found item's row, reserved */
	int nItem;
	/** The found subitem's column, reserved */
	int nSubitem;

} LVFINDINFO;
typedef LVFINDINFO *PLVFINDINFO;

/** Contains listview general notification information */
typedef struct _LVNM_NORMAL {
	/** wParam parameter of the message */
	WPARAM wParam;
	/** lParam parameter of the message */
	LPARAM lParam;
} LVNM_NORMAL;
typedef LVNM_NORMAL *PLVNM_NORMAL;

/** keydown notification information */
typedef LVNM_NORMAL LVNM_KEYDOWN;
typedef LVNM_KEYDOWN *PLVNM_KEYDOWN;

/** Contains listview notification information when mouse down on the header  */
typedef LVNM_NORMAL LVNM_HEADRDOWN;
typedef LVNM_HEADRDOWN *PLVNM_HEADRDOWN;

/** Contains listview notification information when mouse up on the header  */
typedef LVNM_NORMAL LVNM_HEADRUP;
typedef LVNM_HEADRUP *PLVNM_HEADUP;

/** Contains listview notification information when mouse down on the item area */
typedef LVNM_NORMAL LVNM_ITEMRDOWN;
typedef LVNM_ITEMRDOWN *PLVNM_ITEMRDOWN;

/** Contains listview notification information when mouse up on the item area */
typedef LVNM_NORMAL LVNM_ITEMRUP;
typedef LVNM_ITEMRUP *PLVNM_ITEMRUP;

/**
 * \defgroup mgext_ctrl_listview_styles Styles of listview control
 * @{
 */

/**
 * \def LVS_NOTIFY
 * \brief Notifies the parent window.
 *
 * Causes the listview to notify the listview parent window
 * with a notification message when the user make actions, such as clicks, doubleclicks, ...,etc.
 */
#define LVS_NOTIFY                  0x0001L

/**
 * \def LVS_SORT
 * \brief Sorts strings automatically.
 *
 * Causes the listview to sort strings automatically.
 */
#define LVS_SORT                    0x0002L

/**
 * \def LVS_MULTIPLESEL
 * \brief Causes the listview to allow the user to select multiple items.
 */
#define LVS_MULTIPLESEL             0x0008L              //reserved

/**
 * \def LVS_CHECKBOX
 * \brief Displays a check box in an item.
 */
#define LVS_CHECKBOX                0x1000L              //reserved

/**
 * \def LVS_AUTOCHECK
 * \brief If the list box has LVS_CHECKBOX style, this
 *        style tell the box to auto-switch the check box between
 *        checked or un-checked when the user click the check mark box of an item.
 */
#define LVS_AUTOCHECK               0x2000L              //reserved

#define LVS_AUTOCHECKBOX            (LVS_CHECKBOX | LVS_AUTOCHECK)    //reserved


/** @} end of mgext_ctrl_listview_styles */

/**
 * \defgroup mgext_ctrl_listview_msgs Messages of ListView control
 * @{
 */

/**
 *  \def LVM_ADDITEM
 *  \brief Adds a item to listview, this item is also called a row.
 *
 *  \code
 *  LVM_ADDITEM
 *  PLVITEM p;
 *
 *  wParam = 0;
 *  lParam =(LPARAM)p;
 *  \endcode
 *
 *  \param p Pointes to a LVITEM structure that contains the information of
 *           the new item to be added.
 *  \return Returns the index of the new item if successful, or -1 otherwise.
 */
#define LVM_ADDITEM                 0xF110

/**
 * \def LVM_FILLSUBITEM
 * \brief Sets the content of a subitem, indentified by rows and columns.
 *
 * \code
 * LVM_FILLSUBITEM
 * PLVSUBITEM p;
 *
 * lParam = (LPARAM)p;
 * wParam = 0;
 * \endcode
 *
 * \param p the Pointer of the subitem to be added.
 * \return Returns LV_OKAY if successful, or LV_ERR otherwise.
 */
#define LVM_FILLSUBITEM             0xF111

/**
 * \def LVM_ADDCOLUMN
 * \brief Adds a new column to listview, indentified by column.
 *
 * \code
 *  LVM_ADDCOLUMN
 *  PLVCOLUMN p;
 *
 *  wParam = 0;
 *  lParam =(LPARAM)p;
 * \endcode
 *
 * \param p Pointes to a LVCOLUMN structure that contains the information about the new
 *          column to be added.
 */
#define LVM_ADDCOLUMN               0xF112

/**
 * \def LVM_DELITEM
 * \brief Deletes an item form listview, also called a row.
 *
 * \code
 * LVM_DELITEM
 * int nRow;
 *
 * wParam = (WPARAM)nRow;
 * lParam = 0;
 * \endcode
 *
 * \param nRow the index of the item to be removed.
 * \return Returns LV_OKAY if successful, or LV_ERR otherwise.
 */
#define LVM_DELITEM                 0xF113

/**
 * \def LVM_CLEARSUBITEM
 * \brief Clears the content of a subitem, indentified by rows and columns.
 *
 * \code
 * LVM_CLEARSUBITEM
 * PLVSUBITEM p
 *
 * lParam = (LPARAM)p;
 * wParam = 0;
 * \endcode
 *
 * \param p the Pointer of the subitem.
 * \return Returns LV_OKAY if successful, or LV_ERR otherwise.
 */
#define LVM_CLEARSUBITEM            0xF114

/**
 * \def LVM_DELCOLUMN
 * \brief Deletes a column from listview, all subitem in this column will be removed.
 *
 * \code
 * LVM_DELCOLUMN
 * int nCols;
 *
 * wParam = (WPARAM)nCol;
 * lParam = 0;
 * \endcode
 *
 * \param nCol the index of the column to be removed.
 * \return Returns LV_OKAY if successful, or LV_ERR otherwise.
 */
#define LVM_DELCOLUMN               0xF115

/**
 * \def LVM_COLSORT
 * \brief Sorts all subitems according to a certain column.
 *
 * \code
 * LVM_COLSORT
 * int ncol;
 *
 * wParam = (WPARAM)ncol;
 * lParam = 0;
 * \endcode
 *
 * \param ncol Index of the column.
 * \return Returns LV_OKAY if successful, or LV_ERR otherwise.
 */
#define LVM_COLSORT                 0xF116

/**
 * \def LVM_SETSUBITEMCOLOR
 * \brief Sets the text color of a subitem.
 *
 * \code
 * LVM_SETSUBITEMCOLOR
 * PLVSUBITEM psub;
 *
 * lParam = (LPARAM)psub;
 * \endcode
 *
 * \param psub constains the information of the subitem to set.
 * \return Always returns 0;
 */
#define LVM_SETSUBITEMCOLOR         0xF117

/**
 * \def LVM_FINDITEM
 *
 * \code
 * LVM_FINDITEM
 * PLVFINDINFO plvfi;
 *
 * wParam = 0;
 * lParam = (LPARAM)plvfi;
 * \endcode
 *
 * \param plvfi Points to a LVFINDINFO structure containing information for searching.
 *
 * \return Returns the index of the found item if successful, or -1 otherwise.
 */
#define LVM_FINDITEM                0xF118

/**
 *
 * \def LVM_GETSUBITEMTEXT
 * \brief Retrieves the text of a listview subitem.
 *
 * \code
 * LVM_GETSUBITEMTEXT
 * PLVSUBITEM p;
 *
 * wParam = 0;
 * lParam = (LPARAM)p;
 * \endcode
 *
 * \param p Points to a LVSUBITEM structure.
 *
 * \return Returns len of the text if successful, -1 otherwise.
 */

#define LVM_GETSUBITEMTEXT          0xF119

/**
 * \def LVM_GETITEMCOUNT
 * \brief Gets the number of all the items(rows) in a listview.
 *
 * \code
 * LVM_GETITEMCOUNT
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return The number of the items.
 */
#define LVM_GETITEMCOUNT            0xF11A

/**
 * \def LVM_GETCOLUMNCOUNT
 * \brief Gets the number of all the columns in listview.
 *
 * \code
 * LVM_GETCOLUMNCOUNT
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return the number of all the columns in listview.
 */
#define LVM_GETCOLUMNCOUNT          0xF11B

/**
 * \def LVM_GETSELECTEDITEM
 * \brief Gets the current selected item. This message is a internal message of listview.
 *
 * \code
 * LVM_GETSELECTEDITEM
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return the current selected item.
 */
#define LVM_GETSELECTEDITEM         0xF11C

/**
 * \def LVM_DELALLITEM
 * \brief Removes all the items in listview.
 *
 * \code
 * LVM_DEALLITEM
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return Returns TRUE if successful, or FALSE otherwise.
 */
#define LVM_DELALLITEM              0xF11D

/**
 * \def LVM_MODIFYHEAD
 * \brief Changes the title of a column.
 *
 * \code
 * LVM_MODIFYHEAD
 * PLVCOLUMN pcol;
 *
 * wParam = 0;
 * lParam = (LPARAM)pcol;
 * \endcode
 *
 * \param pcol Pointer to a LVCOLUMN struct.
 * \return Returns LV_OKAY if successfull, or LV_ERR otherwise.
 */
#define LVM_MODIFYHEAD              0xF11E

/**
 * \def LVM_SELECTITEM
 * \brief Selects an item.
 *
 * \code
 * LVM_SELECTITEM
 * int nItem;
 *
 * wParam = (WPARAM)nItem;
 * lParam = 0;
 * \endcode
 *
 * \param nItem Index of the item to select.
 * \return Always returns 0.
 */
#define LVM_SELECTITEM		    0xF11F


/**
 * \def LVM_SHOWITEM
 * \brief Makes the item is entirely visible in the list view.
 *
 * \code
 * LVM_SHOWITEM
 * int nRow;
 *
 * wParam = (WPARAM)nRow;
 * lParam = 0;
 * \endcode
 *
 * \param nRow Index of the item to show.
 * \return Always returns 0.
 */
#define LVM_SHOWITEM		    0xF120

/**
 * \def LVM_GETSUBITEMLEN
 * \brief Gets the text len of the subitem.
 *
 * \code
 * LVM_GETSUBITEMLEN
 * PLVSUBITEM psub;
 *
 * wParam = 0;
 * lParam = (LPARAM)psub;
 * \endcode
 *
 * \param psub Pointer to a LVSUBITEM struct containing subitem information.
 * \return Returns the text len if successful, or LV_ERR otherwise.
 */
#define LVM_GETSUBITEMLEN	    0xF121

/**
 * \def LVM_SETCOLUMN
 * \brief Sets the attributes of a listview column.
 *
 * \code
 * LVM_SETCOLUMN
 * PLVCOLUMN pcol;
 *
 * wParam = 0;
 * lParam = (LPARAM)pcol;
 * \endcode
 *
 * \param pcol Points to a LVCOLUMN structure containing the new column information.
 *
 * \return Returns LV_OKAY if successful, or LV_ERR otherwise.
 */
#define LVM_SETCOLUMN		    0xF122

/**
 * \def LVM_SETSUBITEMTEXT
 * \brief Sets the text of a subitem.
 *
 * \code
 * LVM_SETSUBITEMTEXT
 * PLVSUBITEM psub;
 *
 * wParam = 0;
 * lParam = (LPARAM)psub;
 * \endcode
 *
 * \param psub constains the information of the subitem to set.
 * \return Returns LV_OKAY if successful, or LV_ERR otherwise.
 */
#define LVM_SETSUBITEMTEXT	    0xF123

/**
 * \def LVM_SETSUBITEM
 * \brief Sets the attributes of a subitem.
 *
 * \code
 * LVM_SETSUBITEM
 * PLVSUBITEM psub;
 *
 * wParam = 0;
 * lParam = (LPARAM)psub;
 * \endcode
 *
 * \param psub constains the information of the subitem to set.
 * \return Returns LV_OKAY if successful, or LV_ERR otherwise.
 */
#define LVM_SETSUBITEM		    0xF124

/**
 * \def LVM_GETCOLUMN
 * \brief Retrieves the information about a listview column.
 *
 * \code
 * LVM_GETCOLUMN
 * int nCol;
 * PLVCOLUMN pcol;
 *
 * wParam = (WPARAM)nCol;
 * lParam = (LPARAM)pcol;
 * \endcode
 *
 * \param nCol Index of the column.
 * \param pcol Points to a LVCOLUMN structure for retrieving the information
 *             about the column.
 *
 * \return Returns TRUE if successful, or FALSE otherwise.
 */
#define LVM_GETCOLUMN		    0xF125

/**
 * \def LVM_GETCOLUMNWIDTH
 * \brief Retrieves the width of a listview column.
 *
 * \code
 * LVM_GETCOLUMNWIDTH
 * int nCol;
 *
 * wParam = (WPARAM)nCol;
 * lParam = (LPARAM)0;
 * \endcode
 *
 * \param nCol Index of the column.
 *
 * \return Returns the column width if successful, or -1 otherwise.
 */
#define LVM_GETCOLUMNWIDTH	    0xF126

/**
 * \def LVM_GETITEM
 * \brief Retrieves the item's attributes.
 *
 * \code
 * LVM_GETITEM
 * PLVITEM pitem;
 *
 * wParam = 0;
 * lParam = (LPARAM)pitem;
 * \endcode
 *
 * \param pitem Points to an LVITEM structure for retrieving the information
 *              about an item, the nItem field identifies the item.
 *
 * \return Returns LV_OKAY if successful, or LV_ERR otherwise.
 */
#define LVM_GETITEM		    0xF127

/**
 * \def LVM_GETITEMSTATE
 * \brief Retrieves the state of a listview item.
 *
 * \code
 * LVM_GETITEMSTATE
 * int nRow;
 * UINT mask;
 *
 * wParam = (WPARAM)nRow;
 * lParam = (LPARAM)mask;
 * \endcode
 *
 * \param nRow Index of the item.
 * \param mask Contains state information to retrieve, can be the combination
 *             of the following values.
 *
 * \return Returns the current state of the specified item.
 */
#define LVM_GETITEMSTATE	    0xF128

/**
 * \def LVM_GETSELECTEDCOLUMN
 * \brief Retrieves the index of the currently selected column of a listview.
 *
 * \code
 * LVM_GETSELECTEDCOLUMN
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return Returns the index of the selected column.
 */
#define LVM_GETSELECTEDCOLUMN	    0xF129

/**
 * \def LVM_GETSELECTEDCOUNT
 * \brief Retrieves the number of the selected items in a listview.
 *
 * \code
 * LVM_GETSELECTEDCOUNT
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return Returns the number of the selected items.
 */
#define LVM_GETSELECTEDCOUNT	    0xF130

/**
 * \def LVM_GETTOPVISIBLE
 * \brief Retrieves the index of the topmost visible item in a listview.
 *
 * \code
 * LVM_GETTOPVISIBLE
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return Returns the index of the topmost visible item if successful, or zero.
 */
#define LVM_GETTOPVISIBLE	    0xF131

#define LVM_NULL		    0xF132

#define LVM_SETITEMSTATE	    0xF133

/**
 * \def LVM_SORTITEMS
 * \brief Uses an application-defined comparision function to sort the items.
 *
 * \code
 * LVM_SORTITEMS
 * PLVSORTDATA sortData;
 * PFNLVCOMPARE pfnCompare;
 *
 * wParam = (WPARAM)sortData;
 * lParam = (LPARAM)pfnCompare;
 * \endcode
 *
 * \param sortData Sorting datas passed to the comparision function.
 * \param pfnCompare Pointer to the application-defined comparision function. The
 *                   comparision function is called during the sort operation
 *                   each time the relative order of the two items needs to be
 *                   compared.
 *
 *                   The comparison function must return a negative value if the
 *                   first item precedes the second, a positive value if
 *                   the first item follows the second, or zero if the two
 *                   items are equivalent.
 *
 *                   The comparision function has the following form:
 *
 *                   int CompareFunction(int nItem1, int nItem2, PLVSORTDATA sortData);
 *
 *                   nItem1 is the index of the first item, nItem2 is the index
 *                   of the second item, and sortData is passed to CompareFunction
 *                   as the third parameter.
 *
 * \return Returns TRUE if successful, or FALSE otherwise.
 */
#define LVM_SORTITEMS		    0xF134

/**
 * \def LVM_SETITEMHEIGHT
 * \brief Changes the height of all the items.
 *
 * \code
 * LVM_SETITEMHEIGHT
 * int height;
 *
 * wParam = (WPARAM)height;
 * lParam = 0;
 * \endcode
 *
 * \param height The new height of the item.
 * \return Returns TRUE if successful, or FALSE otherwise.
 */
#define LVM_SETITEMHEIGHT	    0xF135

/**
 * \def LVM_SETHEADHEIGHT
 * \brief Changes the height of the header.
 *
 * \code
 * LVM_SETHEADHEIGHT
 * int height;
 *
 * wParam = (WPARAM)height;
 * lParam = 0;
 * \endcode
 *
 * \param height The new height of the header.
 * \return Returns TRUE if successful, or FALSE otherwise.
 */
#define LVM_SETHEADHEIGHT	    0xF136

/**
 * \def LVM_GETITEMADDDATA
 * \brief Gets the 32-bit data value associated with an item.
 *
 * An application sends an LVM_GETITEMADDDATA message to a listview to get the
 * 32-bit data value stored for the item with index of \a wParam;
 * By default this is zero. An application must set the
 * item data value by sending an LVM_SETITEMADDDATA message to the listview for
 * this value to have meaning.
 *
 * \code
 * LVM_GETITEMADDDATA
 * int index;
 *
 * wParam = (WPARAM)index;
 * lParam = 0;
 * \endcode
 *
 * \param index The index of the specified item.
 *
 * \return The 32-bit data value associated with an item on success, otherwise
 *         -1 to indicate an error.
 */
#define LVM_GETITEMADDDATA          0xF137

/**
 * \def LVM_SETITEMADDDATA
 * \brief Associates a 32-bit data value with an item.
 *
 * An application sends an LVM_SETITEMADDDATA message to associate a 32-bit data
 * value specified in the \a lParam parameter with an item in the listview.
 *
 * \code
 * LVM_SETITEMADDDATA
 * int index;
 * DWORD addData;
 *
 * wParam = (WPARAM)index;
 * lParam = (LPARAM)addData;
 * \endcode
 *
 * \param index The index of the specified item.
 * \param addData the 32-bit data value which will associated with the item.
 *
 * \return One of the following values:
 *          - LV_OKAY\n         Success
 *          - LV_ERR\n          Invalid item index
 *
 */
#define LVM_SETITEMADDDATA          0xF138

/**
 * \def LVM_CHOOSEITEM
 * \Selects and shows an item.
 *
 * \code
 * LVM_CHOOSEITEM
 * int nItem;
 *
 * wParam = (WPARAM)Item;
 * lParam = 0;
 * \endcode
 *
 * \param nItem Index of the item to choose.
 * \return Always returns 0.
 */
#define LVM_CHOOSEITEM		    0xF139

/**
 * \def LVM_SETSTRCMPFUNC
 * \brief Sets the STRCMP function used to sort items.
 *
 * An application sends a LVM_SETSTRCMPFUNC message to set a
 * new STRCMP function to sort items in the Listview control.
 *
 * Note that you should send this message before adding
 * any item to the Listview control.
 *
 * \code
 * static int my_strcmp (const char* s1, const char* s2, size_t n)
 * {
 *      ...
 *      return 0;
 * }
 *
 * LVM_SETSTRCMPFUNC
 *
 * wParam = 0;
 * lParam = (LPARAM) my_strcmp;
 * \endcode
 *
 * \param my_strcmp Your own function to compare two strings.
 *
 * \return One of the following values:
 *          - 0\n     Success
 *          - -1\n    Not an empty TreeView control
 */
#define LVM_SETSTRCMPFUNC           0xF140

/** @} end of mgext_ctrl_listview_msgs */

/**
 * \defgroup mgext_ctrl_listview_ncs Notification code of ListView control
 * @{
 */

/**
 * \def LVN_ITEMRDOWN
 * \brief This notification code informs parent window the right mouse button down
 *        on a listview item.
 */
#define LVN_ITEMRDOWN               4

/**
 * \def LVN_ITEMRUP
 * \brief This notification code informs parent window the right mouse button up
 *        on a listview item.
 */
#define LVN_ITEMRUP                 5

/**
 * \def LVN_HEADRDOWN
 * \brief This notification code informs parent window the right mouse button down
 *        on the listview header.
 */
#define LVN_HEADRDOWN               6

/**
 * \def LVN_HEADRUP
 * \brief This notification code informs parent window the right mouse button up
 *        on the listview header.
 */
#define LVN_HEADRUP                 7

/**
 * \def LVN_KEYDOWN
 * \brief This notification code informs parent window that a key has been pressed.
 */
#define LVN_KEYDOWN                 8

/**
 *
 * \def LVN_ITEMDBCLK
 * \brief This notification code informs parent window the current selected item
 *        has be double clicked.
 */
#define LVN_ITEMDBCLK               9

/**
 * \def LVN_ITEMCLK
 * \brief This notification code informs parent window the current selected item
 *        has been clicked.
 */
#define LVN_ITEMCLK                 10

/**
 * \def LVN_SELCHANGE
 * \brief This notification code informs parent window the current selected item
 *        has changed.
 */
#define LVN_SELCHANGE               11

/**
 * \def LVN_COLCHANGE
 * \brief This notification code informs parent window the current selected column
 *        has changed.
 */
#define LVN_COLCHANGE               12


/** @} end of mgext_ctrl_listview_ncs */

/** @} end of mgext_ctrl_listview */

#endif  /* _EXT_CTRL_LISTVIEW */


#ifdef _EXT_CTRL_GRID

/**
 * \defgroup mgext_ctrl_grid Grid control
 * @{
 */

#define CTRL_GRID                ("Grid")

/** Grid return value */
#define GRID_OKAY                0
#define GRID_ERR                 (-1)
#define GRID_ERRSPACE            (-2)

/** Column and header flags */
#define GRIDCF_LEFTALIGN         0x0000         // column text left align, default
#define GRIDCF_RIGHTALIGN        0x0001         // column text right align
#define GRIDCF_CENTERALIGN       0x0002         // column text center align

#define GRIDHF_LEFTALIGN         0x0000         // header text left align, default
#define GRIDHF_RIGHTALIGN        0x0004         // header text right align
#define GRIDHF_CENTERALIGN       0x0008         // header text center align

#define GRID_COL_PRIORTY         0x0010


/**
 * Structure of the grid column header info, contains column header informations.
 * This structure is used for creating or retrieving column header.
 */
typedef struct _GRIDCOLHEADER {
	/** Width of the header*/
	int nWidth;
	/** The column number */
	int nCols;
	/** The title of this column */
	char *pTitle;
	/** Image of the header */
	DWORD image;
	/** Header flags */
	DWORD flags;
	/** Cell infomations */
	DWORD cellflags;
} GRIDCOLHEADER;
typedef GRIDCOLHEADER *PGRIDCOLHEADER;

/**
 * Structure of the grid row header info, contains row header informations.
 * This structure is used for creating or retrieving row header.
 */
typedef struct _GRIDROWHEADER {
	/** Height of the header*/
	int nHeight;
	/** The row number */
	int nRows;
	/** The title of this row*/
	char *pTitle;
	/** Image of the header */
	DWORD image;
	/** Header flags */
	DWORD flags;
	/** Cell infomations*/
	DWORD cellflags;
} GRIDROWHEADER;
typedef GRIDROWHEADER *PGRIDROWHEADER;

/**
 * Structure of cell, contains text info.
 * Use this structure when set a certain cell.
 */
typedef struct _GRIDCELL {
	/** Text in cell */
	char *pszInfo;
	/** Text color */
	int nTextColor;
	/** Additional data */
	DWORD addData;
} GRIDCELL;
typedef GRIDCELL *PGRIDCELL;

#define GRIDM_GETGRIDCOLS         0xF210
#define GRIDM_SETGRIDCOLS         0xF211
#define GRIDM_GETGRIDROWS         0xF212
#define GRIDM_SETGRIDROWS         0xF213

#define GRIDM_ADDCOL              0xF214
#define GRIDM_DELCOL              0xF215
#define GRIDM_ADDROW              0xF216
#define GRIDM_DELROW              0xF217

#define GRIDM_SETHEADHEIGHT       0xF218
#define GRIDM_SETHEADWIDTH        0xF219
#define GRIDM_GETHEADWIDTH        0xF21A
#define GRIDM_GETHEADHEIGHT       0xF21B

#define GRIDM_SETCOLDATA          0xF21C
#define GRIDM_GETCOLDATA          0xF21D
#define GRIDM_SETROWDATA          0xF21E
#define GRIDM_GETROWDATA          0xF21F
#define GRIDM_SETCOLWIDTH         0xF220
#define GRIDM_GETCOLWIDTH         0xF221
#define GRIDM_SETROWHEIGHT        0xF222
#define GRIDM_GETROWHEIGHT        0xF223

#define GRIDM_SETCELLDATA         0xF224
#define GRIDM_GETCELLDATA         0xF225
#define GRIDM_SETCELLFOCUS        0xF226
#define GRIDM_SETCELLEDIT         0xF227 //not implement

/** @} end of mgext_ctrl_grid_ncs */

/** @} end of mgext_ctrl_grid */
#endif


/** @} end of mgext_controls */

/** @} end of mgext_fns */

#ifdef  __cplusplus
}
#endif

#endif /* MGEXT_H */
