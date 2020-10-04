#pragma once
#include "Window.h"
#include "ChillTimer.h"
class APP
{
public:
	APP();
	int Go();
private:
	void DoFrame();
private:
	Window wnd;
	ChillTimer timer;

};