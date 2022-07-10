#ifndef _Drawable_NullHeader_
#define _Drawable_NullHeader_
#include "Drawable.hpp"
class Drawable_Null : public Drawable_ {
public:
	void drawOn(Bitmap32& dst, int x, int y) {}
	void drawOn(Bitmap32& dst, int x, int y, double opacity) {};
};
#endif