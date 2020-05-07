#ifndef I_EQUATABLE_HEADER
#define I_EQUATABLE_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	class IEquatable {
	public:

		API_INTERFACE virtual sp_bool equals(const void* other) const noexcept = 0;

		API_INTERFACE virtual sp_size hashCode() const noexcept = 0;

		/*
		API_INTERFACE virtual bool operator==(T* other) const = 0;
		API_INTERFACE virtual bool operator==(const T& other) const = 0;

		API_INTERFACE virtual bool operator==(T* other) const = 0;
		API_INTERFACE virtual bool operator==(const T& other) const = 0;
		*/

	};
}

#endif // I_EQUATABLE_HEADER