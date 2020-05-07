#ifndef SP_KEYBOARD_EVENT_LISTENER_HEADER
#define SP_KEYBOARD_EVENT_LISTENER_HEADER

#include "SpectrumFoundation.h"
#include "SpKeyboardEvent.h"

namespace NAMESPACE_FOUNDATION
{
	class SpKeyboardEventListener
	{
	public:

		API_INTERFACE inline virtual void onKeyboardEvent(SpKeyboardEvent* evt) = 0;

	};
}

#endif // SP_KEYBOARD_EVENT_LISTENER_HEADER