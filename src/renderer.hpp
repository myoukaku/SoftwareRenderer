#pragma once

#include "window.hpp"
#include "vertex.hpp"
#include "math.hpp"
#undef min
#undef max
#include <algorithm>
#include <cmath>
#include <vector>

namespace sr
{

enum class FillMode
{
	Solid,
	Wireframe,
};

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

	void DrawLine(
		int x0, int y0, std::uint32_t c0,
		int x1, int y1, std::uint32_t c1)
	{
		auto bitmap = m_window->GetBitmap();

		const int dx = std::abs(x1 - x0);
		const int dy = std::abs(y1 - y0);
		const int sx = x0 < x1 ? 1 : -1;
		const int sy = y0 < y1 ? 1 : -1;
		int err = dx - dy;
		int tx = x0;
		int ty = y0;

		const int r0 = (c0      ) & 0xFF;
		const int g0 = (c0 >>  8) & 0xFF;
		const int b0 = (c0 >> 16) & 0xFF;
		const int r1 = (c1      ) & 0xFF;
		const int g1 = (c1 >>  8) & 0xFF;
		const int b1 = (c1 >> 16) & 0xFF;
		const float dr = float(r1 - r0) / std::max(dx, dy);
		const float dg = float(g1 - g0) / std::max(dx, dy);
		const float db = float(b1 - b0) / std::max(dx, dy);
		float tr = static_cast<float>(r0);
		float tg = static_cast<float>(g0);
		float tb = static_cast<float>(b0);

		for (;;)
		{
			const auto r = static_cast<std::uint32_t>(tr) & 0xFF;
			const auto g = static_cast<std::uint32_t>(tg) & 0xFF;
			const auto b = static_cast<std::uint32_t>(tb) & 0xFF;
			bitmap->SetColor(tx, ty, (b << 16) | (g << 8) | r);

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

			tr += dr;
			tg += dg;
			tb += db;
		}
	}

	void DrawTriangle(
		int x0, int y0, std::uint32_t c0,
		int x1, int y1, std::uint32_t c1,
		int x2, int y2, std::uint32_t c2)
	{
		DrawLine(x0, y0, c0, x1, y1, c1);
		DrawLine(x1, y1, c1, x2, y2, c2);
		DrawLine(x2, y2, c2, x0, y0, c0);
	}

private:
	void DrawHorizontalLine(int x0, int x1, int y,
		float r0, float g0, float b0,
		float r1, float g1, float b1)
	{
		auto bitmap = m_window->GetBitmap();

		// 必ず x0 < x1 になるようにする

		if (x0 > x1)
		{
			std::swap(x0, x1);
			std::swap(r0, r1);
			std::swap(g0, g1);
			std::swap(b0, b1);
		}

		const float dr = float(r1 - r0) / (x1 - x0);
		const float dg = float(g1 - g0) / (x1 - x0);
		const float db = float(b1 - b0) / (x1 - x0);

		for (int x = x0; x <= x1; ++x)
		{
			const auto r = static_cast<std::uint32_t>(r0) & 0xFF;
			const auto g = static_cast<std::uint32_t>(g0) & 0xFF;
			const auto b = static_cast<std::uint32_t>(b0) & 0xFF;
			bitmap->SetColor(x, y, (b << 16) | (g << 8) | r);
			r0 += dr;
			g0 += dg;
			b0 += db;
		}
	}

	void FillFlatTriangle(
		int x0, int y0, std::uint32_t c0,
		int x1, int y1, std::uint32_t c1,
		int x2, int y2, std::uint32_t c2)
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

		const int r0 = (c0      ) & 0xFF;
		const int g0 = (c0 >>  8) & 0xFF;
		const int b0 = (c0 >> 16) & 0xFF;
		const int r1 = (c1      ) & 0xFF;
		const int g1 = (c1 >>  8) & 0xFF;
		const int b1 = (c1 >> 16) & 0xFF;
		const int r2 = (c2      ) & 0xFF;
		const int g2 = (c2 >>  8) & 0xFF;
		const int b2 = (c2 >> 16) & 0xFF;
		const float dr1 = float(r1 - r0) / std::max(dx1, dy1);
		const float dg1 = float(g1 - g0) / std::max(dx1, dy1);
		const float db1 = float(b1 - b0) / std::max(dx1, dy1);
		const float dr2 = float(r2 - r0) / std::max(dx2, dy2);
		const float dg2 = float(g2 - g0) / std::max(dx2, dy2);
		const float db2 = float(b2 - b0) / std::max(dx2, dy2);
		float tr1 = static_cast<float>(r0);
		float tg1 = static_cast<float>(g0);
		float tb1 = static_cast<float>(b0);
		float tr2 = static_cast<float>(r0);
		float tg2 = static_cast<float>(g0);
		float tb2 = static_cast<float>(b0);

		for (;;)
		{
			{
				const auto r = static_cast<std::uint32_t>(tr1) & 0xFF;
				const auto g = static_cast<std::uint32_t>(tg1) & 0xFF;
				const auto b = static_cast<std::uint32_t>(tb1) & 0xFF;
				bitmap->SetColor(tx1, ty1, (b << 16) | (g << 8) | r);
			}

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
					{
						const auto r = static_cast<std::uint32_t>(tr2) & 0xFF;
						const auto g = static_cast<std::uint32_t>(tg2) & 0xFF;
						const auto b = static_cast<std::uint32_t>(tb2) & 0xFF;
						bitmap->SetColor(tx2, ty2, (b << 16) | (g << 8) | r);
					}

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

					tr2 += dr2;
					tg2 += dg2;
					tb2 += db2;
				}

				DrawHorizontalLine(tx1, tx2, ty1, tr1, tg1, tb1, tr2, tg2, tb2);
			}

			tr1 += dr1;
			tg1 += dg1;
			tb1 += db1;

			if (tx1 == x1 && ty1 == y1)
			{
				break;
			}
		}
	}

public:
	void FillTriangle(
		int x0, int y0, std::uint32_t c0,
		int x1, int y1, std::uint32_t c1,
		int x2, int y2, std::uint32_t c2)
	{
		// 必ず y0 < y1 < y2 になるようにする

		if (y0 > y1)
		{
			std::swap(y0, y1);
			std::swap(x0, x1);
			std::swap(c0, c1);
		}
		if (y0 > y2)
		{
			std::swap(y0, y2);
			std::swap(x0, x2);
			std::swap(c0, c2);
		}
		if (y1 > y2)
		{
			std::swap(y1, y2);
			std::swap(x1, x2);
			std::swap(c1, c2);
		}

		if (y1 == y2)
		{
			// Bottom-flat triangle
			FillFlatTriangle(x0, y0, c0, x1, y1, c1, x2, y2, c2);
		}
		else if (y0 == y1)
		{
			// Top-flat triangle
			FillFlatTriangle(x2, y2, c2, x1, y1, c1, x0, y0, c0);
		}
		else
		{
			// general case
			FillFlatTriangle(x0, y0, c0, x1, y1, c1, x2, y2, c2);
			FillFlatTriangle(x2, y2, c2, x1, y1, c1, x0, y0, c0);
		}
	}

private:
	std::uint32_t ToColorU32(const Vec3& col) const
	{
		return
			(std::uint32_t(col.x * 255) << 16) |
			(std::uint32_t(col.y * 255) <<  8) |
			(std::uint32_t(col.z * 255));
	}

	void DrawImpl(FillMode mode, const Vertex& v0, const Vertex& v1, const Vertex& v2)
	{
		const auto p0 = v0.pos * m_viewport_mat;
		const auto p1 = v1.pos * m_viewport_mat;
		const auto p2 = v2.pos * m_viewport_mat;

		const std::uint32_t c0 = ToColorU32(v0.col);
		const std::uint32_t c1 = ToColorU32(v1.col);
		const std::uint32_t c2 = ToColorU32(v2.col);

		if (mode == FillMode::Solid)
		{
			FillTriangle(
				(int)p0.x, (int)p0.y, c0,
				(int)p1.x, (int)p1.y, c1,
				(int)p2.x, (int)p2.y, c2);
		}
		else
		{
			DrawTriangle(
				(int)p0.x, (int)p0.y, c0,
				(int)p1.x, (int)p1.y, c1,
				(int)p2.x, (int)p2.y, c2);
		}
	}

public:
	void Draw(FillMode mode, const std::vector<Vertex>& vertices)
	{
		for (std::size_t i = 0; i < vertices.size(); i += 3)
		{
			const auto& v0 = vertices[i+0];
			const auto& v1 = vertices[i+1];
			const auto& v2 = vertices[i+2];

			DrawImpl(mode, v0, v1, v2);
		}
	}

	void Draw(FillMode mode, const std::vector<Vertex>& vertices, const std::vector<std::uint32_t>& indices)
	{
		for (std::size_t i = 0; i < indices.size(); i += 3)
		{
			const auto i0 = indices[i+0];
			const auto i1 = indices[i+1];
			const auto i2 = indices[i+2];

			const auto& v0 = vertices[i0];
			const auto& v1 = vertices[i1];
			const auto& v2 = vertices[i2];

			DrawImpl(mode, v0, v1, v2);
		}
	}

	void SetViewport(int x, int y, int width, int height)
	{
		m_viewport_mat = ViewportMatrix(
			static_cast<float>(x),
			static_cast<float>(y),
			static_cast<float>(width),
			static_cast<float>(height));
	}

private:
	Window*			m_window;
	std::uint32_t	m_clear_color = 0x808080;
	Mat4			m_viewport_mat;
};

}	// namespace sr
