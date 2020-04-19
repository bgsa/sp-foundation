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

		virtual const sp_char* toString() = 0;

		virtual void dispose() override 
		{
		}

	};
}

#endif // !OBJECT_HEADER