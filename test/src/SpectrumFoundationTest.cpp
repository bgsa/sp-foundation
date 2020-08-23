#include "SpectrumFoundationTest.h"

namespace NAMESPACE_FOUNDATION_TEST
{
	API_INTERFACE void resetMemory()
	{
		PoolMemoryAllocator::main()->reset();
		tearDownModule();
		setupModule();
	}

	API_INTERFACE void setupModule()
	{
		StackMemoryAllocator::main()->init(ONE_MEGABYTE * 512);
	}
	API_INTERFACE void tearDownModule()
	{
		StackMemoryAllocator::main()->release();
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

#define CLASS_NAME SpectrumFoundationTest
	SP_TEST_CLASS(CLASS_NAME)
	{
	public:
		SP_TEST_METHOD_DEF(signTest);
	};

	SP_TEST_METHOD(CLASS_NAME, signTest)
	{
		sp_float result = sign(-100.0f);
		sp_float expected = -1.0f;
		Assert::AreEqual(expected, result, L"Wrong value");

		result = sign(100.0f);
		expected = 1.0f;
		Assert::AreEqual(expected, result, L"Wrong value");
	
		result = sign(0.0f);
		expected = 0.0f;
		Assert::AreEqual(expected, result, L"Wrong value");
	}
#undef CLASS_NAME

}