#ifdef GLFW_ENABLED

#ifndef DISPLAY_DEVICE_GLFW_HEADER
#define DISPLAY_DEVICE_GLFW_HEADER

#include "DisplayDevice.h"
#include <GLFW/glfw3.h>

class DisplayDeviceGLFW : public DisplayDevice
{
private:
	GLFWwindow* window;

public:
	API_INTERFACE void init(GLFWwindow* window);
	API_INTERFACE void swapBuffer() override;
};

#endif // DISPLAY_DEVICE_GLFW_HEADER

#endif // !GLFW_ENABLED