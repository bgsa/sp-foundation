#ifndef THREAD_USE_HEADER
#define THREAD_USE_HEADER

#include "SpectrumFoundation.h"
#include <thread>
#include <chrono>

namespace NAMESPACE_FOUNDATION
{
	class ThreadUser
	{
	private:
		std::thread* instance;
		sp_bool isRunning = false;
		
	public:
		void start();
		void stop();
		void sleep(sp_uint miliseconds);
		virtual void run() = 0;
		void join();
		void detach();

		std::thread::id getId();

		~ThreadUser();
	};
}

#endif // !THREAD_USE_HEADER