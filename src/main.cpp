#include "window.hpp"
#include "renderer.hpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	const int width = 800;
	const int height = 600;

	sr::Window window(width, height, L"test");
	sr::Renderer renderer(&window);

	float x0 = 0;
	float y0 = 0;
	float x1 = 0;
	float y1 = 0;
	float x2 = 0;
	float y2 = 0;

	float vx0 = 0.09f;
	float vy0 = 0.12f;
	float vx1 = 0.11f;
	float vy1 = 0.08f;
	float vx2 = 0.10f;
	float vy2 = 0.13f;

	while (window.Update())
	{
		renderer.Begin();

//		renderer.FillTriangle(400, 50, 0xFF0000, 50, 550, 0x00FF00, 750, 550, 0x0000FF);
		//renderer.DrawTriangle(400, 50, 0xFF0000, 50, 550, 0x00FF00, 750, 550, 0x0000FF);
//		renderer.FillTriangle(750, 50, 0x800000, 750, 550, 0x008000, 50, 300, 0x0000FF);
		//renderer.DrawTriangle(400, 50, 0xFFFF00, 50, 300, 0x00FFFF, 750, 550, 0xFFFFFF);
//		renderer.FillTriangle(50, 50, 0x000080, 750, 50, 0xFF0000, 400, 550, 0x000080);
		//renderer.FillTriangle(50, 50, 50, 550, 750, 300, 0x00FF00);

		renderer.FillTriangle(
			(int)x0, (int)y0, 0xFF0000,
			(int)x1, (int)y1, 0x00FF00,
			(int)x2, (int)y2, 0x0000FF);

		x0 += vx0;
		if (x0 < 0 || width < x0)
		{
			vx0 = -vx0;
		}
		y0 += vy0;
		if (y0 < 0 || height < y0)
		{
			vy0 = -vy0;
		}
		x1 += vx1;
		if (x1 < 0 || width < x1)
		{
			vx1 = -vx1;
		}
		y1 += vy1;
		if (y1 < 0 || height < y1)
		{
			vy1 = -vy1;
		}
		x2 += vx2;
		if (x2 < 0 || width < x2)
		{
			vx2 = -vx2;
		}
		y2 += vy2;
		if (y2 < 0 || height < y2)
		{
			vy2 = -vy2;
		}

		//renderer.DrawLine(400, 300, 0xFF0000, 800, 300, 0xFF0000);
		//renderer.DrawLine(400, 300, 0x00FF00, 800,   0, 0x00FF00);
		//renderer.DrawLine(400, 300, 0x0000FF, 400,   0, 0x0000FF);
		//renderer.DrawLine(400, 300, 0xFFFF00,   0,   0, 0xFFFF00);
		//renderer.DrawLine(400, 300, 0x00FFFF,   0, 300, 0x00FFFF);
		//renderer.DrawLine(400, 300, 0xFF00FF,   0, 600, 0xFF00FF);
		//renderer.DrawLine(400, 300, 0xFFFFFF, 400, 600, 0xFFFFFF);
		//renderer.DrawLine(400, 300, 0x808080, 800, 600, 0x808080);

		renderer.End();
	}

	return 0;
}
