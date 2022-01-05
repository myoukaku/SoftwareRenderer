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

		renderer.End();
	}

	return 0;
}
