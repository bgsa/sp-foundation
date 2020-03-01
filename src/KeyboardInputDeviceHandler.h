#ifndef KEYBOARD_INPUT_DEVICE_HANDLER_HEADER
#define KEYBOARD_INPUT_DEVICE_HANDLER_HEADER

#include "SpectrumFoundation.h"
#include "InputDeviceHandler.h"

class KeyboardInputDeviceHandler : public InputDeviceHandler
{
private:
	sp_bool(*isKeyPressedFunction)(sp_int);

public:	
	API_INTERFACE void init(sp_bool(*isKeyPressedFunction)(sp_int)   ) {
		this->isKeyPressedFunction = isKeyPressedFunction;
	}

	API_INTERFACE sp_bool isKeyPressed(sp_int keyCode)
	{
		return isKeyPressedFunction(keyCode);
	}

	API_INTERFACE virtual void onKeyDown(sp_int keyCode) {};
	API_INTERFACE virtual void onKeyUp(sp_int keyCode) {};
};

#endif // !KEYBOARD_INPUT_DEVICE_HANDLER_HEADER