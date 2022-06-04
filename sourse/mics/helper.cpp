#include "../../headers/mics/helper.hpp"


bool Helper::isPointInRect(const int x, const int y, RectF rect)
{
	return (x >= rect.X && x < rect.X + rect.Width && y >= rect.Y && y < rect.Y + rect.Height);
}

bool Helper::isPointInRect(const int x, const int y, RECT rect)
{
	return (x >= rect.left && x < rect.left + rect.right - rect.left && y >= rect.top && y < rect.top + rect.bottom - rect.top);
}
bool Helper::isPointInRect(const int x, const int y, Rect rect)
{
	return (x >= rect.X && x < rect.X + rect.Width && y >= rect.Y && y < rect.Y + rect.Height);
}

bool Helper::isPointInRect(const int x, const int y, const int x2, const int y2)
{
	return  (x >= x2 && x < x2 + 15 && y >= y2 && y < y2 + 15);
}