#ifdef GLFW_ENABLED

#ifndef SP_WINDOW_GLFW_HEADER
#define SP_WINDOW_GLFW_HEADER

#include "SpectrumFoundation.h"
#include "SpWindow.h"
#include "SpEventDispatcher.h"
#include "SpWindowEvent.h"
#include <GLFW/glfw3.h>

namespace NAMESPACE_FOUNDATION
{
	class SpWindowGLFW
		: public SpWindow
	{
	private:
		GLFWwindow* window = NULL;

		static void onClose(GLFWwindow* window)
		{
			SpWindowEvent* evt = sp_mem_new(SpWindowEvent)(SpWindowEventType::Closed);
			SpEventDispatcher::instance()->push(evt);
		}

		static void onResize(GLFWwindow* window, sp_int width, sp_int height)
		{
			SpWindowEvent* evt = sp_mem_new(SpWindowEvent)(SpWindowEventType::Resized);
			SpEventDispatcher::instance()->push(evt);
		}

		static void error(sp_int error, const sp_char* description)
		{
			fprintf(stderr, "Glfw Error %d: %s\n", error, description);
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

			sp_int windowPosition[2] = { 300, 300 };
			sp_int windowSize[2] = { 1280, 720 };

			window = glfwCreateWindow(windowSize[0], windowSize[0], "Spectrum Engine", NULL, NULL);

			if (window == NULL)
			{
				glfwTerminate();
				return;
			}

			glfwMakeContextCurrent(window);
			glfwSwapInterval(1); // Enable vsync

			glfwSetWindowCloseCallback(window, onClose);
			glfwSetWindowSizeCallback(window, onResize);
			//glfwSetWindowPosCallback(window, onWindowMove);
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
			glfwSetWindowPos(window, x, y);
		}

		API_INTERFACE inline sp_int width() override
		{
			sp_int x;
			sp_int y;
			glfwGetWindowSize(window, &x, &y);

			return x;
		}

		API_INTERFACE inline sp_int height() override
		{
			sp_int x;
			sp_int y;
			glfwGetWindowSize(window, &x, &y);

			return y;
		}

		API_INTERFACE inline sp_int x() override
		{
			sp_double x;
			sp_double y;
			glfwGetCursorPos(window, &x, &y);

			return (sp_int) x;
		}

		API_INTERFACE inline sp_int y() override
		{
			sp_double x;
			sp_double y;
			glfwGetCursorPos(window, &x, &y);

			return (sp_int)y;
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