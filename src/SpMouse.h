#ifndef SP_MOUSE_HEADER
#define SP_MOUSE_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	class SpMouseState
	{
	public:
		sp_int x, y;
		sp_int button;

		SpMouseState(sp_int x, sp_int y)
		{
			this->x = x;
			this->y = y;
		}
	};

	class SpMouse
		: public Object
	{
	protected:
		SpMouseState* _state;

	public:

		API_INTERFACE inline SpMouseState* state()
		{
			return _state;
		}

		API_INTERFACE void virtual init() = 0;

		API_INTERFACE inline virtual void setPosition(sp_int x, sp_int y) = 0;

	};
}

#endif // SP_MOUSE_HEADER