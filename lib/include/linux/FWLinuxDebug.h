
#ifndef __FW_LINUXDEBUG_H__
#define __FW_LINUXDEBUG_H__

#include "FWDebugConsole.h"

// if debugging enabled
#ifdef _DEBUG

#include <assert.h>

// preprocessor macros to turn the numeric value of __LINE__ into string form
#define _VAL(x)	#x
#define _STRIZE(x)	_VAL(x)

// FWASSERT macro
#define FWASSERT(x) assert(x)

// FWWARNING() macro
// takes a literal string and outputs a message including the file and line number the macro was used
#define FWWARNING(string)																					\
							do																				\
							{																				\
								fprintf(stderr, __FILE__ "(" _STRIZE(__LINE__) ") : " string "\n");			\
								FWDebugConsole::print(__FILE__ "(" _STRIZE(__LINE__) ") : " string "\n");	\
							} while(0)

#else

// discard FWASSERT()
#define FWASSERT(x) ((void)0)

// discard FWWARNING()
#define FWWARNING(string) ((void)0)

#endif //_DEBUG

#define LITTLE_SHORT(x) (x)
#define LITTLE_INT(x)	(x)
#define BIG_SHORT(x)	(((x & 0xff) << 8) | ((x & 0xff00) >> 8))
#define BIG_INT(x)		(((x & 0xff) << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | ((x & 0xff000000) >> 24))

#endif//__FW_LINUXDEBUG_H__
