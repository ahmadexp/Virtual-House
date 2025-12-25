
#ifndef __FW_PSGLDISPLAYINFO_H__
#define __FW_PSGLDISPLAYINFO_H__

#include "FWDisplayInfo.h"
#include "FWGLInclude.h"

// PSGL display information class.
// Contains the PSGL context.
// Derives from <c>FWDisplayInfo</c>.
class FWPSGLDisplayInfo : public FWDisplayInfo
{
public:
	// PSGL context
	PSGLcontext	*mGlContext;
};

#endif//__FW_PSGLDISPLAYINFO_H__
