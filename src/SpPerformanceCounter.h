#ifndef SP_PERFORMANCE_COUNTER_HEADER
#define SP_PERFORMANCE_COUNTER_HEADER

#include "SpectrumFoundation.h"
#include <chrono>

namespace NAMESPACE_FOUNDATION
{
	class PerformanceCounter
	{
	private:
		std::chrono::high_resolution_clock::time_point startTime;
			
	public:
		
		API_INTERFACE void start()
		{
			startTime = std::chrono::high_resolution_clock::now();
		}

		API_INTERFACE sp_longlong diff() const
		{
			std::chrono::high_resolution_clock::time_point finishTime = std::chrono::high_resolution_clock::now();
			return std::chrono::duration_cast<std::chrono::nanoseconds>(finishTime - startTime).count();
		}

	};
}

#endif // SP_PERFORMANCE_COUNTER_HEADER