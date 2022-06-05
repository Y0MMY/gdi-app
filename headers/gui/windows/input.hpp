#pragma once
#include "infoBox.hpp"
class input : public InfoBox
{
public:
	input();
	const void Draw(Graphics* gt);
	const void update(UINT key, int x, int y);
	const bool ClickInput(HWND hWnd,int x, int y);
	const std::string GetContent() const;
private:
	const void StringInput(Graphics* g);
	StringFormat stringCenter;
	StringFormat textFormat;
	Rect rInput;
	std::wstring content;
	std::string Scontent;
	bool isInFocus = false;
	std::unique_ptr<SolidBrush> fillColor;
	std::unique_ptr<SolidBrush> focusColor;
	HWND hWnd = nullptr;
};

