#ifndef SP_LOGGER_HEADER
#define SP_LOGGER_HEADER

#include "SpectrumFoundation.h"
#include "SpLogProvider.h"
#include "SpString.h"
#include "SpVector.h"
#include <mutex>

namespace NAMESPACE_FOUNDATION
{
	class SpLogger
	{
	private:
		SpVector<SpLogProvider*>* _providers;
		std::mutex locker;

		SpLogger()
		{
			_providers = sp_mem_new(SpVector<SpLogProvider*>)();
		}

	public:

		API_INTERFACE static void init();
		API_INTERFACE static void dispose();

		API_INTERFACE static SpLogger* instance();

		API_INTERFACE SpVector<SpLogProvider*>* providers() const
		{
			return _providers;
		}

		API_INTERFACE void addProvider(SpLogProvider* provider) const
		{
			_providers->add(provider);
		}

		API_INTERFACE inline void error(const sp_char* text)
		{
			for (SpVectorItem<SpLogProvider*>* item = _providers->begin(); item != nullptr; item = item->next())
				item->value()->error(text);
		}

		API_INTERFACE void info(const sp_char* text)
		{
			for (SpVectorItem<SpLogProvider*>* item = _providers->begin(); item != nullptr; item = item->next())
				item->value()->info(text);
		}

		API_INTERFACE void info(const sp_uint value)
		{
			locker.lock();

			sp_char text[128];
			SpString::convert(value, text);

			for (SpVectorItem<SpLogProvider*>* item = _providers->begin(); item != nullptr; item = item->next())
				item->value()->info(text);

			locker.unlock();
		}
		API_INTERFACE void info(const sp_float value)
		{
			locker.lock();

			sp_char text[128];
			SpString::convert(value, text);

			for (SpVectorItem<SpLogProvider*>* item = _providers->begin(); item != nullptr; item = item->next())
				item->value()->info(text);
		
			locker.unlock();
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

			for (SpVectorItem<SpLogProvider*>* item = _providers->begin(); item != nullptr; item = item->next())
				item->value()->info(text);
		}

		API_INTERFACE void info(const sp_longlong value)
		{
			sp_char text[128];
			SpString::convert(value, text);

			for (SpVectorItem<SpLogProvider*>* item = _providers->begin(); item != nullptr; item = item->next())
				item->value()->info(text);
		}
		
		API_INTERFACE inline void debug(const sp_char* text)
		{
			for (SpVectorItem<SpLogProvider*>* item = _providers->begin(); item != nullptr; item = item->next())
				item->value()->debug(text);
		}
		
		API_INTERFACE inline void newLine()
		{
			for (SpVectorItem<SpLogProvider*>* item = _providers->begin(); item != nullptr; item = item->next())
				item->value()->newLine();
		}

		API_INTERFACE inline void onError(sp_int errorCode, const sp_char* description)
		{
			error(description);
		}

		~SpLogger()
		{
			if (_providers != nullptr)
			{
				sp_mem_delete(_providers, SpVector<SpLogProvider*>);
				_providers = nullptr;
			}
		}

	};

#ifdef LOG_ENABLED

	#define sp_log_info1s(text) SpLogger::instance()->info(text)

	#define sp_log_info1u(value) SpLogger::instance()->info(value)
	#define sp_log_info1f(value) SpLogger::instance()->info(value)
	#define sp_log_info3f(value1, value2, value3) SpLogger::instance()->info(value1, value2, value3)
	#define sp_log_info1ll(value) SpLogger::instance()->info(value)

	#define sp_log_debug1s(text) SpLogger::instance()->debug(text)

	#define sp_log_error1s(text) SpLogger::instance()->error(text)

	#define sp_log_newline() SpLogger::instance()->newLine()

#else

#define sp_log_info1s(text)

#define sp_log_info1f(value)
#define sp_log_info3f(value1, value2, value3)
#define sp_log_info1ll(value)

#define sp_log_debug1s(text)

#define sp_log_error1s(text)

#define sp_log_newline()

#endif

}

#endif // !LOG_HEADER