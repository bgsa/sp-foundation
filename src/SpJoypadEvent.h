#ifndef SP_JOYPAD_EVENT_HEADER
#define SP_JOYPAD_EVENT_HEADER

#include "SpectrumFoundation.h"
#include "SpEvent.h"

namespace NAMESPACE_FOUNDATION
{
	enum class SpJoypadEventType
		: sp_uint
	{
		ButtonPressed = 1u,
		ButtonReleased = 2u
	};

	class SpJoypadEvent
		: public SpEvent
	{
	public:

		API_INTERFACE SpJoypadEvent(const SpJoypadEventType& type)
			: SpEvent((sp_uint)type)
		{
		}

		API_INTERFACE inline SpEventCategory category() const override
		{
			return SpEventCategory::Joypad;
		}

	};
}

#endif // SP_JOYPAD_EVENT_HEADERR