#include "Timer.h"

namespace NAMESPACE_FOUNDATION
{
	sp_longlong timeCounter = 0;
	sp_int fpsCounter = 0;

	void Timer::calculateFramesPerSecond() 
	{
		sp_bool oneSecondPassed = timeCounter > 1000;

		if (oneSecondPassed)
		{
			framesPerSecond = fpsCounter;
			timeCounter = 0;
			fpsCounter = 0;
		}

		timeCounter += getElapsedTime();
		fpsCounter ++;
	}

	void Timer::start()
	{
		timeLastFrame = Clock::now();
	}

	void Timer::update()
	{
		high_resolution_clock::time_point currentTime = Clock::now();
		
		deltaTime = duration_cast<milliseconds>(currentTime - timeLastFrame);

		timeLastFrame = currentTime;

		calculateFramesPerSecond();
	}

	sp_longlong Timer::getElapsedTime()
	{
		return deltaTime.count();
	}

	sp_int Timer::getFramesPerSecond()
	{
		return framesPerSecond;
	}

	sp_float Timer::getFramePerSecondLimit()
	{
		return framePerSecondLimit;
	}

	void Timer::setFramePerSecondLimit(sp_float limit)
	{
		framePerSecondLimit = limit;
		skipTick = 1000.0f / limit;
	}

	sp_float Timer::getSkipTick()
	{
		return skipTick;
	}
}