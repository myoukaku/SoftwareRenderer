#include "window.hpp"
#include "renderer.hpp"
#include "vertex.hpp"
#include <vector>
#include <cstdint>
#include <chrono>
#include <sstream>

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

	float r1 = 0.0f;
	float r2 = 0.0f;

	auto current_time = std::chrono::system_clock::now();

	while (window.Update())
	{
		auto t = std::chrono::system_clock::now();
		float elapsed_time = std::chrono::duration<float>(t - current_time).count();
		current_time = t;

		{
			std::stringstream ss;
			ss << "SoftwareRenderer: " << elapsed_time << " sec";
			window.SetTitle(ss.str().c_str());
		}

		renderer.SetMatrix(sr::RotationXMatrix(r1) * sr::RotationYMatrix(r2));
		r1 += 1.0f * elapsed_time;
		r2 += 1.1f * elapsed_time;

		renderer.Begin();

		renderer.Draw(sr::FillMode::Solid, vertices, indices);

		renderer.End();
	}

	return 0;
}
