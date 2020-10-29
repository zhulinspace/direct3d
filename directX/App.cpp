#include"App.h"
#include<directX/Drawable/Melon.h>
#include<directX/Drawable/Box.h>
#include<directX/Drawable/Pyramid.h>
#include<directX/ChiliMath.h>
#include<memory>
#include<algorithm>
#include <sstream>
#include<random>

APP::APP():wnd(800,600,"the game box")
{
	/*std::mt19937 rng(std::random_device{}());
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
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 10.0f));*/

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
		std::uniform_int_distribution<int> typedist{ 0,2 };
	};
	Factory f(wnd.Gfx());
	drawables.reserve(nDrawables);
	std::generate_n(std::back_inserter(drawables), nDrawables, f);
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));

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
	for (auto& b:drawables)
	{
		b->Update(dt);
		b->Draw(wnd.Gfx());
	}

	wnd.Gfx().EndFrame();

}



