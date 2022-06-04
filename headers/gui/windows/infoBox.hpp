#pragma once
#include <memory>
#include "../../stdafx.h"
#include "../../../headers/gui/buttons.hpp"
class InfoBox
{
public:
	InfoBox();
protected:
	std::wstring text;
	RectF rect;
	RECT position;
protected:
	std::unique_ptr<SolidBrush>textColor = nullptr;
	std::unique_ptr<Font>arialFont = nullptr;
	StringFormat stringCenter;
	std::unique_ptr<SolidBrush> backgroundColor;
public: 
	void SetText(const std::wstring text);
	void Draw(Graphics*);
	std::unique_ptr<Buttons> closeInfo;
};