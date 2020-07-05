#ifndef SP_VECTOR_HEADER
#define SP_VECTOR_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	template <typename T>
	class SpVectorItem
		: public Object
	{
		template <typename R> friend class SpVector;
	protected:
		SpVectorItem<T>* _previous;
		SpVectorItem<T>* _next;
		T _data;

		API_INTERFACE SpVectorItem<T>* addNext(const T& data)
		{
			_next = sp_mem_new(SpVectorItem<T>)(data, this);

			return _next;
		}

	public:
		
		API_INTERFACE SpVectorItem()
		{
			_previous = NULL;
			_next = NULL;
			_data = NULL;
		}

		API_INTERFACE SpVectorItem(const T& data, SpVectorItem<T>* previous = NULL)
		{
			_next = NULL;
			_previous = previous;
			_data = data;
		}

		API_INTERFACE inline T value()
		{
			return _data;
		}

		API_INTERFACE inline SpVectorItem<T>* next()
		{
			return _next;
		}

		API_INTERFACE inline SpVectorItem<T>* previous()
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
				sp_mem_delete(_next, SpVectorItem<T>);
				_next = NULL;
				_previous = NULL;
			}
		}

		API_INTERFACE ~SpVectorItem()
		{
			dispose();
		}

	};

	template <typename T>
	class SpVector
		: public Object
	{
	protected:
		sp_uint _length;
		SpVectorItem<T>* _first;
		SpVectorItem<T>* _last;

	public:

		API_INTERFACE SpVector() 
		{
			_length = ZERO_UINT;
			_first = NULL;
		}
		
		API_INTERFACE inline sp_uint length() const noexcept
		{
			return _length;
		}

		API_INTERFACE inline sp_bool isEmpty() const noexcept
		{
			return _length == ZERO_UINT;
		}

		API_INTERFACE inline SpVectorItem<T>* begin() const noexcept
		{
			return _first;
		}

		API_INTERFACE inline SpVectorItem<T>* last() const noexcept
		{
			return _last;
		}

		API_INTERFACE inline virtual SpVectorItem<T>* add(const T& value)
		{
			if (_first == NULL)
			{
				_first = sp_mem_new(SpVectorItem<T>)(value);
				_last = _first;
			}
			else
			{
				_last = _last->addNext(value);
			}

			_length++;
			return _last;
		}

		API_INTERFACE inline virtual void remove(SpVectorItem<T>* item)
		{
			sp_assert(item != NULL, "NullPointerException");

			if (item == _first)
			{
				_first = item->next();
				if (_first != NULL)
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

		API_INTERFACE inline virtual SpVectorItem<T>* find(const sp_uint index)
		{
			sp_assert(index >= ZERO_UINT && index < _length, "IndexOutOfrangeException");

			SpVectorItem<T>* element = _first;

			for (sp_uint i = ZERO_UINT; i != index; i++)
				element = element->next();

			return element;
		}

		API_INTERFACE inline void clear()
		{
			sp_mem_delete(_first, SpVectorItem<T>);

			_first = NULL;
			_last = NULL;
			_length = ZERO_UINT;
		}

		API_INTERFACE inline T operator[](const sp_int index)
		{
			return find((sp_uint)index)->value();
		}
		API_INTERFACE inline T operator[](const sp_int index) const
		{
			return find((sp_uint)index)->value();
		}

		API_INTERFACE inline T operator[](const sp_uint index)
		{
			return *find(index)->value();
		}
		API_INTERFACE inline T operator[](const sp_uint index) const
		{
			return *find(index)->value();
		}

#ifdef ENV_64BITS
		API_INTERFACE inline T operator[](const sp_size index)
		{
			return find((sp_uint)index)->value();
		}
		API_INTERFACE inline T operator[](const sp_size index) const
		{
			return find((sp_uint)index)->value();
		}
#endif

		API_INTERFACE inline virtual const sp_char* toString() override
		{
			return "Spvector";
		}

		API_INTERFACE inline virtual void dispose() override
		{
			if (_first != NULL)
				clear();
		}

		API_INTERFACE ~SpVector()
		{
			dispose();
		}

	};

}

#include "SpVectorOfReferences.h"

#endif // SP_VECTOR_HEADER
