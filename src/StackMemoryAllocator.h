#ifndef STACK_MEMORY_ALLOCATOR_HEADER
#define STACK_MEMORY_ALLOCATOR_HEADER

#include "BasePlatform.h"

#ifdef WINDOWS
	#include "WindowsPlatform.h"
#else
	#include "LinuxPlatform.h"	
#endif

#include <cassert>
#include <cstdlib>
#include <cstring>

#define ALLOC(type) (type*)StackMemoryAllocator::main()->alloc(sizeof(type), ++StackMemoryAllocator::main()->stack_syncPreviousCounter)
#define ALLOC_SIZE(size) StackMemoryAllocator::main()->alloc(size, ++StackMemoryAllocator::main()->stack_syncPreviousCounter)
#define ALLOC_ARRAY(type, count) (type*) StackMemoryAllocator::main()->alloc(sizeof(type) * count, ++StackMemoryAllocator::main()->stack_syncPreviousCounter)
#define ALLOC_RELEASE(object) StackMemoryAllocator::main()->free(object, ++StackMemoryAllocator::main()->stack_syncPreviousCounter)
#define ALLOC_COPY(source, Type, length) (Type*) StackMemoryAllocator::main()->copy(source, sizeof(Type) * length)
#define ALLOC_COPY_TO(source, destiny, type, count) StackMemoryAllocator::main()->copy(source, destiny, sizeof(type) * count)

#ifdef __cplusplus
	#define ALLOC_NEW(type) new (StackMemoryAllocator::main()->alloc(sizeof(type), ++StackMemoryAllocator::main()->stack_syncPreviousCounter)) type
	#define ALLOC_NEW_ARRAY(type, count) new (StackMemoryAllocator::main()->alloc(sizeof(type) * count, ++StackMemoryAllocator::main()->stack_syncPreviousCounter)) type[count]
	#define ALLOC_DELETE(object, type) object->~type(); StackMemoryAllocator::main()->free(object, ++StackMemoryAllocator::main()->stack_syncPreviousCounter)
#endif

// 512MB
#define DEFAULT_MEMORY_SIZE SIZEOF_CHAR * 1024 * 1024 * 512 

class StackMemoryAllocator
{
private:
	void* initialPointer = NULL;
	void* lastPointer = NULL;
	void* currentPointer = NULL;

	sp_size stack_syncCounter;

public:
	sp_size stack_syncPreviousCounter;

	/// <summary>
	/// Default stack allocator
	/// </summary>
	API_INTERFACE static StackMemoryAllocator* main() noexcept;

	/// <summary>
	/// Define the initial size of memory
	/// </summary>
	API_INTERFACE void init(sp_size initialSize = DEFAULT_MEMORY_SIZE) noexcept;

	/// <summary>
	/// Get the memory size available in manager
	/// </summary>
	API_INTERFACE sp_size memorySize() noexcept;

	/// <summary>
	/// Get the RAM size in device
	/// </summary>
	API_INTERFACE static sp_size deviceMemorySize() noexcept;

	/// <summary>
	/// Get the available memory size in manager
	/// </summary>
	API_INTERFACE sp_size availableMemorySize() noexcept;

	/// <summary>
	/// Check if the manager has available memory
	/// </summary>
	API_INTERFACE sp_bool hasAvailableMemory(sp_size size) noexcept;

	/// <summary>
	/// Alloc in the memory
	/// </summary>
	API_INTERFACE void* alloc(sp_size size, sp_uint value) noexcept;

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
	API_INTERFACE void resize(sp_size newSize, sp_uint syncValue) noexcept;

	/// <summary>
	/// Release the memory
	/// </summary>
	API_INTERFACE void free(void* buffers, sp_uint syncValue) noexcept;
	
	/// <summary>
	/// Release all allocated memory in manager
	/// </summary>
	API_INTERFACE void release() noexcept;


	API_INTERFACE ~StackMemoryAllocator();
};

#undef DEFAULT_MEMORY_SIZE

#endif // MEMORY_ALLOCATOR_MANAGER_HEADER