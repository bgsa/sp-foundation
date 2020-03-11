#ifndef TOUCH_INPUT_DEVICE_HANDLER_HEADER
#define TOUCH_INPUT_DEVICE_HANDLER_HEADER

#include "SpectrumFoundation.h"
#include <map>
#include "InputDeviceHandler.h"

namespace NAMESPACE_FOUNDATION
{
	struct TouchPosition {
		sp_float x;
		sp_float y;
	};

	struct TouchEvent {
		sp_int pointerId;
		sp_float pointerSize;
		TouchPosition position;
	};

	struct TouchItem {
		sp_int pointerId;
		sp_float pointerSize;
		TouchPosition initialPosition;
		TouchPosition previousPosition;
		TouchPosition currentPosition;
	};

	class TouchInputDeviceHandler : public InputDeviceHandler
	{
	private:
		std::map<sp_int, TouchItem*> *touchItems;

	public:
		void updateTouchItems(std::map<sp_int, TouchItem*> *touchItems) {
			this->touchItems = touchItems;
		}

		std::map<sp_int, TouchItem*> *getTouchPointers() {
			return touchItems;
		}

		virtual void onTouchPointerIn(TouchEvent e) {};
		virtual void onTouchPointerOut(TouchEvent e) {};

		virtual void onTouchDown(TouchItem* touchItem) {};
		virtual void onTouchUp(TouchItem* touchItem) {};
		virtual void onTouchMove(TouchItem* touchItem) {};
	};
}

#endif // !TOUCH_INPUT_DEVICE_HANDLER_HEADER