#pragma once
#include "Window.h"
#include "ChillTimer.h"
#include"ImguiManager.h"
#include"Camera.h"
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
	Camera  cam;
	//std::vector<std::unique_ptr<class Box>>boxes;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	static constexpr size_t nDrawables = 180;
	bool show_demo_window = true;
	float speed_factor = 1.0f;
};