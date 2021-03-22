#include "SpPoolMemoryAllocator.h"

namespace NAMESPACE_FOUNDATION
{
	static SpPoolMemoryAllocator* instance = new SpPoolMemoryAllocator(SP_POOL_MEMORY_DEFAULT_SIZE);

	SpPoolMemoryAllocator* SpPoolMemoryAllocator::main()
	{
		return instance;
	}
}