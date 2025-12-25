
#ifndef __FW_WIN32GLINCLUDE_H__
#define __FW_WIN32GLINCLUDE_H__

// OpenGL & Cg includes
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <Cg/cgGL.h>

// OGL extensions supported by PSGL, but not by OGL 1.1
#include "FWGLExtensions.h"

// PSGL defines some functions differently, so map those to standard OpenGL
#define glClearDepthf	glClearDepth
#define gluPerspectivef	gluPerspective
#define gluOrtho2Df		gluOrtho2D
#define gluLookAtf		gluLookAt

// GL get proc function
#define FW_GETGLPROC	wglGetProcAddress

#endif//__FW_WIN32GLINCLUDE_H__
