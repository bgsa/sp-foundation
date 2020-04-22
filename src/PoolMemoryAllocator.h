#ifndef POOL_MEMORY_ALLOCATOR_HEADER
#define POOL_MEMORY_ALLOCATOR_HEADER

#ifdef WINDOWS
	#include "WindowsPlatform.h"
#else
	#include "LinuxPlatform.h"	
#endif

#include <cassert>
#include <cstring>
#include <atomic>
#include <stack>

#define DEFAULT_MEMORY_SIZE (ONE_MEGABYTE * 512)
#define DEFAULT_BLOCK_SIZE 64             // 16 (elements) * 4 (bytes) = 16 elements of 4 bytes
#define DEFAULT_BLOCK_SIZE_BIT_DIVISOR 6  // DEFAULT_BLOCK_SIZE >> BIT = 1
#define DEFAULT_BLOCK_SIZE_ADDRESS    16  // DEFAULT_BLOCK_SIZE / SIZEOF_INT  (blocksize / bytes in addres bucket)

#define SP_BLOCK_INDEX(value, initialPointer, mapMemorySize) \
				((value - initialPointer - mapMemorySize) / DEFAULT_BLOCK_SIZE_ADDRESS)

class PoolMemoryBlock
{
public:
	void* pointer;
	sp_size size;

	PoolMemoryBlock() { }

	inline PoolMemoryBlock(sp_size* pointer, sp_size size)
	{
		this->pointer = pointer;
		this->size = size;
	}

	inline sp_size blocks()
	{
		return sp_ceilBit(size, DEFAULT_BLOCK_SIZE_ADDRESS, DEFAULT_BLOCK_SIZE_BIT_DIVISOR);
	}
};

class PoolMemoryAllocator
{
private:
	PoolMemoryAllocator();

public:

	/// <summary>
	/// Define the initial size of memory
	/// </summary>
	API_INTERFACE static void init(sp_size initialSize = DEFAULT_MEMORY_SIZE) noexcept;

	/// <summary>
	/// Get the block index allocated by the pointer
	/// </summary>
	API_INTERFACE static sp_size blockIndex(void* buffer) noexcept;
	
	/// <summary>
	/// Get the RAM size in device
	/// </summary>
	API_INTERFACE static sp_size deviceMemorySize() noexcept;

	/// <summary>
	/// Get the length of allocated blocks
	/// </summary>
	API_INTERFACE static sp_size allocatedBlocks() noexcept;

	/// <summary>
	/// Get the available memory size in manager
	/// </summary>
	API_INTERFACE static sp_size availableMemorySize() noexcept;

	/// <summary>
	/// Check if the manager has available memory
	/// </summary>
	API_INTERFACE static sp_bool hasAvailableMemory(sp_size size) noexcept;

	/// <summary>
	/// Alloc in the memory
	/// </summary>
	API_INTERFACE static void* alloc(sp_size size) noexcept;

	/// <summary>
	/// Alloc (count * size) in the memory
	/// </summary>
	API_INTERFACE static void* alloc(sp_size count, sp_size size) noexcept;

	/// <summary>
	/// Copy the source to a new memory buffer
	/// </summary>
	API_INTERFACE static void* copy(const void* source, sp_size size) noexcept;

	/// <summary>
	/// Copy the source to the destiny
	/// </summary>
	API_INTERFACE static void copy(const void* source, void* destiny, sp_size size) noexcept;

	/// <summary>
	/// Resize the current memory in manager
	/// </summary>
	API_INTERFACE static void resize(sp_size newSize) noexcept;

	/// <summary>
	/// Release the memory
	/// </summary>
	API_INTERFACE static void free(void** buffers) noexcept;

	/// <summary>
	/// Defrag the last memory freed.
	/// </summary>
	API_INTERFACE static void defrag() noexcept;
	
	/// <summary>
	/// Release all allocated memory in manager
	/// </summary>
	API_INTERFACE static void release() noexcept;
};

#undef DEFAULT_MEMORY_SIZE

#endif // POOL_ALLOCATOR_MANAGER_HEADER