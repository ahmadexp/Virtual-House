
#ifndef __FW_DEBUG_H__
#define __FW_DEBUG_H__

#ifdef _WIN32
#include "win32/FWWin32Debug.h"
#endif

#ifdef __linux__
#include "linux/FWLinuxDebug.h"
#endif//__linux__

#ifdef __APPLE__
#include "macos/FWMacOSDebug.h"
#endif//__APPLE__

#ifdef __CELLOS_LV2__
#include "cell/FWCellDebug.h"
#endif//__CELLOS_LV2__

#endif//__FW_DEBUG_H__
