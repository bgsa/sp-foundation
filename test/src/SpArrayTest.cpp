#include "SpectrumFoundationTest.h"
#include "SpArray.h"

#define CLASS_NAME SpArrayTest

namespace NAMESPACE_FOUNDATION_TEST
{
	SP_TEST_CLASS(CLASS_NAME)
	{
	public:
		SP_TEST_METHOD_DEF(constructor_Test1);
		SP_TEST_METHOD_DEF(length_Test1);
		SP_TEST_METHOD_DEF(add_Test1);
		SP_TEST_METHOD_DEF(set_Test1);
	};
	
	SP_TEST_METHOD(CLASS_NAME, constructor_Test1)
	{
		SpArray<sp_char> arr(TEN_SIZE);

		Assert::AreEqual(ZERO_SIZE, arr.length());
		Assert::AreEqual(TEN_SIZE, arr.allocatedLength());
	}

	SP_TEST_METHOD(CLASS_NAME, length_Test1)
	{
		SpArray<sp_char> arr(TEN_SIZE);
		arr.add('1');
		arr.add('2');

		Assert::AreEqual(TWO_SIZE, arr.length());
	}

	SP_TEST_METHOD(CLASS_NAME, add_Test1)
	{
		SpArray<sp_char> arr(TEN_SIZE);
		arr.add('1');
		arr.add('2');

		Assert::AreEqual(arr[0], '1');
		Assert::AreEqual(arr[1], '2');
	}

	SP_TEST_METHOD(CLASS_NAME, set_Test1)
	{
		SpArray<sp_char> arr(TEN_SIZE);
		arr.add('1');
		arr.add('2');
		arr.add('3');
		arr.set(1, 'X');

		Assert::AreEqual(arr[0], '1');
		Assert::AreEqual(arr[1], 'X');
		Assert::AreEqual(arr[2], '3');
	}

}
