#ifndef SP_POOL_MEMORY_ALLOCATOR_HEADER
#define SP_POOL_MEMORY_ALLOCATOR_HEADER

#include "BasePlatform.h"
#include "SpMemoryAllocator.h"
#include "Assertions.h"
#include <cstdlib>
#include <cstring>
#include <vector>

#ifdef MEMORY_PROFILING_ENABLED
	#include "SpMemoryProfiling.h"
#endif

#ifndef SP_POOL_MEMORY_DEFAULT_SIZE
	#define SP_POOL_MEMORY_DEFAULT_SIZE (ONE_MEGABYTE * 512)
#endif

#define SP_BYTE_ADDRESS_LENGTH(byteLength) sp_ceilBit(charLength, SIZEOF_WORD, SIZEOF_WORD_DIVISOR_BIT)

#define sp_mem_header(address) NAMESPACE_FOUNDATION::SpPoolMemoryAllocator::main()->pageHeader(address)
#define sp_mem_alloc(size) NAMESPACE_FOUNDATION::SpPoolMemoryAllocator::main()->alloc(size, __FILENAME__, __func__, __LINE__)
#define sp_mem_calloc(length, size) NAMESPACE_FOUNDATION::SpPoolMemoryAllocator::main()->alloc( (length) * (size), __FILENAME__, __func__, __LINE__)
#define sp_mem_release(address) NAMESPACE_FOUNDATION::SpPoolMemoryAllocator::main()->free((void*)address)

#ifdef __cplusplus
	#define sp_mem_new(Type) new (NAMESPACE_FOUNDATION::SpPoolMemoryAllocator::main()->alloc(sizeof(Type), __FILENAME__, __func__, __LINE__)) Type
	#define sp_mem_new_array(Type, length) new (NAMESPACE_FOUNDATION::SpPoolMemoryAllocator::main()->alloc(sizeof(Type) * (length), __FILENAME__, __func__, __LINE__)) Type[ (length) ]
	#define sp_mem_new_templated1(Type, Type1) new (NAMESPACE_FOUNDATION::SpPoolMemoryAllocator::main()->alloc(sizeof(Type), __FILENAME__, __func__, __LINE__)) Type<Type1>
	#define sp_mem_new_templated2(Type, Type1, Type2) new (NAMESPACE_FOUNDATION::SpPoolMemoryAllocator::main()->alloc(sizeof(Type<Type1,Type2>), __FILENAME__, __func__, __LINE__)) Type<Type1, Type2>
	#define sp_mem_delete(address, Type) (address)->~Type(); sp_mem_release(address);
#endif

namespace NAMESPACE_FOUNDATION
{
	class SpMemoryPageHeader
	{
	public:
		sp_size addressLength;
		sp_size data;

		API_INTERFACE inline SpMemoryPageHeader()
		{
			this->addressLength = ZERO_SIZE;
			this->data = ZERO_SIZE;
		}
	};

	class SpPoolMemoryAllocator
		: public SpMemoryAllocator
	{
	private:
		sp_size _initialPointer;
		sp_size _currentPointer;
		sp_size lastPointer;

		std::vector<sp_size*> freedMemory;
		sp_size freedMemoryLength = ZERO_SIZE;

		volatile sp_bool memoryAligned;

		inline void init(const sp_size size)
		{
			sp_assert(size > ZERO_SIZE, "IndexOutOfRange");
			
			_initialPointer = (sp_size)std::malloc(size);
			_currentPointer = _initialPointer;
			lastPointer = _initialPointer + size;

			freedMemory.reserve(100);

			sp_assert(_initialPointer != 0, "NullPointerException");
		}

	public:

		API_INTERFACE static SpPoolMemoryAllocator* main();

		API_INTERFACE inline SpPoolMemoryAllocator(const sp_size size)
		{
			memoryAligned = false;
			init(size);
		}

		API_INTERFACE inline void enableMemoryAlignment() noexcept
		{
			memoryAligned = true;
		}
		API_INTERFACE inline void disableMemoryAlignment() noexcept
		{
			memoryAligned = false;
		}

		API_INTERFACE inline sp_size firstAddress() const noexcept override
		{
			return _initialPointer;
		}

		API_INTERFACE inline sp_size currentAddress() const noexcept override
		{
			return _currentPointer;
		}

		API_INTERFACE inline sp_size findFirstFit(sp_size addressLength) noexcept
		{
			for (size_t i = 0; i < freedMemoryLength; ++i)
				if (*(freedMemory[i] - ONE_SIZE) >= addressLength)
					return (sp_size) freedMemory[i];

			return _currentPointer;
		}

		API_INTERFACE HEAP_PROFILING_ALLOC inline void* alloc(const sp_size size, const sp_char* filename = nullptr, const sp_char* functionName = nullptr, const sp_uint line = 0) noexcept override
		{
			sp_size addressLength = sp_ceilBit(size, SIZEOF_WORD);

			sp_assert(lastPointer > _currentPointer + SIZEOF_WORD + multiplyBy(addressLength, SIZEOF_WORD_DIVISOR_BIT), "OutOfMemoryException");

			if (!memoryAligned)
			{
				// findFirstFit block of memory ...
				for (sp_size i = 0; i < freedMemoryLength; ++i)
					if (*(freedMemory[i] - ONE_SIZE) >= addressLength)
					{
						sp_size* newPointer = freedMemory[i] - ONE_SIZE;

						// resize the remaining memory block for a new free block
						if (newPointer[0] - addressLength > ONE_SIZE)    // if the block size is "too big", 
						{
							freedMemory[i] = freedMemory[i] + addressLength + ONE_SIZE; // create a new free block with the remaining size
							(freedMemory[i] - 1)[0] = newPointer[0] - addressLength - ONE_SIZE; // set the length of block header

							newPointer[0] = addressLength;
						}
						else
						{
							freedMemoryLength--; // free the memory block
							freedMemory.erase(freedMemory.begin() + i);
						}

						return (void*)(newPointer + ONE_SIZE);
					}
			}

			((sp_size*)_currentPointer)[0] = addressLength;
			_currentPointer += SIZEOF_WORD + multiplyBy(addressLength, SIZEOF_WORD_DIVISOR_BIT);

			sp_size newPointer = (_currentPointer - multiplyBy(addressLength, SIZEOF_WORD_DIVISOR_BIT));

#ifdef MEMORY_PROFILING_ENABLED	
			SpMemoryProfilingInstance->alloc(newPointer, addressLength, filename, functionName, line);
#endif

			return (void*)newPointer;
		}

		API_INTERFACE inline void free(void* address) noexcept override
		{
			SpMemoryPageHeader* header = pageHeader(address);

			if (header->addressLength * SIZEOF_WORD + (sp_size)address == _currentPointer)
			{
				_currentPointer = (sp_size)header;
			}
			else
			{
				freedMemoryLength++;
				freedMemory.push_back((sp_size*)address);
			}

#ifdef MEMORY_PROFILING_ENABLED
			SpMemoryProfilingInstance->free((sp_size)address);
#endif
		}

		API_INTERFACE inline SpMemoryPageHeader* pageHeader(void* address) noexcept
		{
			return (SpMemoryPageHeader*)((sp_size*)address - ONE_SIZE);
		}

		API_INTERFACE inline sp_size memorySize() const noexcept override
		{
			return lastPointer - _initialPointer;
		}

		API_INTERFACE inline sp_bool hasAvailableMemory(const sp_size size) const noexcept
		{
			return (lastPointer - _currentPointer - size) > ZERO_SIZE;
		}

		API_INTERFACE inline void resize(sp_size newSize) noexcept
		{
			_initialPointer = (sp_size)std::realloc((void*)_initialPointer, newSize);

			sp_assert(_initialPointer != 0, "NullPointerException");

			_currentPointer = _initialPointer;
			lastPointer = _initialPointer + newSize;
		}

		API_INTERFACE inline sp_size freedMemorySize() const noexcept
		{
			return freedMemoryLength;
		}

		API_INTERFACE inline static void copy(const void* source, void* destiny, sp_size size) noexcept
		{
			std::memcpy(destiny, source, size);
		}

		API_INTERFACE inline sp_size globalMemorySize() noexcept
		{
#ifdef WINDOWS
			MEMORYSTATUSEX status;
			status.dwLength = sizeof(status);
			GlobalMemoryStatusEx(&status);
			return (sp_size)status.ullTotalPhys;
#elif defined (LINUX) || defined(OSX)
			//return vmsize.t_rm;
			return 0;
#endif
		}

		API_INTERFACE inline void reset() noexcept
		{
			const sp_size size = memorySize();

			dispose();

			init(size);
		}

		API_INTERFACE inline void dispose() noexcept override
		{
			if (_initialPointer != ZERO_SIZE)
			{
				freedMemory.clear();
				freedMemoryLength = ZERO_SIZE;

				std::free((void*)_initialPointer);

				_initialPointer = ZERO_SIZE;
				_currentPointer = ZERO_SIZE;
				lastPointer = ZERO_SIZE;
			}
		}

		API_INTERFACE inline ~SpPoolMemoryAllocator() noexcept
		{
			dispose();
		}
	};
}

#endif // SP_POOL_MEMORY_ALLOCATOR_HEADER