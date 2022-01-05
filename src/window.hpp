#pragma once

#include "bitmap.hpp"
#include <Windows.h>
#include <memory>

namespace sr
{

class Window
{
public:
	Window(int width, int height, const TCHAR* title)
	{
		auto hwnd = Create(width, height, title);

		::ShowWindow(hwnd, SW_SHOW);
	}

	~Window()
	{
	}

	bool Update()
	{
		::MSG msg;

		while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				return false;
			}

			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		return true;
	}

private:
	void OnCreate(HWND hwnd)
	{
		auto hdc = GetDC(hwnd);
		m_bitmap = std::make_unique<Bitmap>(hdc, 800, 600);
		ReleaseDC(hwnd, hdc);
	}

	void OnPaint(HWND hwnd)
	{
		PAINTSTRUCT ps;
		auto hdc = ::BeginPaint(hwnd, &ps);
		BitBlt(hdc, 0, 0, m_bitmap->width(), m_bitmap->height(), m_bitmap->hdc(), 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);
	}

	static LRESULT CALLBACK
	WndProc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
	{
		Window* this_ = nullptr;

		if (msg == WM_CREATE)
		{
			// Windowクラスへのポインタをセットします。
			// これはCreateWindowExの引数で渡されたものです。
			auto const* create_struct = reinterpret_cast<LPCREATESTRUCT>(l_param);
			this_ = reinterpret_cast<Window*>(create_struct->lpCreateParams);
			::SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this_));
		}
		else
		{
			// Windowクラスへのポインタを取得します。
			// WM_CREATEより前に別のメッセージが来ることがあり、その場合nullptrになることに注意
			this_ = reinterpret_cast<Window*>(::GetWindowLongPtr(hwnd, GWLP_USERDATA));
		}

		if (!this_)
		{
			return ::DefWindowProc(hwnd, msg, w_param, l_param);
		}

		switch (msg)
		{
		case WM_CREATE:
			this_->OnCreate(hwnd);
			break;

		case WM_PAINT:
			this_->OnPaint(hwnd);
			break;

		case WM_DESTROY:
			::PostQuitMessage(0);
			return 0;
		}

		return ::DefWindowProc(hwnd, msg, w_param, l_param);
	}

	static bool
	RegisterWindowClass(const TCHAR* class_name)
	{
		auto const instance = ::GetModuleHandle(nullptr);
		WNDCLASSEX const wc =
		{
			sizeof(wc),
			CS_OWNDC,
			WndProc,
			0,
			0,
			instance,
			::LoadIcon(nullptr, IDI_APPLICATION),
			::LoadCursor(nullptr, IDC_ARROW),
			::CreateSolidBrush(RGB(0, 0, 0)),
			nullptr,
			class_name,
			nullptr
		};

		return ::RegisterClassEx(&wc) != 0;
	}

	HWND Create(int width, int height, const TCHAR* title)
	{
		auto const class_name = L"test window";

		if (!RegisterWindowClass(class_name))
		{
			return nullptr;
		}

		DWORD const window_style_ex = WS_EX_OVERLAPPEDWINDOW;
		DWORD const window_style = WS_OVERLAPPEDWINDOW;
		bool  const has_menu = false;

		::RECT r;
		::SetRect(&r, 0, 0, width, height);
		::AdjustWindowRectEx(&r, window_style, has_menu, window_style_ex);

		return ::CreateWindowEx(
				   window_style_ex,
				   class_name,
				   title,
				   window_style,
				   0,	// x
				   0,	// y
				   r.right - r.left,
				   r.bottom - r.top,
				   0,	// parent
				   0,	// menu
				   ::GetModuleHandle(nullptr),
				   this);
	}

private:
	std::unique_ptr<Bitmap>		m_bitmap;
};

}	// namespace sr
