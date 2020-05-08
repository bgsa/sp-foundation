#ifndef SP_MOUSE_EVENT_HEADER
#define SP_MOUSE_EVENT_HEADER

#include "SpectrumFoundation.h"
#include "SpEvent.h"
#include "SpMouse.h"

namespace NAMESPACE_FOUNDATION
{

	class SpMouseEvent
		: public SpEvent
	{
	public:
		SpMouseState state = SpMouseState(ZERO_INT, ZERO_INT);

		API_INTERFACE SpMouseEvent(const sp_int type)
			: SpEvent(type)
		{
		}

		API_INTERFACE inline SpEventCategory category() const override
		{
			return SpEventCategory::Mouse;
		}

	};
}

#endif // SP_MOUSE_EVENT_HEADER