#include "SpectrumFoundationTest.h"
#include "SpString.h"
#include <mutex>

#define CLASS_NAME PoolAllocatorTest

namespace NAMESPACE_FOUNDATION_TEST
{
	SP_TEST_CLASS(CLASS_NAME)
	{
	private:
		std::mutex locker;

	public:
		SP_TEST_METHOD_DEF(alloc_Test1);
		SP_TEST_METHOD_DEF(alloc_Test2);
		SP_TEST_METHOD_DEF(alloc_Test3);
		SP_TEST_METHOD_DEF(free_Test1);
		SP_TEST_METHOD_DEF(free_Test2);
		SP_TEST_METHOD_DEF(free_Test3);
		
		SP_TEST_METHOD_DEF(alloc_PerformanceTest);
	};
	
	SP_TEST_METHOD(CLASS_NAME, alloc_Test1)
	{
		locker.lock();
		NAMESPACE_FOUNDATION_TEST::resetMemory();

		void* memoryAllocated = sp_mem_calloc(FOUR_SIZE, TWO_SIZE * ONE_MEGABYTE);
		Assert::IsNotNull(memoryAllocated);
		locker.unlock();
	}

	SP_TEST_METHOD(CLASS_NAME, alloc_Test2)
	{
		locker.lock();
		NAMESPACE_FOUNDATION_TEST::resetMemory();

		sp_size* memoryAllocated1 = (sp_size*)sp_mem_alloc(SIZEOF_FLOAT);
		sp_size* memoryAllocated2 = (sp_size*)sp_mem_alloc(SIZEOF_FLOAT);

		memoryAllocated1[0] = 10;
		memoryAllocated2[0] = 555;

		sp_mem_release(memoryAllocated2);

		sp_size* memoryAllocated3 = (sp_size*)sp_mem_alloc(TEN_UINT * SIZEOF_FLOAT);
		memoryAllocated3[0] = 200;

		Assert::AreEqual(ZERO_SIZE, SpPoolMemoryAllocator::main()->freedMemorySize());
		Assert::AreEqual(memoryAllocated2, memoryAllocated3);
		locker.unlock();
	}

	SP_TEST_METHOD(CLASS_NAME, alloc_Test3)
	{
		locker.lock();
		NAMESPACE_FOUNDATION_TEST::resetMemory();

		SpString* arr = sp_mem_new(SpString)[3];
		
		SpString* s1 = sp_mem_new(SpString)(1);
		s1->add('X');
		arr[0] = *s1;

		SpString* s2 = sp_mem_new(SpString)(2);
		s2->add('Y');
		s2->add('Z');
		arr[1] = *s2;

		SpString* s3 = sp_mem_new(SpString)(3);
		s3->add('A');
		s3->add('B');
		s3->add('C');
		arr[2] = *s3;

		locker.unlock();
	}

	SP_TEST_METHOD(CLASS_NAME, free_Test1)
	{
		locker.lock();
		NAMESPACE_FOUNDATION_TEST::resetMemory();

		sp_size* memoryAllocated1 = (sp_size*)sp_mem_alloc(SIZEOF_FLOAT);
		sp_size* memoryAllocated2 = (sp_size*)sp_mem_calloc(FOUR_SIZE + ONE_SIZE, SIZEOF_FLOAT);
		sp_size* memoryAllocated3 = (sp_size*)sp_mem_alloc(SIZEOF_FLOAT);

		memoryAllocated1[0] = 10;

		memoryAllocated2[0] = 2;
		memoryAllocated2[1] = 3;
		memoryAllocated2[2] = 4;

		memoryAllocated3[0] = 555;
		
		sp_mem_release(memoryAllocated2);

		Assert::AreEqual(ONE_SIZE, SpPoolMemoryAllocator::main()->freedMemorySize());
		locker.unlock();
	}

	SP_TEST_METHOD(CLASS_NAME, free_Test2)
	{
		locker.lock();
		NAMESPACE_FOUNDATION_TEST::resetMemory();

		sp_size* memoryAllocated1 = (sp_size*)sp_mem_alloc(SIZEOF_FLOAT);
		sp_size* memoryAllocated2 = (sp_size*)sp_mem_calloc(FOUR_SIZE + ONE_SIZE, SIZEOF_FLOAT);
		sp_size* memoryAllocated3 = (sp_size*)sp_mem_alloc(SIZEOF_FLOAT);

		memoryAllocated1[0] = 10;

		memoryAllocated2[0] = 2;
		memoryAllocated2[1] = 3;
		memoryAllocated2[2] = 4;

		memoryAllocated3[0] = 555;

		sp_mem_release(memoryAllocated2);
		Assert::AreEqual(ONE_SIZE, SpPoolMemoryAllocator::main()->freedMemorySize());

		sp_size* memoryAllocated4 = (sp_size*)sp_mem_alloc(SIZEOF_FLOAT);
		Assert::AreEqual(memoryAllocated2, memoryAllocated4);

		Assert::AreEqual(ONE_SIZE, SpPoolMemoryAllocator::main()->freedMemorySize());
		Assert::AreEqual(THREE_SIZE, (memoryAllocated4 + 1)[0]);
		locker.unlock();
	}

	SP_TEST_METHOD(CLASS_NAME, free_Test3)
	{
		locker.lock();
		NAMESPACE_FOUNDATION_TEST::resetMemory();

		sp_size* memoryAllocated1 = (sp_size*)sp_mem_alloc(SIZEOF_FLOAT);
		sp_size* memoryAllocated2 = (sp_size*)sp_mem_calloc(FOUR_SIZE + ONE_SIZE, SIZEOF_FLOAT);
		sp_size* memoryAllocated3 = (sp_size*)sp_mem_alloc(SIZEOF_FLOAT);

		memoryAllocated1[0] = 10;

		memoryAllocated2[0] = 2;
		memoryAllocated2[1] = 3;
		memoryAllocated2[2] = 4;

		memoryAllocated3[0] = 555;

		sp_mem_release(memoryAllocated2);
		Assert::AreEqual(ONE_SIZE, SpPoolMemoryAllocator::main()->freedMemorySize());

		sp_size* memoryAllocated4 = (sp_size*)sp_mem_calloc(FOUR_SIZE, SIZEOF_FLOAT);
		Assert::AreEqual(memoryAllocated2, memoryAllocated4);
		Assert::AreEqual(ZERO_SIZE, SpPoolMemoryAllocator::main()->freedMemorySize());
		locker.unlock();
	}

	SP_TEST_METHOD(CLASS_NAME, alloc_PerformanceTest)
	{
		locker.lock();
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
		locker.unlock();
	}

}
