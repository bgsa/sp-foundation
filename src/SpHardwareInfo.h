#ifndef SP_HARDWARE_INFO_HEADER
#define SP_HARDWARE_INFO_HEADER

#include "SpectrumFoundation.h"
#include "SpVector.h"
#include "SpProcessorInfo.h"
#include <thread>

namespace NAMESPACE_FOUNDATION
{
	class SpHardwareInfo
	{
	private:
		sp_bool isLoaded;
		SpVector<SpProcessorInfo*>* _processors;

		SpHardwareInfo()
		{
			isLoaded = false;
			_processors = nullptr;
		}

		API_INTERFACE void load()
		{
			_processors = sp_mem_new(SpVector<SpProcessorInfo*>)();

			SpProcessorInfo* processor1 = sp_mem_new(SpProcessorInfo)();
			processor1->cores = std::thread::hardware_concurrency();
			_processors->add(processor1);
		}

	public:

		API_INTERFACE static inline SpHardwareInfo* instance()
		{
			static SpHardwareInfo* _instance = sp_mem_new(SpHardwareInfo)();

			if (!_instance->isLoaded)
				_instance->load();

			return _instance;
		}

		API_INTERFACE inline SpVector<SpProcessorInfo*>* processors()
		{
			return _processors;
		}

	};
}

#endif // SP_HARDWARE_INFO_HEADER