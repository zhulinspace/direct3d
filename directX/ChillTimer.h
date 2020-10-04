#pragma once
#include<chrono>
class ChillTimer
{
public:
	ChillTimer();
	float Mark();
	float Peek() const;
private:
	std::chrono::steady_clock::time_point last;
};