#include "ThreadUser.h"

void ThreadUser::start()
{
	isRunning = true;
	instance = new std::thread(&ThreadUser::run, this);
}

void ThreadUser::stop() 
{
	isRunning = false;
}

void ThreadUser::sleep(sp_uint miliseconds)
{	
	std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
}

void ThreadUser::join()
{
	instance->join();
}

void ThreadUser::detach()
{
	instance->detach();
}

std::thread::id ThreadUser::getId()
{
	return std::this_thread::get_id();
}

ThreadUser::~ThreadUser()
{
	if (instance != nullptr)
		delete instance;
}
