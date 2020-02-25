#ifndef TOUCH_INPUT_DEVICE_HEADER
#define TOUCH_INPUT_DEVICE_HEADER

#include "InputDevice.h"
#include "TouchInputDeviceHandler.h"

class TouchInputDevice : public InputDevice
{
public:

	virtual void addHandler(TouchInputDeviceHandler* handler) = 0;
	virtual void removeHandler(TouchInputDeviceHandler* handler) = 0;

};

#endif // !TOUCH_INPUT_DEVICE_HEADER