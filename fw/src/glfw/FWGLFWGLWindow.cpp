// GLFW-based OpenGL Window implementation for macOS/Linux/Windows
// Uses pure C GLFW library instead of platform-specific code

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _WIN32
#include <unistd.h>
#endif
#include "FWDebug.h"
#include "glfw/FWGLFWGLWindow.h"
#include "FWApplication.h"
#include "FWInput.h"
#include "FWTime.h"

// GLFW error callback
static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

// GLFW window resize callback
static void glfw_resize_callback(GLFWwindow* window, int width, int height)
{
	FWGLFWGLWindow* pWindow = (FWGLFWGLWindow*)glfwGetWindowUserPointer(window);
	if (pWindow) {
		pWindow->resize(width, height);
	} else {
		if (height == 0) height = 1;
		glViewport(0, 0, width, height);
	}
}

// GLFW key callback for basic input
static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// ESC to quit
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
FWGLFWGLWindow::FWGLFWGLWindow(int argc, char **ppArgv, const FWDisplayInfo &dispInfo, const FWStartupInfo &startupInfo)
	: FWWindow(argc, ppArgv, dispInfo, startupInfo)
	, mpWindow(NULL)
{
	printf("DEBUG: FWGLFWGLWindow constructor starting\n");
	fflush(stdout);
	
	// Initialize GLFW
	glfwSetErrorCallback(glfw_error_callback);
	
	printf("DEBUG: Calling glfwInit()\n");
	fflush(stdout);
	
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		fflush(stderr);
		exit(EXIT_FAILURE);
	}
	
	printf("DEBUG: GLFW initialized successfully\n");
	fflush(stdout);

	// Configure OpenGL context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_STENCIL_BITS, 8);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	
	// Antialiasing
	if (dispInfo.mAntiAlias) {
		glfwWindowHint(GLFW_SAMPLES, 4);
	}

	// Create window
	const char* title = startupInfo.mWindowTitle[0] ? startupInfo.mWindowTitle : "Virtual House";
	int width = dispInfo.mWidth > 0 ? dispInfo.mWidth : 800;
	int height = dispInfo.mHeight > 0 ? dispInfo.mHeight : 600;
	
	printf("DEBUG: Creating window: %dx%d, title='%s'\n", width, height, title);
	fflush(stdout);
	
	mpWindow = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!mpWindow) {
		fprintf(stderr, "Failed to create GLFW window\n");
		fflush(stderr);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	printf("DEBUG: Window created successfully\n");
	fflush(stdout);

	// Make OpenGL context current
	glfwMakeContextCurrent(mpWindow);
	
	// Set user pointer so callbacks can access this instance
	glfwSetWindowUserPointer(mpWindow, this);
	
	// Set callbacks
	glfwSetFramebufferSizeCallback(mpWindow, glfw_resize_callback);
	glfwSetKeyCallback(mpWindow, glfw_key_callback);
	
	// Enable VSync
	glfwSwapInterval(1);

	// Initialize viewport
	int fbWidth, fbHeight;
	glfwGetFramebufferSize(mpWindow, &fbWidth, &fbHeight);
	glViewport(0, 0, fbWidth, fbHeight);

	printf("GLFW window created: %dx%d (Framebuffer: %dx%d)\n", width, height, fbWidth, fbHeight);
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
	
	// Set default texture unit (if using multitexture)
	// Note: glActiveTexture requires GL 1.3+ or ARB_multitexture extension
	// We'll handle this in extensions if needed
	
	// Initialize input system with window handle
	printf("DEBUG: About to initialize FWInput\n");
	fflush(stdout);
	FWInput::init(mpWindow);
	
	printf("DEBUG: FWInput initialized\n");
	fflush(stdout);
	
	// Initialize rest of application (calls FWApplication::onInit)
	printf("DEBUG: About to call FWWindow::init()\n");
	fflush(stdout);
	FWWindow::init();
	
	printf("DEBUG: FWWindow::init() completed, mInit=%d\n", mInit);
	fflush(stdout);
	
	// Call resize if initialization succeeded
	// IMPORTANT: Use framebuffer size (pixels), not logical window size, for correct Retina rendering
	if (mInit) {
		printf("DEBUG: About to call resize(%d, %d)\n", fbWidth, fbHeight);
		fflush(stdout);
		resize(fbWidth, fbHeight);
		printf("DEBUG: resize() completed\n");
		fflush(stdout);
	}
	
	// Store display info
	mDispInfo = dispInfo;
	mDispInfo.mWidth = fbWidth;    // Use pixels
	mDispInfo.mHeight = fbHeight;  // Use pixels
	
	// printf("DEBUG: FWGLFWGLWindow constructor completed\n");
	// fflush(stdout);
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
FWGLFWGLWindow::~FWGLFWGLWindow()
{
	destroy();
}

//-----------------------------------------------------------------------------
// Destroy window
//-----------------------------------------------------------------------------
void FWGLFWGLWindow::destroy()
{
	if (mpWindow) {
		glfwDestroyWindow(mpWindow);
		mpWindow = NULL;
	}
	glfwTerminate();
}

//-----------------------------------------------------------------------------
// Flip buffers
//-----------------------------------------------------------------------------
void FWGLFWGLWindow::flip()
{
	if (mpWindow) {
		glfwSwapBuffers(mpWindow);
	}
}

//-----------------------------------------------------------------------------
// Update (matches Linux architecture)
//-----------------------------------------------------------------------------
bool FWGLFWGLWindow::update()
{
	// printf("DEBUG: update() called, mInit=%d mUpdate=%d\n", mInit, mUpdate);
	// fflush(stdout);
	
	if (mInit && mUpdate) {
		// Process GLFW events
		// printf("DEBUG: about to glfwPollEvents()\n");
		// fflush(stdout);
		glfwPollEvents();
		
		// printf("DEBUG: glfwPollEvents() done\n");
		// fflush(stdout);
		
		// Check if window should close
		if (mpWindow && glfwWindowShouldClose(mpWindow)) {
			return false;
		}
		
		// printf("DEBUG: about to FWWindow::update()\n");
		// fflush(stdout);
		
		// Call base update
		FWWindow::update();
		
		// printf("DEBUG: FWWindow::update() done\n");
		// fflush(stdout);
		
		return mUpdate;
	} else {
		return false;
	}
}

//-----------------------------------------------------------------------------
// Set rendering context
//-----------------------------------------------------------------------------
void FWGLFWGLWindow::setRenderingContext()
{
	if (mpWindow) {
		glfwMakeContextCurrent(mpWindow);
	}
}

//-----------------------------------------------------------------------------
// Clear rendering context
//-----------------------------------------------------------------------------
void FWGLFWGLWindow::clearRenderingContext()
{
	glfwMakeContextCurrent(NULL);
}

//-----------------------------------------------------------------------------
// Get window handle (for input system)
//-----------------------------------------------------------------------------
void* FWGLFWGLWindow::getWindowHandle()
{
	return mpWindow;
}
