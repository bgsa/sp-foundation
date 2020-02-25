#ifdef GLFW

#ifndef WINDOW_INPUT_DEVICE_GLFW_HEADER
#define WINDOW_INPUT_DEVICE_GLFW_HEADER

#include "apollo.h"
#include "WindowInputDevice.h"
#include <algorithm>
#include <GLFW/glfw3.h>

class WindowInputDeviceGLFW : public WindowInputDevice
{
private:
	WindowInputDeviceGLFW();

	GLFWwindow* window;
	std::vector<WindowInputDeviceHandler*> handlers;

public:

	API_INTERFACE static WindowInputDeviceGLFW* getInstance();

	API_INTERFACE void init(GLFWwindow* window);
	API_INTERFACE void update(sp_longlong elapsedTime);

	API_INTERFACE void close();
	API_INTERFACE void resize(sp_int width, sp_int height);

	API_INTERFACE void addHandler(WindowInputDeviceHandler* handler);
	API_INTERFACE void removeHandler(WindowInputDeviceHandler* handler);
};

#endif // !WINDOW_INPUT_DEVICE_GLFW_HEADER

#endif // GLFW