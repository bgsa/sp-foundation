#include "SpectrumFoundationTest.h"

#define CLASS_NAME PoolAllocatorTest

namespace NAMESPACE_FOUNDATION_TEST
{
	SP_TEST_CLASS(CLASS_NAME)
	{
	public:
		SP_TEST_METHOD_DEF(alloc_Test1);
		SP_TEST_METHOD_DEF(free_Test1);
		SP_TEST_METHOD_DEF(alloc_PerformanceTest);
	};
	
	SP_TEST_METHOD(CLASS_NAME, alloc_Test1)
	{
		NAMESPACE_FOUNDATION_TEST::resetMemory();

		void* memoryAllocated = sp_mem_calloc(FOUR_SIZE, TWO_SIZE * ONE_MEGABYTE);
		Assert::IsNotNull(memoryAllocated);
	}

	SP_TEST_METHOD(CLASS_NAME, free_Test1)
	{
		sp_size* memoryAllocated1 = (sp_size*)sp_mem_alloc(SIZEOF_FLOAT);
		sp_size* memoryAllocated2 = (sp_size*)sp_mem_calloc(FOUR_SIZE + ONE_SIZE, SIZEOF_FLOAT);
		sp_size* memoryAllocated3 = (sp_size*)sp_mem_alloc(SIZEOF_FLOAT);

		memoryAllocated1[0] = 10;

		memoryAllocated2[0] = 2;
		memoryAllocated2[1] = 3;
		memoryAllocated2[2] = 4;

		memoryAllocated3[0] = 555;
		
		sp_mem_release(memoryAllocated2);

		Assert::AreEqual(ONE_SIZE, PoolMemoryAllocator::main()->freedMemorySize());
	}

	SP_TEST_METHOD(CLASS_NAME, alloc_PerformanceTest)
	{
		NAMESPACE_FOUNDATION_TEST::resetMemory();

		std::chrono::high_resolution_clock::time_point  currentTime1 = std::chrono::high_resolution_clock::now();

		for (sp_size i = 0; i < 1000000; i++)
			sp_mem_alloc(16);

		std::chrono::high_resolution_clock::time_point  currentTime2 = std::chrono::high_resolution_clock::now();
		std::chrono::nanoseconds spent1 = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime2 - currentTime1);

		currentTime1 = std::chrono::high_resolution_clock::now();

		for (sp_size i = 0; i < 1000000; i++)
			new float[4];

		currentTime2 = std::chrono::high_resolution_clock::now();
		std::chrono::nanoseconds spent2 = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime2 - currentTime1);
	}

}
