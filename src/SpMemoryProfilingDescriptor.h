#ifndef SP_MEMORY_PROFILING_DESCRIPTOR_HEADER
#define SP_MEMORY_PROFILING_DESCRIPTOR_HEADER

#include "BasePlatform.h"

#if defined(WINDOWS)
	#include "WindowsPlatform.h"
#elif defined(LINUX)
	#include "LinuxPlatform.h"	
#elif defined(OSX)
	#include "OSXPlatform.h"	
#endif

#include <cstring>
#include "SpMemoryAllocator.h"

namespace NAMESPACE_FOUNDATION
{
	class SpMemoryProfilingDescriptor
	{
	public:
		sp_size address;
		sp_size size;
		sp_char* filename;
		sp_char* functionName;
		sp_uint line;

		API_INTERFACE inline SpMemoryProfilingDescriptor(const sp_size address, const sp_size size, const sp_char* filename, const sp_char* functionName, const sp_uint line)
		{
			this->address = address;
			this->size = size;
			this->line = line;

			const sp_size filenameLength = std::strlen(filename);
			this->filename = new sp_char[filenameLength + 1];
			std::memcpy(this->filename, filename, filenameLength);
			this->filename[filenameLength] = '\0';

			const sp_size functionNameLength = std::strlen(functionName);
			this->functionName = new sp_char[functionNameLength + 1];
			std::memcpy(this->functionName, functionName, functionNameLength);
			this->functionName[functionNameLength] = '\0';
		}

		API_INTERFACE inline void dispose()
		{
			address = 0;
			size = 0;
			line = 0;

			if (filename != nullptr)
			{
				delete[] filename;
				filename = nullptr;
			}

			if (functionName != nullptr)
			{
				delete[] functionName;
				functionName = nullptr;
			}
		}

		~SpMemoryProfilingDescriptor()
		{
			dispose();
		}

	};
}


#endif // SP_MEMORY_PROFILING_DESCRIPTOR_HEADER
