#ifndef SP_EVENT_HEADER
#define SP_EVENT_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	enum class SpEventCategory
		: sp_int
	{
		Window = 1,
		Editor = 2,
		Keyboard = 3,
		Mouse = 4,
		Joypad = 5,
		Collision = 6,
		Gameplay = 7,
		Custom1 = 8,
		Custom2 = 9,
		Custom3 = 10
	};

	class SpEvent
	{
	public:
		sp_int type;
		
		API_INTERFACE SpEvent(const sp_int type)
		{
			this->type = type;
		}

		API_INTERFACE inline virtual SpEventCategory category() const = 0;

	};

}

#endif // SP_EVENT_HEADER