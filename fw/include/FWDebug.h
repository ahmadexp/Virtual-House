
#ifndef __FW_DEBUG_H__
#define __FW_DEBUG_H__

// Use generic debug implementation for Windows, Linux
#if defined(_WIN32) || defined(__linux__)
#include <assert.h>
#ifdef _DEBUG
#define FWASSERT(x) assert(x)
#define FWWARNING(string) do { fprintf(stderr, "%s(%d): %s\n", __FILE__, __LINE__, string); } while(0)
#else
#define FWASSERT(x)
#define FWWARNING(string)
#endif
#endif // _WIN32 || __linux__

#ifdef __APPLE__
#include "macos/FWMacOSDebug.h"
#endif//__APPLE__

#ifdef __CELLOS_LV2__
#include "cell/FWCellDebug.h"
#endif//__CELLOS_LV2__

#endif//__FW_DEBUG_H__
