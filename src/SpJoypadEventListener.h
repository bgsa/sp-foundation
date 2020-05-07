#ifndef SP_JOYPAD_EVENT_LISTENER_HEADER
#define SP_JOYPAD_EVENT_LISTENER_HEADER

#include "SpectrumFoundation.h"
#include "SpJoypadEvent.h"

namespace NAMESPACE_FOUNDATION
{
	class SpJoypadEventListener
	{
	public:

		API_INTERFACE inline virtual void onJoypadEvent(SpJoypadEvent* evt) = 0;

	};
}

#endif // SP_JOYPAD_EVENT_LISTENER_HEADER