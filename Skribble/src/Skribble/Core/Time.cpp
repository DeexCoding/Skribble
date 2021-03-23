#include "skpch.h"

#include "Time.h"

namespace Skribble
{
	float Time::elapsedSeconds = 0.0f;
	float Time::elapsedMilliseconds = 0.0f;

	void Time::Calculate(float lastFrameTime)
	{
		float realTime = GetCurrentRealTime();
		Time::elapsedSeconds = realTime - lastFrameTime;
		Time::elapsedMilliseconds = Time::elapsedSeconds * 1000.0f;
	}
}