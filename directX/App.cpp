#include"App.h"
#include <sstream>
#include<random>

APP::APP():wnd(800,600,"the game box")
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
	std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
	for (auto i = 0; i < 80; i++)
	{
		boxes.push_back(
			std::make_unique<Box>(
				wnd.Gfx(), rng, adist, ddist, odist, rdist
				)
		);
	}
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 10.0f));
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

	auto dt = timer.Mark();
	wnd.Gfx().ClearBuffer(0.07f, 0.0f, 0.12f);
	for (auto& b:boxes)
	{
		b->Update(dt);
		b->Draw(wnd.Gfx());
	}

	wnd.Gfx().EndFrame();

}



