#include "Timer.h"

namespace NAMESPACE_FOUNDATION
{
	sp_float timeCounter = 0;
	sp_int fpsCounter = 0;

	void Timer::calculateFramesPerSecond() 
	{
		if (timeCounter > 1000.0f) // if one second passed ...
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
		
		deltaTime = duration_cast<nanoseconds>(currentTime - timeLastFrame);

		timeLastFrame = currentTime;

		calculateFramesPerSecond();
	}

	sp_float Timer::getElapsedTime()
	{
		return deltaTime.count() / 1000000.0f;
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