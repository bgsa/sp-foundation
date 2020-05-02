#ifndef SP_ARRAY_OF_STRING_HEADER
#define SP_ARRAY_OF_STRING_HEADER

#include "SpectrumFoundation.h"
#include "SpString.h"

namespace NAMESPACE_FOUNDATION
{
	class SpArrayOfString
		: public SpArray<SpString>
	{
		friend class SpString;
	public:

		API_INTERFACE SpArrayOfString(const sp_uint length, const sp_uint reserved = ZERO_UINT)
			: SpArray<SpString>(length, reserved)
		{
		}

		API_INTERFACE inline virtual const sp_char* toString() override
		{
			return "SpArray Of String";
		}

		API_INTERFACE inline virtual void dispose() override
		{
			if (_data != NULL)
			{
				for (sp_uint i = ZERO_UINT; i < _length; i++)
					if (_data[i] != NULL)
					{
						_data[i].~SpString();
					}
				
				sp_mem_release(_data);
			}
		}

		API_INTERFACE ~SpArrayOfString()
		{
			dispose();
		}

	};

}

#endif // SP_ARRAY_OF_STRING_HEADER
