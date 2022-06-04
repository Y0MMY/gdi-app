#pragma once
#include "infoBox.hpp"
class input : public InfoBox
{
public:
	input();
	const void Draw(Graphics* gt);
	const void update(UINT key, int x, int y);
	const bool ClickInput(HWND hWnd,int x, int y);
private:
	const void StringInput(Graphics* g);
	const std::wstring GetContent();
	StringFormat stringCenter;
	StringFormat textFormat;
	Rect rInput;
	std::wstring content;
	bool isInFocus = false;
	std::unique_ptr<SolidBrush> fillColor;
	std::unique_ptr<SolidBrush> focusColor;
	HWND hWnd = nullptr;
};

