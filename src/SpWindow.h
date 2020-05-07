#ifndef SP_WINDOW_HEADER
#define SP_WINDOW_HEADER

#include "SpectrumFoundation.h"
#include "SpString.h"

namespace NAMESPACE_FOUNDATION
{
	class SpWindow
		: public Object
	{
	public:

		API_INTERFACE inline virtual void* handler() = 0;

		API_INTERFACE inline virtual sp_int width() = 0;

		API_INTERFACE inline virtual sp_int height() = 0;

		API_INTERFACE inline virtual sp_int x() = 0;

		API_INTERFACE inline virtual sp_int y() = 0;

		API_INTERFACE inline virtual void init() = 0;

		API_INTERFACE inline virtual void setTitle(const sp_char* title) = 0;

		API_INTERFACE inline virtual void setPosition(sp_int x, sp_int y) = 0;

		API_INTERFACE inline virtual void close() = 0;

		API_INTERFACE inline virtual void refresh() = 0;

	};
}

#endif // SP_WINDOW_HEADER