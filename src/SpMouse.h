#ifndef SP_MOUSE_HEADER
#define SP_MOUSE_HEADER

#include "SpectrumFoundation.h"

#ifdef GLFW_ENABLED
	#include <GLFW/glfw3.h>

	#define SP_MOUSE_EVENT_BUTTON_PRESSED  GLFW_PRESS
	#define SP_MOUSE_EVENT_BUTTON_RELEASED GLFW_RELEASE
	#define SP_MOUSE_EVENT_MOVED           2
	#define SP_MOUSE_EVENT_SCROLLED        3
	#define SP_MOUSE_EVENT_ENTER           4
	#define SP_MOUSE_EVENT_OUT             5

	#define SP_MOUSE_BUTTON_LEFT    GLFW_MOUSE_BUTTON_LEFT
	#define SP_MOUSE_BUTTON_MIDDLE  GLFW_MOUSE_BUTTON_MIDDLE
	#define SP_MOUSE_BUTTON_RIGHT   GLFW_MOUSE_BUTTON_RIGHT
#endif // GLFW_ENABLED

namespace NAMESPACE_FOUNDATION
{
	class SpMouseState
	{
	public:
		sp_int previousX, previousY;
		sp_int x, y;
		sp_float scrollDeltaY;
		sp_int button;

		SpMouseState(sp_int x, sp_int y)
		{
			this->x = x;
			this->y = y;
			previousX = ZERO_INT;
			previousY = ZERO_INT;
			scrollDeltaY = ZERO_FLOAT;
		}
	};

	class SpMouse
		: public Object
	{
	protected:
		SpMouseState* _state;

	public:

		API_INTERFACE inline SpMouseState* state()
		{
			return _state;
		}

		API_INTERFACE void virtual init() = 0;

		API_INTERFACE inline virtual void setPosition(sp_int x, sp_int y) = 0;

		API_INTERFACE inline virtual sp_bool isButtonPressed(sp_int button) = 0;

		API_INTERFACE inline virtual sp_bool isButtonReleased(sp_int button) = 0;

		API_INTERFACE inline virtual sp_bool isLeftButtonPressed() = 0;

		API_INTERFACE inline virtual sp_bool isRightButtonPressed() = 0;

		API_INTERFACE inline virtual sp_bool isMiddleButtonPressed() = 0;

	};
}

#endif // SP_MOUSE_HEADER