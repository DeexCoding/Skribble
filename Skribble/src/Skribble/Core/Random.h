#pragma once

#include <limits>
#include <random>

class Random
{
public:
	static void Init()
	{
		randomEngine.seed(std::random_device()());
	}

	//Generates an int between 0? (including) and intager max (including)
	static int Int()
	{
		return (int)distribution(randomEngine);
	}

	//Generates an int between 0? (including) and max (including)
	static int Int(int max)
	{
		return (int)distribution(randomEngine) % max + 1;
	}

	//Generates an int between min (including) and max (including)
	static int Int(int min, int max)
	{
		return (int)(distribution(randomEngine) % ((max - min) + 1)) + min;
	}

	//Generates a float between 0 (including) and 1 (including)
	static float Float()
	{
		return (float)distribution(randomEngine) / (float)(std::numeric_limits<uint32_t>::max)();
	}

	//Generates a float between 0 (including) and max (including)
	static float Float(float max)
	{
		return Float() + (float)Int((int)max - 1);
	}

	//Generates a float between min (including) and max (including)
	static float Float(float min, float max)
	{
		return Float(max - min) + min;
	}

private:
	static std::mt19937 randomEngine;
	static std::uniform_int_distribution<std::mt19937::result_type> distribution;

};