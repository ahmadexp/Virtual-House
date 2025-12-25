// GLFW main entry point for macOS

#include "glfw/FWGLFWGLWindow.h"
#include "FWApplication.h"
#include <stdio.h>

//-----------------------------------------------------------------------------
// main()
// Description: Entry point for GLFW-based application
//-----------------------------------------------------------------------------
int main(int argc, char **ppArgv)
{
	FWGLFWGLWindow *pWindow;

	// Create window
	pWindow = new FWGLFWGLWindow(argc - 1, &ppArgv[1], 
		FWApplication::getApplication()->getDisplayInfo(), 
		FWApplication::getApplication()->getStartupInfo());

	// printf("DEBUG: Window created, entering main loop\n");
	// fflush(stdout);

	// Main loop (matches Linux architecture)
	bool IsRunning = true;
	int frame = 0;
	while(IsRunning)
	{
		// printf("DEBUG: Frame %d - about to update()\n", frame);
		// fflush(stdout);
		
		// Call update and render
		IsRunning = pWindow->update();
		
		// printf("DEBUG: Frame %d - update() returned %d, about to render()\n", frame, IsRunning);
		// fflush(stdout);
		
		pWindow->render();
		
		// printf("DEBUG: Frame %d - render() completed\n", frame);
		// fflush(stdout);
		
		frame++;
	}

	// Cleanup
	pWindow->destroy();
	delete pWindow;
	
	return 0;
}
