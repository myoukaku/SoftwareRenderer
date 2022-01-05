#include "window.hpp"

int WINAPI WinMain(
	HINSTANCE /*hInstance*/, 
	HINSTANCE /*hPrevInstance*/, 
	LPSTR /*lpCmdLine*/, 
	int /*nCmdShow*/)
{
	const int width = 800;
	const int height = 600;

	sr::Window window(width, height, L"test");

	while (window.Update())
	{
	}

	return 0;
}
