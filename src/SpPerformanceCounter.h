#ifndef SP_PERFORMANCE_COUNTER_HEADER
#define SP_PERFORMANCE_COUNTER_HEADER

#include "SpectrumFoundation.h"
#include "SpLogger.h"
#include <chrono>

namespace NAMESPACE_FOUNDATION
{
	class PerformanceCounter
	{
	private:
		std::chrono::high_resolution_clock::time_point startTime;
			
	public:

		/// <summary>
		/// Construct and start the performance counter
		/// </summary>
		/// <returns>Instance</returns>
		API_INTERFACE PerformanceCounter()
		{
			start();
		}

		/// <summary>
		/// Reset the performance counter
		/// </summary>
		/// <returns></returns>
		API_INTERFACE inline void reset()
		{
			start();
		}

		/// <summary>
		/// Start/Reset the performance counter
		/// </summary>
		/// <returns>void</returns>
		API_INTERFACE inline void start()
		{
			startTime = std::chrono::high_resolution_clock::now();
		}

		/// <summary>
		/// Get elapsed time in nanoseconds
		/// </summary>
		/// <returns>Elapsed time in nanoseconds</returns>
		API_INTERFACE inline sp_longlong diff() const
		{
			std::chrono::high_resolution_clock::time_point finishTime = std::chrono::high_resolution_clock::now();
			return std::chrono::duration_cast<std::chrono::nanoseconds>(finishTime - startTime).count();
		}

		API_INTERFACE inline void logElapsedTime(sp_char* name)
		{
			const sp_longlong _elapsedTime = diff();

			sp_log_info1s(name);
			sp_log_info1ll(_elapsedTime);
			sp_log_newline();
		}

	};
}

#endif // SP_PERFORMANCE_COUNTER_HEADER