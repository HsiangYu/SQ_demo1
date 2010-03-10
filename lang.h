
#ifndef _LANG_H_
#define _LANG_H_

#define LANG_EN 1
#define LANG_CN  2
#define LANG_TW  3

#define LANG LANG_EN

#if (LANG == LANG_EN )
#include "lang_en.h"
#elif (LANG == LANG_TW)
#include "lang_tw.h"
#elif (LANG == LANG_CN)
#include "lang_cn.h"
#endif


#endif /* _LANG_H_ */

