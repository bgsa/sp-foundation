#ifndef STACK_MEMORY_ALLOCATOR_HEADER
#define STACK_MEMORY_ALLOCATOR_HEADER

#ifdef WINDOWS
	#include "WindowsPlatform.h"
#else
	#include "LinuxPlatform.h"	
#endif

#include <cassert>
#include <cstdlib>
#include <cstring>

#define ALLOC(type) (type*)StackMemoryAllocator::alloc(sizeof(type), ++stack_syncPreviousCounter)
#define ALLOC_SIZE(size) StackMemoryAllocator::alloc(size, ++stack_syncPreviousCounter)
#define ALLOC_ARRAY(type, count) (type*) StackMemoryAllocator::alloc(sizeof(type) * count, ++stack_syncPreviousCounter)
#define ALLOC_RELEASE(object) StackMemoryAllocator::free(object, ++stack_syncPreviousCounter)
#define ALLOC_COPY(source, type, count) (type*) StackMemoryAllocator::copy(source, sizeof(type) * count, ++stack_syncPreviousCounter)
#define ALLOC_COPY_TO(source, destiny, type, count) StackMemoryAllocator::copy(source, destiny, sizeof(type) * count)

#ifdef __cplusplus
	#define ALLOC_NEW(type) new (StackMemoryAllocator::alloc(sizeof(type), ++stack_syncPreviousCounter)) type
	#define ALLOC_NEW_ARRAY(type, count) new (StackMemoryAllocator::alloc(sizeof(type) * count, ++stack_syncPreviousCounter)) type[count]
	#define ALLOC_DELETE(object, type) object->~type(); StackMemoryAllocator::free(object, ++stack_syncPreviousCounter)
#endif

// 512MB
#define DEFAULT_MEMORY_SIZE SIZEOF_CHAR * 1024 * 1024 * 512 

static sp_size stack_syncCounter = ONE_SIZE;
static sp_size stack_syncPreviousCounter = ZERO_SIZE;

class StackMemoryAllocator
{
private:
	StackMemoryAllocator();

public:

	/// <summary>
	/// Define the initial size of memory
	/// </summary>
	API_INTERFACE static void init(sp_size initialSize = DEFAULT_MEMORY_SIZE) noexcept;

	/// <summary>
	/// Get the memory size available in manager
	/// </summary>
	API_INTERFACE static sp_size memorySize() noexcept;

	/// <summary>
	/// Get the RAM size in device
	/// </summary>
	API_INTERFACE static sp_size deviceMemorySize() noexcept;

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
	API_INTERFACE static void* alloc(sp_size size, sp_uint value) noexcept;

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
	API_INTERFACE static void resize(sp_size newSize, sp_uint syncValue) noexcept;

	/// <summary>
	/// Release the memory
	/// </summary>
	API_INTERFACE static void free(void* buffers, sp_uint syncValue) noexcept;
	
	/// <summary>
	/// Release all allocated memory in manager
	/// </summary>
	API_INTERFACE static void release() noexcept;
};

#undef DEFAULT_MEMORY_SIZE

#endif // MEMORY_ALLOCATOR_MANAGER_HEADER