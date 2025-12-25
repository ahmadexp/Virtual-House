
#ifndef __FW_NULLWINDOW_H__
#define __FW_NULLWINDOW_H__

#include "FWWindow.h"

// Null graphics window encapsulation class.
// Derives from <c>FWWindow</c>.
class FWNullWindow : public FWWindow
{
public:
						FWNullWindow(int argc, char **ppArgv, const FWDisplayInfo &dispInfo, const FWStartupInfo &startupInfo);
						~FWNullWindow();

	bool				update();
	void				destroy();

	void				*getWindowSystemContext();

private:
	void				setRenderingContext();
	void				clearRenderingContext();
	void				flip();
	FWDisplayInfo&		getDisplayInfo();

	// Generic display info
	FWDisplayInfo		mDispInfo;

};

#endif//__FW_NULLWINDOW_H__
