#ifndef SP_KEYBOARD_HEADER
#define SP_KEYBOARD_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	class SpKeyboard 
		: public Object
	{
	public:

		API_INTERFACE inline virtual void init() = 0;

		API_INTERFACE inline virtual sp_bool isKeyPressed(sp_int key) const = 0;

	};
}

#endif // SP_KEYBOARD_HEADER