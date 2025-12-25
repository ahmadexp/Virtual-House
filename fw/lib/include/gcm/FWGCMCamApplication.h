
#ifndef __FW_GCMCAMAPPLICATION_H__
#define __FW_GCMCAMAPPLICATION_H__

#include "FWGCMApplication.h"
#include "FWCamera.h"

// GCM and camera application class.
// Derives from FWGCMApplication. Contains an FWCamera object.
class FWGCMCamApplication : public FWGCMApplication
{
public:
					FWGCMCamApplication();
	virtual			~FWGCMCamApplication();

	virtual bool	onInit(int argc, char **ppArgv);
	virtual void	onShutdown();
	virtual bool	onUpdate();
	virtual void	onRender();
	virtual void	onSize(const FWDisplayInfo &dispInfo);

protected:
	// Camera object
	FWCamera				mCamera;
};

#endif//__FW_GCMCAMAPPLICATION_H__
