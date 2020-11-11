#ifndef POOL_MEMORY_ALLOCATOR_HEADER
#define POOL_MEMORY_ALLOCATOR_HEADER

#include "BasePlatform.h"

#if defined(WINDOWS)
	#include "WindowsPlatform.h"
#elif defined(LINUX)
	#include "LinuxPlatform.h"	
#elif defined(OSX)
	#include "OSXPlatform.h"	
#endif
#ifndef NAMESPACE_FOUNDATION
	#define NAMESPACE_FOUNDATION SpFoundation
#endif // NAMESPACE_FOUNDATION

#include "Assertions.h"
#include <cstdlib>
#include <cstring>
#include <vector>

#ifndef SP_DEFAULT_MEMORY_SIZE
	#define SP_DEFAULT_MEMORY_SIZE (ONE_MEGABYTE * 512)
#endif

#define SP_BYTE_ADDRESS_LENGTH(byteLength) sp_ceilBit(charLength, SIZEOF_WORD, SIZEOF_WORD_DIVISOR_BIT)

#define sp_mem_header(buffer) ((MemoryPageHeader*)(((sp_size*)arr) - ONE_SIZE))
#define sp_mem_alloc(size) NAMESPACE_FOUNDATION::PoolMemoryAllocator::main()->alloc(size)
#define sp_mem_calloc(length, size) NAMESPACE_FOUNDATION::PoolMemoryAllocator::main()->alloc( (length) * (size))
#define sp_mem_release(buffer) NAMESPACE_FOUNDATION::PoolMemoryAllocator::main()->free( (sp_size*)(buffer) )

#ifdef __cplusplus
	#define sp_mem_new(Type) new (NAMESPACE_FOUNDATION::PoolMemoryAllocator::main()->alloc(sizeof(Type))) Type
	#define sp_mem_new_array(Type, length) new (NAMESPACE_FOUNDATION::PoolMemoryAllocator::main()->alloc(sizeof(Type) * (length))) Type[ (length) ]
	#define sp_mem_new_templated1(Type, Type1) new (NAMESPACE_FOUNDATION::PoolMemoryAllocator::main()->alloc(sizeof(Type))) Type<Type1>
	#define sp_mem_new_templated2(Type, Type1, Type2) new (NAMESPACE_FOUNDATION::PoolMemoryAllocator::main()->alloc(sizeof(Type<Type1,Type2>))) Type<Type1, Type2>
	#define sp_mem_delete(buffer, Type) (buffer)->~Type(); sp_mem_release(buffer);
#endif

namespace NAMESPACE_FOUNDATION
{
	class MemoryPageHeader
	{
	public:
		sp_size addressLength;
		sp_size data;

		API_INTERFACE inline MemoryPageHeader()
		{
			this->addressLength = ZERO_SIZE;
			this->data = ZERO_SIZE;
		}
	};

	class PoolMemoryAllocator
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

			sp_assert(_initialPointer != NULL, "NullPointerException");
		}

	public:

		API_INTERFACE static PoolMemoryAllocator* main();

		API_INTERFACE inline PoolMemoryAllocator(const sp_size size)
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

		API_INTERFACE inline sp_size currentAddress() const noexcept
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

		API_INTERFACE HEAP_PROFILING_ALLOC inline void* alloc(const sp_size size) noexcept
		{
			sp_size addressLength = sp_ceilBit(size, SIZEOF_WORD, SIZEOF_WORD_DIVISOR_BIT);

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

			return (void*)newPointer;
		}

#define IS_LAST_ALLOCATION ((sp_size)*(buffer - ONE_SIZE)) * SIZEOF_WORD + (sp_size)buffer == _currentPointer
		API_INTERFACE inline void free(sp_size* buffer) noexcept
		{
			if (IS_LAST_ALLOCATION)
			{
				_currentPointer = (sp_size)(buffer - ONE_SIZE);
			}
			else
			{
				freedMemoryLength++;
				freedMemory.push_back(buffer);
			}
		}
#undef IS_LAST_ALLOCATION

		API_INTERFACE inline MemoryPageHeader* pageHeader(void* address) noexcept
		{
			return (MemoryPageHeader*)((sp_size*)address - ONE_SIZE);
		}

		API_INTERFACE inline sp_size memorySize() const noexcept
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

			sp_assert(_initialPointer != NULL, "NullPointerException");

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

			release();

			init(size);
		}

		API_INTERFACE inline void release() noexcept
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

		API_INTERFACE inline ~PoolMemoryAllocator() noexcept
		{
			release();
		}
	};
}

#endif // POOL_MEMORY_ALLOCATOR_HEADER
