#ifndef SP_CONTIGUOUS_MEMORY_ARRAY_HEADER
#define SP_CONTIGUOUS_MEMORY_ARRAY_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	template <typename T, typename LengthType>
	class SpContiguousMemoryArray
	{
	protected:
		LengthType _length;
		T* _list;

	public:
		
		/// <summary>
		/// Default constructor
		/// </summary>
		/// <returns></returns>
		API_INTERFACE inline SpContiguousMemoryArray()
		{
			_length = 0;
			_list = nullptr;
		}

		/// <summary>
		/// Get the length of array
		/// </summary>
		/// <returns></returns>
		API_INTERFACE inline LengthType length() const
		{
			return _length;
		}

		/// <summary>
		/// Get an item by index
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		API_INTERFACE inline T* get(const LengthType index) const
		{
			return &_list[index];
		}

		/// <summary>
		/// Add new item to array
		/// </summary>
		/// <returns></returns>
		API_INTERFACE inline LengthType add()
		{
			if (_length > 0)
			{
				const sp_size tSize = sizeof(T) * _length;
				void* temp = ALLOC_SIZE(tSize);
				std::memcpy(temp, _list, tSize);

				sp_mem_release(_list);

				_length++;
				_list = sp_mem_new_array(T, _length);

				std::memcpy(_list, temp, tSize);

				ALLOC_RELEASE(temp);
			}
			else
			{
				_length++;
				_list = sp_mem_new_array(T, _length);
			}

			return _length - 1;
		}

		/// <summary>
		/// Remove an item by index
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		API_INTERFACE inline void remove(const LengthType index)
		{
			sp_assert(index < _length, "IndexOutOfRangeException");

			void* previousTs = nullptr, * nextTs = nullptr;

			const sp_size previousTsSize = sizeof(T) * index;
			if (previousTsSize != 0)
			{
				previousTs = ALLOC_SIZE(previousTsSize);
				std::memcpy(previousTs, _list, previousTsSize);
			}

			const sp_size nextTsSize = sizeof(T) * (_length - index - 1);
			if (nextTsSize != 0)
			{
				nextTs = ALLOC_SIZE(nextTsSize);
				std::memcpy(nextTs, &_list[index + 1], nextTsSize);
			}

			sp_mem_release(_list);
			_length--;

			if (_length == 0)
			{
				_list = nullptr;
				return;
			}

			_list = sp_mem_new_array(T, _length);

			if (previousTsSize != 0)
				std::memcpy(_list, previousTs, previousTsSize);

			if (nextTsSize != 0)
				std::memcpy(&_list[index], nextTs, nextTsSize);

			if (previousTsSize != 0)
				ALLOC_RELEASE(previousTs);
			else if (nextTsSize != 0)
				ALLOC_RELEASE(nextTs);
		}

		/// <summary>
		/// Dispose all allocated resources
		/// </summary>
		/// <returns></returns>
		API_INTERFACE inline void dispose()
		{
			if (_length > 0)
			{
				sp_mem_release(_list);
				_list = nullptr;
			}

			_length = 0;
		}

		~SpContiguousMemoryArray()
		{
			dispose();
		}

	};
}

#endif // SP_CONTIGUOUS_MEMORY_ARRAY_HEADER