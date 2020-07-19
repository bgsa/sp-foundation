#ifndef SP_THREAD_POOL_HEADER
#define SP_THREAD_POOL_HEADER

#include "SpectrumFoundation.h"
#include "SpHardwareInfo.h"
#include "MutexSpinLock.h"
#include <thread>
#include <functional>

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
		MutexSpinLock* workersMutex;
		SpVector<SpThreadTask*>* tasks;
		sp_uint threadAvailableIndex;

		SpThreadPool()
		{
			sp_uint coresLength = SpHardwareInfo::instance()->processors()->begin()->value()->cores;

			threadLength = multiplyBy2(coresLength);
			//threadLength = coresLength;
			threads = sp_mem_new_array(SpThread, threadLength + 1);
			workersMutex = sp_mem_new_array(MutexSpinLock, threadLength + 1);
			threadAvailableIndex = ZERO_UINT;

			tasks = new SpVector<SpThreadTask*>[threadLength];
		}

		static void run(sp_uint id)
		{
			SpThreadPool* threadPool = SpThreadPool::instance();

			while (true)
			{
				SpVectorItem<SpThreadTask*>* taskQueue = threadPool->tasks[id].begin();

				if (taskQueue != nullptr)
				{
					while (taskQueue != nullptr)
					{
						SpThreadTask* task = taskQueue->value();

						task->func(task->parameter);

						taskQueue = taskQueue->next();
					}

					threadPool->workersMutex[id].lock();
					threadPool->tasks[id].clear();
					threadPool->workersMutex[id].unlock();
				}
				else
				{
					std::this_thread::sleep_for(std::chrono::nanoseconds(10000)); // 0.01 miliseconds
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
			sp_bool isEmpty = true;

			while (true)
			{
				for (sp_uint i = 0; i < threadLength; i++)
					isEmpty = isEmpty && tasks[i].length() == ZERO_UINT;

				if (isEmpty)
					break;
				else
				{
					//std::this_thread::sleep_for(std::chrono::nanoseconds(100000)); // 0.1 miliseconds
					isEmpty = true;
				}
			}
		}

	};
}

#endif // SP_THREAD_POOL_HEADER