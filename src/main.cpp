#include "window.hpp"

int WINAPI WinMain(
	HINSTANCE /*hInstance*/, 
	HINSTANCE /*hPrevInstance*/, 
	LPSTR /*lpCmdLine*/, 
	int /*nCmdShow*/)
{
	sr::Window window(800, 600, L"test");

	while (window.Update())
	{
	}

	return 0;
}
