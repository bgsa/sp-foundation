#ifndef WINDOW_INPUT_DEVICE_HEADER
#define WINDOW_INPUT_DEVICE_HEADER

#include "apollo.h"
#include "InputDevice.h"
#include "WindowInputDeviceHandler.h"

class WindowInputDevice : public InputDevice
{
public:

	API_INTERFACE virtual void addHandler(WindowInputDeviceHandler* handler) = 0;
	API_INTERFACE virtual void removeHandler(WindowInputDeviceHandler* handler) = 0;

};

#endif // !WINDOW_INPUT_DEVICE_HEADER