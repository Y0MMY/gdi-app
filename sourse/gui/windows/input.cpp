#include "../../../headers/gui/windows/input.hpp"
#include "../../../headers/gui/mics/rectCorner.hpp"
input::input()
{
	stringCenter.SetAlignment(StringAlignmentCenter);
	textFormat.SetAlignment(StringAlignment::StringAlignmentNear);
	textFormat.SetLineAlignment(StringAlignmentCenter);
	fillColor = std::make_unique<SolidBrush>(Color(250, 250, 250));
	focusColor = std::make_unique<SolidBrush>(Color(91, 23, 155));
	rInput.X = 249;
	rInput.Y = 290;
	rInput.Width = 302;
	rInput.Height = 57;

}
const void input::Draw(Graphics* gt)
{
	Corner::FillRoundRect(gt, backgroundColor.get() ,{ position.left, position.top, position.right - position.left, position.bottom - position.top }, (Color(255, 91, 23, 155)), 5);
	gt->DrawString(
		text.c_str(),
		-1,
		arialFont.get(),
		RectF(position.left, position.top + 50, position.right - position.left, position.bottom - position.top),
		&stringCenter,
		textColor.get());
	 if(isInFocus)Corner::FillRoundRect(gt, fillColor.get(), rInput, Color(250, 250, 250), 5);
	 else Corner::FillRoundRect(gt, focusColor.get(), rInput, Color(250, 250, 250), 5);
	 if (!content.empty()) StringInput(gt);
}


const void input::update(UINT key, int x, int y)
{	
	if (isInFocus)
	{
		if (key == VK_RETURN) return;
		if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(VK_BACK) & 1)
		{
			content = L"\0";
			Scontent = "\0";
			InvalidateRect(hWnd, 0, 1);
			return;
		}
		if (key == VK_BACK)
		{
			if (content.size() > 0)
			{
				content.pop_back();
				Scontent.pop_back();
			}
			InvalidateRect(hWnd, 0, 1);
			return;
		}
		char str[2]; 	
		sprintf((char*)str, "%c", key); 	
		std::string s = str;
		Scontent += str;
		content += Helper::ConvertStringToWstring(s.c_str());
		InvalidateRect(hWnd, 0, 1);
	}
}

const void input::StringInput(Graphics* g)
{
	if(isInFocus) g->DrawString(content.c_str(), -1, arialFont.get(), RectF(rInput.X, rInput.Y, rInput.Width, rInput.Height),
		&textFormat, focusColor.get());
	else  g->DrawString(content.c_str(), -1, arialFont.get(), RectF(rInput.X, rInput.Y, rInput.Width, rInput.Height),
		&textFormat, fillColor.get());
}
const bool input::ClickInput(HWND hWnd,int x, int y)
{
	if (!this->hWnd) this->hWnd = hWnd;
	if (Helper::isPointInRect(x, y, rInput))
	{
		isInFocus = true;
		InvalidateRect(hWnd, 0, 1);
		return true;
	}
	else isInFocus = false;
	InvalidateRect(hWnd, 0, 1);
	return false;
}

const std::string input::GetContent() const
{
	return Scontent;
}


