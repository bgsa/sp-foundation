#ifndef POOL_MEMORY_ALLOCATOR_HEADER
#define POOL_MEMORY_ALLOCATOR_HEADER

#ifdef WINDOWS
	#include "WindowsPlatform.h"
#else
	#include "LinuxPlatform.h"	
#endif

#include <cassert>
#include <cstdlib>
#include <vector>

#ifndef SP_DEFAULT_MEMORY_SIZE
	#define SP_DEFAULT_MEMORY_SIZE (ONE_MEGABYTE * 512)
#endif

#define sp_mem_alloc(size) PoolMemoryAllocator::main()->alloc(size, ++PoolMemoryAllocator::main()->syncPreviousCounter)
#define sp_mem_calloc(length, size) PoolMemoryAllocator::main()->alloc(length * size, ++PoolMemoryAllocator::main()->syncPreviousCounter)
#define sp_mem_release(buffer) PoolMemoryAllocator::main()->free((void**)&buffer)
#define sp_mem_new(Type) new (PoolMemoryAllocator::main()->alloc(size, ++PoolMemoryAllocator::main()->syncPreviousCounter)) Type
#define sp_mem_delete(buffer, Type) buffer->~Type(); sp_mem_release(buffer)

namespace SpFoundation
{
	class MemoryBlock
	{
	public:
		sp_size addressLength;
		sp_size next;
		sp_size data;

		API_INTERFACE inline MemoryBlock()
		{
			this->addressLength = ZERO_SIZE;
			this->next = ZERO_SIZE;
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

		sp_size syncCounter = ONE_SIZE;

	public:
		sp_size syncPreviousCounter = ZERO_SIZE;

		API_INTERFACE static PoolMemoryAllocator* main();

		API_INTERFACE inline PoolMemoryAllocator(const sp_size size)
		{
			assert(size > ZERO_SIZE);

			initialPointer = (sp_size)std::malloc(size);
			currentPointer = initialPointer;
			lastPointer = initialPointer + size;

			freedMemory.reserve(100);

			assert(initialPointer != NULL);
		}

		API_INTERFACE inline void* alloc(const sp_size size, sp_uint syncValue) noexcept
		{
			while (syncCounter != syncValue) { }

			const sp_size addressSize = multiplyBy(sp_ceilBit(size, SIZEOF_WORD, SIZEOF_WORD_DIVISOR_BIT), SIZEOF_WORD_DIVISOR_BIT);

			((sp_size*)currentPointer)[0] = addressSize;
			((sp_size*)currentPointer)[SIZEOF_WORD] = 0;
			currentPointer += SIZEOF_TWO_WORDS + addressSize + 1;

			void* newPointer = (void*) currentPointer;

			syncCounter++;

			return newPointer;
		}

		API_INTERFACE inline void free(void** buffer) noexcept
		{
			freedMemory.push_back((sp_size*)buffer);
		}

		API_INTERFACE inline void release() noexcept
		{
			if (initialPointer != ZERO_SIZE)
			{
				std::free((void*)initialPointer);
				initialPointer = ZERO_SIZE;
			}
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
			return freedMemory.size();
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

		API_INTERFACE inline ~PoolMemoryAllocator() noexcept
		{
			release();
		}
	};
}

#endif // POOL_MEMORY_ALLOCATOR_HEADER