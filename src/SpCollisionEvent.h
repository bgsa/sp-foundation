#ifndef SP_COLLISION_EVENT_HEADER
#define SP_COLLISION_EVENT_HEADER

#include "SpectrumFoundation.h"
#include "SpEvent.h"

namespace NAMESPACE_FOUNDATION
{
	enum class SpCollisionType
		: sp_uint
	{
		RigidBody = 1u
	};

	class SpCollisionEvent
		: public SpEvent
	{
	public:

		sp_uint indexBody1;
		sp_uint indexBody2;

		API_INTERFACE SpCollisionEvent(const SpCollisionType& type = SpCollisionType::RigidBody)
			: SpEvent((sp_uint)type)
		{
		}

		API_INTERFACE inline SpEventCategory category() const override
		{
			return SpEventCategory::Collision;
		}

	};
}

#endif // SP_COLLISION_EVENT_HEADER