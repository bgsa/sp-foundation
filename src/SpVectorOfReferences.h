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
		SpVectorItem<T*>* _next;
		T* _data;

		API_INTERFACE SpVectorItem<T*>* addNext(T* data)
		{
			_next = sp_mem_new(SpVectorItem<T*>)(data);
			_next->_data = data;

			return _next;
		}

	public:

		API_INTERFACE SpVectorItem()
		{
			_next = NULL;
			_data = NULL;
		}

		API_INTERFACE SpVectorItem(T* data)
		{
			_next = NULL;
			_data = data;
		}

		API_INTERFACE inline T value()
		{
			return _data;
		}

		API_INTERFACE inline SpVectorItem<T*>* next()
		{
			return _next;
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

		API_INTERFACE inline SpVectorItem<T*>* begin() const noexcept
		{
			return _first;
		}

		API_INTERFACE inline SpVectorItem<T*>* last() const noexcept
		{
			return _last;
		}

		API_INTERFACE inline virtual SpVectorItem<T*>* add(T* value)
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

		API_INTERFACE inline T* operator[](const sp_int index) const
		{
			assert(index >= ZERO_INT && (sp_uint)index < _length);

			SpVectorItem<T*>* item = _first;
			sp_int counter = ZERO_INT;

			while (item != NULL && index != counter)
			{
				item = item->next();
				counter++;
			}

			return item->_data;
		}

		API_INTERFACE inline T* operator[](const sp_uint index) const
		{
			assert(index >= ZERO_UINT && index < _length);
			return _data[index];
		}

#ifdef ENV_64BITS
		API_INTERFACE inline T* operator[](const sp_size index) const
		{
			assert(index >= ZERO_SIZE && (sp_uint)index < _length);
			return _data[index];
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