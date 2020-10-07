#include"App.h"
#include <sstream>
APP::APP():wnd(800,600,"the game box")
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
	wnd.Gfx().ClearBuffer(1, 0, 0);
	wnd.Gfx().EndFrame();

}



