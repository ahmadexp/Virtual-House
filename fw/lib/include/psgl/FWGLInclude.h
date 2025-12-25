
#ifndef __FW_GLINCLUDE_H__
#define __FW_GLINCLUDE_H__

// stop some gl.h's including glext.h
#define GL_GLEXT_LEGACY

// OGL on win32
#if defined(_WIN32) && !defined(PSGL)
#include "win32/FWWin32GLInclude.h"
#endif//defined(_WIN32) && !defined(PSGL)

// OGL on linux
#if defined(__linux__) && !defined(PSGL)
#include "linux/FWLinuxGLInclude.h"
#endif//defined(__linux__) && !defined(PSGL)

// PSGL (Cell only at present)
#ifdef PSGL
#include "FWPSGLInclude.h"
#endif//PSGL

#endif//__FW_GLINCLUDE_H__
