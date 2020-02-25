#ifndef LOG_HEADER
#define LOG_HEADER

#include "apollo.h"
#include <cstdio>
#include <iostream>
#include <string>
#include "StringHelper.h"

#ifdef ANDROID
#include <android/log.h>
#endif

#ifdef MS_TEST
	#include "CppUnitTest.h"
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#endif

class Log
{
public:

	API_INTERFACE static void error(std::string errorMessage)
	{
#ifdef ANDROID
		__android_log_print(ANDROID_LOG_ERROR, "ERROR", "%s", errorMessage.c_str());
#endif
#if defined(WINDOWS) || defined(LINUX) || defined(MAC)
		printf("%s%c", errorMessage.c_str(), END_OF_LINE);
#endif
#ifdef MS_TEST
		Logger::WriteMessage(errorMessage.c_str());
#endif
	}

	API_INTERFACE static void info(std::string message)
	{
#ifdef ANDROID
		__android_log_print(ANDROID_LOG_INFO, "INFO", "%s", message.c_str());
#endif
#if defined(WINDOWS) || defined(LINUX) || defined(MAC)
		printf("%s%c", message.c_str(), END_OF_LINE);
#endif	
#ifdef MS_TEST
		Logger::WriteMessage(message.c_str());
#endif
	}

	API_INTERFACE static void debug(std::string message)
	{
#ifdef ANDROID
		__android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "%s", message.c_str());
#endif
#if defined(WINDOWS) || defined(LINUX) || defined(MAC)
		printf("%s%c", message.c_str(), END_OF_LINE);
#endif		
#ifdef MS_TEST
		Logger::WriteMessage(message.c_str());
#endif
	}

	API_INTERFACE static void onError(sp_int errorCode, const sp_char* description)
	{
		error("Error: " + std::string(description));
	}

};

#endif // !LOG_HEADER