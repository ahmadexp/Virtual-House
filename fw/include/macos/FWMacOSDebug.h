
#ifndef __FW_MACOSDEBUG_H__
#define __FW_MACOSDEBUG_H__

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
#define FWWARNING(x) ((void)0)

#endif//_DEBUG

#endif//__FW_MACOSDEBUG_H__
