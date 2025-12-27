#include "FWLinuxInput.h"
#include "FWInput.h"
#include <cstdio>

// Platform static methods
bool FWInput::platformInit(void *pPlatformData)
{
    // Stub implementation
    return true;
}

void FWInput::platformShutdown()
{
    // Stub implementation
}

void FWInput::platformUpdate()
{
    // Stub implementation
}

// ----------------------------------------------------------------------------
// FWInputDeviceMouse
// ----------------------------------------------------------------------------
// Constructor/Destructor/getType are already implemented in FWInput.cpp... EXCEPT the destructor apparently?
// The linker didn't complain about duplicate destructors, so we must implement them here.
FWInputDeviceMouse::~FWInputDeviceMouse()
{
}

void FWInputDeviceMouse::update()
{
    // Stub: no actual mouse update logic
}


// ----------------------------------------------------------------------------
// FWInputDeviceKeyboard
// ----------------------------------------------------------------------------
// Constructor/Destructor/getType are already implemented in FWInput.cpp... EXCEPT the destructor.
FWInputDeviceKeyboard::~FWInputDeviceKeyboard()
{
}

void FWInputDeviceKeyboard::update()
{
    // Stub: no actual keyboard update logic
}


// ----------------------------------------------------------------------------
// FWInputDevicePad
// ----------------------------------------------------------------------------
// Constructor/Destructor/getType are already implemented in FWInput.cpp... EXCEPT the destructor.
FWInputDevicePad::~FWInputDevicePad()
{
}

void FWInputDevicePad::update()
{
    // Stub
}
