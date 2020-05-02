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
		SP_TEST_METHOD_DEF(operatorSubscript_Test1);
		SP_TEST_METHOD_DEF(clear_Test1);
		SP_TEST_METHOD_DEF(reserve_Test1);
		SP_TEST_METHOD_DEF(count_Test1);
		SP_TEST_METHOD_DEF(indexOf_Test1);
		SP_TEST_METHOD_DEF(startWith_Char_Test1);
		SP_TEST_METHOD_DEF(startWith_CharArray_Test1);
		SP_TEST_METHOD_DEF(dispose_Test1);
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
		Assert::AreEqual(TWO_UINT, arr.length());
	}

	SP_TEST_METHOD(CLASS_NAME, operatorSubscript_Test1)
	{
		SpString arr(TEN_UINT);
		arr.add('1');
		arr.add('2');
		arr.add('3');
		arr[1] = 'X';

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

	SP_TEST_METHOD(CLASS_NAME, reserve_Test1)
	{
		SpString arr(TEN_UINT);
		Assert::AreEqual(arr.length(), ZERO_UINT);

		arr.reserve(THREE_UINT);		
		Assert::AreEqual(arr.length(), THREE_UINT);
	}

	SP_TEST_METHOD(CLASS_NAME, count_Test1)
	{
		SpString arr("Teste do T de taTu");
		sp_uint result = arr.count('T');
		Assert::AreEqual(THREE_UINT, result);

		arr = "Teste do T de taTu";
		result = arr.count('t');
		Assert::AreEqual(TWO_UINT, result);
	}

	SP_TEST_METHOD(CLASS_NAME, indexOf_Test1)
	{
		SpString arr("Teste do T de taTu");
		sp_uint result = arr.indexOf('T');
		Assert::AreEqual(ZERO_UINT, result);

		arr = "Teste do T de taTu";
		result = arr.indexOf('d');
		Assert::AreEqual(6u, result);
	}

	SP_TEST_METHOD(CLASS_NAME, startWith_Char_Test1)
	{
		SpString arr("Teste do T de taTu");
		Assert::IsTrue(arr.startWith('T'));

		arr = "Teste do T de taTu";
		Assert::IsFalse(arr.startWith(' '));

		arr = "Teste do T de taTu";
		Assert::IsFalse(arr.startWith('e'));
	}

	SP_TEST_METHOD(CLASS_NAME, startWith_CharArray_Test1)
	{
		SpString arr("Teste do T de taTu");
		Assert::IsTrue(arr.startWith("Teste do T de ta"));

		arr = "Teste do T de taTu";
		Assert::IsFalse(arr.startWith("Teste do t de"));

		arr = "Teste do T de taTu";
		Assert::IsFalse(arr.startWith("este do T"));

		arr = "Teste do T de taTu";
		Assert::IsFalse(arr.startWith(" Teste do T"));
	}

	SP_TEST_METHOD(CLASS_NAME, dispose_Test1)
	{
		SpString* arr1 = sp_mem_new(SpString)("Teste do T de taTu");
		sp_mem_delete(arr1, SpString);

		SpString* arr2 = sp_mem_new(SpString)("Teste do T de taTu");
		sp_mem_delete(arr2, SpString);

		Assert::AreEqual((sp_size)arr1, (sp_size)arr2);
	}

}
