#include "../../headers/mics/BitmapHelper.hpp"


std::shared_ptr<CachedBitmap> BitmapHelper::createCachedBitmap(Bitmap* originalBitmap, HDC hdc)
{
    Graphics gt(hdc);
    return std::make_shared<CachedBitmap>(originalBitmap,&gt);
            
}