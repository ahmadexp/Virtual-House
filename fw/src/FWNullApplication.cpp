
#include "FWNullApplication.h"

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters: 
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWNullApplication::FWNullApplication()
{
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters: 
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWNullApplication::~FWNullApplication()
{
}

//-----------------------------------------------------------------------------
// Description: Overloadable init function
// Parameters:	argc - Number of arguments
//				ppArgv - Argument list
// Returns: True if ok, false if not
// Notes: 
//-----------------------------------------------------------------------------
bool FWNullApplication::onInit(int argc, char **ppArgv)
{
	return FWApplication::onInit(argc, ppArgv);
}

//-----------------------------------------------------------------------------
// Description: Overloadable shutdown function
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWNullApplication::onShutdown()
{
	FWApplication::onShutdown();
}

//-----------------------------------------------------------------------------
// Description: Overloadable update function
// Parameters: 
// Returns: False if want to quit, true otherwise
// Notes: 
//-----------------------------------------------------------------------------
bool FWNullApplication::onUpdate()
{
	return FWApplication::onUpdate();
}

//-----------------------------------------------------------------------------
// Description: Overloadable render function
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWNullApplication::onRender()
{
}

//-----------------------------------------------------------------------------
// Description: Overloadable size function
// Parameters:	dispInfo - Reference to disp info class
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWNullApplication::onSize(const FWDisplayInfo &dispInfo)
{
	// copy disp info class
	mDispInfo.mWidth = dispInfo.mWidth;
	mDispInfo.mHeight = dispInfo.mHeight;
}
