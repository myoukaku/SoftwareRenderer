#pragma once

#include "window.hpp"

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
		int dx = std::abs(x1-x0);
		int dy = std::abs(y1-y0);
		int sx = x0 < x1 ? 1 : -1;
		int sy = y0 < y1 ? 1 : -1;
		int err = dx-dy;
		auto bitmap = m_window->GetBitmap();
		for (;;)
		{
			bitmap->SetColor(x0, y0, col);
			if (x0 == x1 && y0 == y1)
			{
				break;
			}
			int e2 = 2*err;
			if (e2 > -dy)
			{
				err = err - dy;
				x0 += sx;
			}
			if (e2 <  dx)
			{
				err = err + dx;
				y0 += sy;
			}
		}
	}

private:
	Window*			m_window;
	std::uint32_t	m_clear_color = 0x404040;
};

}	// namespace sr
