#pragma once

#include "window.hpp"
#undef min
#undef max
#include <algorithm>

namespace sr
{

class Renderer
{
public:
	Renderer(Window* window)
		: m_window(window)
	{
	}

	~Renderer()
	{
	}

	void Begin()
	{
		m_window->GetBitmap()->Clear(m_clear_color);
	}

	void End()
	{
		::InvalidateRect(m_window->GetHWND(), NULL, FALSE);
	}

	void DrawLine(int x0, int y0, int x1, int y1, std::uint32_t col)
	{
		auto bitmap = m_window->GetBitmap();

		const int dx = std::abs(x1 - x0);
		const int dy = std::abs(y1 - y0);
		const int sx = x0 < x1 ? 1 : -1;
		const int sy = y0 < y1 ? 1 : -1;
		int err = dx - dy;
		int tx = x0;
		int ty = y0;

		for (;;)
		{
			bitmap->SetColor(tx, ty, col);
			if (tx == x1 && ty == y1)
			{
				break;
			}

			const int e2 = 2 * err;

			if (e2 > -dy)
			{
				err -= dy;
				tx += sx;
			}

			if (e2 <  dx)
			{
				err += dx;
				ty += sy;
			}
		}
	}

	void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, std::uint32_t col)
	{
		DrawLine(x0, y0, x1, y1, col);
		DrawLine(x1, y1, x2, y2, col);
		DrawLine(x2, y2, x0, y0, col);
	}

private:
	void DrawHorizontalLine(int x0, int x1, int y, std::uint32_t col)
	{
		auto bitmap = m_window->GetBitmap();
		const int xmin = std::min(x0, x1);
		const int xmax = std::max(x0, x1);
		for (int x = xmin; x <= xmax; ++x)
		{
			bitmap->SetColor(x, y, col);
		}
	}

	void FillFlatTriangle(int x0, int y0, int x1, int y1, int x2, int y2, std::uint32_t col, bool flag)
	{
		auto bitmap = m_window->GetBitmap();

		const int dx1 = std::abs(x1 - x0);
		const int dy1 = std::abs(y1 - y0);
		const int dx2 = std::abs(x2 - x0);
		const int dy2 = std::abs(y2 - y0);
		const int sx1 = x0 < x1 ? 1 : -1;
		const int sy1 = y0 < y1 ? 1 : -1;
		const int sx2 = x0 < x2 ? 1 : -1;
		const int sy2 = y0 < y2 ? 1 : -1;
		int err1 = dx1 - dy1;
		int err2 = dx2 - dy2;
		int tx1 = x0;
		int ty1 = y0;
		int tx2 = x0;
		int ty2 = y0;

		for (;;)
		{
			bitmap->SetColor(tx1, ty1, col);

			const int e2_1 = 2 * err1;

			if (e2_1 > -dy1)
			{
				err1 -= dy1;
				tx1 += sx1;
			}

			if (e2_1 <  dx1)
			{
				err1 += dx1;
				ty1 += sy1;

				while (ty1 != ty2)
				{
					bitmap->SetColor(tx2, ty2, col);
		
					const int e2_2 = 2 * err2;

					if (e2_2 > -dy2)
					{
						err2 -= dy2;
						tx2 += sx2;
					}

					if (e2_2 <  dx2)
					{
						err2 += dx2;
						ty2 += sy2;
					}
				}

				if (flag || (ty1 != y1 && ty2 != y2))
				{
					DrawHorizontalLine(tx1, tx2, ty1, col);
				}
			}

			if (tx1 == x1 && ty1 == y1)
			{
				break;
			}
		}
	}

public:
	void FillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, std::uint32_t col)
	{
		if (y0 > y1)
		{
			std::swap(y0, y1);
			std::swap(x0, x1);
		}
		if (y0 > y2)
		{
			std::swap(y0, y2);
			std::swap(x0, x2);
		}
		if (y1 > y2)
		{
			std::swap(y1, y2);
			std::swap(x1, x2);
		}

		if (y1 == y2)
		{
			// Bottom-flat triangle
			FillFlatTriangle(x0, y0, x1, y1, x2, y2, col, true);
		}
		else if (y0 == y1)
		{
			// Top-flat triangle
			FillFlatTriangle(x2, y2, x1, y1, x0, y0, col, true);
		}
		else
		{
			// general case
			FillFlatTriangle(x0, y0, x1, y1, x2, y2, col, true);
			FillFlatTriangle(x2, y2, x1, y1, x0, y0, col, false);
		}
	}

private:
	Window*			m_window;
	std::uint32_t	m_clear_color = 0x000000;
};

}	// namespace sr
