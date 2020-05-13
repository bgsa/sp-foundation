#ifdef GLFW_ENABLED

#ifndef SP_MOUSE_GLFW_HEADER
#define SP_MOUSE_GLFW_HEADER

#include "SpectrumFoundation.h"
#include "SpMouse.h"
#include "SpMouseEvent.h"
#include "SpEventDispatcher.h"
#include "SpDevices.h"
#include <GLFW/glfw3.h>

namespace NAMESPACE_FOUNDATION
{
	class SpMouseGLFW
		: public SpMouse
	{
	private:
		GLFWwindow*	window;

		static void onMove(GLFWwindow* window, sp_double x, sp_double y)
		{
			SpDevices* devices = (SpDevices*)glfwGetWindowUserPointer(window);

			SpMouseEvent* evt = sp_mem_new(SpMouseEvent)(SP_MOUSE_EVENT_MOVED);
			evt->mouse = devices->mouse;
			evt->state.previousX = devices->mouse->state()->x;
			evt->state.previousY = devices->mouse->state()->y;
			evt->state.x = (sp_int) x;
			evt->state.y = (sp_int) y;

			devices->mouse->state()->x = (sp_int)x;
			devices->mouse->state()->y = (sp_int)y;

			SpEventDispatcher::instance()->push(evt);
		}

		static void onClick(GLFWwindow* window, sp_int button, sp_int action, sp_int mods)
		{
			SpDevices* devices = (SpDevices*)glfwGetWindowUserPointer(window);

			sp_double x, y;
			glfwGetCursorPos(window, &x, &y);

			SpMouseEvent* evt = sp_mem_new(SpMouseEvent)(action);
			evt->mouse = devices->mouse;
			evt->state.x = (sp_int)x;
			evt->state.y = (sp_int)y;
			evt->state.button = button;

			SpEventDispatcher::instance()->push(evt);
		}

		static void onScroll(GLFWwindow* window, sp_double xoffset, sp_double yoffset)
		{
			SpDevices* devices = (SpDevices*)glfwGetWindowUserPointer(window);

			SpMouseEvent* evt = sp_mem_new(SpMouseEvent)(SP_MOUSE_EVENT_SCROLLED);
			evt->mouse = devices->mouse;
			evt->state.scrollDeltaY = (sp_float)yoffset;
			SpEventDispatcher::instance()->push(evt);
		}

		static void onEnter(GLFWwindow* window, sp_int entered)
		{
			SpDevices* devices = (SpDevices*)glfwGetWindowUserPointer(window);

			SpMouseEvent* evt = sp_mem_new(SpMouseEvent)(entered ? SP_MOUSE_EVENT_ENTER : SP_MOUSE_EVENT_OUT);
			evt->mouse = devices->mouse;
			SpEventDispatcher::instance()->push(evt);
		}

	public:

		API_INTERFACE SpMouseGLFW(GLFWwindow* window)
		{
			this->window = window;
		}

		API_INTERFACE void init() override
		{
			sp_double x, y;
			glfwGetCursorPos(window, &x, &y);

			_state = sp_mem_new(SpMouseState)((sp_int)x, (sp_int)y);

			glfwSetCursorPosCallback(window, onMove);
			glfwSetMouseButtonCallback(window, onClick);
			glfwSetScrollCallback(window, onScroll);
			glfwSetCursorEnterCallback(window, onEnter);
		}

		API_INTERFACE inline void setPosition(sp_int x, sp_int y) override
		{
			_state->x = x;
			_state->y = y;
			glfwSetCursorPos(window, x, y);
		}

		API_INTERFACE inline sp_bool isButtonPressed(sp_int button) override
		{
			return glfwGetMouseButton(window, button) == SP_MOUSE_EVENT_BUTTON_PRESSED;
		}

		API_INTERFACE inline sp_bool isButtonReleased(sp_int button)
		{
			return glfwGetMouseButton(window, button) == SP_MOUSE_EVENT_BUTTON_RELEASED;
		}

		API_INTERFACE inline sp_bool isLeftButtonPressed() override
		{
			return glfwGetMouseButton(window, SP_MOUSE_BUTTON_LEFT) == SP_MOUSE_EVENT_BUTTON_PRESSED;
		}

		API_INTERFACE inline sp_bool isRightButtonPressed() override
		{
			return glfwGetMouseButton(window, SP_MOUSE_BUTTON_RIGHT) == SP_MOUSE_EVENT_BUTTON_PRESSED;
		}

		API_INTERFACE inline sp_bool isMiddleButtonPressed() override
		{
			return glfwGetMouseButton(window, SP_MOUSE_BUTTON_MIDDLE) == SP_MOUSE_EVENT_BUTTON_PRESSED;
		}

		API_INTERFACE inline void dispose() override
		{
			if (_state != nullptr)
			{
				sp_mem_delete(_state, SpMouseState);
				_state = nullptr;
			}
		}

		API_INTERFACE inline const sp_char* toString() override
		{
			return "SpMouseGLFW";
		}

		API_INTERFACE ~SpMouseGLFW()
		{
			dispose();
		}
	};
}

#endif // SP_MOUSE_GLFW_HEADER

#endif // GLFW_ENABLED