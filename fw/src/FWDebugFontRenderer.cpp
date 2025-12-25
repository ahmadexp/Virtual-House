
#include "FWDebugFontRenderer.h"
#include "FWDebugFont.h"

// color passed by FWDebugFont
float	FWDebugFontRenderer::sR;
float	FWDebugFontRenderer::sG;
float	FWDebugFontRenderer::sB;
float	FWDebugFontRenderer::sA;

//-----------------------------------------------------------------------------
// Description: Constructor
// Parameters: 
// Returns:
// Notes: Sets static pointer for renderer instance
//-----------------------------------------------------------------------------
FWDebugFontRenderer::FWDebugFontRenderer()
{
	FWDebugFont::spRenderer = this;
}

//-----------------------------------------------------------------------------
// Description: Destructor
// Parameters: 
// Returns:
// Notes:
//-----------------------------------------------------------------------------
FWDebugFontRenderer::~FWDebugFontRenderer()
{
}
