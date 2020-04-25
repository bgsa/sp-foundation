#ifndef OBJECT_HEADER
#define OBJECT_HEADER

#include "SpectrumFoundation.h"
#include "Disposable.h"
//#include "IEquatable.h"

namespace NAMESPACE_FOUNDATION
{
	class Object 
		: public Disposible
	{
	public:

		API_INTERFACE virtual const sp_char* toString() = 0;

		API_INTERFACE virtual void dispose() override
		{
		}

	};
}

#endif // !OBJECT_HEADER