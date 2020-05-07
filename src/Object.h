#ifndef OBJECT_HEADER
#define OBJECT_HEADER

#include "SpectrumFoundation.h"
#include "Disposable.h"
#include "IEquatable.h"

namespace NAMESPACE_FOUNDATION
{
	class Object 
		: public IEquatable
		, public Disposible
	{
	public:

		API_INTERFACE inline virtual const sp_char* toString() = 0;

		API_INTERFACE inline virtual sp_size hashCode() const noexcept override
		{
			return (sp_size)this;
		}

		API_INTERFACE inline virtual sp_bool equals(const void* other) const noexcept override
		{
			return this == other;
		}

		API_INTERFACE inline virtual void dispose() override { }

	};
}

#endif // !OBJECT_HEADER