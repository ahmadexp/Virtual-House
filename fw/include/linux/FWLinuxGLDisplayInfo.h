
#ifndef __FW_LINUXGLDISPLAYINFO_H__
#define __FW_LINUXGLDISPLAYINFO_H__

#include "FWDisplayInfo.h"
#include "FWGLInclude.h"

// Linux OpenGL display information class.
// Contains the GLX context for the window.
// Derives from <c>FWDisplayInfo</c>.
class FWLinuxGLDisplayInfo : public FWDisplayInfo
{
public:
	// OpenGL context
	GLXContext	mGlContext;
};

#endif//__FW_LINUXGLDISPLAYINFO_H__
