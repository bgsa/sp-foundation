#ifdef GLFW_ENABLED

#ifndef POINTER_INPUT_DEVICE_GLFW_HEADER
#define POINTER_INPUT_DEVICE_GLFW_HEADER

#include "SpectrumFoundation.h"
#include <algorithm>
#include "PointerInputDevice.h"
#include "PointerInputDeviceHandler.h"
#include <GLFW/glfw3.h>
#include "RendererSize.h"

class PointerInputDeviceGLFW : public PointerInputDevice
{
private:
		
public:

	API_INTERFACE PointerInputDeviceGLFW();

	API_INTERFACE void init(GLFWwindow* window);
	API_INTERFACE void update(sp_longlong elapsedTime);
	
	API_INTERFACE void addHandler(PointerInputDeviceHandler* handler);
	API_INTERFACE void removeHandler(PointerInputDeviceHandler* handler);
};

#endif // !POINTER_INPUT_DEVICE_GLFW_HEADER

#endif // !GLFW_ENABLED