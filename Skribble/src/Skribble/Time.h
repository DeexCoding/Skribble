#pragma once

namespace Skribble
{
	class Time
	{
	public:
		static float GetCurrentRealTime();

		static void Calculate(float lastFrameTime);

		static float elapsedSeconds;
		static float elapsedMilliseconds;
	};
}