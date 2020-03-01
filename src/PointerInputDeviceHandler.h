#ifndef POINTER_INPUT_DEVICE_HANDLER_HEADER
#define POINTER_INPUT_DEVICE_HANDLER_HEADER

#include "SpectrumFoundation.h"
#include "InputDeviceHandler.h"

enum MouseButton {
	NONE,
	LEFT,
	RIGHT,
	MIDDLE	
};

enum WheelDirection {
	UP,
	DOWN
};

struct MouseState {
	sp_float position[2];
	sp_bool leftButtonPressed;
	sp_bool rightButtonPressed;
	sp_bool middleButtonPressed;
};

class MouseEvent 
{
public:
	MouseButton button;	
	sp_float previousPosition[2];
	sp_float currentPosition[2];
	WheelDirection direction;
	sp_float scrollOffset[2];
	MouseState state;

	void log() {
		Log::info("MOUSE POSITION (" + StringHelper::toString(currentPosition[0]) + " , " + StringHelper::toString(currentPosition[1]) + ")");
	}
};

class PointerInputDeviceHandler : public InputDeviceHandler
{
private:
	MouseState(*getMouseStateFunction)();

public:
	void init(MouseState(*getMouseStateFunction)()) {
		this->getMouseStateFunction = getMouseStateFunction;
	}

	MouseState getMouseState() {
		return getMouseStateFunction();
	}

	virtual void onMouseMove(MouseEvent& e) {};
	
	virtual void onMouseDown(MouseEvent& e) {};
	virtual void onMouseUp(MouseEvent& e) {};

	virtual void onDoubleClick(MouseEvent& e) {};

	virtual void onScroll(MouseEvent& e) {}

	virtual void onMouseEnter(MouseEvent& e) {};
};

#endif // !POINTER_INPUT_DEVICE_HANDLER_HEADER