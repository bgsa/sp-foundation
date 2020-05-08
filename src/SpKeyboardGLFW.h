#ifdef GLFW_ENABLED

#ifndef SP_KEYBOARD_GLFW_HEADER
#define SP_KEYBOARD_GLFW_HEADER

#include "SpectrumFoundation.h"
#include "SpKeyboard.h"
#include "SpKeyboardEvent.h"
#include "SpEventDispatcher.h"
#include <GLFW/glfw3.h>

namespace NAMESPACE_FOUNDATION
{
#define SP_KEYBOARD_KEY_PRESSED  GLFW_PRESS
#define SP_KEYBOARD_KEY_RELEASED GLFW_RELEASE

	class SpKeyboardGLFW
		: public SpKeyboard
	{
	private:
		GLFWwindow* window;

		static void onKeyboardEvent(GLFWwindow* window, sp_int key, sp_int scancode, sp_int action, sp_int mods)
		{
			SpKeyboardEvent* evt = sp_mem_new(SpKeyboardEvent)(action);
			evt->key = key;

			SpEventDispatcher::instance()->push(evt);
		}

	public:

		API_INTERFACE SpKeyboardGLFW(GLFWwindow* window)
		{
			this->window = window;
		}

		API_INTERFACE void init() override
		{
			glfwSetInputMode(window, GLFW_STICKY_KEYS, ONE_INT); // for pooling do not lose any event
			glfwSetKeyCallback(window, onKeyboardEvent);
		}

		API_INTERFACE inline sp_bool isKeyPressed(sp_int key) const override
		{
			return glfwGetKey(window, key) == SP_KEYBOARD_KEY_PRESSED;
		}

		API_INTERFACE inline const sp_char* toString() override
		{
			return "SpKeyboardGLFW";
		}
	};
}

#endif // SP_KEYBOARD_GLFW_HEADER

#endif // GLFW_ENABLED