#ifndef SP_LOG_MSTEST_PROVIDER_HEADER
#define SP_LOG_MSTEST_PROVIDER_HEADER

#include "SpectrumFoundation.h"
#include "SpLogProvider.h"

namespace NAMESPACE_FOUNDATION
{
	class SpLogMsTestProvider
		: public SpLogProvider
	{
	public:

		API_INTERFACE void info(const sp_char* text) override
		{
			OutputDebugStringA(text);
		}

		API_INTERFACE void debug(const sp_char* text) override
		{
			OutputDebugStringA(text);
		}

		API_INTERFACE void error(const sp_char* text) override
		{
			OutputDebugStringA(text);
		}

		API_INTERFACE void newLine() override
		{
			sp_char temp[1];
			temp[0] = END_OF_LINE;
			OutputDebugStringA(temp);
		}

	};
}

#endif // SP_LOG_MSTEST_PROVIDER_HEADER