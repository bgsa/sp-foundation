#ifndef SP_COLLISION_EVENT_LISTENER_HEADER
#define SP_COLLISION_EVENT_LISTENER_HEADER

#include "SpectrumFoundation.h"
#include "SpCollisionEvent.h"

namespace NAMESPACE_FOUNDATION
{
	class SpCollisionEventListener
	{
	public:

		API_INTERFACE inline virtual void onCollisionEvent(SpCollisionEvent* evt) = 0;

	};
}

#endif // SP_COLLISION_EVENT_LISTENER_HEADER