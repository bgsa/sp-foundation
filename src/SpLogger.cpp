#include "SpLogger.h"

namespace NAMESPACE_FOUNDATION
{
	extern SpLogger* _instance = nullptr;

	void SpLogger::init(SpLogProvider* defaultProvider)
	{
		sp_assert(_instance == nullptr, "InvalidOperationException");

		_instance = sp_mem_new(SpLogger)(defaultProvider);
	}
	
	void SpLogger::dispose()
	{
		if (_instance != nullptr)
			sp_mem_delete(_instance, SpLogger);

		_instance = nullptr;
	}

	SpLogger* SpLogger::instance()
	{
		return _instance;
	}

}