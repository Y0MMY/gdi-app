#include "headers/mics/Books.hpp"
#include "headers/mics/FileTXT.hpp"
#include "headers/mics/exception.hpp"
#include "headers/mics/virtualClass.hpp"
#include "headers/gui/windows/window.hpp"
#include "App.hpp"

using namespace std;    


int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	try
	{
		return App{}.Go();
	}
	catch (const MyException& e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
		OutputDebugStringA(e.what());
	}
	catch (...)
	{
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
}


