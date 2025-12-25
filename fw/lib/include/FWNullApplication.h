
#ifndef __FW_NULLAPPLICATION_H__
#define __FW_NULLAPPLICATION_H__

#include "FWApplication.h"
#include "FWNullDebugFontRenderer.h"

// Null application base class.
// Derives from <c>FWApplication</c>.
class FWNullApplication : public FWApplication
{
public:
							FWNullApplication();
	virtual					~FWNullApplication();

	virtual bool			onInit(int argc, char **ppArgv);
	virtual void			onShutdown();
	virtual bool			onUpdate();
	virtual void			onRender();
	virtual void			onSize(const FWDisplayInfo &dispInfo);

private:
	// null font renderer instance
	FWNullDebugFontRenderer	mFontRenderer;

};

#endif//__FW_NULLAPPLICATION_H__
