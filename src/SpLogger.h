#ifndef SP_LOGGER_HEADER
#define SP_LOGGER_HEADER

#include <stdio.h>
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
		API_INTERFACE void info(const sp_int value)
		{
			locker.lock();

			sp_char text[128];
			SpString::convert(value, text);

			for (SpVectorItem<SpLogProvider*>* item = _providers->begin(); item != nullptr; item = item->next())
				item->value()->info(text);

			locker.unlock();
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

			sp_size len = std::strlen(text);
			text[len]   = ',';
			text[len+1] = ' ';

			SpString::convert(value2, &text[len + 2]);
			
			len = std::strlen(text);
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
		API_INTERFACE inline void debug(const sp_float value)
		{
			sp_char text[32];
			SpString::convert(value, text);

			for (SpVectorItem<SpLogProvider*>* item = _providers->begin(); item != nullptr; item = item->next())
				item->value()->debug(text);
		}
		API_INTERFACE inline void debug(const sp_uint value)
		{
			sp_char text[32];
			SpString::convert(value, text);

			for (SpVectorItem<SpLogProvider*>* item = _providers->begin(); item != nullptr; item = item->next())
				item->value()->debug(text);
		}
		API_INTERFACE inline void debug(const sp_float* list, const sp_uint listLength)
		{
			for (sp_uint i = 0u; i < listLength; i++)
			{
				debug(list[i]);
				debug(", ");
			}
		}
		API_INTERFACE inline void debug(const sp_float* list, const sp_uint rows, const sp_uint columns)
		{
			for (sp_uint i = 0u; i < rows; i++)
			{
				for (sp_uint c = 0; c < columns; c++)
				{
					debug(list[i]);
					debug(", ");
				}
				newLine();
			}
		}
		API_INTERFACE inline void debug(const sp_char* text, const sp_float value)
		{
			locker.lock();

			const sp_size length = std::strlen(text);
			
			sp_char* result = ALLOC_ARRAY(sp_char, length + 20);
			std::memcpy(result, text, length);
			
			SpString::convert(value, &result[length]);
			
			for (SpVectorItem<SpLogProvider*>* item = _providers->begin(); item != nullptr; item = item->next())
			{
				item->value()->debug(result);
				item->value()->newLine();
			}

			ALLOC_RELEASE(result);
			locker.unlock();
		}
		API_INTERFACE void debug(const sp_float value1, const sp_float value2, const sp_float value3)
		{
			sp_char text[64];

			SpString::convert(value1, text);

			sp_size len = std::strlen(text);
			text[len] = ',';
			text[len + 1] = ' ';

			SpString::convert(value2, &text[len + 2]);

			len = strlen(text);
			text[len] = ',';
			text[len + 1] = ' ';

			SpString::convert(value3, &text[len + 2]);

			for (SpVectorItem<SpLogProvider*>* item = _providers->begin(); item != nullptr; item = item->next())
				item->value()->debug(text);
		}
		API_INTERFACE void debug(const sp_longlong value)
		{
			sp_char text[128];
			SpString::convert(value, text);

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
	#define sp_log_newline() SpLogger::instance()->newLine()

	#define sp_log_info1s(text) SpLogger::instance()->info(text)

	#define sp_log_info1i(value) SpLogger::instance()->info(value)
	#define sp_log_info1u(value) SpLogger::instance()->info(value)
	#define sp_log_info1f(value) SpLogger::instance()->info(value)
	#define sp_log_info3f(value1, value2, value3) SpLogger::instance()->info(value1, value2, value3)
	#define sp_log_info1ll(value) SpLogger::instance()->info(value)

	#define sp_log_debug1s(text) SpLogger::instance()->debug(text)
	#define sp_log_debug1snl(text) SpLogger::instance()->debug(text); sp_log_newline();
	#define sp_log_debug1ll(value) SpLogger::instance()->debug(value)
	#define sp_log_debug1f(value) SpLogger::instance()->debug(value)
	#define sp_log_debug1u(value) SpLogger::instance()->debug(value)
	#define sp_log_debugXf(list, listLength) SpLogger::instance()->debug(list, listLength)
	#define sp_log_debug_matrix(values, rows, columns) SpLogger::instance()->debug(values, rows, columns)
	#define sp_log_debug1sfnl(text, value) SpLogger::instance()->debug(text, value)

	#define sp_log_error1s(text) SpLogger::instance()->error(text)

#else
	#define sp_log_newline()

	#define sp_log_info1s(text) 

	#define sp_log_info1i(value)
	#define sp_log_info1u(value)
	#define sp_log_info1f(value)
	#define sp_log_info3f(value1, value2, value3)
	#define sp_log_info1ll(value)

	#define sp_log_debug1s(text)
	#define sp_log_debug1snl(text)
	#define sp_log_debug1ll(value)
	#define sp_log_debug1f(value) 
	#define sp_log_debug1u(value)
	#define sp_log_debugXf(list, listLength)
	#define sp_log_debug_matrix(values, rows, columns)
	#define sp_log_debug1sfnl(text, value)

	#define sp_log_error1s(text)

#endif

}

#endif // !LOG_HEADER