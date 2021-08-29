#ifndef SP_NAME_MANAGER_HEADER
#define SP_NAME_MANAGER_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	class SpFixedNameArray
	{
	protected:
		sp_size _length;
		sp_int _maxLength;
		sp_char* _names;

	public:

		/// <summary>
		/// Default constructor
		/// </summary>
		/// <param name="maxLength"></param>
		/// <returns></returns>
		API_INTERFACE inline SpFixedNameArray(const sp_int maxLength = 100)
		{
			_maxLength = maxLength;
			_length = 0;
			_names = nullptr;
		}

		API_INTERFACE inline void newName()
		{
			if (_names != nullptr)
			{
				const sp_size namesSize = sizeof(sp_char) * (_length - 1) * _maxLength;

				void* temp = ALLOC_SIZE(namesSize);
				std::memcpy(temp, _names, namesSize);

				sp_mem_release(_names);

				_names = sp_mem_new_array(sp_char, _length * _maxLength);

				std::memcpy(_names, temp, namesSize);
				ALLOC_RELEASE(temp);
			}
			else
			{
				_names = sp_mem_new_array(sp_char, _maxLength);
			}

			std::memset(&_names[(_length - 1) * _maxLength], 0, _maxLength);
		}

		API_INTERFACE inline void removeName(const sp_uint index)
		{
			if (_length != 0)
			{
				void* previousNames = nullptr, * nextNames = nullptr;

				const sp_size previousNamesSize = sizeof(sp_char) * index * _maxLength;
				if (previousNamesSize != 0)
				{
					previousNames = ALLOC_SIZE(previousNamesSize);
					std::memcpy(previousNames, _names, previousNamesSize);
				}

				const sp_size nextNamesSize = sizeof(sp_char) * (_length - index) * _maxLength;
				if (nextNamesSize != 0)
				{
					nextNames = ALLOC_SIZE(nextNamesSize);
					std::memcpy(nextNames, &_names[(index + 1) * _maxLength], nextNamesSize);
				}

				sp_mem_release(_names);

				_names = sp_mem_new_array(sp_char, _length * _maxLength);

				if (previousNamesSize != 0)
					std::memcpy(_names, previousNames, previousNamesSize);

				if (nextNamesSize != 0)
					std::memcpy(&_names[index * _maxLength], nextNames, nextNamesSize);

				if (previousNamesSize != 0)
					ALLOC_RELEASE(previousNames);
				else if (nextNamesSize != 0)
					ALLOC_RELEASE(nextNames);
			}
			else
			{
				sp_mem_release(_names);
				_names = nullptr;
			}
		}

		/// <summary>
		/// Get a name by index
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		API_INTERFACE inline sp_char* name(const sp_uint index) const
		{
			return &_names[index * _maxLength];
		}

		/// <summary>
		/// Set a name by index
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		API_INTERFACE inline void name(const sp_uint index, const sp_char* newName, const sp_uint newNameLength)
		{
			std::memcpy(&_names[index * _maxLength], newName, newNameLength);
		}

		/// <summary>
		/// Set a name max length
		/// </summary>
		/// <returns></returns>
		API_INTERFACE inline void maxLength(const sp_size maxLength)
		{
			_maxLength = maxLength;
		}

		/// <summary>
		/// Dispose all allocated resources
		/// </summary>
		/// <returns></returns>
		API_INTERFACE inline void dispose()
		{
			if (_length > 0)
			{
				sp_mem_release(_names);
				_names = nullptr;
				_length = 0;
			}
		}

		~SpFixedNameArray()
		{
			dispose();
		}

	};
}

#endif // SP_NAME_MANAGER_HEADER