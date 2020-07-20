#ifndef SP_MUTEX_SPIN_LOCK_HEADER
#define SP_MUTEX_SPIN_LOCK_HEADER

#include "SpectrumFoundation.h"

namespace NAMESPACE_FOUNDATION
{
	class SpMutexSpinLock
	{
	private:
		volatile sp_bool locked = false;

	public:

		API_INTERFACE inline void lock()
		{
			while (locked) { }  //std::this_thread::sleep_for(std::chrono::nanoseconds(1000));

			locked = true;
		}

		API_INTERFACE inline void unlock()
		{
			locked = false;
		}

	};
}

#endif // SP_MUTEX_SPIN_LOCK_HEADER