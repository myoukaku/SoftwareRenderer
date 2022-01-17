#pragma once

namespace sr
{

struct Vec3
{
	float x;
	float y;
	float z;

	float& operator[](std::size_t i)
	{
		return *((&x) + i);
	}

	const float& operator[](std::size_t i) const
	{
		return *((&x) + i);
	}
};

struct Vec4
{
	float x;
	float y;
	float z;
	float w;

	float& operator[](std::size_t i)
	{
		return *((&x) + i);
	}

	const float& operator[](std::size_t i) const
	{
		return *((&x) + i);
	}
};

struct Mat4
{
	float m[4][4];
};

inline Mat4 ViewportMatrix(float x, float y, float w, float h)
{
	w = w/2;
	h = h/2;
	return
	{{
		{ w,   0,   0, 0 },
		{ 0,  -h,   0, 0 },
		{ 0,   0,   1, 0 },
		{ x+w, y+h, 0, 1 },
	}};
}

inline Vec4 operator*(const Vec4& v, const Mat4& m)
{
	Vec4 result{};

	for (std::size_t j = 0; j < 4; ++j)
	{
		for (std::size_t k = 0; k < 4; ++k)
		{
			result[j] += v[k] * m.m[k][j];
		}
	}

	return result;
}

inline Vec3 operator*(const Vec3& v, const Mat4& m)
{
	auto t = Vec4{v.x, v.y, v.z, 1} * m;
	return {t.x, t.y, t.z};
}

}	// namespace sr
