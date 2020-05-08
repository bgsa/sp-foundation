#ifndef SP_KEYBOARD_EVENT_HEADER
#define SP_KEYBOARD_EVENT_HEADER

#include "SpectrumFoundation.h"
#include "SpEvent.h"

namespace NAMESPACE_FOUNDATION
{
	class SpKeyboardEvent
		: public SpEvent
	{
	public:
		sp_int key;

		API_INTERFACE SpKeyboardEvent(const sp_int type)
			: SpEvent(type)
		{
		}

		API_INTERFACE inline SpEventCategory category() const override
		{
			return SpEventCategory::Keyboard;
		}

	};
}

#endif // SP_KEYBOARD_EVENT_HEADER