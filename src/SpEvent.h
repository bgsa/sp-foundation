#ifndef SP_EVENT_HEADER
#define SP_EVENT_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	enum class SpEventCategory
		: sp_uint
	{
		Window = 1u,
		Editor = 2u,
		Keyboard = 3u,
		Mouse = 4u,
		Joypad = 5u,
		GamePlay = 6u,
		Custom1 = 7u,
		Custom2 = 8u,
		Custom3 = 9u
	};

	class SpEvent
	{
	public:
		sp_uint type;
		
		API_INTERFACE SpEvent(const sp_uint type)
		{
			this->type = type;
		}

		API_INTERFACE inline virtual SpEventCategory category() const = 0;

	};

}

#endif // SP_EVENT_HEADER