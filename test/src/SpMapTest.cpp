#include "SpectrumFoundationTest.h"
#include "SpMap.h"
#include "SpString.h"

#define CLASS_NAME SpMapTest

namespace NAMESPACE_FOUNDATION_TEST
{
	SP_TEST_CLASS(CLASS_NAME)
	{
	public:
		SP_TEST_METHOD_DEF(constructor);
		SP_TEST_METHOD_DEF(add);
		SP_TEST_METHOD_DEF(find);
		SP_TEST_METHOD_DEF(remove);
		SP_TEST_METHOD_DEF(operator_subscript);
	};
	
	SP_TEST_METHOD(CLASS_NAME, constructor)
	{
		SpMap<sp_uint, sp_uint>* map = sp_mem_new_templated2(SpMap, sp_uint, sp_uint)();

		Assert::AreEqual(ZERO_UINT, map->length());
	}

	SP_TEST_METHOD(CLASS_NAME, add)
	{
		SpMap<sp_uint, SpString*>* map = sp_mem_new_templated2(SpMap, sp_uint, SpString*)();
		SpString* str1 = sp_mem_new(SpString)("Value 1");

		map->add(str1->hashCode(), str1);

		Assert::AreEqual(ONE_UINT, map->length());

		sp_mem_delete(str1, SpString);
		sp_mem_delete(map, SpMap);
	}

	SP_TEST_METHOD(CLASS_NAME, find)
	{
		SpMap<sp_uint, SpString*>* map = sp_mem_new_templated2(SpMap, sp_uint, SpString*)();
		SpString* str1 = sp_mem_new(SpString)("Value 1");
		map->add(str1->hashCode(), str1);

		SpString* str2 = map->find(str1->hashCode());

		Assert::IsTrue(str1->equals(str2));

		sp_mem_delete(str1, SpString);
		sp_mem_delete(map, SpMap);
	}

	SP_TEST_METHOD(CLASS_NAME, remove)
	{
		SpMap<sp_uint, SpString*>* map = sp_mem_new_templated2(SpMap, sp_uint, SpString*)();
		SpString* str1 = sp_mem_new(SpString)("Value 1");
		map->add(str1->hashCode(), str1);

		map->remove(str1->hashCode());

		Assert::AreEqual(ZERO_UINT, map->length());

		sp_mem_delete(str1, SpString);
		sp_mem_delete(map, SpMap);
	}

	SP_TEST_METHOD(CLASS_NAME, operator_subscript)
	{
		SpMap<sp_uint, SpString*>* map = sp_mem_new_templated2(SpMap, sp_uint, SpString*)();
		SpString* str1 = sp_mem_new(SpString)("Value 1");
		map->add(str1->hashCode(), str1);

		SpString* str2 = map[0][str1->hashCode()];

		Assert::IsTrue(str1->equals(str2));

		sp_mem_delete(str1, SpString);
		sp_mem_delete(map, SpMap);
	}

}
