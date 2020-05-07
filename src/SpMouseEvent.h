#ifndef SP_MOUSE_EVENT_HEADER
#define SP_MOUSE_EVENT_HEADER

#include "SpectrumFoundation.h"
#include "SpEvent.h"

namespace NAMESPACE_FOUNDATION
{
	enum class SpMouseEventType
		: sp_uint
	{
		ButtonPressed = 1u,
		ButtonReleased = 2u,
		Moved = 3u,
		Scrolled = 4u
	};

	class SpMouseEvent
		: public SpEvent
	{
	public:

		API_INTERFACE SpMouseEvent(const SpMouseEventType& type)
			: SpEvent((sp_uint)type)
		{
		}

		API_INTERFACE inline SpEventCategory category() const override
		{
			return SpEventCategory::Mouse;
		}

	};
}

#endif // SP_MOUSE_EVENT_HEADER