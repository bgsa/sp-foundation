#ifndef SP_STRING_ID_HEADER
#define SP_STRING_ID_HEADER

#include "SpectrumFoundation.h"
#include "SpString.h"

namespace NAMESPACE_FOUNDATION
{
	class SpStringId
	{
	private:

		void init(const sp_char* name, const sp_size initialCRC = ZERO_SIZE)
		{
			const sp_size length = std::strlen(name) + 1;

			id = strHash(name, length, initialCRC);

			this->name = sp_mem_new_array(sp_char, length);
			std::memcpy(this->name, name, length);
		}

	public:
		sp_size id;
		sp_char* name;

		API_INTERFACE inline SpStringId()
		{
			id = 0;
			name = nullptr;
		}

		API_INTERFACE inline SpStringId(const sp_char* name, const sp_size initialCRC = ZERO_SIZE)
		{
			init(name, initialCRC);
		}

		API_INTERFACE inline SpStringId& operator=(const sp_char* name)
		{
			dispose();
			init(name);

			return *this;
		}

		API_INTERFACE inline void dispose()
		{
			if (name != nullptr)
			{
				sp_mem_release(name);
				name = nullptr;
			}
		}

		~SpStringId()
		{
			dispose();
		}

	};
}

#endif // SP_STRING_ID_HEADER