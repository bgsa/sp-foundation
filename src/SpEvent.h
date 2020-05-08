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
		GamePlay = 6,
		Custom1 = 7,
		Custom2 = 8,
		Custom3 = 9
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