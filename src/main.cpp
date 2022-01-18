#include "window.hpp"
#include "renderer.hpp"
#include "vertex.hpp"
#include <vector>
#include <cstdint>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	const int width = 800;
	const int height = 600;

	sr::Window window(width, height, L"test");
	sr::Renderer renderer(&window);

	renderer.SetViewport(0, 0, width, height);

#if 0
	const std::vector<sr::Vertex> vertices =
	{
		{{ 0.0f,  0.9f, 0.0f}, {1.0f, 0.0f, 0.0f}},
		{{-0.9f, -0.9f, 0.0f}, {0.0f, 1.0f, 0.0f}},
		{{ 0.9f, -0.9f, 0.0f}, {0.0f, 0.0f, 1.0f}},
	};
#endif

	const std::vector<sr::Vertex> vertices =
	{
		{{ 0.5f,  0.5f,  0.5f}, { 1.0f, 0.0f, 1.0f }},
		{{ 0.5f,  0.5f, -0.5f}, { 1.0f, 0.0f, 1.0f }},
		{{ 0.5f, -0.5f,  0.5f}, { 1.0f, 0.0f, 1.0f }},
		{{ 0.5f, -0.5f, -0.5f}, { 1.0f, 0.0f, 1.0f }},

		{{-0.5f,  0.5f,  0.5f}, { 0.0f, 1.0f, 1.0f }},
		{{-0.5f, -0.5f,  0.5f}, { 0.0f, 1.0f, 1.0f }},
		{{-0.5f,  0.5f, -0.5f}, { 0.0f, 1.0f, 1.0f }},
		{{-0.5f, -0.5f, -0.5f}, { 0.0f, 1.0f, 1.0f }},

		{{-0.5f,  0.5f,  0.5f}, { 1.0f, 0.0f, 0.0f }},
		{{ 0.5f,  0.5f,  0.5f}, { 1.0f, 0.0f, 0.0f }},
		{{-0.5f, -0.5f,  0.5f}, { 1.0f, 0.0f, 0.0f }},
		{{ 0.5f, -0.5f,  0.5f}, { 1.0f, 0.0f, 0.0f }},

		{{-0.5f,  0.5f, -0.5f}, { 0.0f, 1.0f, 0.0f }},
		{{-0.5f, -0.5f, -0.5f}, { 0.0f, 1.0f, 0.0f }},
		{{ 0.5f,  0.5f, -0.5f}, { 0.0f, 1.0f, 0.0f }},
		{{ 0.5f, -0.5f, -0.5f}, { 0.0f, 1.0f, 0.0f }},

		{{-0.5f,  0.5f, -0.5f}, { 0.0f, 0.0f, 1.0f }},
		{{ 0.5f,  0.5f, -0.5f}, { 0.0f, 0.0f, 1.0f }},
		{{-0.5f,  0.5f,  0.5f}, { 0.0f, 0.0f, 1.0f }},
		{{ 0.5f,  0.5f,  0.5f}, { 0.0f, 0.0f, 1.0f }},

		{{-0.5f, -0.5f, -0.5f}, { 1.0f, 1.0f, 0.0f }},
		{{-0.5f, -0.5f,  0.5f}, { 1.0f, 1.0f, 0.0f }},
		{{ 0.5f, -0.5f, -0.5f}, { 1.0f, 1.0f, 0.0f }},
		{{ 0.5f, -0.5f,  0.5f}, { 1.0f, 1.0f, 0.0f }},
	};
	const std::vector<std::uint32_t> indices =
	{
		0+0, 0+2, 0+1,
		0+1, 0+2, 0+3,

		4+0, 4+2, 4+1,
		4+1, 4+2, 4+3,

		8+0, 8+2, 8+1,
		8+1, 8+2, 8+3,

		12+0, 12+2, 12+1,
		12+1, 12+2, 12+3,

		16+0, 16+2, 16+1,
		16+1, 16+2, 16+3,

		20+0, 20+2, 20+1,
		20+1, 20+2, 20+3,
	};

	while (window.Update())
	{
		renderer.Begin();

		renderer.Draw(sr::FillMode::Solid, vertices, indices);

		renderer.End();
	}

	return 0;
}
