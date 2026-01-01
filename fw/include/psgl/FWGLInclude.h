
#ifndef __FW_GLINCLUDE_H__
#define __FW_GLINCLUDE_H__

// stop some gl.h's including glext.h
#define GL_GLEXT_LEGACY

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <GLFW/glfw3.h>
#include "psgl/FWGLExtensions.h"
#define glClearDepthf glClearDepth
#define gluPerspectivef gluPerspective
#define gluOrtho2Df gluOrtho2D
#define gluLookAtf gluLookAt
#define FW_GETGLPROC(x) glfwGetProcAddress(x)

#endif//__FW_GLINCLUDE_H__
