#ifndef SP_THREAD_POOL_HEADER
#define SP_THREAD_POOL_HEADER

#include "SpectrumFoundation.h"
#include "SpHardwareInfo.h"
#include "SpMutexSpinLock.h"
#include <thread>
#include <functional>
#include <mutex>

namespace NAMESPACE_FOUNDATION
{
	class SpThreadTask
	{
	public:
		void (*func)(void*);
		void* parameter;
	};

	class SpThread
	{
	public:
		std::thread runner;
	};

	class SpThreadPool
	{
	private:
		sp_uint threadLength;
		SpThread* threads;
		SpMutexSpinLock* workersMutex;
		SpVector<SpThreadTask*>* tasks;
		sp_uint threadAvailableIndex;

		std::mutex globalMutex;

		SpThreadPool()
		{
			sp_uint coresLength = SpHardwareInfo::instance()->processors()->begin()->value()->cores;

			threadLength = multiplyBy4(coresLength);
			//threadLength = coresLength;
			threads = sp_mem_new_array(SpThread, threadLength + 1);
			workersMutex = sp_mem_new_array(SpMutexSpinLock, threadLength + 1);
			threadAvailableIndex = ZERO_UINT;

			tasks = new SpVector<SpThreadTask*>[threadLength];
		}

		static void run(sp_uint id)
		{
			SpThreadPool* threadPool = SpThreadPool::instance();

			while (true)
			{
				SpVectorItem<SpThreadTask*>* taskQueue = threadPool->tasks[id].begin();

				if (taskQueue == nullptr) // if task list is empty, sleep...
					std::this_thread::sleep_for(std::chrono::nanoseconds(10000)); // 0.01 miliseconds
				else
				{
					while (taskQueue != nullptr) // while task list is not empty, do ...
					{
						SpThreadTask* task = taskQueue->value();

						task->func(task->parameter);

						taskQueue = taskQueue->next();
					}

					threadPool->workersMutex[id].lock();
					threadPool->tasks[id].clear();
					threadPool->workersMutex[id].unlock();
				}
			}
		}

	public:

		API_INTERFACE inline static SpThreadPool* instance()
		{
			static SpThreadPool* _instance = sp_mem_new(SpThreadPool)();
			return _instance;
		}

		API_INTERFACE inline void init()
		{
			for (sp_uint i = 0; i < threadLength; i++)
				threads[i].runner = std::thread(run, i);
		}

		API_INTERFACE inline void schedule(SpThreadTask* task)
		{
			if (threadAvailableIndex >= threadLength)
				threadAvailableIndex = ZERO_UINT;

			workersMutex[threadAvailableIndex].lock();
			tasks[threadAvailableIndex].add(task);
			workersMutex[threadAvailableIndex].unlock();

			threadAvailableIndex++;
		}

		API_INTERFACE inline void waitToFinish()
		{
			sp_bool isEmpty = false;

			while (!isEmpty)
			{
				isEmpty = true;

				for (sp_uint i = 0; i < threadLength; i++)
					isEmpty = isEmpty && tasks[i].length() == ZERO_UINT;
			}
		}

	};
}

#endif // SP_THREAD_POOL_HEADER