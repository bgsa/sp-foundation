#ifndef SP_MEMORY_PROFILING_HEADER
#define SP_MEMORY_PROFILING_HEADER

#include "BasePlatform.h"

#if defined(WINDOWS)
	#include "WindowsPlatform.h"
#elif defined(LINUX)
	#include "LinuxPlatform.h"	
#elif defined(OSX)
	#include "OSXPlatform.h"	
#endif

#include "SpMemoryAllocator.h"
#include "SpMemoryProfilingDescriptor.h"
#include <map>

namespace NAMESPACE_FOUNDATION
{
	class SpMemoryProfiling
	{
	public:
		std::map<sp_size, SpMemoryProfilingDescriptor*> allocations;

		API_INTERFACE inline SpMemoryProfiling()
		{
		}

		API_INTERFACE inline void dispose()
		{
		}

		API_INTERFACE inline void alloc(const sp_size address, const sp_size size, const sp_char* filename, const sp_char* functionName, const sp_uint line)
		{
			allocations.emplace(address, new SpMemoryProfilingDescriptor(address, size, filename, functionName, line));
		}

		API_INTERFACE inline void free(const sp_size address)
		{
			SpMemoryProfilingDescriptor* descriptor = allocations[address];
			delete descriptor;

			allocations.erase(address);
		}
		
		API_INTERFACE static void init();
		API_INTERFACE static void release();

		~SpMemoryProfiling()
		{
			dispose();
		}

	};

	extern SpMemoryProfiling* SpMemoryProfilingInstance;
}

#endif // SP_MEMORY_PROFILING_HEADER