#include "Timer.h"

using namespace std::chrono;

Timer::Timer()
{
	last = steady_clock::now();
}

float Timer::Reset()
{
	auto now = steady_clock::now();
	duration<float> dur = now - last;
	last = now;
	return dur.count();
}

float Timer::Get() const
{
	return static_cast<float>( (steady_clock::now() - last).count() );
}
