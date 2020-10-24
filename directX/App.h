#pragma once
#include "Window.h"
#include "ChillTimer.h"
#include<directX/Drawable/Box.h>
class APP
{
public:
	APP();
	~APP();
	int Go();
private:
	void DoFrame();
private:
	Window wnd;
	ChillTimer timer;
	std::vector<std::unique_ptr<class Box>>boxes;

};