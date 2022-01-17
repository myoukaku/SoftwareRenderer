#include "window.hpp"
#include "renderer.hpp"
#include "vertex.hpp"
#include <vector>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	const int width = 800;
	const int height = 600;

	sr::Window window(width, height, L"test");
	sr::Renderer renderer(&window);

	renderer.SetViewport(0, 0, width, height);

	std::vector<sr::Vertex> vertices =
	{
		{{ 0.0f,  0.9f, 0.0f}, {1.0f, 0.0f, 0.0f}},
		{{-0.9f, -0.9f, 0.0f}, {0.0f, 1.0f, 0.0f}},
		{{ 0.9f, -0.9f, 0.0f}, {0.0f, 0.0f, 1.0f}},
	};

	while (window.Update())
	{
		renderer.Begin();

		renderer.Draw(sr::FillMode::Solid, vertices);

		renderer.End();
	}

	return 0;
}
