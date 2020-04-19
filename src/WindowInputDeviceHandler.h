#ifndef WINDOW_INPUT_DEVICE_HANDLER_HEADER
#define WINDOW_INPUT_DEVICE_HANDLER_HEADER

#include "SpectrumFoundation.h"
#include "InputDeviceHandler.h"

namespace NAMESPACE_FOUNDATION
{
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
		API_INTERFACE virtual void onHide() {};
		API_INTERFACE virtual void onShow() {};
		API_INTERFACE virtual void onMove(WindowMoveEvent& moveEvent) {};
		API_INTERFACE virtual void onClose() {};
		API_INTERFACE virtual void onResize(sp_int width, sp_int height) {};
		API_INTERFACE virtual void onMaximized() {};
		API_INTERFACE virtual void onFullScreen() {};
		API_INTERFACE virtual void onFocusIn() {};
		API_INTERFACE virtual void onFocusOut() {};
	};
}

#endif // !WINDOW_INPUT_DEVICE_HANDLER_HEADER