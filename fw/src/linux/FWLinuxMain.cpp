#include "FWLinuxGLWindow.h"
#include "FWApplication.h"
#include <cstdio>

int main(int argc, char **ppArgv)
{
    FWLinuxGLWindow *pWindow = new FWLinuxGLWindow(argc - 1, &ppArgv[1],
        FWApplication::getApplication()->getDisplayInfo(),
        FWApplication::getApplication()->getStartupInfo());
    bool IsRunning = true;
    while (IsRunning) {
        IsRunning = pWindow->update();
        pWindow->render();
    }
    pWindow->destroy();
    delete pWindow;
    return 0;
}
