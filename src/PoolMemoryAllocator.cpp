#include "PoolMemoryAllocator.h"

namespace SpFoundation
{
	static PoolMemoryAllocator* instance = new PoolMemoryAllocator(SP_DEFAULT_MEMORY_SIZE);

	PoolMemoryAllocator* PoolMemoryAllocator::main()
	{
		return instance;
	}
}