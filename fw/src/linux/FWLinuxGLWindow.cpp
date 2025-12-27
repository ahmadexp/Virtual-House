#include "FWLinuxGLWindow.h"
#include "FWLinuxGLDisplayInfo.h"
#include "FWLinuxXInfo.h"
#include "FWApplication.h"
#include "FWInput.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <X11/Xatom.h>

FWLinuxGLWindow::FWLinuxGLWindow(int argc, char **ppArgv, const FWDisplayInfo &dispInfo, const FWStartupInfo &startupInfo)
    : FWWindow(argc, ppArgv, dispInfo, startupInfo)
{
    // Initialize X11 Display
    mXInfo.mpDisplay = XOpenDisplay(NULL);
    if (mXInfo.mpDisplay == NULL) {
        printf("ERROR: Unable to open X Display\n");
        exit(1);
    }

    int root = DefaultRootWindow(mXInfo.mpDisplay);
    int screen = DefaultScreen(mXInfo.mpDisplay);

    // Choose OpenGL Visual
    GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
    mpVisual = glXChooseVisual(mXInfo.mpDisplay, 0, att);

    if (mpVisual == NULL) {
        printf("ERROR: No appropriate visual found\n");
        exit(1);
    } 

    Colormap cmap = XCreateColormap(mXInfo.mpDisplay, root, mpVisual->visual, AllocNone);

    XSetWindowAttributes swa;
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask | StructureNotifyMask;

    // Create Window
    // Use startupInfo for title if available, or default
    const char* title = startupInfo.mWindowTitle;
    if (!title || strlen(title) == 0) title = "FW Application";

    mXInfo.mWidth = 800; // Default width
    mXInfo.mHeight = 600; // Default height

    // Override with display info if valid
    if (dispInfo.mWidth > 0 && dispInfo.mHeight > 0) {
        mXInfo.mWidth = dispInfo.mWidth;
        mXInfo.mHeight = dispInfo.mHeight;
    }

    mXInfo.mWindow = XCreateWindow(mXInfo.mpDisplay, root, 0, 0, mXInfo.mWidth, mXInfo.mHeight, 0, 
                                   mpVisual->depth, InputOutput, mpVisual->visual, CWColormap | CWEventMask, &swa);

    XStoreName(mXInfo.mpDisplay, mXInfo.mWindow, title);
    
    // Handle Window Close Protocol
    Atom wmDelete = XInternAtom(mXInfo.mpDisplay, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(mXInfo.mpDisplay, mXInfo.mWindow, &wmDelete, 1);

    XMapWindow(mXInfo.mpDisplay, mXInfo.mWindow);

    // Create GL Context
    mContext = glXCreateContext(mXInfo.mpDisplay, mpVisual, NULL, GL_TRUE);
    if(mContext == NULL) {
        printf("ERROR: Unable to create GLX Context\n");
        exit(1);
    }

    glXMakeCurrent(mXInfo.mpDisplay, mXInfo.mWindow, mContext);
    
    // Store dimensions in mDispInfo
    mDispInfo.mWidth = mXInfo.mWidth;
    mDispInfo.mHeight = mXInfo.mHeight;
    mDispInfo.mGlContext = mContext;

    // Initialize Input (passing XInfo as platform data)
    FWInput::init((void*)&mXInfo);

    // Call init to setup framework (fonts, etc)
    init();

    // Start the timer!
    FWTime::startTime();

    // Trigger initial resize
    resize(mXInfo.mWidth, mXInfo.mHeight);
}

FWLinuxGLWindow::~FWLinuxGLWindow()
{
    destroy();
}

bool FWLinuxGLWindow::update()
{
    // Process X Events
    if (!xUpdate()) return false;

    // Call base update
    FWWindow::update();

    return true;
}

void FWLinuxGLWindow::destroy()
{
    if (mContext) {
        glXMakeCurrent(mXInfo.mpDisplay, None, NULL);
        glXDestroyContext(mXInfo.mpDisplay, mContext);
        mContext = NULL;
    }
    if (mXInfo.mpDisplay) {
        XDestroyWindow(mXInfo.mpDisplay, mXInfo.mWindow);
        XCloseDisplay(mXInfo.mpDisplay);
        mXInfo.mpDisplay = NULL;
    }
}

void* FWLinuxGLWindow::getWindowSystemContext()
{
    return (void*)&mXInfo;
}

void FWLinuxGLWindow::setRenderingContext()
{
    if (mXInfo.mpDisplay && mXInfo.mWindow && mContext) {
        glXMakeCurrent(mXInfo.mpDisplay, mXInfo.mWindow, mContext);
    }
}

void FWLinuxGLWindow::clearRenderingContext()
{
    if (mXInfo.mpDisplay) {
        glXMakeCurrent(mXInfo.mpDisplay, None, NULL);
    }
}

void FWLinuxGLWindow::flip()
{
    if (mXInfo.mpDisplay && mXInfo.mWindow) {
        glXSwapBuffers(mXInfo.mpDisplay, mXInfo.mWindow);
    }
}

FWDisplayInfo& FWLinuxGLWindow::getDisplayInfo()
{
    return mDispInfo;
}

bool FWLinuxGLWindow::xUpdate()
{
    if (!mXInfo.mpDisplay) return false;

    XEvent xev;
    while (XPending(mXInfo.mpDisplay)) {
        XNextEvent(mXInfo.mpDisplay, &xev);
        
        switch(xev.type) {
            case ConfigureNotify:
                if (xev.xconfigure.width != mXInfo.mWidth || xev.xconfigure.height != mXInfo.mHeight) {
                    mXInfo.mWidth = xev.xconfigure.width;
                    mXInfo.mHeight = xev.xconfigure.height;
                    resize(mXInfo.mWidth, mXInfo.mHeight);
                }
                break;
            case ClientMessage:
                // Check for window close
                 if ((Atom)xev.xclient.data.l[0] == XInternAtom(mXInfo.mpDisplay, "WM_DELETE_WINDOW", True)) {
                    printf("Window Close Requested\n");
                    return false;
                }
                break;
            case KeyPress:
                // TODO: Feed input
                break;
            case KeyRelease:
                // TODO: Feed input
                break;
        }
    }
    return true;
}
