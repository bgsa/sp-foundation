#ifndef TIMER_HEADER
#define TIMER_HEADER

#include "SpectrumFoundation.h"
#include <chrono>

namespace NAMESPACE_FOUNDATION
{
	class Timer
	{
		typedef std::chrono::high_resolution_clock Clock;
		typedef std::chrono::high_resolution_clock::time_point TimePoint;

	private:
		TimePoint timeLastFrame;
		sp_int _framesPerSecond;
		sp_float _framePerSecondLimit = 30.0f;
		
		sp_float timeCounter = 0;
		sp_int fpsCounter = 0;

		void calculateFramesPerSecond()
		{
			if (timeCounter > 1000.0f) // if one second passed ...
			{
				_framesPerSecond = fpsCounter;
				timeCounter = 0;
				fpsCounter = 0;
			}

			timeCounter += elapsedTime();
			fpsCounter++;
		}
		
	public:

		API_INTERFACE static Timer* physicTimer();
		API_INTERFACE static Timer* renderTimer();
		API_INTERFACE static Timer* frameTimer();

		API_INTERFACE static void init();

		API_INTERFACE inline void start()
		{
			timeLastFrame = Clock::now();
			//timeLastFrame -= std::chrono::milliseconds(1L);
			update();
		}

		API_INTERFACE inline void update()
		{
			timeLastFrame = Clock::now();
			calculateFramesPerSecond();
		}

		API_INTERFACE inline sp_float elapsedTime() const
		{
			sp_float time = std::chrono::duration_cast<std::chrono::nanoseconds>
				(Clock::now() - timeLastFrame).count() / 1000000.0f;

			return time;
		}

		API_INTERFACE inline sp_int framesPerSecond() const
		{
			return _framesPerSecond;
		}

		API_INTERFACE inline sp_float framePerSecondLimit() const
		{
			return _framePerSecondLimit;
		}

		API_INTERFACE inline void framePerSecondLimit(sp_float limit)
		{
			_framePerSecondLimit = limit;
		}


	};
}

#endif // !TIMER_HEADER