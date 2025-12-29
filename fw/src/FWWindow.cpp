
#include <stdio.h>
#ifdef __CELLOS_LV2__
#include <sys/paths.h>
#endif

// Include string.h for memset/strchr
#include <string.h>

#include "FWWindow.h"
#include "FWApplication.h"
#include "FWInput.h"
#include "FWTime.h"
#include "FWDebugFont.h"
#include "FWDebugConsole.h"

// Pointer to the window object
FWWindow *FWWindow::spWindow = NULL;

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters:	argc - Number of arguments
//				ppArgv - Argument list
//				dispInfo - Display info class
//				startupInfo - Startup info class
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
FWWindow::FWWindow(int argc, char **ppArgv, const FWDisplayInfo &dispInfo, const FWStartupInfo &startupInfo) :
mArgc(argc),
mppArgv(ppArgv),
mpArgFile(NULL)
{
	// set static window pointer
	spWindow = this;

	// parse arguments file if it exists
	parseArgumentsFile(startupInfo.mArgumentsFilename);

	// stop unused parameter warning
	(void)dispInfo;
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
FWWindow::~FWWindow()
{
	if(mpArgFile)
	{
		delete []mpArgFile;
		delete []mppArgv;
	}
}

//-----------------------------------------------------------------------------
// Description: Init framework
// Parameters: 
// Returns:
// Notes: Called by window class
//-----------------------------------------------------------------------------
void FWWindow::init()
{
	printf("DEBUG: FWWindow::init() - starting\n");
	fflush(stdout);
	
	// initialize timer functions
	printf("DEBUG: About to call FWTime::init()\n");
	fflush(stdout);
	FWTime::init();
	printf("DEBUG: FWTime::init() completed\n");
	fflush(stdout);

	// initialize font functions
	printf("DEBUG: About to call FWDebugFont::init()\n");
	fflush(stdout);
	// TEMPORARY: Commenting out to debug
	// try {
	// 	FWDebugFont::init();
	// } catch (...) {
	// 	fprintf(stderr, "EXCEPTION caught in FWDebugFont::init()\n");
	// 	fflush(stderr);
	// 	throw;
	// }
	printf("DEBUG: FWDebugFont::init() skipped (commented out)\n");
	fflush(stdout);

	// initialize debug console
	mUseDebugConsole = FWApplication::getApplication()->getStartupInfo().mUseDebugConsole;
	printf("DEBUG: mUseDebugConsole = %d\n", mUseDebugConsole);
	fflush(stdout);
	if(mUseDebugConsole)
		FWDebugConsole::init();

	// call application init function
	printf("DEBUG: About to call application onInit()\n");
	fflush(stdout);
	mInit = mUpdate = FWApplication::getApplication()->onInit(mArgc, mppArgv);
	printf("DEBUG: Application onInit() returned %d\n", mInit);
	fflush(stdout);
}

//-----------------------------------------------------------------------------
// Description: Update framework
// Parameters: 
// Returns:
// Notes: Called by window class
//-----------------------------------------------------------------------------
void FWWindow::update()
{
	// printf("DEBUG: FWWindow::update() - about to FWTime::update()\n");
	// fflush(stdout);
	// update timer function
	FWTime::update();
	
	// printf("DEBUG: FWWindow::update() - about to FWInput::update()\n");
	// fflush(stdout);
	// update input devices
	FWInput::update();
	
	// printf("DEBUG: FWWindow::update() - about to debug console\n");
	// fflush(stdout);
	// update console
	if(mUseDebugConsole)
		FWDebugConsole::update();
	
	// printf("DEBUG: FWWindow::update() - about to onUpdate()\n");
	// fflush(stdout);
	// call application update
	mUpdate = FWApplication::getApplication()->onUpdate();
	
	// printf("DEBUG: FWWindow::update() - completed\n");
	// fflush(stdout);
}

//-----------------------------------------------------------------------------
// Description: Render scene
// Parameters: 
// Returns:
// Notes: Called by window class once per frame
//-----------------------------------------------------------------------------
void FWWindow::render()
{
	if(mInit && mUpdate)
	{
		// set rendering context in case it's not set
		setRenderingContext();

		// call application render
		FWApplication::getApplication()->onRender();

		// render console
		if(mUseDebugConsole)
			FWDebugConsole::render();

		// swap buffers
		flip();

		// we did clear the rendering context here
		// but removed it by popular request
	}
}

//-----------------------------------------------------------------------------
// Description: Destroy everything
// Parameters: 
// Returns:
// Notes: Called by window class on shutdown
//-----------------------------------------------------------------------------
void FWWindow::destroy()
{
	// call application shutdown function
	if(mInit)
		FWApplication::getApplication()->onShutdown();

	// shutdown input
	FWInput::shutdown();

	// free font resources
	FWDebugFont::shutdown();
}

//-----------------------------------------------------------------------------
// Description: Get command line args from file and parse them
// Parameters:	pArgumentsFile - Name of arguments file
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void FWWindow::parseArgumentsFile(const char *pArgumentsFile)
{
#ifdef __CELLOS_LV2__
	char	fileName[256];
	snprintf(fileName, sizeof(fileName), "%s/%s", SYS_APP_HOME, pArgumentsFile);
	
	FILE	*fp = fopen(fileName, "r");
#else
	FILE	*fp = fopen(pArgumentsFile, "r");
#endif

	if(fp == NULL)
		return;

	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);

	// allocate an extra byte, in case the file doesn't terminate
	// with a '\0'
	mpArgFile = new char[size + 1];
	memset(mpArgFile, 0, size + 1);

	fseek(fp, 0, SEEK_SET);
	fread(mpArgFile, 1, size, fp);
	fclose(fp);

	// Make a conservative guess at the number of arguments
	int numArgs = 1;
	char *pArg = mpArgFile;
	while((pArg = strchr(pArg, ' ')) != NULL)
	{
		pArg ++;
		numArgs ++;
	}

	// Generate an argument list
	mppArgv = new char *[numArgs];
	pArg = mpArgFile;
	bool inQuote = false;
	for(mArgc = 0; mArgc < numArgs; mArgc ++)
	{
		// consume whitespace
		while((*pArg == ' ') || (*pArg == '\t') || (*pArg == '\n'))
			pArg ++;

		// check for end of string
		if(*pArg == '\0')
			break;

		// is it a quote?
		if((*pArg == '\"') || (inQuote == true))
		{
			// set pointer to start of quoted string
			if(inQuote == true)
				mppArgv[mArgc] = pArg;
			else
				mppArgv[mArgc] = ++ pArg;

			// find closing quote
			while(*pArg && *pArg != '\"')
				pArg ++;

			// check for end of string
			if(*pArg == '\0')
			{
				mArgc ++;
				break;
			}

			// replace closing quote with null terminator
			*pArg ++ ='\0';
			inQuote = false;
		}
		else
		{
			// set pointer to start of string
			mppArgv[mArgc] = pArg;

			// consume non-whitespace
			while(*pArg && (*pArg != ' ') && (*pArg != '\t') && (*pArg != '\n') && (*pArg != '\"'))
				pArg ++;

			// check for end of string
			if(*pArg == '\0')
			{
				mArgc ++;
				break;
			}

			if(*pArg == '\"')
				inQuote = true;
			
			// replace whitespace with null terminator
			*pArg ++ ='\0';
		}
	}
}

//-----------------------------------------------------------------------------
// Description: Called on window resize
// Parameters:	width - New width of window
//				height - New height of window
// Returns:
// Notes: Called by window class
//-----------------------------------------------------------------------------
void FWWindow::resize(int width, int height)
{
	if(mInit && mUpdate)
	{
		// set rendering context in case it's not set
		setRenderingContext();

		FWDisplayInfo &dispInfo = getDisplayInfo();

		dispInfo.mWidth = width;
		dispInfo.mHeight = height;

		// refresh debug console
		if(mUseDebugConsole)
			FWDebugConsole::resize(dispInfo);

		// call application resize
		FWApplication::getApplication()->onSize(dispInfo);

		// we did clear the rendering context here
		// but removed it by popular request
	}
}
