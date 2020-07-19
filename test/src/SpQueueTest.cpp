#include "SpectrumFoundationTest.h"
#include "SpQueue.h"

#define CLASS_NAME SpQueueTest

namespace NAMESPACE_FOUNDATION_TEST
{
	SP_TEST_CLASS(CLASS_NAME)
	{
	public:
		SP_TEST_METHOD_DEF(push);
		SP_TEST_METHOD_DEF(length);
		SP_TEST_METHOD_DEF(isEmpty);
		SP_TEST_METHOD_DEF(pop);
		SP_TEST_METHOD_DEF(front);
	};
	
	SP_TEST_METHOD(CLASS_NAME, push)
	{
		SpQueue<sp_int> queue;
		SpQueueItem<sp_int>* item1 = queue.push(TWO_INT);
		SpQueueItem<sp_int>* item2 = queue.push(FOUR_INT);

		Assert::AreEqual(TWO_INT, item1->value());
		Assert::AreEqual(FOUR_INT, item2->value());
	}

	SP_TEST_METHOD(CLASS_NAME, length)
	{
		SpQueue<sp_int> queue;
		SpQueueItem<sp_int>* item1 = queue.push(TWO_INT);
		SpQueueItem<sp_int>* item2 = queue.push(FOUR_INT);

		Assert::AreEqual(TWO_UINT, queue.length());

		queue.pop();

		Assert::AreEqual(ONE_UINT, queue.length());
	}

	SP_TEST_METHOD(CLASS_NAME, isEmpty)
	{
		SpQueue<sp_int> queue;

		Assert::AreEqual(true, queue.isEmpty());

		SpQueueItem<sp_int>* item1 = queue.push(TWO_INT);
		SpQueueItem<sp_int>* item2 = queue.push(FOUR_INT);

		Assert::AreEqual(false, queue.isEmpty());
		queue.pop();
		Assert::AreEqual(false, queue.isEmpty());
		queue.pop();
		Assert::AreEqual(true, queue.isEmpty());
	}

	SP_TEST_METHOD(CLASS_NAME, pop)
	{
		SpQueue<sp_int> queue;
		SpQueueItem<sp_int>* item1 = queue.push(TWO_INT);
		SpQueueItem<sp_int>* item2 = queue.push(FOUR_INT);

		sp_int expected = TWO_UINT;
		Assert::AreEqual(expected, queue.pop());

		expected = FOUR_UINT;
		Assert::AreEqual(expected, queue.pop());

		Assert::AreEqual(ZERO_UINT, queue.length());
	}

	SP_TEST_METHOD(CLASS_NAME, front)
	{
		SpQueue<sp_int> queue;
		SpQueueItem<sp_int>* item1 = queue.push(TWO_INT);
		SpQueueItem<sp_int>* item2 = queue.push(FOUR_INT);

		sp_int expected = TWO_UINT;
		Assert::AreEqual(expected, queue.front());

		expected = TWO_UINT;
		Assert::AreEqual(expected, queue.front());

		queue.pop();

		expected = FOUR_UINT;
		Assert::AreEqual(expected, queue.front());

		Assert::AreEqual(ONE_UINT, queue.length());
	}

}
