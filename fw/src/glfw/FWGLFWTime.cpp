// GLFW-based time implementation

#include <GLFW/glfw3.h>
#include "FWTime.h"

static double s_startTime = 0.0;
FWTimeVal FWTime::sZero;
FWTimeVal FWTime::sStoppedTime;
FWTimeVal FWTime::sCurrentTime;
bool FWTime::sIsStopped = false;

//-----------------------------------------------------------------------------
// Initialize time
//-----------------------------------------------------------------------------
void FWTime::init()
{
	s_startTime = glfwGetTime();
	sCurrentTime.mVal = 0;
}

//-----------------------------------------------------------------------------
// Get current time
//-----------------------------------------------------------------------------
FWTimeVal FWTime::getCurrentTime()
{
	FWTimeVal tv;
	tv.mVal = (uint64_t)((glfwGetTime() - s_startTime) * _MICROSECS);
	return tv;
}

//-----------------------------------------------------------------------------
// Start/stop time (for pausing)
//-----------------------------------------------------------------------------
void FWTime::startTime()
{
	sIsStopped = false;
}

void FWTime::stopTime()
{
	sIsStopped = true;
	sStoppedTime = sCurrentTime;
}

//-----------------------------------------------------------------------------
// Update time
//-----------------------------------------------------------------------------
void FWTime::update()
{
	if (!sIsStopped)
		sCurrentTime = getCurrentTime();
	else
		sCurrentTime = sStoppedTime;
}
