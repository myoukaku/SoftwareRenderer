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

private:
	Window*			m_window;
	std::uint32_t	m_clear_color = 0x404040;
};

}	// namespace sr
