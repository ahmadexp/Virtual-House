
#ifndef __FW_MACOSGLINCLUDE_H__
#define __FW_MACOSGLINCLUDE_H__

// OpenGL includes for macOS
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

// OGL extensions supported by PSGL, but not by OGL 1.1
#include "psgl/FWGLExtensions.h"

// PSGL defines some functions differently, so map those to standard OpenGL
#define glClearDepthf	glClearDepth
#define gluPerspectivef gluPerspective
#define gluOrtho2Df		gluOrtho2D
#define gluLookAtf		gluLookAt

// GL get proc function - macOS doesn't use glXGetProcAddress
#define FW_GETGLPROC(x)	NULL

#endif//__FW_MACOSGLINCLUDE_H__
