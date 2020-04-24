#ifndef MUTEX_SPIN_LOCK_HEADER
#define MUTEX_SPIN_LOCK_HEADER

#include "SpectrumFoundation.h"
#include <atomic>

namespace NAMESPACE_FOUNDATION
{
	class MutexSpinLock
	{
	private:
		std::atomic_flag flag = ATOMIC_FLAG_INIT;

	public:

		API_INTERFACE inline void lock()
		{
			while (std::atomic_flag_test_and_set_explicit(&flag, std::memory_order_relaxed));
		}

		API_INTERFACE inline void unlock()
		{
			std::atomic_flag_clear_explicit(&flag, std::memory_order_release);
		}

	};
}

#endif // !MUTEX_SPIN_LOCK_HEADER