#ifndef SP_WINDOW_EVENT_HEADER
#define SP_WINDOW_EVENT_HEADER

#include "SpectrumFoundation.h"
#include "SpEvent.h"

namespace NAMESPACE_FOUNDATION
{

	enum class SpWindowEventType
		: sp_uint
	{
		Closed    = 1u,
		Resized   = 2u,
		Moved     = 3u,
		Focus     = 4u,
		LostFocus = 5u
	};

	class SpWindowEvent
		: public SpEvent
	{
	public:

		API_INTERFACE SpWindowEvent(const SpWindowEventType& type)
			: SpEvent((sp_uint)type)
		{
		}

		API_INTERFACE inline SpEventCategory category() const override
		{
			return SpEventCategory::Window;
		}

	};
}

#endif // SP_WINDOW_EVENT_HEADER