
#ifndef __FW_DEBUG_H__
#define __FW_DEBUG_H__

#ifdef _WIN32
#include "win32/FWWin32Debug.h"
#endif

#ifdef __linux__
// Use generic debug implementation
#include <assert.h>
#ifdef _DEBUG
#define FWASSERT(x) assert(x)
#define FWWARNING(string) do { fprintf(stderr, "%s(%d): %s\n", __FILE__, __LINE__, string); } while(0)
#else
#define FWASSERT(x)
#define FWWARNING(string)
#endif
#endif//__linux__

#ifdef __CELLOS_LV2__
#include "cell/FWCellDebug.h"
#endif//__CELLOS_LV2__

#endif//__FW_DEBUG_H__
