#include "window.hpp"
#include "renderer.hpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	const int width = 800;
	const int height = 600;

	sr::Window window(width, height, L"test");
	sr::Renderer renderer(&window);

	while (window.Update())
	{
		renderer.Begin();

		renderer.DrawLine(400, 300, 800, 300, 0xFF0000);
		renderer.DrawLine(400, 300, 800,   0, 0x00FF00);
		renderer.DrawLine(400, 300, 400,   0, 0x0000FF);
		renderer.DrawLine(400, 300,   0,   0, 0xFFFF00);
		renderer.DrawLine(400, 300,   0, 300, 0x00FFFF);
		renderer.DrawLine(400, 300,   0, 600, 0xFF00FF);
		renderer.DrawLine(400, 300, 400, 600, 0xFFFFFF);
		renderer.DrawLine(400, 300, 800, 600, 0x808080);

		renderer.End();
	}

	return 0;
}
