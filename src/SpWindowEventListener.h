#ifndef SP_WINDOW_EVENT_LISTENER_HEADER
#define SP_WINDOW_EVENT_LISTENER_HEADER

#include "SpectrumFoundation.h"
#include "SpWindowEvent.h"

namespace NAMESPACE_FOUNDATION
{
	class SpWindowEventListener
	{
	public:

		API_INTERFACE inline virtual void onWindowEvent(SpWindowEvent* evt) = 0;

	};
}

#endif // SP_WINDOW_EVENT_LISTENER_HEADER