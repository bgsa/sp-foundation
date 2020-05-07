#ifndef SP_PAIR_HEADER
#define SP_PAIR_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	template <typename KEY, typename VALUE>
	class SpPair
	{
	public:
		KEY key;
		VALUE value;

		SpPair()
		{

		}

		SpPair(KEY key, VALUE value)
		{
			this->key = key;
			this->value = value;
		}

	};
}

#endif // SP_PAIR_HEADER