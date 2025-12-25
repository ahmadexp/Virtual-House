#include "FWApplication.h"
#include "FWTime.h"

// Static pointer to the application
FWApplication *FWApplication::spApplication = NULL;

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters: 
// Returns:
// Notes: Sets static pointer to application object
//-----------------------------------------------------------------------------
FWApplication::FWApplication()
{
	// set the static pointer to ourselves
	spApplication = this;
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
FWApplication::~FWApplication()
{
}


//-----------------------------------------------------------------------------
// Description: Overloadable initialization function
// Parameters:	argc - Number of arguments
//				ppArgv - Argument list
// Returns: True if application initialized ok, false otherwise
// Notes: 
//-----------------------------------------------------------------------------
bool FWApplication::onInit(int argc, char **ppArgv)
{
	// stop unused parameter warnings
	(void)argc;
	(void)ppArgv;

	return true;
}

//-----------------------------------------------------------------------------
// Description: Overloadable shutdown function
// Parameters: 
// Returns:
// Notes: 
//-----------------------------------------------------------------------------
void FWApplication::onShutdown()
{
}

//-----------------------------------------------------------------------------
// Description: Overloadable update function
// Parameters: 
// Returns: True if the application wants to continue, false otherwise
// Notes:
//-----------------------------------------------------------------------------
bool FWApplication::onUpdate()
{
	return true;
}
