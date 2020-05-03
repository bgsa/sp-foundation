#include "StackMemoryAllocator.h"

static StackMemoryAllocator* instance = new StackMemoryAllocator();

StackMemoryAllocator* StackMemoryAllocator::main() noexcept
{
	return instance;
}

void StackMemoryAllocator::init(const sp_size initialSize) noexcept
{
	initialPointer = std::malloc(initialSize);

	sp_assert(initialPointer != NULL);

	currentPointer = initialPointer;
	lastPointer = (void*) ((sp_size)initialPointer + initialSize);

	stack_syncCounter = ONE_SIZE;
	stack_syncPreviousCounter = ZERO_SIZE;
}

void StackMemoryAllocator::free(void* buffer, sp_uint syncValue) noexcept
{
	while (stack_syncCounter != syncValue) {}

	sp_assert(buffer != NULL);
	sp_assert(buffer >= initialPointer && buffer <= lastPointer);

	if (currentPointer > buffer) // memory has already freed by previous pointer
		currentPointer = buffer;

	stack_syncCounter++;
}

sp_size StackMemoryAllocator::deviceMemorySize() noexcept
{
#ifdef WINDOWS
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	return (sp_size) status.ullTotalPhys;
#elif UNIX
	//return vmsize.t_rm;
	return 0;
#endif
}

void* StackMemoryAllocator::alloc(const sp_size size, sp_uint syncValue) noexcept
{
	while (stack_syncCounter != syncValue) { }

	sp_assert(hasAvailableMemory(size));

	void* buffer = currentPointer;

	currentPointer = (void*) ((sp_size)currentPointer + size);

	sp_assert(((sp_size)lastPointer) > ((sp_size)currentPointer));

	stack_syncCounter++;
	return buffer;
}

void* StackMemoryAllocator::copy(const void* source, sp_size size) noexcept
{
	void* newBuffer = ALLOC_SIZE(size);

	std::memcpy(newBuffer, source, size);

	return newBuffer;
}

void StackMemoryAllocator::copy(const void* source, void* destiny, sp_size size) noexcept
{
	std::memcpy(destiny, source, size);
}

void StackMemoryAllocator::resize(sp_size newSize, sp_uint syncValue) noexcept
{
	while (stack_syncCounter != syncValue) { }

	initialPointer = std::realloc(initialPointer, newSize);

	sp_assert(initialPointer != NULL);

	currentPointer = initialPointer;
	lastPointer = (void*) ((sp_size)initialPointer + newSize);

	stack_syncCounter++;
}

sp_bool StackMemoryAllocator::hasAvailableMemory(const sp_size size) noexcept
{
	return ((sp_size)lastPointer - (sp_size)currentPointer - size) > ZERO_SIZE;
}

sp_size StackMemoryAllocator::memorySize() noexcept
{
	return (sp_size)lastPointer - (sp_size)initialPointer;
}

sp_size StackMemoryAllocator::availableMemorySize() noexcept
{
	return (sp_size)lastPointer - (sp_size)currentPointer;
}

void StackMemoryAllocator::release() noexcept
{
	if (initialPointer != NULL)
	{
		std::free(initialPointer);

		initialPointer = NULL;
		lastPointer = NULL;
		currentPointer = NULL;

		stack_syncCounter = ONE_SIZE;
		stack_syncPreviousCounter = ZERO_SIZE;
	}
}

StackMemoryAllocator::~StackMemoryAllocator()
{
	release();
}