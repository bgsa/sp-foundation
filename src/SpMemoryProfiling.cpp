#include "SpMemoryProfiling.h"

namespace NAMESPACE_FOUNDATION
{

	SpMemoryProfiling* SpMemoryProfilingInstance = nullptr;

	void SpMemoryProfiling::init()
	{
		if (SpMemoryProfilingInstance == nullptr)
		{
			SpMemoryProfilingInstance = new SpMemoryProfiling;
		}
	}

	void SpMemoryProfiling::release()
	{
		if (SpMemoryProfilingInstance != nullptr)
		{
			delete SpMemoryProfilingInstance;
			SpMemoryProfilingInstance = nullptr;
		}
	}

}