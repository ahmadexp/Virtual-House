
#ifndef __FW_DEBUG_H__
#define __FW_DEBUG_H__

#include <assert.h>
#ifdef _DEBUG
#define FWASSERT(x) assert(x)
#define FWWARNING(string) do { fprintf(stderr, "%s(%d): %s\n", __FILE__, __LINE__, string); } while(0)
#else
#define FWASSERT(x)
#define FWWARNING(string)
#endif

#endif//__FW_DEBUG_H__
