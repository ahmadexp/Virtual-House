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
FWInputDeviceMouse::FWInputDeviceMouse(void *pPlatformData) : FWInputDevice(pPlatformData)
{
    mIsClientRelative = false;
}

FWInputDeviceMouse::~FWInputDeviceMouse()
{
}

FWInput::DeviceType FWInputDeviceMouse::getType() const
{
    return FWInput::DeviceType_Mouse;
}

void FWInputDeviceMouse::update()
{
    // Stub: no actual mouse update logic
}


// ----------------------------------------------------------------------------
// FWInputDeviceKeyboard
// ----------------------------------------------------------------------------
FWInputDeviceKeyboard::FWInputDeviceKeyboard(void *pPlatformData) : FWInputDevice(pPlatformData)
{
}

FWInputDeviceKeyboard::~FWInputDeviceKeyboard()
{
}

FWInput::DeviceType FWInputDeviceKeyboard::getType() const
{
    return FWInput::DeviceType_Keyboard;
}

void FWInputDeviceKeyboard::update()
{
    // Stub: no actual keyboard update logic
}


// ----------------------------------------------------------------------------
// FWInputDevicePad
// ----------------------------------------------------------------------------
FWInputDevicePad::FWInputDevicePad(void *pPlatformData) : FWInputDevice(pPlatformData)
{
}

FWInputDevicePad::~FWInputDevicePad()
{
}

FWInput::DeviceType FWInputDevicePad::getType() const
{
    return FWInput::DeviceType_Pad;
}

void FWInputDevicePad::update()
{
    // Stub
}
