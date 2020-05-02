#include "SpectrumFoundationTest.h"
#include "SpArrayOfString.h"
#include "SpText.h"

#define CLASS_NAME SpArrayOfStringTest

namespace NAMESPACE_FOUNDATION_TEST
{
	SP_TEST_CLASS(CLASS_NAME)
	{
	public:
		SP_TEST_METHOD_DEF(dispose);
	};
	
	SP_TEST_METHOD(CLASS_NAME, dispose)
	{
		char* content = "v 1.1111 2.2222 3.3333";
		SpText text = SpText(content);

		for (sp_size i = ZERO_SIZE; i < 10; i++)
		{
			if (text[0]->startWith("v"))
			{
				const SpArrayOfString* values = text[0]->split(' ');

				sp_mem_delete(values, SpArrayOfString);
			}
		}
	}

}
