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
			_next = nullptr;
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
			if (_next != nullptr)
			{
				sp_mem_delete(_next, SpVectorItem<T*>);
				_next = nullptr;
			}
/*
			if (_data != NULL)
			{
				sp_mem_delete(_data, T);
				_data = nullptr;
				_previous = nullptr;
			}
			*/
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
			_first = nullptr;
			_last = nullptr;
		}

		API_INTERFACE inline sp_uint length() const noexcept
		{
			return _length;
		}

		API_INTERFACE inline sp_bool isEmpty() const noexcept
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
			if (_first == nullptr)
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
			sp_assert(item != nullptr, "NullPointerException");

			if (item == _first)
			{
				_first = item->next();

				if (_first == nullptr)
					_last = nullptr;
				else
					_first->_previous = nullptr;
			}
			else
				if (item == _last)
				{
					_last = item->previous();
					_last->_next = nullptr;
				}
				else
					item->previous()->_next = item->next();

			item->_previous = nullptr;
			item->_next = nullptr;
			_length--;
		}

		API_INTERFACE inline void removeFirst()
		{
			sp_assert(_first != nullptr, "NullPointerException");

			_first = _first->next();
			_length--;
		}

		API_INTERFACE inline virtual SpVectorItemReference* find(const sp_uint index)
		{
			return findReference(index);
		}

		API_INTERFACE inline virtual SpVectorItemReference* find(const T* value)
		{
			for (SpVectorItemReference* item = _first; item != nullptr; item = item->next())
				if (item->value() == value)
					return item;

			return nullptr;
		}

		API_INTERFACE inline virtual void clear()
		{
			_first = nullptr;
			_last = nullptr;
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
			if (_first != nullptr)
			{
				sp_mem_delete(_first, SpVectorItem<T*>);

				_first = nullptr;
				_last = nullptr;
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