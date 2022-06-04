#include "../../headers/gui/buttons.hpp"
#include "../../headers/gui/mics/rectCorner.hpp"
Buttons::Buttons(/* args */) noexcept
{
    this->position = {};
    this->hovered = false;
	this->pressed = false;
	this->clicked = false;
	this->disabled = false;
	this->isColor = false;
}
Buttons::Buttons(const std::wstring text, const Color normal, const Color hovered,const  Color clicked, const RectF rect): Buttons()
{
    this->isColor = true;
    this->text = text;
	this->styleButtons.colorNormal = std::make_unique<SolidBrush>(normal);
	this->styleButtons.colorHovered = std::make_unique<SolidBrush>(hovered);
	this->styleButtons.colorHovered = std::make_unique<SolidBrush>(hovered);
	this->styleButtons._colorClick = std::make_unique<SolidBrush>(clicked);
	this->styleButtons.colorClick = std::make_unique<Color>(clicked);
	this->styleButtons.arialFont = std::make_unique<Font>(L"Arial", (REAL)18);
	this->position.left = rect.X;
	this->position.top = rect.Y;
	this->position.right = rect.X + rect.Width;
	this->position.bottom = rect.Y + rect.Height;
	stringCenter.SetAlignment(StringAlignmentCenter);
	stringCenter.SetLineAlignment(StringAlignmentCenter);
}
void Buttons::invalidateButton(const HWND hWnd)
{
	InvalidateRect(hWnd, &position, true);
	clicked = false;
}
bool Buttons::isHovered() 
{
	return hovered;
}
bool Buttons::isClicked()
{
	if (clicked)
	{
		hovered = false;
		return true;
	}

	return false;
}
void Buttons::draw( Graphics* g) 
{
	 if (isColor) {
	 	if (!hovered && !clicked)
	 	{
	 		Corner::FillRoundRect(g, styleButtons.colorNormal.get(), { position.left, position.top, position.right - position.left, position.bottom - position.top }, *styleButtons.colorClick, 5);
			g->DrawString(
				text.c_str(),
				-1,
				styleButtons.arialFont.get(),
				RectF(position.left, position.top, position.right - position.left, position.bottom - position.top),
				&stringCenter,
				styleButtons.colorHovered.get());
	 	}
	 	else if (hovered)
	 	{
			Corner::FillRoundRect(g, styleButtons.colorHovered.get(), { position.left, position.top, position.right - position.left, position.bottom - position.top }, *styleButtons.colorClick, 5);
			g->DrawString(
				text.c_str(),
				-1,
				styleButtons.arialFont.get(),
				RectF(position.left, position.top, position.right - position.left, position.bottom - position.top),
				&stringCenter,
				styleButtons.colorNormal.get());
	 	}
		else if(clicked)
		{
			Corner::FillRoundRect(g, styleButtons._colorClick.get(), { position.left, position.top, position.right - position.left, position.bottom - position.top }, *styleButtons.colorClick, 5);
			g->DrawString(
				text.c_str(),
				-1,
				styleButtons.arialFont.get(),
				RectF(position.left, position.top, position.right - position.left, position.bottom - position.top),
				&stringCenter,
				styleButtons.colorHovered.get());
		}
	 }
}
void Buttons::DisableButton()
{
	disabled = true;
}
void Buttons::EnableButton()
{
	disabled = false;
}
void Buttons::mouseReleased(HWND hWnd, int x, int y)
{
	if (disabled)
		return;

	if (std::abs(position.left - x) < 0)
		x = position.left;
	if (Helper::isPointInRect(x, y, position))
	{
		pressed = false;
		hovered = true;
		invalidateButton(hWnd);
		clicked = true;
	}
}
void Buttons::mouseMoved(HWND hWnd, int x, int y)
{
	if (disabled)
		return;

	if (std::abs(position.left - x) < 0)
		x = position.left;

	if (Helper::isPointInRect(x, y, position))
	{
		// mouse is on the button
		if (hovered)
		{

			// button is already being hovered
			// do nothing
		}
		else
		{
			// button is not hovered
			if (!pressed)
			{
				// hover if not pressed
				hovered = true;
				invalidateButton(hWnd);
			}
		}
	}
	else if (pressed || hovered)
	{
		// mouse is not on minimize button, but the button is pressed or hovered
		pressed = false;
		hovered = false;
		invalidateButton(hWnd);
	}
}

std::shared_ptr<CachedBitmap> Buttons::getBitmap()
{
	if (disabled)
		return stateButtons.disabledCachedBitmap;
	else if (pressed)
		return stateButtons.pressedCachedBitmap;
	else if (hovered)
		return stateButtons.hoveredCachedBitmap;

	return stateButtons.normalCachedBitmap;
}
