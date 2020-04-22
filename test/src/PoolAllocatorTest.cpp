#include "SpectrumFoundationTest.h"

#define CLASS_NAME PoolAllocatorTest

namespace NAMESPACE_FOUNDATION_TEST
{
	SP_TEST_CLASS(CLASS_NAME)
	{
	public:
		SP_TEST_METHOD_DEF(alloc_Test1);
		SP_TEST_METHOD_DEF(alloc_Test2);
		SP_TEST_METHOD_DEF(defrag_Test1);
		SP_TEST_METHOD_DEF(alloc_PerformanceTest);
	};

	SP_TEST_METHOD(CLASS_NAME, alloc_Test1)
	{
		NAMESPACE_FOUNDATION_TEST::resetMemory();

		void* memoryAllocated = PoolMemoryAllocator::alloc(2 * SIZEOF_FLOAT);
		Assert::IsNotNull(memoryAllocated);
		Assert::AreEqual(ONE_SIZE, PoolMemoryAllocator::allocatedBlocks());

		const sp_size elements = DEFAULT_BLOCK_SIZE / SIZEOF_FLOAT;

		memoryAllocated = PoolMemoryAllocator::alloc(TWO_SIZE * elements * SIZEOF_FLOAT);
		Assert::IsNotNull(memoryAllocated);
		Assert::AreEqual(THREE_SIZE, PoolMemoryAllocator::allocatedBlocks());

		memoryAllocated = PoolMemoryAllocator::alloc(FOUR_SIZE * elements * SIZEOF_FLOAT);
		Assert::IsNotNull(memoryAllocated);
		Assert::AreEqual((sp_size)7u , PoolMemoryAllocator::allocatedBlocks());

		memoryAllocated = PoolMemoryAllocator::alloc(SIZEOF_CHAR);
		Assert::IsNotNull(memoryAllocated);
		Assert::AreEqual((sp_size)8u, PoolMemoryAllocator::allocatedBlocks());
	}

	SP_TEST_METHOD(CLASS_NAME, alloc_Test2)
	{
		NAMESPACE_FOUNDATION_TEST::resetMemory();

		void* memoryAllocated = PoolMemoryAllocator::alloc(FOUR_SIZE, TWO_SIZE * ONE_MEGABYTE);
		Assert::IsNotNull(memoryAllocated);
		Assert::AreEqual((sp_size)131072u, PoolMemoryAllocator::allocatedBlocks());
	}

	SP_TEST_METHOD(CLASS_NAME, defrag_Test1)
	{
		NAMESPACE_FOUNDATION_TEST::resetMemory();

		void* memoryAllocated1 = PoolMemoryAllocator::alloc(ONE_SIZE, SIZEOF_FLOAT);
		void* memoryAllocated2 = PoolMemoryAllocator::alloc(DEFAULT_BLOCK_SIZE_ADDRESS + 1, SIZEOF_FLOAT);
		void* memoryAllocated3 = PoolMemoryAllocator::alloc(ONE_SIZE, SIZEOF_FLOAT);

		Assert::AreEqual(FOUR_SIZE, PoolMemoryAllocator::allocatedBlocks());

		PoolMemoryAllocator::free(&memoryAllocated2);
		PoolMemoryAllocator::defrag();

		sp_size allocatedBlocks = PoolMemoryAllocator::allocatedBlocks();

		Assert::AreEqual(TWO_SIZE, allocatedBlocks);
	}

	SP_TEST_METHOD(CLASS_NAME, alloc_PerformanceTest)
	{
		NAMESPACE_FOUNDATION_TEST::resetMemory();

		std::chrono::high_resolution_clock::time_point  currentTime1 = std::chrono::high_resolution_clock::now();

		for (sp_size i = 0; i < 1000000; i++)
			PoolMemoryBlock* a = (PoolMemoryBlock*) PoolMemoryAllocator::alloc(16);

		std::chrono::high_resolution_clock::time_point  currentTime2 = std::chrono::high_resolution_clock::now();
		std::chrono::nanoseconds spent1 = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime2 - currentTime1);

		currentTime1 = std::chrono::high_resolution_clock::now();

		for (sp_size i = 0; i < 1000000; i++)
			PoolMemoryBlock* a = new PoolMemoryBlock[2];

		currentTime2 = std::chrono::high_resolution_clock::now();
		std::chrono::nanoseconds spent2 = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime2 - currentTime1);
	}

}
