#include "SpectrumFoundationTest.h"
#include "SpString.h"

#define CLASS_NAME SpStringTest

namespace NAMESPACE_FOUNDATION_TEST
{
	SP_TEST_CLASS(CLASS_NAME)
	{
	public:
		SP_TEST_METHOD_DEF(constructor_Test1);
		SP_TEST_METHOD_DEF(length_Test1);
		SP_TEST_METHOD_DEF(add_Test1);
		SP_TEST_METHOD_DEF(set_Test1);
		SP_TEST_METHOD_DEF(clear_Test1);
	};
	
	SP_TEST_METHOD(CLASS_NAME, constructor_Test1)
	{
		SpString* arr = sp_mem_new(SpString)(TEN_SIZE);
		arr->add('a');
		arr->add('b');
		arr->add('c');
		arr->add('d');
		arr->add('e');
		arr->add('f');
		arr->add('g');
		arr->add('h');
		arr->add('i');
		arr->add('j');


		Assert::AreEqual(TEN_SIZE, arr->length());
		Assert::AreEqual(TEN_SIZE + ONE_SIZE, arr->allocatedLength());
		sp_mem_delete(arr, SpString);
	}

	SP_TEST_METHOD(CLASS_NAME, length_Test1)
	{
		SpString arr(TEN_SIZE);
		arr.add('1');
		arr.add('2');

		Assert::AreEqual(TWO_SIZE, arr.length());
	}

	SP_TEST_METHOD(CLASS_NAME, add_Test1)
	{
		SpString arr(TEN_SIZE);
		arr.add('1');
		arr.add('2');

		Assert::AreEqual(arr[0], '1');
		Assert::AreEqual(arr[1], '2');
	}

	SP_TEST_METHOD(CLASS_NAME, set_Test1)
	{
		SpString arr(TEN_SIZE);
		arr.add('1');
		arr.add('2');
		arr.add('3');
		arr.set(1, 'X');

		Assert::AreEqual(arr[0], '1');
		Assert::AreEqual(arr[1], 'X');
		Assert::AreEqual(arr[2], '3');
	}

	SP_TEST_METHOD(CLASS_NAME, clear_Test1)
	{
		SpString arr(TEN_SIZE);
		arr.add('1');
		arr.add('2');
		arr.add('3');

		Assert::AreEqual(THREE_SIZE, arr.length());
		
		arr.clear();
		Assert::AreEqual(ZERO_SIZE, arr.length());

		arr.add('W');
		Assert::AreEqual(ONE_SIZE, arr.length());
		Assert::AreEqual('W', arr[0]);
	}

}
