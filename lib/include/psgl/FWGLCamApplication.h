
#ifndef __FW_GLCAMAPPLICATION_H__
#define __FW_GLCAMAPPLICATION_H__

#include "FWGLApplication.h"
#include "FWCamera.h"

// OpenGL and camera application class.
// Derives from <c>FWGLApplication</c>. This class contains an <c>FWCamera</c> object,
// but does not implement any input. If a default input implementation is required,
// the application should derive from <c>FWGLCamControlApplication</c> instead.
class FWGLCamApplication : public FWGLApplication
{
public:
					FWGLCamApplication();
	virtual			~FWGLCamApplication();

	virtual bool	onInit(int argc, char **ppArgv);
	virtual void	onShutdown();
	virtual bool	onUpdate();
	virtual void	onRender();
	virtual void	onSize(const FWDisplayInfo &dispInfo);

protected:
	// Camera object
	FWCamera				mCamera;
};

#endif//__FW_GLCAMAPPLICATION_H__
