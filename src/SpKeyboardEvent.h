#ifndef SP_KEYBOARD_EVENT_HEADER
#define SP_KEYBOARD_EVENT_HEADER

#include "SpectrumFoundation.h"
#include "SpEvent.h"

namespace NAMESPACE_FOUNDATION
{
	enum class SpKeyboardEventType
		: sp_uint
	{
		KeyPressed = 1u,
		KeyReleased = 2u,
	};

	class SpKeyboardEvent
		: public SpEvent
	{
	public:

		API_INTERFACE SpKeyboardEvent(const SpKeyboardEventType& type)
			: SpEvent((sp_uint)type)
		{
		}

		API_INTERFACE inline SpEventCategory category() const override
		{
			return SpEventCategory::Keyboard;
		}

	};
}

#endif // SP_KEYBOARD_EVENT_HEADER