#ifndef SP_MAP_HEADER
#define SP_MAP_HEADER

#include "SpectrumFoundation.h"
#include "SpVector.h"
#include "SpPair.h"

namespace NAMESPACE_FOUNDATION
{
	template <typename KEY, typename VALUE>
	class SpMap
		: public Object
	{
	protected:
		SpVector<SpPair<KEY, VALUE>> map;

	public:

		SpMap(const SpMap<KEY, VALUE>&& other) = delete;
		
		API_INTERFACE SpMap()
		{
		}

		API_INTERFACE inline sp_uint length() const noexcept
		{
			return map.length();
		}

		API_INTERFACE inline void add(const SpPair<KEY, VALUE>& item) noexcept
		{
			map.add(item);
		}

		API_INTERFACE inline void add(const KEY& key, const VALUE& value) noexcept
		{
			this->add(SpPair<KEY, VALUE>(key, value));
		}

		API_INTERFACE inline void remove(const KEY& key) noexcept
		{
			for (SpVectorItem<SpPair<KEY, VALUE>>* item = map.begin(); item != NULL; item = item->next())
				if (item->value().key == key)
				{
					map.remove(item);
					return;
				}
		}

		API_INTERFACE inline SpVectorItem<SpPair<KEY, VALUE>>* begin() const noexcept
		{
			return map.begin();
		}

		API_INTERFACE inline VALUE find(const KEY& key) const noexcept
		{
			for (SpVectorItem<SpPair<KEY,VALUE>>* item = map.begin(); item != NULL; item = item->next())
			{
				if (item->value().key == key)
					return item->value().value;
			}
			return NULL;
		}

		API_INTERFACE inline VALUE operator[](const KEY& key) const noexcept
		{
			return find(key);
		}

		API_INTERFACE inline virtual const sp_char* toString() override
		{
			return "SpMap";
		}
	};

}

#endif // SP_ARRAY_HEADER
