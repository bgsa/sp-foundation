#include "ThreadTest.h"

#include <mutex>
#include <iostream>

namespace NAMESPACE_FOUNDATION
{
	static std::mutex locker;

	void ThreadTest::run()
	{
		//thread_local int x = 0;  // declaring x variable in current thread context!!!

		while (true) 
		{
			locker.lock();
			std::cout << "TESTE" << '\n'; // critical region
			locker.unlock();

			sleep(1000);
		}	
	}
}