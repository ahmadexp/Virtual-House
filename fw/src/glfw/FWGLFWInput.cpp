// GLFW-based input implementation for macOS

#include <GLFW/glfw3.h>
#include <string.h>
#include "FWInput.h"

// Window handle
static GLFWwindow* s_pWindow = NULL;

// Key mapping from GLFW to FW key codes
static int sKeyboardMap[256];

// Mouse state
struct FWGLFWMouseInfo {
	double mLastX;
	double mLastY;
	bool mInit;
};

//-----------------------------------------------------------------------------
// Platform initialization
//-----------------------------------------------------------------------------
bool FWInput::platformInit(void *pPlatformData)
{
	s_pWindow = (GLFWwindow*)pPlatformData;
	
	// Create input devices
	FWGLFWMouseInfo *pMouseInfo = new FWGLFWMouseInfo;
	pMouseInfo->mInit = true;
	FWInputDeviceMouse *pMouse = new FWInputDeviceMouse((void*)pMouseInfo);
	FWInputDeviceKeyboard *pKeybd = new FWInputDeviceKeyboard(NULL);
	
	// Initialize keyboard mapping
	memset(sKeyboardMap, 0, sizeof(sKeyboardMap));
	sKeyboardMap[FWInput::Channel_Key_A] = GLFW_KEY_A;
	sKeyboardMap[FWInput::Channel_Key_B] = GLFW_KEY_B;
	sKeyboardMap[FWInput::Channel_Key_C] = GLFW_KEY_C;
	sKeyboardMap[FWInput::Channel_Key_D] = GLFW_KEY_D;
	sKeyboardMap[FWInput::Channel_Key_E] = GLFW_KEY_E;
	sKeyboardMap[FWInput::Channel_Key_F] = GLFW_KEY_F;
	sKeyboardMap[FWInput::Channel_Key_G] = GLFW_KEY_G;
	sKeyboardMap[FWInput::Channel_Key_H] = GLFW_KEY_H;
	sKeyboardMap[FWInput::Channel_Key_I] = GLFW_KEY_I;
	sKeyboardMap[FWInput::Channel_Key_J] = GLFW_KEY_J;
	sKeyboardMap[FWInput::Channel_Key_K] = GLFW_KEY_K;
	sKeyboardMap[FWInput::Channel_Key_L] = GLFW_KEY_L;
	sKeyboardMap[FWInput::Channel_Key_M] = GLFW_KEY_M;
	sKeyboardMap[FWInput::Channel_Key_N] = GLFW_KEY_N;
	sKeyboardMap[FWInput::Channel_Key_O] = GLFW_KEY_O;
	sKeyboardMap[FWInput::Channel_Key_P] = GLFW_KEY_P;
	sKeyboardMap[FWInput::Channel_Key_Q] = GLFW_KEY_Q;
	sKeyboardMap[FWInput::Channel_Key_R] = GLFW_KEY_R;
	sKeyboardMap[FWInput::Channel_Key_S] = GLFW_KEY_S;
	sKeyboardMap[FWInput::Channel_Key_T] = GLFW_KEY_T;
	sKeyboardMap[FWInput::Channel_Key_U] = GLFW_KEY_U;
	sKeyboardMap[FWInput::Channel_Key_V] = GLFW_KEY_V;
	sKeyboardMap[FWInput::Channel_Key_W] = GLFW_KEY_W;
	sKeyboardMap[FWInput::Channel_Key_X] = GLFW_KEY_X;
	sKeyboardMap[FWInput::Channel_Key_Y] = GLFW_KEY_Y;
	sKeyboardMap[FWInput::Channel_Key_Z] = GLFW_KEY_Z;
	sKeyboardMap[FWInput::Channel_Key_0] = GLFW_KEY_0;
	sKeyboardMap[FWInput::Channel_Key_1] = GLFW_KEY_1;
	sKeyboardMap[FWInput::Channel_Key_2] = GLFW_KEY_2;
	sKeyboardMap[FWInput::Channel_Key_3] = GLFW_KEY_3;
	sKeyboardMap[FWInput::Channel_Key_4] = GLFW_KEY_4;
	sKeyboardMap[FWInput::Channel_Key_5] = GLFW_KEY_5;
	sKeyboardMap[FWInput::Channel_Key_6] = GLFW_KEY_6;
	sKeyboardMap[FWInput::Channel_Key_7] = GLFW_KEY_7;
	sKeyboardMap[FWInput::Channel_Key_8] = GLFW_KEY_8;
	sKeyboardMap[FWInput::Channel_Key_9] = GLFW_KEY_9;
	sKeyboardMap[FWInput::Channel_Key_Space] = GLFW_KEY_SPACE;
	sKeyboardMap[FWInput::Channel_Key_Enter] = GLFW_KEY_ENTER;
	sKeyboardMap[FWInput::Channel_Key_Escape] = GLFW_KEY_ESCAPE;
	sKeyboardMap[FWInput::Channel_Key_Left] = GLFW_KEY_LEFT;
	sKeyboardMap[FWInput::Channel_Key_Right] = GLFW_KEY_RIGHT;
	sKeyboardMap[FWInput::Channel_Key_Up] = GLFW_KEY_UP;
	sKeyboardMap[FWInput::Channel_Key_Down] = GLFW_KEY_DOWN;
	
	return true;
}

//-----------------------------------------------------------------------------
// Platform shutdown
//-----------------------------------------------------------------------------
void FWInput::platformShutdown()
{
	s_pWindow = NULL;
}

//-----------------------------------------------------------------------------
// Platform update
//-----------------------------------------------------------------------------
void FWInput::platformUpdate()
{
	// Nothing needed - GLFW handles events via glfwPollEvents
}

//-----------------------------------------------------------------------------
// Mouse update
//-----------------------------------------------------------------------------
void FWInputDeviceMouse::update()
{
	if (!s_pWindow) {
		mXAxis[0] = mYAxis[0] = mZAxis[0] = 0;
		mButtons[0] = mButtons[1] = mButtons[2] = false;
		FWInputDevice::update();
		return;
	}
	
	FWGLFWMouseInfo *pMouseInfo = (FWGLFWMouseInfo*)mpPlatformData;
	
	// Get cursor position
	double xpos, ypos;
	glfwGetCursorPos(s_pWindow, &xpos, &ypos);
	
	// Get window size for normalization
	int width, height;
	glfwGetWindowSize(s_pWindow, &width, &height);
	
	if (pMouseInfo->mInit) {
		// First frame - no delta
		pMouseInfo->mInit = false;
		mXAxis[0] = mYAxis[0] = mZAxis[0] = 0;
	} else {
		if (mIsClientRelative) {
			// Normalized coordinates
			mXAxis[0] = (int)((xpos / width) * 255);
			mYAxis[0] = (int)((ypos / height) * 255);
			mZAxis[0] = 0;
		} else {
			// Delta motion
			mXAxis[0] = (int)((xpos - pMouseInfo->mLastX) * 255);
			mYAxis[0] = (int)((ypos - pMouseInfo->mLastY) * 255);
			mZAxis[0] = 0;
		}
	}
	
	// Update buttons
	mButtons[0] = glfwGetMouseButton(s_pWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
	mButtons[1] = glfwGetMouseButton(s_pWindow, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;
	mButtons[2] = glfwGetMouseButton(s_pWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
	
	// Save position
	pMouseInfo->mLastX = xpos;
	pMouseInfo->mLastY = ypos;
	
	FWInputDevice::update();
}

//-----------------------------------------------------------------------------
// Mouse destructor
//-----------------------------------------------------------------------------
FWInputDeviceMouse::~FWInputDeviceMouse()
{
	if (mpPlatformData) {
		delete (FWGLFWMouseInfo*)mpPlatformData;
	}
}

//-----------------------------------------------------------------------------
// Keyboard update
//-----------------------------------------------------------------------------
void FWInputDeviceKeyboard::update()
{
	if (!s_pWindow) {
		for (int i = 0; i < 256; i++)
			mKeys[i] = false;
		FWInputDevice::update();
		return;
	}
	
	// Update all keys
	// Update all keys
	for (int i = 0; i < 256; i++) {
		if (sKeyboardMap[i] != 0 && i >= FWInput::Channel_Key_A) {
			mKeys[i - FWInput::Channel_Key_A] = (glfwGetKey(s_pWindow, sKeyboardMap[i]) == GLFW_PRESS);
		}
	}
	
	FWInputDevice::update();
}

//-----------------------------------------------------------------------------
// Keyboard destructor
//-----------------------------------------------------------------------------
FWInputDeviceKeyboard::~FWInputDeviceKeyboard()
{
}

//-----------------------------------------------------------------------------
// Gamepad update (stub)
//-----------------------------------------------------------------------------
void FWInputDevicePad::update()
{
	FWInputDevice::update();
}

//-----------------------------------------------------------------------------
// Gamepad destructor
//-----------------------------------------------------------------------------
FWInputDevicePad::~FWInputDevicePad()
{
}
