#ifndef SP_INDEX_MAP_HEADER
#define SP_INDEX_MAP_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	template <typename T>
	class SpIndexMap
	{
	private:
		sp_size _length;
		T* _indexes;

	public:

		/// <summary>
		/// Default constructor
		/// </summary>
		/// <returns></returns>
		API_INTERFACE inline SpIndexMap()
		{
			_length = 0;
			_indexes = nullptr;
		}

		/// <summary>
		/// Get the length of map
		/// </summary>
		/// <returns></returns>
		API_INTERFACE inline sp_size length() const
		{
			return _length;
		}

		/// <summary>
		/// Add new item to map
		/// </summary>
		/// <returns></returns>
		API_INTERFACE inline sp_size add(const T value)
		{
			if (_length > 0)
			{
				const sp_size tSize = sizeof(T) * _length;
				void* temp = ALLOC_SIZE(tSize);
				std::memcpy(temp, _indexes, tSize);

				sp_mem_release(_indexes);

				_length++;
				_indexes = sp_mem_new_array(T, _length);

				std::memcpy(_indexes, temp, tSize);

				ALLOC_RELEASE(temp);
			}
			else
			{
				_length++;
				_indexes = sp_mem_new_array(T, _length);
			}

			return _length - 1;
		}

		/// <summary>
		/// Remove a map item by index
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		API_INTERFACE inline void remove(const sp_size index)
		{
			sp_assert(index < _length, "IndexOutOfRangeException");

			void* previousTs = nullptr, * nextTs = nullptr;

			const sp_size previousTsSize = sizeof(T) * index;
			if (previousTsSize != 0)
			{
				previousTs = ALLOC_SIZE(previousTsSize);
				std::memcpy(previousTs, _indexes, previousTsSize);
			}

			const sp_size nextTsSize = sizeof(T) * (_length - index - 1);
			if (nextTsSize != 0)
			{
				nextTs = ALLOC_SIZE(nextTsSize);
				std::memcpy(nextTsSize, &_indexes[index + 1], nextTsSize);
			}

			sp_mem_release(_indexes);
			_length--;

			if (_length == 0)
			{
				_indexes = nullptr;
				return;
			}

			_indexes = sp_mem_new_array(T, _length);

			if (previousTsSize != 0)
				std::memcpy(_indexes, previousTs, previousTsSize);

			if (nextTsSize != 0)
				std::memcpy(&_indexes[index], nextTs, nextTsSize);

			if (previousTsSize != 0)
				ALLOC_RELEASE(previousTs);
			else if (nextTsSize != 0)
				ALLOC_RELEASE(nextTs);
		}

		/// <summary>
		/// Get an value by index map
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		API_INTERFACE inline T get(const sp_size index) const
		{

		}

		/// <summary>
		/// Get an value by index map
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		API_INTERFACE inline T operator[](const sp_int index) const
		{
			sp_assert(index >= ZERO_INT && (sp_size)index < _length, "IndexOutOfRangeException");
			return _indexes[index];
		}

		/// <summary>
		/// Get an value by index map
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		API_INTERFACE inline T operator[](const sp_uint index) const
		{
			sp_assert(index >= ZERO_UINT && (sp_size)index < _length, "IndexOutOfRangeException");
			return _indexes[index];
		}

#ifdef ENV_64BITS
		/// <summary>
		/// Get an value by index map
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		API_INTERFACE inline T operator[](const sp_size index) const
		{
			sp_assert(index >= ZERO_SIZE && index < _length, "IndexOutOfRangeException");
			return _indexes[index];
		}
#endif

		/// <summary>
		/// Release all allocated resources
		/// </summary>
		/// <returns></returns>
		API_INTERFACE inline void dispose()
		{
			if (_length > 0)
			{
				sp_mem_release(_indexes);
				_indexes = nullptr;
				_length = 0;
			}
		}

		~SpIndexMap()
		{
			dispose();
		}

	};
}

#endif // SP_INDEX_MAP_HEADER