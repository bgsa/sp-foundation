#ifndef MEMORY_ALLOCATOR_MANAGER_HEADER
#define MEMORY_ALLOCATOR_MANAGER_HEADER

#include <cassert>
#include <mutex>

#define ALLOC(type) (type*)MemoryAllocatorManager::alloc(sizeof(type))
#define ALLOC_SIZE(size) MemoryAllocatorManager::alloc(size)
#define ALLOC_ARRAY(type, count) (type*) MemoryAllocatorManager::alloc(sizeof(type) * count)
#define ALLOC_RELEASE(object) MemoryAllocatorManager::free(object)
#define ALLOC_COPY(source, type, count) (type*) MemoryAllocatorManager::copy(source, sizeof(type) * count)
#define ALLOC_COPY_TO(source, destiny, type, count) MemoryAllocatorManager::copy(source, destiny, sizeof(type) * count)

#ifdef __cplusplus
	#define ALLOC_NEW(type) new (MemoryAllocatorManager::alloc(sizeof(type))) type
	#define ALLOC_NEW_ARRAY(type, count) new (MemoryAllocatorManager::alloc(sizeof(type) * count)) type[count]
	#define ALLOC_DELETE(object, type) object->~type(); MemoryAllocatorManager::free(object)
#endif

// 512MB
#define DEFAULT_MEMORY_SIZE sizeof(char) * 1024 * 1024 * 512 

class MemoryAllocatorManager
{
private:
	MemoryAllocatorManager();

public:

	/// <summary>
	/// Define the initial size of memory
	/// </summary>
	static void init(size_t initialSize = DEFAULT_MEMORY_SIZE) noexcept;

	/// <summary>
	/// Get the memory size available in manager
	/// </summary>
	static size_t memorySize() noexcept;

	/// <summary>
	/// Get the RAM size in device
	/// </summary>
	static size_t deviceMemorySize() noexcept;

	/// <summary>
	/// Get the available memory size in manager
	/// </summary>
	static size_t availableMemorySize() noexcept;

	/// <summary>
	/// Check if the manager has available memory
	/// </summary>
	static bool hasAvailableMemory(size_t size) noexcept;

	/// <summary>
	/// Alloc in the memory
	/// </summary>
	static void* alloc(size_t size) noexcept;

	/// <summary>
	/// Alloc (count * size) in the memory
	/// </summary>
	static void* alloc(size_t count, size_t size) noexcept;

	/// <summary>
	/// Copy the source to a new memory buffer
	/// </summary>
	static void* copy(const void* source, size_t size) noexcept;

	/// <summary>
	/// Copy the source to the destiny
	/// </summary>
	static void copy(const void* source, void* destiny, size_t size) noexcept;

	/// <summary>
	/// Resize the current memory in manager
	/// </summary>
	static void resize(size_t newSize) noexcept;

	/// <summary>
	/// Release the memory
	/// </summary>
	static void free(void* buffers) noexcept;
	
	/// <summary>
	/// Release all allocated memory in manager
	/// </summary>
	static void release() noexcept;
};

#undef DEFAULT_MEMORY_SIZE

#endif // MEMORY_ALLOCATOR_MANAGER_HEADER