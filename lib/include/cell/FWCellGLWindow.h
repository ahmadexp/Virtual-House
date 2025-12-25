
#ifndef __FW_CELLGLWINDOW_H__
#define __FW_CELLGLWINDOW_H__

#include "FWWindow.h"
#include "FWGLInclude.h"
#include "FWPSGLDisplayInfo.h"
#include "FWStartupInfo.h"

// Cell OpenGL (PSGL) specific graphics encapsulation class.
// Derives from the <c>FWWindow</c> class.
class FWCellGLWindow : public FWWindow
{
public:
					FWCellGLWindow(int argc, char **ppArgv, const FWDisplayInfo &dispInfo, const FWStartupInfo &startupInfo);
	virtual				~FWCellGLWindow();

	bool				update();
	void				destroy();

	virtual void			*getWindowSystemContext();

private:
	void				createDeviceAndSurfaces();
	virtual void			setRenderingContext();
	virtual void			clearRenderingContext();
	virtual void			flip();
	virtual FWDisplayInfo&		getDisplayInfo();

	// PSGL buffer parameters
	// PSGLbufferParameters		mBufferParams;
	// pointer to PSGL device
	PSGLdevice			*mpDevice;
	// display info
	FWPSGLDisplayInfo		mDispInfo;
	// window instance
	static FWCellGLWindow		*spCellGLWindow;

};


//-----------------------------------------------------------------------------
// Description: Returns the PSGL device (no actual window on this platform)
// Parameters: 
// Returns: Pointer to the PSGL device
// Notes:
//-----------------------------------------------------------------------------
inline void *FWCellGLWindow::getWindowSystemContext()
{
	return (void *)mpDevice;
}

#endif//__FW_CELLGLWINDOW_H__
