
#ifndef __FW_LINUXGLWINDOW_H__
#define __FW_LINUXGLWINDOW_H__

#include "FWWindow.h"
#include "FWGLInclude.h"
#include "FWLinuxGLDisplayInfo.h"
#include "FWStartupInfo.h"
#include "FWLinuxXInfo.h"

// Linux OpenGL specific graphics window encapsulation class.
// Derives from <c>FWWindow</c>.
class FWLinuxGLWindow : public FWWindow
{
public:
							FWLinuxGLWindow(int argc, char **ppArgv, const FWDisplayInfo &dispInfo, const FWStartupInfo &startupInfo);
	virtual 				~FWLinuxGLWindow();

	bool					update();
	void					destroy();

	virtual void			*getWindowSystemContext();

private:
	virtual void			setRenderingContext();
	virtual void			clearRenderingContext();
	virtual void			flip();
	virtual FWDisplayInfo&	getDisplayInfo();

	bool					xUpdate();

	// X Info
	FWLinuxXInfo			mXInfo;
	// display info
	FWLinuxGLDisplayInfo	mDispInfo;

};

#endif//__FW_LINUXGLWINDOW_H__
