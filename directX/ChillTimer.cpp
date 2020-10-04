#include"ChillTimer.h"

using namespace std::chrono;

ChillTimer::ChillTimer()
{
	last = steady_clock::now();
}

float ChillTimer::Mark()
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float>frameTime = last - old;
	return frameTime.count();
}

float ChillTimer::Peek() const
{
	return duration<float>(steady_clock::now() - last).count();
}

