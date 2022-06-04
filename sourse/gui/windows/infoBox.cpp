#include "../../../headers/gui/windows/infoBox.hpp"
#include "../../../headers/gui/mics/rectCorner.hpp"

InfoBox::InfoBox()
{
	stringCenter.SetAlignment(StringAlignmentCenter);
	stringCenter.SetLineAlignment(StringAlignmentCenter);
	arialFont = std::make_unique<Font>(L"Arial", (REAL)14);
	textColor = std::make_unique<SolidBrush>(Color(255, 255, 255));
	this->rect.X = 336;
	this->rect.Y = 373;
	this->rect.Width = 127;
	this->rect.Height = 44;
	this->position.left = 150;
	this->position.top = 175;
	this->position.right = 150 + 500;
	this->position.bottom = 175 + 250;
	closeInfo = std::make_unique<Buttons>(L"Далее", (Color(255, 62, 144, 232)), (Color(255, 255, 255)), (Color(255, 78, 60, 163)), RectF(rect));
	backgroundColor = std::make_unique<SolidBrush>((Color(91, 23, 155)));
}
void InfoBox::SetText(const std::wstring text)
{
	this->text = text;
}
void InfoBox::Draw(Graphics* gt)
{
	Corner::FillRoundRect(gt, backgroundColor.get(), { position.left, position.top, position.right - position.left, position.bottom - position.top }, (Color(255, 91, 23, 155)), 5);
	gt->DrawString(
		text.c_str(),
		-1,
		arialFont.get(),
		RectF(position.left, position.top, position.right - position.left, position.bottom - position.top),
		&stringCenter,
		textColor.get());
	closeInfo.get()->draw(gt);
	
}
