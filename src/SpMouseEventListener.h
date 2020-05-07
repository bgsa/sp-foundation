#ifndef SP_MOUSE_EVENT_LISTENER_HEADER
#define SP_MOUSE_EVENT_LISTENER_HEADER

#include "SpectrumFoundation.h"
#include "SpMouseEvent.h"

namespace NAMESPACE_FOUNDATION
{
	class SpMouseEventListener
	{
	public:

		API_INTERFACE inline virtual void onMouseEvent(SpMouseEvent* evt) = 0;

	};
}

#endif // SP_MOUSE_EVENT_LISTENER_HEADER