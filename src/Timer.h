#pragma once

#include "apollo.h"
#include <chrono>

using namespace std::chrono;

typedef high_resolution_clock Clock;

class Timer
{
private:
	high_resolution_clock::time_point timeLastFrame;
	milliseconds deltaTime;
	sp_int framesPerSecond;
	sp_float framePerSecondLimit = 30.0f;
	sp_float skipTick = 1000.0f / framePerSecondLimit;
	
	void calculateFramesPerSecond();
	
public:
	API_INTERFACE void start();
	API_INTERFACE void update();

	API_INTERFACE inline sp_longlong getElapsedTime();
	API_INTERFACE sp_int getFramesPerSecond();

	API_INTERFACE inline sp_float getFramePerSecondLimit();
	API_INTERFACE inline void setFramePerSecondLimit(sp_float limit);

	API_INTERFACE sp_float getSkipTick();
};

