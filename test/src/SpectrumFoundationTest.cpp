#include "SpectrumFoundationTest.h"

namespace NAMESPACE_FOUNDATION_TEST
{
	API_INTERFACE void resetMemory()
	{
		tearDownModule();
		setupModule();
	}

	API_INTERFACE void setupModule()
	{
		StackMemoryAllocator::init(ONE_MEGABYTE * 512);
		PoolMemoryAllocator::init(ONE_MEGABYTE * 512);
	}
	API_INTERFACE void tearDownModule()
	{
		StackMemoryAllocator::release();
		PoolMemoryAllocator::release();
	}

#ifdef MSTEST_ENABLED
	TEST_MODULE_INITIALIZE(ModuleInitialize)
	{
		setupModule();
	}
	TEST_MODULE_CLEANUP(ModuleCleanup)
	{
		tearDownModule();
	}
#endif // MSTEST_ENABLED

}