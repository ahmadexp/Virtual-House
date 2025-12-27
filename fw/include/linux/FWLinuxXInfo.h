
#ifndef __FW_LINUXXINFO_H__
#define __FW_LINUXXINFO_H__

#include <X11/X.h>

// X information
class FWLinuxXInfo
{
public:
	// X Display
	Display		*mpDisplay;
	// Window handle
	Window		mWindow;
	// Window position
	int			mXPos, mYPos;
	// Window dimensions
	int			mWidth, mHeight;
	// Window moved?
	bool		mWindowMoved;
	// Window in focus?
	bool		mWindowFocus;
};

#endif//__FW_LINUXXINFO_H__
