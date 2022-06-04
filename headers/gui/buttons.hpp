#ifndef __BUTTONS_H__
#define __BUTTONS_H__
#include "../../headers/mics/helper.hpp"
#include "../mics/BitmapHelper.hpp"
#include <memory>
class Buttons
{
private:
    struct
    {
        std::shared_ptr<CachedBitmap> normalCachedBitmap;  
	    std::shared_ptr<CachedBitmap> hoveredCachedBitmap;
	    std::shared_ptr<CachedBitmap> pressedCachedBitmap;
	    std::shared_ptr<CachedBitmap> disabledCachedBitmap;
    } stateButtons;
private:
    std::wstring text;
private:
    struct
    {
        std::unique_ptr<SolidBrush>colorNormal = nullptr;
        std::unique_ptr<SolidBrush>colorHovered = nullptr;
        std::unique_ptr<SolidBrush>_colorClick = nullptr;
        std::unique_ptr<Color>colorClick = nullptr;
        std::unique_ptr<Font>arialFont = nullptr;
    } styleButtons;
private:
	bool hovered;
	bool pressed;
	bool clicked;
	bool disabled;
	bool isColor;
    RECT position;
    StringFormat stringCenter;
private:
    std::shared_ptr<CachedBitmap> getBitmap();
public:
    Buttons() noexcept;
    ~Buttons() = default;
    Buttons(const std::wstring text, const Color normal, const Color hovered, const Color clicked, const RectF rect); 
    //Buttons( Bitmap* normalBitmap,  Bitmap* hoveredBitmap,  Bitmap* disabledBitmap, const HDC hdc);// btn w/. bitmaps
    void mouseReleased(const HWND hWnd,  int x, const int y);
    void mouseMoved(const HWND hWnd,  int x, const int y);
    bool isClicked();
    bool isHovered();
    void draw( Graphics* g);
    void invalidateButton(const HWND hWnd);
    void DisableButton();
    void EnableButton();
};


#endif // __BUTTONS_H__