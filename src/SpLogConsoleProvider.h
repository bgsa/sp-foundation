#ifndef SP_LOG_CONSOLE_PROVIDER_HEADER
#define SP_LOG_CONSOLE_PROVIDER_HEADER

#include "SpectrumFoundation.h"
#include "SpLogProvider.h"

namespace NAMESPACE_FOUNDATION
{
	class SpLogConsoleProvider
		: public SpLogProvider
	{
	public:

		API_INTERFACE void info(const char* text) override
		{
#ifdef ANDROID
			__android_log_print(ANDROID_LOG_INFO, "INFO", "%s", text);
#endif
#if defined(WINDOWS) || defined(LINUX) || defined(OSX)
			printf("%s%c", text, END_OF_LINE);
#endif	
#ifdef MSTEST_ENABLED
			//OutputDebugStringA(text);
#endif
		}

		API_INTERFACE void debug(const char* text) override
		{
#ifdef ANDROID
			__android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "%s", text);
#endif
#if defined(WINDOWS) || defined(LINUX) || defined(OSX)
			printf("%s%c", text, END_OF_LINE);
#endif		
#ifdef MSTEST_ENABLED
			//OutputDebugStringA(text);
#endif
		}

		API_INTERFACE void error(const char* text) override
		{
#ifdef ANDROID
			__android_log_print(ANDROID_LOG_ERROR, "ERROR", "%s", text);
#endif
#if defined(WINDOWS) || defined(LINUX) || defined(OSX)
			printf("%s%c", text, END_OF_LINE);
#endif
#ifdef MSTEST_ENABLED
			//OutputDebugStringA(text);
#endif
		}

	};
}

#endif // SP_LOG_CONSOLE_PROVIDER_HEADER