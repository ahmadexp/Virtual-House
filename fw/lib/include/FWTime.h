#ifndef __FW_TIME_H__
#define __FW_TIME_H__

#ifdef _WIN32
#include "win32/FWWin32Time.h"
#endif//_MSC_VER

#ifdef __linux__
#include "linux/FWLinuxTime.h"
#endif//__linux__

#ifdef __CELLOS_LV2__
#include "cell/FWCellTime.h"
#endif//__CELLOS_LV2__

#endif//__FW_TIME_H__
