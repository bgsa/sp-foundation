#ifndef SP_REGION_HEADER
#define SP_REGION_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	class SpRegion
	{
	public:
		sp_float top, left, width, height;

		API_INTERFACE SpRegion()
		{
		}

		API_INTERFACE SpRegion(const sp_float top, const sp_float left, const sp_float width, const sp_float height)
		{
			this->top = top;
			this->left = left;
			this->width = width;
			this->height = height;
		}

	};
}

#endif // SP_REGION