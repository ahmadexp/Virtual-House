#include "linux/FWLinuxTime.h"

// Define static members
FWTimeVal FWTime::sZero(0.0f);
FWTimeVal FWTime::sStoppedTime;
FWTimeVal FWTime::sCurrentTime;
bool FWTime::sIsStopped = true;

void FWTime::init()
{
    sCurrentTime = FWTimeVal(0.0f);
    sIsStopped = true;
}
