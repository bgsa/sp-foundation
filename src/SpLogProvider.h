#ifndef SP_LOG_PROVIDER_HEADER
#define SP_LOG_PROVIDER_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	class SpLogProvider
	{
	public:

		API_INTERFACE virtual void error(const sp_char* text) = 0;

		API_INTERFACE virtual void info(const sp_char* text) = 0;

		API_INTERFACE virtual void debug(const sp_char* text) = 0;

		API_INTERFACE virtual void newLine() = 0;

	};
}

#endif // SP_LOG_PROVIDER_HEADER