#ifndef SP_LOGGER_HEADER
#define SP_LOGGER_HEADER

#include "SpectrumFoundation.h"
#include "SpLogProvider.h"
#include "SpString.h"

namespace NAMESPACE_FOUNDATION
{
	class SpLogger
	{
	private:
		SpLogProvider* _provider;

		SpLogger(SpLogProvider* provider)
		{
			_provider = provider;
		}

	public:

		API_INTERFACE static void init(SpLogProvider* defaultProvider);
		API_INTERFACE static void dispose();

		API_INTERFACE static SpLogger* instance();

		API_INTERFACE SpLogProvider* provider() const
		{
			return _provider;
		}

		API_INTERFACE inline void error(const sp_char* text)
		{
			_provider->error(text);
		}

		API_INTERFACE void info(const sp_char* text)
		{
			_provider->info(text);
		}

		API_INTERFACE void info(const sp_float value)
		{
			sp_char text[128];
			SpString::convert(value, text);
			_provider->info(text);
		}
		API_INTERFACE void info(const sp_float value1, const sp_float value2, const sp_float value3)
		{
			sp_char text[64];

			SpString::convert(value1, text);

			sp_uint len = strlen(text);
			text[len]   = ',';
			text[len+1] = ' ';

			SpString::convert(value2, &text[len + 2]);
			
			len = strlen(text);
			text[len] = ',';
			text[len + 1] = ' ';

			SpString::convert(value3, &text[len + 2]);

			_provider->info(text);
		}

		API_INTERFACE inline void debug(const sp_char* text)
		{
			_provider->debug(text);
		}
		
		API_INTERFACE inline void newLine()
		{
			_provider->newLine();
		}

		API_INTERFACE inline void onError(sp_int errorCode, const sp_char* description)
		{
			error(description);
		}

	};

#define sp_log_info1s(text) SpLogger::instance()->info(text)

#define sp_log_info1f(value) SpLogger::instance()->info(value)
#define sp_log_info3f(value1, value2, value3) SpLogger::instance()->info(value1, value2, value3)

#define sp_log_debug1s(text) SpLogger::instance()->debug(text)

#define sp_log_error1s(text) SpLogger::instance()->error(text)

#define sp_log_newline() SpLogger::instance()->newLine()

}

#endif // !LOG_HEADER