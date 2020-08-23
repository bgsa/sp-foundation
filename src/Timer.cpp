#include "Timer.h"

namespace NAMESPACE_FOUNDATION
{
	static Timer* _physicTimer;
	static Timer* _renderTimer;
	static Timer* _frameTimer;

	Timer* Timer::physicTimer()
	{
		return _physicTimer;
	}

	Timer* Timer::renderTimer()
	{
		return _renderTimer;
	}

	Timer* Timer::frameTimer()
	{
		return _frameTimer;
	}

	void Timer::init()
	{
		_physicTimer = sp_mem_new(Timer);
		_renderTimer = sp_mem_new(Timer);
		_frameTimer = sp_mem_new(Timer);

		_physicTimer->start();
		_renderTimer->start();
		_frameTimer->start();
	}

}