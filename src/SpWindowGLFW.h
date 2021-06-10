#ifdef GLFW_ENABLED

#ifndef SP_WINDOW_GLFW_HEADER
#define SP_WINDOW_GLFW_HEADER

#include "SpectrumFoundation.h"
#include "SpWindow.h"
#include "SpEventDispatcher.h"
#include "SpWindowEvent.h"
#include "SpMouseGLFW.h"
#include "SpKeyboardGLFW.h"
#include "SpDevices.h"
#include <GLFW/glfw3.h>

namespace NAMESPACE_FOUNDATION
{
	class SpWindowGLFW
		: public SpWindow
	{
	private:
		GLFWwindow* window = NULL;
		SpMouseGLFW* mouse;
		SpKeyboardGLFW* keyboard;

		static void onClose(GLFWwindow* window)
		{
			SpWindowEvent* evt = sp_mem_new(SpWindowEvent)(SpWindowEventType::Closed);
			SpEventDispatcher::instance()->push(evt);
		}

		static void onResize(GLFWwindow* window, sp_int width, sp_int height)
		{
			SpWindowEvent* evt = sp_mem_new(SpWindowEvent)(SpWindowEventType::Resized);

			SpDevices* devices = (SpDevices*)glfwGetWindowUserPointer(window);
			SpWindowState* currentState = devices->window->state();

			const sp_int titleBarHeight = getTitleBarHeight();

			evt->previousState = SpWindowState(currentState->x, currentState->y, currentState->width, currentState->height, 
				SpSize<sp_int>(currentState->width, currentState->height - titleBarHeight));

			currentState->width = width;
			currentState->height = height;

			SpEventDispatcher::instance()->push(evt);
		}

		static void onWindowMove(GLFWwindow* window, sp_int x, sp_int y)
		{
			SpWindowEvent* evt = sp_mem_new(SpWindowEvent)(SpWindowEventType::Resized);

			SpDevices* devices = (SpDevices*)glfwGetWindowUserPointer(window);
			SpWindowState* currentState = devices->window->state();

			evt->previousState = SpWindowState(currentState->x, currentState->y, currentState->width, currentState->height, currentState->availableRegion);

			currentState->x = x;
			currentState->y = y;

			SpEventDispatcher::instance()->push(evt);
		}

		static void error(sp_int error, const sp_char* description)
		{
			fprintf(stderr, "Glfw Error %d: %s\n", error, description);
		}

		static sp_int getTitleBarHeight()
		{
#ifdef WINDOWS
			return GetSystemMetrics(SM_CYCAPTION);
#else
			titleBarHeight = 0;
		TODO: get title bar of window for Linux / MacOS
#endif
		}

	public:

		API_INTERFACE inline void init() override
		{
			glfwSetErrorCallback(error);

			if (!glfwInit())
				return;

#ifdef OPENGLES_ENABLED
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
			glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
#endif

			GLFWmonitor* glfwMonitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(glfwMonitor);
			
			sp_int xpos, ypos, width, height;
			glfwGetMonitorWorkarea(glfwMonitor, &xpos, &ypos, &width, &height);

			titleBarHeight = getTitleBarHeight();

			window = glfwCreateWindow(width, height, "Spectrum Engine", NULL, NULL);

			if (window == NULL)
			{
				glfwTerminate();
				return;
			}

			glfwSetWindowPos(window, xpos, ypos + titleBarHeight);


			glfwMakeContextCurrent(window);
			//glfwSwapInterval(1); // Enable v-sync
			glfwSwapInterval(0); // Disable vsync (much much faster in swap buffer)

			glfwSetWindowCloseCallback(window, onClose);
			glfwSetWindowSizeCallback(window, onResize);
			glfwSetWindowPosCallback(window, onWindowMove);

			_state = sp_mem_new(SpWindowState)(0, 0, width, height, SpSize<sp_int>(width, height - titleBarHeight));

			mouse = sp_mem_new(SpMouseGLFW)(window);
			mouse->init();

			keyboard = sp_mem_new(SpKeyboardGLFW)(window);
			keyboard->init();

			SpDevices* devices = SpDevices::instance();
			devices->window = this;
			devices->mouse = mouse;
			devices->keyboard = keyboard;

			glfwSetWindowUserPointer(window, devices);
		}

		API_INTERFACE inline void* handler() override
		{
			return window;
		}

		API_INTERFACE inline void setTitle(const sp_char* title) override
		{
			glfwSetWindowTitle(window, title);
		}

		API_INTERFACE inline void setPosition(sp_int x, sp_int y) override
		{
			_state->x = x;
			_state->y = y;
			glfwSetWindowPos(window, x, y);
		}

		API_INTERFACE inline void setSize(sp_int width, sp_int height) override
		{
			_state->width = width;
			_state->height = height;
			glfwSetWindowSize(window, width, height);
		}

		API_INTERFACE inline void close() override
		{
			SpWindowGLFW::onClose(window);
		}

		API_INTERFACE inline void refresh() override
		{
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		API_INTERFACE inline void dispose() override
		{
			if (_state != nullptr)
			{
				sp_mem_delete(_state, SpWindowState);
				_state = nullptr;
			}

			if (mouse != nullptr)
			{
				sp_mem_delete(mouse, SpMouseGLFW);
				mouse = nullptr;
			}

			if (keyboard != nullptr)
			{
				sp_mem_delete(keyboard, SpKeyboardGLFW);
				keyboard = nullptr;
			}

			glfwDestroyWindow(window);
			glfwTerminate();
		}

		API_INTERFACE inline const sp_char* toString() override
		{
			return "SpWindowGLFW";
		}

	};
}

#endif // SP_WINDOW_GLFW_HEADER

#endif // GLFW_ENABLED