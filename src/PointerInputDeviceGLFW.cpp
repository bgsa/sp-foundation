#ifdef GLFW

#include "PointerInputDeviceGLFW.h"

GLFWwindow* mouseWindow;
std::vector<PointerInputDeviceHandler*> handlersPointer;
sp_float previousPointerPositionDevice[2];

PointerInputDeviceGLFW::PointerInputDeviceGLFW()
{
	previousPointerPositionDevice[0] = 0.0f;
	previousPointerPositionDevice[1] = 0.0f;
}

void onClick(GLFWwindow* window, sp_int button, sp_int action, sp_int mods)
{
	sp_double posx, posy;
	glfwGetCursorPos(mouseWindow, &posx, &posy);

	sp_int screenHeight = RendererSize::getInstance()->getHeight();

	MouseEvent e;
	e.currentPosition[0] = sp_float(posx);
	e.currentPosition[1] = screenHeight - sp_float(posy);

	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		e.button = MouseButton::LEFT;
		break;

	case GLFW_MOUSE_BUTTON_RIGHT:
		e.button = MouseButton::RIGHT;
		break;

	case GLFW_MOUSE_BUTTON_MIDDLE:
		e.button = MouseButton::MIDDLE;
		break;
	}

	if (action == GLFW_PRESS)
		for (PointerInputDeviceHandler* handler : handlersPointer)
			handler->onMouseDown(e);
	else
		for (PointerInputDeviceHandler* handler : handlersPointer)
			handler->onMouseUp(e);
}

void onMove(GLFWwindow* window, sp_double posx, sp_double posy)
{
	int screenHeight = RendererSize::getInstance()->getHeight();

	MouseEvent e;
	e.previousPosition[0] = previousPointerPositionDevice[0];
	e.previousPosition[1] = previousPointerPositionDevice[1];
	e.currentPosition[0] = sp_float(posx);
	e.currentPosition[1] = screenHeight - sp_float(posy);

	int leftButtonState = glfwGetMouseButton(mouseWindow, GLFW_MOUSE_BUTTON_LEFT);
	int rightButtonState = glfwGetMouseButton(mouseWindow, GLFW_MOUSE_BUTTON_RIGHT);
	int middleButtonState = glfwGetMouseButton(mouseWindow, GLFW_MOUSE_BUTTON_MIDDLE);
	
	e.state.position[0] = e.currentPosition[0];
	e.state.position[1] = e.currentPosition[1];
	e.state.leftButtonPressed = leftButtonState == GLFW_PRESS;
	e.state.rightButtonPressed = rightButtonState == GLFW_PRESS;
	e.state.middleButtonPressed = middleButtonState == GLFW_PRESS;

	for (PointerInputDeviceHandler* handler : handlersPointer)
		handler->onMouseMove(e);

	previousPointerPositionDevice[0] = e.currentPosition[0];
	previousPointerPositionDevice[1] = e.currentPosition[1];
}

MouseState getMouseState()
{
	sp_double posx, posy;
	glfwGetCursorPos(mouseWindow, &posx, &posy);

	sp_int screenHeight = RendererSize::getInstance()->getHeight();

	sp_float position[2];
	position[0] = sp_float(posx);
	position[1] = screenHeight - sp_float(posy);

	sp_int leftButtonState = glfwGetMouseButton(mouseWindow, GLFW_MOUSE_BUTTON_LEFT);
	sp_int rightButtonState = glfwGetMouseButton(mouseWindow, GLFW_MOUSE_BUTTON_RIGHT);
	sp_int middleButtonState = glfwGetMouseButton(mouseWindow, GLFW_MOUSE_BUTTON_MIDDLE);

	sp_bool leftButtonPressed = leftButtonState == GLFW_PRESS;
	sp_bool rightButtonPressed = rightButtonState == GLFW_PRESS;
	sp_bool middleButtonPressed = middleButtonState == GLFW_PRESS;

	MouseState result;
	result.position[0] = position[0];
	result.position[1] = position[1];
	result.leftButtonPressed = leftButtonPressed;
	result.rightButtonPressed = rightButtonPressed;
	result.middleButtonPressed = middleButtonPressed;

	return result;
}

void onScroll(GLFWwindow* window, sp_double xoffset, sp_double yoffset)
{
	MouseState state = getMouseState();
	WheelDirection direction = WheelDirection::UP;

	if (xoffset == 0.0)
		if (yoffset > 0)
			direction = WheelDirection::UP;
		else
			direction = WheelDirection::DOWN;

	MouseEvent e;
	e.currentPosition[0] = state.position[0];
	e.currentPosition[1] = state.position[1];
	e.direction = direction;
	e.scrollOffset[0] = sp_float(xoffset);
	e.scrollOffset[1] = sp_float(yoffset);

	for (PointerInputDeviceHandler* handler : handlersPointer)
		handler->onScroll(e);
}

void PointerInputDeviceGLFW::init(GLFWwindow* window)
{
	mouseWindow = window;

	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1); // for pooling do not lose event

	glfwSetMouseButtonCallback(window, onClick);
	glfwSetCursorPosCallback(window, onMove);
	glfwSetScrollCallback(window, onScroll);
}

void PointerInputDeviceGLFW::addHandler(PointerInputDeviceHandler* handler) {
	handler->init(&getMouseState);
	handlersPointer.push_back(handler);
}

void PointerInputDeviceGLFW::removeHandler(PointerInputDeviceHandler* handler)
{
	std::vector<PointerInputDeviceHandler*>::iterator item = std::find(handlersPointer.begin(), handlersPointer.end(), handler);

	if (item != handlersPointer.end())
		handlersPointer.erase(item);
}

void PointerInputDeviceGLFW::update(sp_longlong elapsedTime)
{
}

#endif