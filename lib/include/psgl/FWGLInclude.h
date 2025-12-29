
#ifndef __FW_GLINCLUDE_H__
#define __FW_GLINCLUDE_H__

// stop some gl.h's including glext.h
#define GL_GLEXT_LEGACY

// OGL on win32
#if defined(_WIN32) && !defined(PSGL)
#include "win32/FWWin32GLInclude.h"
#endif//defined(_WIN32) && !defined(PSGL)

// OGL on linux - use GLFW
#if defined(__linux__) && !defined(PSGL)
#include <GL/gl.h>
#include <GLFW/glfw3.h>
void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
void gluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top);
GLint gluBuild2DMipmaps(GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *data);
#include <Cg/cgGL.h>
#include "psgl/FWGLExtensions.h"
#define glClearDepthf glClearDepth
#define gluPerspectivef gluPerspective
#define gluOrtho2Df gluOrtho2D
#define gluLookAtf gluLookAt
#define FW_GETGLPROC(x) glfwGetProcAddress(x)
#endif//defined(__linux__) && !defined(PSGL)

// PSGL (Cell only at present)
#ifdef PSGL
#include "FWPSGLInclude.h"
#endif//PSGL

#endif//__FW_GLINCLUDE_H__
