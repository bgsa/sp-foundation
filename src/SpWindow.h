#ifndef SP_WINDOW_HEADER
#define SP_WINDOW_HEADER

#include "SpectrumFoundation.h"
#include "SpString.h"
#include "SpSize.h"

namespace NAMESPACE_FOUNDATION
{
	class SpWindowState
	{
		friend class SpWindow;
	public:

		sp_int x, y, width, height;
		SpSize<sp_int> availableRegion;

		API_INTERFACE inline SpWindowState(sp_int x, sp_int y, sp_int width, sp_int height, const SpSize<sp_int>& availableRegion)
		{
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
			this->availableRegion = availableRegion;
		}

		API_INTERFACE inline sp_float aspectRatio()
		{
			return (sp_float)(width / height);
		}

	};

	class SpWindow
		: public Object
	{
	protected:
		SpWindowState* _state;

	public:
		sp_int titleBarHeight;

		API_INTERFACE inline SpWindowState* state() const noexcept
		{
			return _state;
		}

		API_INTERFACE inline virtual void* handler() = 0;

		API_INTERFACE inline virtual void init() = 0;

		API_INTERFACE inline virtual void setTitle(const sp_char* title) = 0;

		API_INTERFACE inline virtual void setPosition(sp_int x, sp_int y) = 0;

		API_INTERFACE inline virtual void setSize(sp_int width, sp_int height) = 0;

		API_INTERFACE inline virtual void close() = 0;

		API_INTERFACE inline virtual void refresh() = 0;

	};
}

#endif // SP_WINDOW_HEADER