// GLFW-based OpenGL Window header

#ifndef FW_GLFW_GL_WINDOW_H
#define FW_GLFW_GL_WINDOW_H

#include "FWWindow.h"

// Forward declaration
struct GLFWwindow;

//-----------------------------------------------------------------------------
// FWGLFWGLWindow - GLFW-based OpenGL window implementation
//-----------------------------------------------------------------------------
class FWGLFWGLWindow : public FWWindow
{
public:
	FWGLFWGLWindow(int argc, char **ppArgv, const FWDisplayInfo &dispInfo, const FWStartupInfo &startupInfo);
	virtual ~FWGLFWGLWindow();

	bool update();
	virtual void destroy();
	virtual void flip();
	virtual void setRenderingContext();
	virtual void clearRenderingContext();
	virtual FWDisplayInfo &getDisplayInfo() { return mDispInfo; }
	virtual void *getWindowSystemContext() { return mpWindow; }
	
	void* getWindowHandle();

protected:
	GLFWwindow* mpWindow;
	FWDisplayInfo mDispInfo;
};

#endif // FW_GLFW_GL_WINDOW_H
