#ifdef GLFW

#ifndef KEYBOARD_INPUT_DEVICE_GLFW_HEADER
#define KEYBOARD_INPUT_DEVICE_GLFW_HEADER

#include "apollo.h"
#include "KeyboardInputDevice.h"
#include <algorithm>
#include <GLFW/glfw3.h>

class KeyboardInputDeviceGLFW : public KeyboardInputDevice
{
private:
	GLFWwindow* window;
	
public:
	API_INTERFACE void init(GLFWwindow*);
	API_INTERFACE void update(sp_longlong elapsedTime);

	API_INTERFACE bool isKeyPressed(sp_int virtualKey);

	API_INTERFACE void addHandler(KeyboardInputDeviceHandler* handler);
	API_INTERFACE void removeHandler(KeyboardInputDeviceHandler* handler);
};

#endif // KEYBOARD_INPUT_DEVICE_GLFW_HEADER

#endif // GLFW