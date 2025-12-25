
#ifndef __FW_NULLDEBUGFONTRENDERER_H__
#define __FW_NULLDEBUGFONTRENDERER_H__

#include "FWDebugFontRenderer.h"

// Null debug font renderer, used by <c>FWDebugFont</c>.
// Instantiated within <c>FWNullApplication</c>.
class FWNullDebugFontRenderer : public FWDebugFontRenderer
{
public:
					FWNullDebugFontRenderer();
	virtual 		~FWNullDebugFontRenderer();

	virtual void	init();
	virtual void	shutdown();
	virtual void	printStart(float r, float g, float b, float a);
	virtual void	printPass(FWDebugFont::Position *pPositions, FWDebugFont::TexCoord *pTexCoords, FWDebugFont::Color *pColors, int numVerts);
	virtual void	printEnd();

};

#endif//__FW_NULLDEBUGFONTRENDERER_H__
