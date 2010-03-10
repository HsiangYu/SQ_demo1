#ifndef _MINI133_H
#define _MINI133_H

#include "lang.h"

#define DEB //printf


#define MAX_FILE_LIST  40



extern int loadbk(HWND);

#if 0
#include <minigui/mgext.h>
#else

/**
 * \defgroup ctrl_scrollview_styles Styles of scrollview control
 * @{
 */

#define SVS_NOTIFY         0x0001L
#define SVS_UPNOTIFY       0x0002L
#define SVS_AUTOSORT       0x0004L
#define SVS_LOOP           0x0008L


/**
 * \defgroup mgext_ctrl_monthcal_styles Styles of monthcalendar control
 * @{
 */

/**
 * \def MCS_CHN
 * \brief Displays chinese label.
 */
#define MCS_CHN            0x0001L

/**
 * \def MCS_ENG_L
 * \brief Displays long english label.
 */
#define MCS_ENG_L          0x0002L

/**
 * \def MCS_ENG_S
 * \brief Displays short english label.
 */
#define MCS_ENG_S          0x0003L

/**
 * \def MCS_NOTIFY
 * \brief Notifies the parent window when something happens.
 */
#define MCS_NOTIFY         0x0004L

/** @} end of mgext_ctrl_monthcal_styles */




/**
 * \var typedef unsigned long DWORD
 * \brief A type definition for unsigned long integer (double word).
 */
//typedef unsigned long   DWORD;



//struct _BITMAP;
//typedef struct _BITMAP BITMAP;
//typedef BITMAP* PBITMAP;


/**
 * \def CBS_BMP_16X16
 * \brief The size of the item bitmap is 16x16.
 */
#define CBS_BMP_16X16        0x0000

/**
 * \def CTRL_COOLBAR
 * \brief The class name of coolbar control.
 */
#define CTRL_COOLBAR         ("CoolBar")

#define TYPE_BARITEM         1
#define TYPE_BMPITEM         2
#define TYPE_TEXTITEM        3


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
 * \def MCS_CHN
 * \brief Displays chinese label.
 */
#define MCS_CHN              0x0001L

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
#define MCM_GETCURDATE       0xF310




#endif

#endif /* _MIMI133_H */
