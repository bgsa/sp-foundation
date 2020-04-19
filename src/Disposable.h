#ifndef DISPOSABLE_HEADER
#define DISPOSABLE_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	class Disposible
	{
	public:

		API_INTERFACE virtual void dispose() = 0;

	};
}

#endif // !DISPOSABLE_HEADER