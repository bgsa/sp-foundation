#ifndef SP_QUEUE_HEADER
#define SP_QUEUE_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	template <typename T>
	class SpQueueItem
	{
		template <typename T> 
		friend class SpQueue;

	private:
		T _value;
		SpQueueItem* _next;

	public:

		API_INTERFACE SpQueueItem(const T& item)
		{
			this->_value = item;
			_next = nullptr;
		}

		API_INTERFACE inline T& value()
		{
			return _value;
		}

		API_INTERFACE inline SpQueueItem* next() const
		{
			return _next;
		}

	};

	template <typename T>
	class SpQueue
	{
	private:
		SpQueueItem<T>* _head;
		SpQueueItem<T>* _tail;
		sp_uint _length;

	public:
		
		API_INTERFACE SpQueue()
		{
			_head = nullptr;
			_tail = nullptr;
			_length = ZERO_UINT;
		}

		API_INTERFACE inline SpQueueItem<T>* push(const T& item)
		{
			if (_tail == nullptr)
			{
				_tail = sp_mem_new(SpQueueItem<T>)(item);
				_head = _tail;
			}
			else
			{
				_tail->_next = sp_mem_new(SpQueueItem<T>)(item);
				_tail = _tail->_next;
			}

			_length++;
			return _tail;
		}

		API_INTERFACE inline T& pop()
		{
			sp_assert(_head != nullptr, "InvalidOperationException");
			SpQueueItem<T>* next = _head->_next;
			T& value = _head->_value;

			sp_mem_delete(_head, SpQueueItem<T>);

			_head = next;
			_length--;

			return value;
		}

		API_INTERFACE inline T& front() const
		{
			sp_assert(_head != nullptr, "InvalidOperationException");
			return _head->_value;
		}

		API_INTERFACE inline sp_uint length() const
		{
			return _length;
		}

		API_INTERFACE inline sp_bool isEmpty() const
		{
			return _length == ZERO_UINT;
		}

	};
}

#endif // SP_QUEUE