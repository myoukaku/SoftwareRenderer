#include <Windows.h>

namespace sr
{

static LRESULT CALLBACK
WndProc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
	switch (msg)
	{
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

static HWND
OpenWindow(int width, int height, const TCHAR* title)
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
			   nullptr);
}

static bool
UpdateWindow()
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

}	// namespace sr

int WINAPI WinMain(
	HINSTANCE /*hInstance*/, 
	HINSTANCE /*hPrevInstance*/, 
	LPSTR /*lpCmdLine*/, 
	int /*nCmdShow*/)
{
	auto hwnd = sr::OpenWindow(800, 600, L"test");
	::ShowWindow(hwnd, SW_SHOW);

	while (sr::UpdateWindow())
	{
	}

	return 0;
}
