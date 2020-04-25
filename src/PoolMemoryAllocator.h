#ifndef POOL_MEMORY_ALLOCATOR_HEADER
#define POOL_MEMORY_ALLOCATOR_HEADER

#ifdef WINDOWS
	#include "WindowsPlatform.h"
#else
	#include "LinuxPlatform.h"	
#endif

#ifndef NAMESPACE_FOUNDATION
	#define NAMESPACE_FOUNDATION SpFoundation
#endif // NAMESPACE_FOUNDATION

#include <cassert>
#include <cstdlib>
#include <vector>

#ifndef SP_DEFAULT_MEMORY_SIZE
	#define SP_DEFAULT_MEMORY_SIZE (ONE_MEGABYTE * 512)
#endif

#define sp_mem_alloc(size) NAMESPACE_FOUNDATION::PoolMemoryAllocator::main()->alloc(size, ++NAMESPACE_FOUNDATION::PoolMemoryAllocator::main()->syncPreviousCounter)
#define sp_mem_calloc(length, size) NAMESPACE_FOUNDATION::PoolMemoryAllocator::main()->alloc( (length) * (size), ++NAMESPACE_FOUNDATION::PoolMemoryAllocator::main()->syncPreviousCounter)
#define sp_mem_release(buffer) NAMESPACE_FOUNDATION::PoolMemoryAllocator::main()->free( (sp_size*)(buffer) )
#define sp_mem_new(Type) (Type*) new (NAMESPACE_FOUNDATION::PoolMemoryAllocator::main()->alloc(sizeof(Type), ++NAMESPACE_FOUNDATION::PoolMemoryAllocator::main()->syncPreviousCounter)) Type
#define sp_mem_delete(buffer, Type) (buffer)->~Type(); sp_mem_release(buffer);

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
		sp_size initialPointer;
		sp_size currentPointer;
		sp_size lastPointer;

		std::vector<sp_size*> freedMemory;
		sp_size freedMemoryLength = ZERO_SIZE;

		sp_size syncCounter;

		inline void init(const sp_size size)
		{
			assert(size > ZERO_SIZE);
			
			initialPointer = (sp_size)std::malloc(size);
			currentPointer = initialPointer;
			lastPointer = initialPointer + size;

			freedMemory.reserve(100);

			syncCounter = ONE_SIZE;
			syncPreviousCounter = ZERO_SIZE;

			assert(initialPointer != NULL);
		}

	public:
		sp_size syncPreviousCounter = ZERO_SIZE;

		API_INTERFACE static PoolMemoryAllocator* main();

		API_INTERFACE inline PoolMemoryAllocator(const sp_size size)
		{
			init(size);
		}

		API_INTERFACE inline sp_size findFirstFit(sp_size addressLength) noexcept
		{
			for (size_t i = 0; i < freedMemoryLength; ++i)
				if (*(freedMemory[i] - ONE_SIZE) >= addressLength)
					return (sp_size) freedMemory[i];

			return currentPointer;
		}

		API_INTERFACE inline void* alloc(const sp_size size, sp_uint syncValue) noexcept
		{
			while (syncCounter != syncValue) { }

			sp_size addressLength = sp_ceilBit(size, SIZEOF_WORD, SIZEOF_WORD_DIVISOR_BIT);

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
						freedMemoryLength--; // free the memory block

					syncCounter++;
					return (void*)(newPointer + ONE_SIZE);
				}

			((sp_size*)currentPointer)[0] = addressLength;
			currentPointer += SIZEOF_WORD + multiplyBy(addressLength, SIZEOF_WORD_DIVISOR_BIT);

			sp_size newPointer = (currentPointer - multiplyBy(addressLength, SIZEOF_WORD_DIVISOR_BIT));

			syncCounter++;
			return (void*)newPointer;
		}

		API_INTERFACE inline void free(sp_size* buffer) noexcept
		{
			freedMemoryLength++;
			freedMemory.push_back(buffer);
		}

		API_INTERFACE inline MemoryPageHeader* pageHeader(void* address) noexcept
		{
			return (MemoryPageHeader*)((sp_size*)address - ONE_SIZE);
		}

		API_INTERFACE inline sp_size memorySize() noexcept
		{
			return lastPointer - initialPointer;
		}

		API_INTERFACE inline sp_bool hasAvailableMemory(const sp_size size) noexcept
		{
			return (lastPointer - currentPointer - size) > ZERO_SIZE;
		}

		API_INTERFACE inline void resize(sp_size newSize) noexcept
		{
			initialPointer = (sp_size)std::realloc((void*)initialPointer, newSize);

			assert(initialPointer != NULL);

			currentPointer = initialPointer;
			lastPointer = initialPointer + newSize;
		}

		API_INTERFACE inline sp_size freedMemorySize() noexcept
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
#elif UNIX
			//return vmsize.t_rm;
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
			if (initialPointer != ZERO_SIZE)
			{
				freedMemory.clear();
				freedMemoryLength = ZERO_SIZE;

				std::free((void*)initialPointer);

				initialPointer = ZERO_SIZE;
				currentPointer = ZERO_SIZE;
				lastPointer = ZERO_SIZE;

				syncCounter = ONE_SIZE;
			}
		}

		API_INTERFACE inline ~PoolMemoryAllocator() noexcept
		{
			release();
		}
	};
}

#endif // POOL_MEMORY_ALLOCATOR_HEADER