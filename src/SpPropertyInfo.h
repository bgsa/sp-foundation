#ifndef SP_PROPERTY_INFO
#define SP_PROPERTY_INFO

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	class SpPropertyInfo
	{
	private:
		const sp_char* _name;
		const sp_char* _type;
		void* _value;

	public:

		API_INTERFACE SpPropertyInfo(const sp_char* name, const sp_char* type, void* value)
		{
			_name = name;
			_type = type;
			_value = value;
		}

		API_INTERFACE inline const sp_char* name() const
		{
			return _name;
		}

		API_INTERFACE inline const sp_char* type() const
		{
			return _type;
		}

		API_INTERFACE inline void* value() const
		{
			return _value;
		}

		~SpPropertyInfo()
		{
			if (_name != nullptr)
			{
				sp_mem_release(_name);
				_name = nullptr;
			}

			if (_type != nullptr)
			{
				sp_mem_release(_type);
				_type = nullptr;
			}

			if (_value != nullptr)
			{
				sp_mem_release(_value);
				_value = nullptr;
			}
		}
		
	};
}

#endif // SP_PROPERTY_INFO