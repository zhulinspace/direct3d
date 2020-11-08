#pragma once
#include "Window.h"
#include "ChillTimer.h"
#include"ImguiManager.h"
class APP
{
public:
	APP();
	~APP();
	int Go();
private:
	void DoFrame();
private:
	ImguiManager imgui;
	Window wnd;
	ChillTimer timer;
	//std::vector<std::unique_ptr<class Box>>boxes;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	static constexpr size_t nDrawables = 180;
};