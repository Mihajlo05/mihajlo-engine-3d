#pragma once

#include <chrono>

class Timer
{
public:
	Timer();
	float Reset();
	float Get() const;
private:
	std::chrono::time_point<std::chrono::steady_clock> last;
};