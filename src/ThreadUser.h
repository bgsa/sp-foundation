#pragma once

#include "apollo.h"
#include <thread>
#include <chrono>

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

