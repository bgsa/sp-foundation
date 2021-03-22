#include "SpStackMemoryAllocator.h"

namespace NAMESPACE_FOUNDATION
{
	static SpStackMemoryAllocator* instance = new SpStackMemoryAllocator();

	SpStackMemoryAllocator* SpStackMemoryAllocator::main() noexcept
	{
		return instance;
	}

	void SpStackMemoryAllocator::init(const sp_size initialSize) noexcept
	{
		initialPointer = std::malloc(initialSize);

		sp_assert(initialPointer != NULL, "NullPointerException");

		currentPointer = initialPointer;
		lastPointer = (void*)((sp_size)initialPointer + initialSize);
	}

	void SpStackMemoryAllocator::free(void* buffer) noexcept
	{
		sp_assert(buffer != NULL, "NullPointerException");
		sp_assert(buffer >= initialPointer && buffer <= lastPointer, "IndexOutOfRangeException");

		if (currentPointer > buffer) // memory has already freed by previous pointer
			currentPointer = buffer;
	}

	sp_size SpStackMemoryAllocator::deviceMemorySize() noexcept
	{
#ifdef WINDOWS
		MEMORYSTATUSEX status;
		status.dwLength = sizeof(status);
		GlobalMemoryStatusEx(&status);
		return (sp_size)status.ullTotalPhys;
#elif UNIX
		//return vmsize.t_rm;
		return 0;
#endif
	}

	void* SpStackMemoryAllocator::alloc(const sp_size size) noexcept
	{
		sp_assert(hasAvailableMemory(size), "OutOfMemoryException");

		void* buffer = currentPointer;

		currentPointer = (void*)((sp_size)currentPointer + size);

		sp_assert(((sp_size)lastPointer) > ((sp_size)currentPointer), "OutOfMemoryException");

		return buffer;
	}

	void* SpStackMemoryAllocator::copy(const void* source, sp_size size) noexcept
	{
		void* newBuffer = ALLOC_SIZE(size);

		std::memcpy(newBuffer, source, size);

		return newBuffer;
	}

	void SpStackMemoryAllocator::copy(const void* source, void* destiny, sp_size size) noexcept
	{
		std::memcpy(destiny, source, size);
	}

	void SpStackMemoryAllocator::resize(sp_size newSize) noexcept
	{
		initialPointer = std::realloc(initialPointer, newSize);

		sp_assert(initialPointer != NULL, "NullPointerException");

		currentPointer = initialPointer;
		lastPointer = (void*)((sp_size)initialPointer + newSize);
	}

	sp_bool SpStackMemoryAllocator::hasAvailableMemory(const sp_size size) noexcept
	{
		return ((sp_size)lastPointer - (sp_size)currentPointer - size) > ZERO_SIZE;
	}

	sp_size SpStackMemoryAllocator::memorySize() const noexcept
	{
		return (sp_size)lastPointer - (sp_size)initialPointer;
	}

	sp_size SpStackMemoryAllocator::availableMemorySize() noexcept
	{
		return (sp_size)lastPointer - (sp_size)currentPointer;
	}

	void SpStackMemoryAllocator::dispose() noexcept
	{
		if (initialPointer != NULL)
		{
			std::free(initialPointer);

			initialPointer = NULL;
			lastPointer = NULL;
			currentPointer = NULL;
		}
	}

	SpStackMemoryAllocator::~SpStackMemoryAllocator()
	{
		dispose();
	}
}