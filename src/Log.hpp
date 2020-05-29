#ifndef LOG_HEADER
#define LOG_HEADER

#include "SpectrumFoundation.h"

#ifdef ANDROID
#include <android/log.h>
#endif

#ifdef MSTEST_ENABLED
	#include "CppUnitTest.h"
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#endif

namespace NAMESPACE_FOUNDATION
{
	class Log
	{
	public:

		API_INTERFACE static void error(const char* text)
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

		API_INTERFACE static void info(const char* text)
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

		API_INTERFACE static void debug(const char* text)
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

		API_INTERFACE static void onError(int errorCode, const char* description)
		{
			error("Error: ");
			error(description);
		}

	};
}

#endif // !LOG_HEADER