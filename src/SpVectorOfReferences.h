#ifndef SP_VECTOR_REFERENCES_HEADER
#define SP_VECTOR_REFERENCES_HEADER

#include "SpVector.h"

namespace NAMESPACE_FOUNDATION
{
	template <class T>
	class SpVectorItem<T*>
		: public Object
	{
		template <typename R> friend class SpVector;
	protected:
		SpVectorItem<T*>* _previous;
		SpVectorItem<T*>* _next;
		T* _data;

		API_INTERFACE SpVectorItem<T*>* addNext(T* data)
		{
			_next = sp_mem_new(SpVectorItem<T*>)(data, this);

			return _next;
		}

	public:

		API_INTERFACE SpVectorItem()
		{
			_next = NULL;
			_data = NULL;
		}

		API_INTERFACE SpVectorItem(T* data, SpVectorItem<T*>* previous = NULL)
		{
			_next = NULL;
			_data = data;
			_previous = previous;
		}

		API_INTERFACE inline T* value()
		{
			return _data;
		}

		API_INTERFACE inline SpVectorItem<T*>* next()
		{
			return _next;
		}

		API_INTERFACE inline SpVectorItem<T*>* previous()
		{
			return _previous;
		}

		API_INTERFACE inline virtual const sp_char* toString() override
		{
			return "SpVectorItem";
		}

		API_INTERFACE inline virtual void dispose() override
		{
			if (_next != NULL)
			{
				sp_mem_delete(_next, SpVectorItem<T*>);
				_next = NULL;
			}

			if (_data != NULL)
			{
				sp_mem_delete(_data, T);
				_data = NULL;
				_previous = NULL;
			}
		}

		API_INTERFACE ~SpVectorItem()
		{
			dispose();
		}

	};

	
	template <typename T>
	class SpVector<T*>
		: public Object
	{
	protected:
		sp_uint _length;
		SpVectorItem<T*>* _first;
		SpVectorItem<T*>* _last;

		typedef class SpVectorItem<T*> SpVectorItemReference;

	private:
		API_INTERFACE inline virtual SpVectorItemReference* findReference(const sp_uint index)
		{
			sp_assert(index >= ZERO_UINT && index < _length, "IndexOutOfrangeException");

			SpVectorItem<T*>* element = _first;

			for (sp_uint i = ZERO_UINT; i != index; i++)
				element = element->next();

			return element;
		}

	public:

		API_INTERFACE SpVector()
		{
			_length = ZERO_UINT;
			_first = NULL;
		}

		API_INTERFACE inline sp_uint length() noexcept
		{
			return _length;
		}

		API_INTERFACE inline sp_bool isEmpty() noexcept
		{
			return _length == ZERO_UINT;
		}

		API_INTERFACE inline SpVectorItemReference* begin() const noexcept
		{
			return _first;
		}

		API_INTERFACE inline SpVectorItemReference* last() const noexcept
		{
			return _last;
		}

		API_INTERFACE inline virtual SpVectorItemReference* add(T* value)
		{
			if (_first == NULL)
			{
				_first = sp_mem_new(SpVectorItem<T*>)(value);
				_last = _first;
			}
			else
			{
				_last = _last->addNext(value);
			}

			_length++;
			return _last;
		}

		API_INTERFACE inline virtual void remove(SpVectorItemReference* item)
		{
			sp_assert(item != NULL, "NullPointerException");

			if (item == _first)
			{
				_first = item->next();

				if (_first == NULL)
					_last = NULL;
				else
					_first->_previous = NULL;
			}
			else
				if (item == _last)
				{
					_last = item->previous();
					_last->_next = NULL;
				}
				else
					item->previous()->_next = item->next();

			item->_previous = NULL;
			item->_next = NULL;
			_length--;
		}

		API_INTERFACE inline virtual SpVectorItemReference* find(const sp_uint index)
		{
			return findReference(index);
		}

		API_INTERFACE inline virtual void clear()
		{
			//while (_last != nullptr)
			//	remove(_last);
			_first = NULL;
			_last = NULL;
			_length = ZERO_UINT;
		}

		API_INTERFACE inline T* operator[](const sp_int index)
		{
			return findReference((sp_uint)index)->value();
		}
		API_INTERFACE inline T* operator[](const sp_int index) const
		{
			return findReference((sp_uint)index)->value();
		}

		API_INTERFACE inline T* operator[](const sp_uint index)
		{
			return findReference(index)->value();
		}
		API_INTERFACE inline T* operator[](const sp_uint index) const
		{
			return findReference(index)->value();
		}

#ifdef ENV_64BITS
		API_INTERFACE inline T* operator[](const sp_size index)
		{
			return findReference((sp_uint) index)->value();
		}
		API_INTERFACE inline T* operator[](const sp_size index) const
		{
			return findReference((sp_uint)index)->value();
		}
#endif

		API_INTERFACE inline virtual const sp_char* toString() override
		{
			return "Spvector";
		}

		API_INTERFACE inline virtual void dispose() override
		{
			if (_first != NULL)
			{
				sp_mem_delete(_first, SpVectorItem<T*>);

				_first = NULL;
				_last = NULL;
				_length = ZERO_UINT;
			}
		}

		API_INTERFACE ~SpVector()
		{
			dispose();
		}
	};

}

#endif // SP_VECTOR_REFERENCES_HEADER