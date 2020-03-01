#ifndef WINDOW_INPUT_DEVICE_HANDLER_HEADER
#define WINDOW_INPUT_DEVICE_HANDLER_HEADER

#include "SpectrumFoundation.h"
#include "InputDeviceHandler.h"

class WindowMoveEvent 
{
public:
	sp_int previousPostion[2];
	sp_int newPosition[2];

	WindowMoveEvent() {	}
	WindowMoveEvent(sp_int previousPostion[2], sp_int newPosition[2])
	{
		this->previousPostion[0] = previousPostion[0];
		this->previousPostion[1] = previousPostion[1];

		this->newPosition[0] = newPosition[0];
		this->newPosition[1] = newPosition[1];
	}
};

class WindowInputDeviceHandler : public InputDeviceHandler
{
public:
	virtual void onHide() {};
	virtual void onShow() {};
	virtual void onMove(WindowMoveEvent& moveEvent) {};
	virtual void onClose() {};
	virtual void onResize(sp_int width, sp_int height) {};
	virtual void onMaximized() {};
	virtual void onFullScreen() {};
	virtual void onFocusIn() {};
	virtual void onFocusOut() {};
};

#endif // !WINDOW_INPUT_DEVICE_HANDLER_HEADER