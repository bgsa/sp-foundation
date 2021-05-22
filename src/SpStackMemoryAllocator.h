#ifndef STACK_MEMORY_ALLOCATOR_HEADER
#define STACK_MEMORY_ALLOCATOR_HEADER

#include "BasePlatform.h"
#include "SpMemoryAllocator.h"
#include "Assertions.h"
#include <cstdlib>
#include <cstring>

#define ALLOC(type) (type*)NAMESPACE_FOUNDATION::SpStackMemoryAllocator::main()->alloc(sizeof(type))
#define ALLOC_SIZE(size) NAMESPACE_FOUNDATION::SpStackMemoryAllocator::main()->alloc(size)
#define ALLOC_ARRAY(type, count) (type*) NAMESPACE_FOUNDATION::SpStackMemoryAllocator::main()->alloc(sizeof(type) * count)
#define ALLOC_RELEASE(object) NAMESPACE_FOUNDATION::SpStackMemoryAllocator::main()->free(object)
#define ALLOC_COPY(source, Type, length) (Type*) NAMESPACE_FOUNDATION::SpStackMemoryAllocator::main()->copy(source, sizeof(Type) * length)
#define ALLOC_COPY_TO(source, destiny, type, count) NAMESPACE_FOUNDATION::SpStackMemoryAllocator::main()->copy(source, destiny, sizeof(type) * count)

#ifdef __cplusplus
	#define ALLOC_NEW(type) new (NAMESPACE_FOUNDATION::SpStackMemoryAllocator::main()->alloc(sizeof(type))) type
	#define ALLOC_NEW_ARRAY(type, count) new (NAMESPACE_FOUNDATION::SpStackMemoryAllocator::main()->alloc(sizeof(type) * count)) type[count]
	#define ALLOC_DELETE(object, type) object->~type(); NAMESPACE_FOUNDATION::SpStackMemoryAllocator::main()->free(object)
#endif

// 512MB
#define SP_STACK_MEMORY_DEFAULT_SIZE (sizeof(sp_char) * 1024 * 1024 * 512)

namespace NAMESPACE_FOUNDATION
{
	class SpStackMemoryAllocator
		: public SpMemoryAllocator
	{
	private:
		void* initialPointer = NULL;
		void* lastPointer = NULL;
		void* currentPointer = NULL;

	public:

		/// <summary>
		/// Default stack allocator
		/// </summary>
		API_INTERFACE static SpStackMemoryAllocator* main() noexcept;

		/// <summary>
		/// Define the initial size of memory
		/// </summary>
		API_INTERFACE void init(const sp_size initialSize) noexcept override;

		/// <summary>
		/// Get the memory size available in manager
		/// </summary>
		API_INTERFACE sp_size memorySize() const noexcept override;

		/// <summary>
		/// Get the current pointer address
		/// </summary>
		/// <returns>Memory address value</returns>
		API_INTERFACE sp_size currentAddress() const noexcept
		{
			return (sp_size)currentPointer;
		}

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
		API_INTERFACE void* alloc(const sp_size size) noexcept override;

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
		API_INTERFACE void resize(sp_size newSize) noexcept;

		/// <summary>
		/// Release the memory
		/// </summary>
		API_INTERFACE void free(void* buffers) noexcept override;

		/// <summary>
		/// Release all allocated memory in manager
		/// </summary>
		API_INTERFACE void dispose() noexcept override;


		API_INTERFACE ~SpStackMemoryAllocator();
	};
}

#endif // MEMORY_ALLOCATOR_MANAGER_HEADER