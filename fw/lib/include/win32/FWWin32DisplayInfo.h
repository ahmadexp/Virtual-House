
#ifndef __FW_WIN32DISPLAYINFO_H__
#define __FW_WIN32DISPLAYINFO_H__

#include "FWDisplayInfo.h"
#include "FWGLInclude.h"

// Win32 display information class.
// Contains the Win32 OpenGL context.
// Derives from <c>FWDisplayInfo</c>.
class FWWin32DisplayInfo : public FWDisplayInfo
{
public:
	// OpenGL context
	HGLRC		mGlContext;

};

#endif//__FW_WIN32DISPLAYINFO_H__
