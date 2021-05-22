#include "SpectrumFoundationTest.h"
#include "SpVector.h"

#define CLASS_NAME SpVectorTest

namespace NAMESPACE_FOUNDATION_TEST
{
	SP_TEST_CLASS(CLASS_NAME)
	{
	public:
		SP_TEST_METHOD_DEF(add);
		SP_TEST_METHOD_DEF(length);
		SP_TEST_METHOD_DEF(dispose);
		SP_TEST_METHOD_DEF(remove);
		SP_TEST_METHOD_DEF(find);
	};
	
	SP_TEST_METHOD(CLASS_NAME, add)
	{
		SpVector<sp_int> vec;
		SpVectorItem<sp_int>* item1 = vec.add(TWO_INT);
		SpVectorItem<sp_int>* item2 = vec.add(FOUR_INT);

		Assert::AreEqual(TWO_INT, vec[0]);
		Assert::AreEqual(FOUR_INT, vec[1]);

		Assert::IsTrue(item1->previous() == NULL);
		Assert::IsTrue(item1 == item2->previous());

		Assert::IsTrue(item1->next() == item2);
	}

	SP_TEST_METHOD(CLASS_NAME, remove)
	{
		SpVector<sp_int> vec;
		SpVectorItem<sp_int>* item1 = vec.add(TWO_INT);
		SpVectorItem<sp_int>* item2 = vec.add(FOUR_INT);
		SpVectorItem<sp_int>* item3 = vec.add(6);
		Assert::AreEqual(THREE_UINT, vec.length());

		vec.remove(item2);

		Assert::AreEqual(TWO_UINT, vec.length());
		Assert::AreEqual(TWO_INT, vec[0]);
		Assert::AreEqual(6, vec[1]);

		SpVectorItem<sp_int>* item4 = vec.add(TEN_INT);

		vec.remove(item1);

		Assert::AreEqual(TWO_UINT, vec.length());
		Assert::AreEqual(6, vec[0]);
		Assert::AreEqual(TEN_INT, vec[1]);

		SpVectorItem<sp_int>* item5 = vec.add(12);

		vec.remove(item5);

		Assert::AreEqual(TWO_UINT, vec.length());
		Assert::AreEqual(6, vec[0]);
		Assert::AreEqual(TEN_INT, vec[1]);
	}

	SP_TEST_METHOD(CLASS_NAME, find)
	{
		SpVector<sp_int> vec;
		SpVectorItem<sp_int>* item1 = vec.add(TWO_INT);
		SpVectorItem<sp_int>* item2 = vec.add(FOUR_INT);
		SpVectorItem<sp_int>* item3 = vec.add(THREE_INT);

		Assert::AreEqual(TWO_INT, vec.find(ZERO_UINT)->value());
		Assert::AreEqual(FOUR_INT, vec.find(ONE_UINT)->value());
		Assert::AreEqual(THREE_INT, vec.find(TWO_UINT)->value());
	}

	SP_TEST_METHOD(CLASS_NAME, length)
	{
		SpVector<sp_int> vec;
		vec.add(TWO_INT);
		vec.add(FOUR_INT);

		Assert::AreEqual(TWO_UINT, vec.length());
	}

	SP_TEST_METHOD(CLASS_NAME, dispose)
	{
		SpVector<sp_int> vec1;
		SpVectorItem<sp_int>* item1 = vec1.add(TWO_INT);
		SpVectorItem<sp_int>* item2  = vec1.add(FOUR_INT);

		vec1.dispose();

		sp_int* arrInt1 = (sp_int*)sp_mem_calloc(2u, sizeof(sp_int));
		sp_int* arrInt2 = (sp_int*)sp_mem_calloc(2u, sizeof(sp_int));
		arrInt1[0] = 1;
		arrInt1[1] = 2;
		arrInt2[0] = 3;
		arrInt2[1] = 4;

		SpVector<sp_int*> vec2;
		vec2.add(arrInt1);
		vec2.add(arrInt2);

		Assert::AreEqual(1, vec2[0][0]);
		Assert::AreEqual(2, vec2[0][1]);
		Assert::AreEqual(3, vec2[1][0]);
		Assert::AreEqual(4, vec2[1][1]);

		vec2.dispose();
	}

}
