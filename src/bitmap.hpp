#pragma once

#include <Windows.h>
#include <cstdint>

namespace sr
{

class Bitmap
{
public:
	Bitmap(HDC hdc, int width, int height)
		: m_width(width)
		, m_height(height)
	{
		BITMAPINFO info;
		info.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
		info.bmiHeader.biWidth       = width;
		info.bmiHeader.biHeight      = -height;	// 上から順にピクセルが並ぶようにする
		info.bmiHeader.biPlanes      = 1;
		info.bmiHeader.biBitCount    = 32;
		info.bmiHeader.biCompression = BI_RGB;
		m_handle = ::CreateDIBSection(
			NULL, &info, DIB_RGB_COLORS, reinterpret_cast<void**>(&m_pixels), NULL, 0);

		m_hdc = CreateCompatibleDC(hdc);
		m_handle_old = (HBITMAP)SelectObject(m_hdc, m_handle);
	}

	~Bitmap()
	{
		SelectObject(m_hdc, m_handle_old);

		// m_pixels を自分で解放してはいけない
		DeleteObject(m_handle);	// Bitmapを削除した時、m_pixelsも自動的に解放される

		DeleteDC(m_hdc);
	}

	int width(void) const
	{
		return m_width;
	}

	int height(void) const
	{
		return m_height;
	}

	HDC hdc(void) const
	{
		return m_hdc;
	}

	void Clear(std::uint32_t col)
	{
		for (int i = 0; i < m_width * m_height; ++i)
		{
			m_pixels[i] = col;
		}
	}

	void SetColor(int x, int y, std::uint32_t col)
	{
		if (0 <= x && x < m_width &&
			0 <= y && y < m_height)
		{
			m_pixels[y * m_width + x] = col;
		}
	}

private:
	int				m_width;
	int				m_height;
	std::uint32_t*	m_pixels = nullptr;
	HBITMAP			m_handle = NULL;
	HBITMAP			m_handle_old = NULL;
	HDC				m_hdc = NULL;
};

}	// namespace sr
