#pragma once
#include "../../headers/stdafx.h"


class ProgressBar
{
public:
	ProgressBar(Rect rect);

	void setValue(int newValue);
	void drawBar(Graphics* g);
	void drawText(Graphics* g);
	void invalidateProgressBar(HWND hWnd);
	bool ActionDraw();
	void SetString(std::wstring);
private:
	std::unique_ptr<Font>arialFont = nullptr;
	std::unique_ptr<SolidBrush> pen;
	std::unique_ptr <SolidBrush > brush;
	Rect rect, headerTextRect, valueTextRect;
	RECT r;
	std::wstring headerText;
	int previousValue;
	int value;
	int maxValue;
	bool draw;
	long long lastDraw;
};
