#ifndef __BITMAPHELPER_H__
#define __BITMAPHELPER_H__
#include <memory>
#include "../../headers/stdafx.h"
#include <Wincodec.h>

class BitmapHelper
{
public:
	static std::shared_ptr<CachedBitmap> createCachedBitmap(Bitmap* originalBitmap, HDC hdc);
	static Bitmap* loadScaledFromResource(int id, float scale);
	static Bitmap* loadScaledFromResource(int id, float xScale, float yScale);
	static Bitmap* loadFromResource(int id);
	static Bitmap* resizeBitmap(Bitmap* source, int newWidth, int newHeight);

	static Gdiplus::Bitmap* ResizeClone(Bitmap* bmp, INT width, INT height);
private:
	static IStream* createStreamOnResource(LPCTSTR lpName, LPCTSTR lpType);
};

#endif // __BITMAPHELPER_H__