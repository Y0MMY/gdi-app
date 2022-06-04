#pragma once
#include "headers/gui/windows/window.hpp"

class App
{
public:
	App();
	// master frame / message loop
	int Go();
private:
	void DoFrame();
private:
	Window wnd;
	std::unique_ptr<std::thread> th;
};