#include "../../headers/gui/ProgressBar.hpp"
#include <Windows.h>
#include <gdiplus.h>
#include "../../headers/gui/mics/rectCorner.hpp"

ProgressBar::ProgressBar(Rect rect)
{
	this->rect = rect;
	this->value = 0;
	this->maxValue = 100;
	this->headerText = L"Loading...";
	this->draw = false;
	this->r = {rect.X, rect.Y, rect.X + rect.Width, rect.Y + rect.Height };
	pen = std::make_unique<SolidBrush>(Color(150, 132, 12, 1));
	brush = std::make_unique<SolidBrush >(Color(255, 255, 255, 255));
	this->arialFont = std::make_unique<Font>(L"Arial", (REAL)12);
}
bool ProgressBar::ActionDraw()
{
	return draw = !draw;
}
void ProgressBar::setValue(int newValue)
{
	previousValue = value;
	value = newValue;
}
void ProgressBar::SetString(std::wstring str)
{
	headerText = str;
}
void ProgressBar::drawBar(Graphics* g)
{
	if (!draw)
		return;

	int progressBarHeight = r.bottom - r.top;

	Rect progressPosition;
	progressPosition.X = r.left;
	progressPosition.Y = r.top;
	progressPosition.Height = abs(r.bottom - r.top);

	float fractionalProgress = (float)value / (float)maxValue;
	if (fractionalProgress > 0.995)
		fractionalProgress = 0.995;

	int totalBarWidth = rect.Width - 13;

	int currentBarWidth = (int)((float)totalBarWidth * fractionalProgress);
	if (currentBarWidth > totalBarWidth)
		currentBarWidth = totalBarWidth;
	progressPosition.Width = currentBarWidth;

	int indicatorX = (int)(r.left + currentBarWidth - (progressBarHeight / 2.35f));

	Corner::FillRoundRect(g, brush.get(), rect, (Color(255, 255, 255, 255)), 5);
	Corner::FillRoundRect(g, pen.get(), {rect.X,rect.Y,indicatorX ,rect.Height}, (Color(255, 255, 255, 255)), 5);
	
}

void ProgressBar::drawText(Graphics* g)
{
	if (!draw)
		return;

	int padding = (r.right - r.left) * 0.02;
	RectF layout = RectF(rect.X + padding, rect.Y - 300, rect.X + rect.Width - 2 * padding, rect.Y + rect.Height);
	StringFormat sf(StringFormatFlagsNoWrap);
	sf.SetLineAlignment(StringAlignmentCenter);
	g->DrawString(headerText.c_str(), -1, arialFont.get(), layout, &sf, brush.get());
}

void ProgressBar::invalidateProgressBar(HWND hWnd)
{

	InvalidateRect(hWnd, 0, true);
}