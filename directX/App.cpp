#include"App.h"
#include<directX/Drawable/Sheet.h>
#include<directX/Drawable/Melon.h>
#include<directX/Drawable/Box.h>
#include<directX/Drawable/Pyramid.h>
#include<directX/ChiliMath.h>
#include<memory>
#include<algorithm>
#include <sstream>
#include<random>
#include<directX/Drawable/SkinnedBox.h>
#include<directX/Surface.h>
#include<directX/GDIPlusManager.h>
#include"imgui/imgui.h"
#include"imgui/imgui_impl_dx11.h"
#include"imgui/imgui_impl_win32.h"

GDIPlusManager gdipm;


APP::APP():wnd(800,600,"the game box")
{

	class Factory
	{
	public:
		Factory(Graphics& gfx)
			:
			gfx(gfx)
		{}
		std::unique_ptr<Drawable> operator()()
		{
			switch (typedist(rng))
			{
			case 0:
				return std::make_unique<Pyramid>(
					gfx, rng, adist, ddist,
					odist, rdist
					);
			case 1:
				return std::make_unique<Box>(
					gfx, rng, adist, ddist,
					odist, rdist, bdist
					);
			case 2:
				return std::make_unique<Melon>(
					gfx, rng, adist, ddist,
					odist, rdist, longdist, latdist
					);
			case 3:
				return std::make_unique<Sheet>(
					gfx, rng, adist, ddist,
					odist, rdist
					);
			case 4:
				return std::make_unique<SkinnedBox>(
					gfx, rng, adist, ddist,
					odist, rdist
					);
			default:
				assert(false && "bad drawable type in factory");
				return {};
			}
		}
	private:
		Graphics& gfx;
		std::mt19937 rng{ std::random_device{}() };
		std::uniform_real_distribution<float> adist{ 0.0f,PI * 2.0f };
		std::uniform_real_distribution<float> ddist{ 0.0f,PI * 0.5f };
		std::uniform_real_distribution<float> odist{ 0.0f,PI * 0.08f };
		std::uniform_real_distribution<float> rdist{ 6.0f,20.0f };
		std::uniform_real_distribution<float> bdist{ 0.4f,3.0f };
		std::uniform_int_distribution<int> latdist{ 5,20 };
		std::uniform_int_distribution<int> longdist{ 10,40 };
		std::uniform_int_distribution<int> typedist{ 0,4 };
	};
	Factory f(wnd.Gfx());
	drawables.reserve(nDrawables);
	std::generate_n(std::back_inserter(drawables), nDrawables, f);

	//const auto s = Surface::FromFile("images//test.png");
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
	wnd.Gfx().SetCamera(DirectX::XMMatrixTranslation(0.0f, 0.0f, 20.0f));

}

APP::~APP()
{
	

}



int APP::Go()
{
	while (1)
	{
		//process all message pending,but not to block
		if (const auto ecode = Window::ProcessMessages())
		{
			return *ecode;
		}
		DoFrame();
	}
}

void APP::DoFrame()
{
	/*while (!wnd.mouse.IsEmpty())
	{
		const auto e = wnd.mouse.Read();
		switch (e.GetType())
		{
		case Mouse::Event::Type::Leave:
			wnd.SetTitle("Gone");
			break;
		case Mouse::Event::Type::Move:
		{
			std::ostringstream oss;
			oss << "Mouse Position:(" << e.GetPosX() << "," << e.GetPosY();
			wnd.SetTitle(oss.str());
		}

		default:
			break;
		}
	}*/
	/*const float t = timer.Peek();
	std::ostringstream oss;
	oss << "Time elapsed :" << t;
	wnd.SetTitle(oss.str());*/
	/*wnd.Gfx().ClearBuffer(0, 0, 0);
	wnd.Gfx().DrawTestTriangle(
		-timer.Peek(),
		0.0f,
		0.0f
	);
	wnd.Gfx().DrawTestTriangle(
		timer.Peek(),
		wnd.mouse.GetPosX()/400.0f-1.0f,
		-wnd.mouse.GetPosY()/300.0f+1.0f
	);*/

	auto dt = timer.Mark()*speed_factor;
	

	
	wnd.Gfx().BeginFrame(0.07f, 0.0f, 0.12f);

	for (auto& b:drawables)
	{
		b->Update(dt);
		b->Update(wnd.kbd.KeyIsPressed(VK_SPACE) ? 0.0f : dt);
		b->Draw(wnd.Gfx());
	}

	
	/*if (show_demo_window)
	{
		ImGui::ShowDemoWindow(&show_demo_window);
	}
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());*/
	
	//imgui window to control simulation speed
	static char buffer[1024];

	if (ImGui::Begin("simulation speed"))
	{
		ImGui::SliderFloat("speed factor", &speed_factor, 0.0f, 4.0f);
		ImGui::Text("Appliaction average %.3f ms/frame (%.1f FPS)",1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::InputText("Butts", buffer, sizeof(buffer));
	}
	ImGui::End();

	//present
	wnd.Gfx().EndFrame();

}



