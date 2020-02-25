#ifdef GLFW

#ifndef DISPLAY_DEVICE_GLFW_HEADER
#define DISPLAY_DEVICE_GLFW_HEADER

#include "DisplayDevice.h"
#include <GLFW/glfw3.h>

class DisplayDeviceGLFW : public DisplayDevice
{
private:
	GLFWwindow* window;

public:
	API_INTERFACE void API_INTERFACE init(GLFWwindow* window);
	API_INTERFACE void API_INTERFACE swapBuffer() override;
};

#endif // DISPLAY_DEVICE_GLFW_HEADER

#endif