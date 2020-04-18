#ifndef OBJECT_HEADER
#define OBJECT_HEADER

#include "SpectrumFoundation.h"
//#include "IEquatable.h"

namespace NAMESPACE_FOUNDATION
{
	class Object //: public IEquatable<Object>
	{
	public:

		virtual const sp_char* toString() = 0;

	};
}

#endif // !OBJECT_HEADER