#include "FWLinuxGLWindow.h"
#include "FWLinuxGLDisplayInfo.h"
#include "FWLinuxXInfo.h"
#include "FWApplication.h"
#include <cstdio>

FWLinuxGLWindow::FWLinuxGLWindow(int argc, char **ppArgv, const FWDisplayInfo &dispInfo, const FWStartupInfo &startupInfo)
    : FWWindow(argc, ppArgv, dispInfo, startupInfo)
{
    // Minimal stub constructor – no platform-specific initialization.
    (void)argc; (void)ppArgv; (void)dispInfo; (void)startupInfo;
}

FWLinuxGLWindow::~FWLinuxGLWindow() {}

bool FWLinuxGLWindow::update() {
    // Stub update – always continue running.
    return true;
}

void FWLinuxGLWindow::destroy() {
    // Stub destroy – nothing to clean up.
}

void* FWLinuxGLWindow::getWindowSystemContext() {
    return nullptr;
}

void FWLinuxGLWindow::setRenderingContext() {}
void FWLinuxGLWindow::clearRenderingContext() {}
void FWLinuxGLWindow::flip() {}
FWDisplayInfo& FWLinuxGLWindow::getDisplayInfo() {
    // Return reference to stored display info (placeholder).
    static FWDisplayInfo dummy;
    return dummy;
}

bool FWLinuxGLWindow::xUpdate() {
    return true;
}
