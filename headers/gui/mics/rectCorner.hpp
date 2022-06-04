#pragma once
#include "../../../headers/stdafx.h"
struct Corner {
	static void GetRoundRectPath(GraphicsPath* pPath, Rect r, int dia);
	static void DrawRoundRect(Graphics* pGraphics, Rect r, Color color, int radius, int width);
	static void FillRoundRect(Graphics* pGraphics, Brush* pBrush, Rect r, Color border, int radius);
};
