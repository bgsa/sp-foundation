#ifndef SP_MEMORY_ALLOCATOR_HEADER
#define SP_MEMORY_ALLOCATOR_HEADER

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
#endif


namespace NAMESPACE_FOUNDATION
{
	class SpMemoryAllocator
	{
	public:

		API_INTERFACE virtual void init(const sp_size size) = 0;

		API_INTERFACE virtual sp_size firstAddress() const noexcept = 0;

		API_INTERFACE virtual sp_size currentAddress() const noexcept = 0;

		API_INTERFACE virtual void* alloc(const sp_size size) noexcept = 0;

		API_INTERFACE virtual void free(void* buffer) noexcept = 0;

		API_INTERFACE virtual sp_size memorySize() const noexcept = 0;

		API_INTERFACE virtual void dispose() = 0;

	};
}

#endif // SP_MEMORY_ALLOCATOR_HEADER