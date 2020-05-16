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

	/* Key mapping */
	#define GLFW_KEY_UNKNOW               -1
	#define SP_KEYBOARD_KEY_SPACE         GLFW_KEY_SPACE
	#define SP_KEYBOARD_KEY_APOSTROPHE    GLFW_KEY_APOSTROPHE /* ' */
	#define SP_KEYBOARD_KEY_COMMA         GLFW_KEY_COMMA      /* , */
	#define SP_KEYBOARD_KEY_MINUS         GLFW_KEY_MINUS      /* - */
	#define SP_KEYBOARD_KEY_PERIOD        GLFW_KEY_PERIOD     /* . */
	#define SP_KEYBOARD_KEY_SLASH         GLFW_KEY_SLASH      /* / */
	#define SP_KEYBOARD_KEY_0             GLFW_KEY_0
	#define SP_KEYBOARD_KEY_1             GLFW_KEY_1
	#define SP_KEYBOARD_KEY_2             GLFW_KEY_2
	#define SP_KEYBOARD_KEY_3             GLFW_KEY_3
	#define SP_KEYBOARD_KEY_4             GLFW_KEY_4
	#define SP_KEYBOARD_KEY_5             GLFW_KEY_5
	#define SP_KEYBOARD_KEY_6             GLFW_KEY_6
	#define SP_KEYBOARD_KEY_7             GLFW_KEY_7
	#define SP_KEYBOARD_KEY_8             GLFW_KEY_8
	#define SP_KEYBOARD_KEY_9             GLFW_KEY_9
	#define SP_KEYBOARD_KEY_SEMICOLON     GLFW_KEY_SEMICOLON /* ; */
	#define SP_KEYBOARD_KEY_EQUAL         GLFW_KEY_EQUAL /* = */
	#define SP_KEYBOARD_KEY_A             GLFW_KEY_A
	#define SP_KEYBOARD_KEY_B             GLFW_KEY_B
	#define SP_KEYBOARD_KEY_C             GLFW_KEY_C
	#define SP_KEYBOARD_KEY_D             GLFW_KEY_D
	#define SP_KEYBOARD_KEY_E             GLFW_KEY_E
	#define SP_KEYBOARD_KEY_F             GLFW_KEY_F
	#define SP_KEYBOARD_KEY_G             GLFW_KEY_G
	#define SP_KEYBOARD_KEY_H             GLFW_KEY_H
	#define SP_KEYBOARD_KEY_I             GLFW_KEY_I
	#define SP_KEYBOARD_KEY_J             GLFW_KEY_J
	#define SP_KEYBOARD_KEY_K             GLFW_KEY_K
	#define SP_KEYBOARD_KEY_L             GLFW_KEY_L
	#define SP_KEYBOARD_KEY_M             GLFW_KEY_M
	#define SP_KEYBOARD_KEY_N             GLFW_KEY_N
	#define SP_KEYBOARD_KEY_O             GLFW_KEY_O
	#define SP_KEYBOARD_KEY_P             GLFW_KEY_P
	#define SP_KEYBOARD_KEY_Q             GLFW_KEY_Q
	#define SP_KEYBOARD_KEY_R             GLFW_KEY_R
	#define SP_KEYBOARD_KEY_S             GLFW_KEY_S
	#define SP_KEYBOARD_KEY_T             GLFW_KEY_T
	#define SP_KEYBOARD_KEY_U             GLFW_KEY_U
	#define SP_KEYBOARD_KEY_V             GLFW_KEY_V
	#define SP_KEYBOARD_KEY_W             GLFW_KEY_W
	#define SP_KEYBOARD_KEY_X             GLFW_KEY_X
	#define SP_KEYBOARD_KEY_Y             GLFW_KEY_Y
	#define SP_KEYBOARD_KEY_Z             GLFW_KEY_Z
	#define SP_KEYBOARD_KEY_LEFT_BRACKET  GLFW_KEY_LEFT_BRACKET    /* [ */
	#define SP_KEYBOARD_KEY_BACKSLASH     GLFW_KEY_BACKSLASH         /* \ */
	#define SP_KEYBOARD_KEY_RIGHT_BRACKET GLFW_KEY_RIGHT_BRACKET  /* ] */
	#define SP_KEYBOARD_KEY_GRAVE_ACCENT  GLFW_KEY_GRAVE_ACCENT    /* ` */
	#define SP_KEYBOARD_KEY_WORLD_1       GLFW_KEY_WORLD_1     /* non-US #1 */
	#define SP_KEYBOARD_KEY_WORLD_2       GLFW_KEY_WORLD_2     /* non-US #2 */

	/* Function keys */
	#define SP_KEYBOARD_KEY_ESCAPE         GLFW_KEY_ESCAPE
	#define SP_KEYBOARD_KEY_ENTER          GLFW_KEY_ENTER
	#define SP_KEYBOARD_KEY_TAB            GLFW_KEY_TAB
	#define SP_KEYBOARD_KEY_BACKSPACE      GLFW_KEY_BACKSPACE
	#define SP_KEYBOARD_KEY_INSERT         GLFW_KEY_INSERT
	#define SP_KEYBOARD_KEY_DELETE         GLFW_KEY_DELETE
	#define SP_KEYBOARD_KEY_RIGHT          GLFW_KEY_RIGHT
	#define SP_KEYBOARD_KEY_LEFT           GLFW_KEY_LEFT
	#define SP_KEYBOARD_KEY_DOWN           GLFW_KEY_DOWN
	#define SP_KEYBOARD_KEY_UP             GLFW_KEY_UP
	#define SP_KEYBOARD_KEY_PAGE_UP        GLFW_KEY_PAGE_UP
	#define SP_KEYBOARD_KEY_PAGE_DOWN      GLFW_KEY_PAGE_DOWN
	#define SP_KEYBOARD_KEY_HOME           GLFW_KEY_HOME
	#define SP_KEYBOARD_KEY_END            GLFW_KEY_END
	#define SP_KEYBOARD_KEY_CAPS_LOCK      GLFW_KEY_CAPS_LOCK
	#define SP_KEYBOARD_KEY_SCROLL_LOCK    GLFW_KEY_SCROLL_LOCK
	#define SP_KEYBOARD_KEY_NUM_LOCK       GLFW_KEY_NUM_LOCK
	#define SP_KEYBOARD_KEY_PRINT_SCREEN   GLFW_KEY_PRINT_SCREEN
	#define SP_KEYBOARD_KEY_PAUSE          GLFW_KEY_PAUSE
	#define SP_KEYBOARD_KEY_F1             GLFW_KEY_F1
	#define SP_KEYBOARD_KEY_F2             GLFW_KEY_F2
	#define SP_KEYBOARD_KEY_F3             GLFW_KEY_F3
	#define SP_KEYBOARD_KEY_F4             GLFW_KEY_F4
	#define SP_KEYBOARD_KEY_F5             GLFW_KEY_F5
	#define SP_KEYBOARD_KEY_F6             GLFW_KEY_F6
	#define SP_KEYBOARD_KEY_F7             GLFW_KEY_F7
	#define SP_KEYBOARD_KEY_F8             GLFW_KEY_F8
	#define SP_KEYBOARD_KEY_F9             GLFW_KEY_F9
	#define SP_KEYBOARD_KEY_F10            GLFW_KEY_F10
	#define SP_KEYBOARD_KEY_F11            GLFW_KEY_F11
	#define SP_KEYBOARD_KEY_F12            GLFW_KEY_F12
	#define SP_KEYBOARD_KEY_F13            GLFW_KEY_F13
	#define SP_KEYBOARD_KEY_F14            GLFW_KEY_F14
	#define SP_KEYBOARD_KEY_F15            GLFW_KEY_F15
	#define SP_KEYBOARD_KEY_F16            GLFW_KEY_F16
	#define SP_KEYBOARD_KEY_F17            GLFW_KEY_F17
	#define SP_KEYBOARD_KEY_F18            GLFW_KEY_F18
	#define SP_KEYBOARD_KEY_F19            GLFW_KEY_F19
	#define SP_KEYBOARD_KEY_F20            GLFW_KEY_F20
	#define SP_KEYBOARD_KEY_F21            GLFW_KEY_F21
	#define SP_KEYBOARD_KEY_F22            GLFW_KEY_F22
	#define SP_KEYBOARD_KEY_F23            GLFW_KEY_F23
	#define SP_KEYBOARD_KEY_F24            GLFW_KEY_F24
	#define SP_KEYBOARD_KEY_F25            GLFW_KEY_F25
	#define SP_KEYBOARD_KEY_KP_0           GLFW_KEY_KP_0
	#define SP_KEYBOARD_KEY_KP_1           GLFW_KEY_KP_1
	#define SP_KEYBOARD_KEY_KP_2           GLFW_KEY_KP_2
	#define SP_KEYBOARD_KEY_KP_3           GLFW_KEY_KP_3
	#define SP_KEYBOARD_KEY_KP_4           GLFW_KEY_KP_4
	#define SP_KEYBOARD_KEY_KP_5           GLFW_KEY_KP_5
	#define SP_KEYBOARD_KEY_KP_6           GLFW_KEY_KP_6
	#define SP_KEYBOARD_KEY_KP_7           GLFW_KEY_KP_7
	#define SP_KEYBOARD_KEY_KP_8           GLFW_KEY_KP_8
	#define SP_KEYBOARD_KEY_KP_9           GLFW_KEY_KP_9
	#define SP_KEYBOARD_KEY_KP_DECIMAL     GLFW_KEY_KP_DECIMAL
	#define SP_KEYBOARD_KEY_KP_DIVIDE      GLFW_KEY_KP_DIVIDE
	#define SP_KEYBOARD_KEY_KP_MULTIPLY    GLFW_KEY_KP_MULTIPLY
	#define SP_KEYBOARD_KEY_KP_SUBTRACT    GLFW_KEY_KP_SUBTRACT
	#define SP_KEYBOARD_KEY_KP_ADD         GLFW_KEY_KP_ADD
	#define SP_KEYBOARD_KEY_KP_ENTER       GLFW_KEY_KP_ENTER
	#define SP_KEYBOARD_KEY_KP_EQUAL       GLFW_KEY_KP_EQUAL
	#define SP_KEYBOARD_KEY_SHIFT          GLFW_KEY_LEFT_SHIFT
	#define SP_KEYBOARD_KEY_CONTROL        GLFW_KEY_LEFT_CONTROL
	#define SP_KEYBOARD_KEY_LEFT_ALT       GLFW_KEY_LEFT_ALT
	#define SP_KEYBOARD_KEY_LEFT_SUPER     GLFW_KEY_LEFT_SUPER
	#define SP_KEYBOARD_KEY_RIGHT_SHIFT    GLFW_KEY_RIGHT_SHIFT
	#define SP_KEYBOARD_KEY_RIGHJT_CONTROL GLFW_KEY_RIGHT_CONTROL
	#define SP_KEYBOARD_KEY_RIGHT_ALT      GLFW_KEY_RIGHT_ALT
	#define SP_KEYBOARD_KEY_RIGHT_SUPER    GLFW_KEY_RIGHT_SUPER
	#define SP_KEYBOARD_KEY_MENU           GLFW_KEY_MENU
	#define SP_KEYBOARD_KEY_LAST           GLFW_KEY_LAST
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