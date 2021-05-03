#ifndef SP_LOG_CONSOLE_PROVIDER_HEADER
#define SP_LOG_CONSOLE_PROVIDER_HEADER

#include "SpectrumFoundation.h"
#include "SpLogProvider.h"

namespace NAMESPACE_FOUNDATION
{
	class SpLogConsoleProvider
		: public SpLogProvider
	{
	private:

#ifdef WINDOWS
		CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
		HANDLE stdOutHandler;
#endif

	public:

		/// <summary>
		/// Default constructor
		/// </summary>
		/// <returns></returns>
		API_INTERFACE inline SpLogConsoleProvider()
		{
#ifdef WINDOWS
			stdOutHandler = GetStdHandle(STD_OUTPUT_HANDLE);

			if (stdOutHandler != INVALID_HANDLE_VALUE)
			{
				if (GetConsoleScreenBufferInfo(stdOutHandler, &csbiInfo))
				{
					csbiInfo.wAttributes = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;

					COORD newCoord = csbiInfo.dwSize;
					newCoord.Y *= 10;
					if (!SetConsoleScreenBufferSize(stdOutHandler, newCoord))
						error("Error SetConsoleScreenBufferSize");
				}
			}
			else
				stdOutHandler = nullptr;
#endif
		}

#ifdef WINDOWS
		API_INTERFACE inline void setForeColor(WORD color)
		{
			if (stdOutHandler != NULL)
				SetConsoleTextAttribute(stdOutHandler, color);
		}
#endif

		API_INTERFACE void info(const char* text) override
		{
#ifdef WINDOWS
			setForeColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
#endif

#ifdef ANDROID
			__android_log_print(ANDROID_LOG_INFO, "INFO", "%s", text);
#endif

#if defined(WINDOWS) || defined(LINUX) || defined(OSX)
			printf("%s", text);
#endif
		}

		API_INTERFACE void debug(const char* text) override
		{
#ifdef WINDOWS
			setForeColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
#endif

#ifdef ANDROID
			__android_log_print(ANDROID_LOG_DEBUG, "DEBUG", "%s", text);
#endif
#if defined(WINDOWS) || defined(LINUX) || defined(OSX)
			printf("%s", text);
#endif
		}

		API_INTERFACE void error(const char* text) override
		{
#ifdef WINDOWS
			setForeColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
#endif

#ifdef ANDROID
			__android_log_print(ANDROID_LOG_ERROR, "ERROR", "%s", text);
#endif
#if defined(WINDOWS) || defined(LINUX) || defined(OSX)
			printf("%s", text);
#endif
		}

		API_INTERFACE void newLine() override
		{
#ifdef ANDROID
			__android_log_print(ANDROID_LOG_ERROR, "ERROR", "%s", text);
#endif
#if defined(WINDOWS) || defined(LINUX) || defined(OSX)
			printf("%c", END_OF_LINE);
#endif
		}

	};
}

#endif // SP_LOG_CONSOLE_PROVIDER_HEADER