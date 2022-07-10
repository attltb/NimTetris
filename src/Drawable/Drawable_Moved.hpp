#ifndef _Drawable_MovedHeader_
#define _Drawable_MovedHeader_
#include "Drawable.hpp"
class Drawable_Moved : public Drawable_ {
	int disp_x;
	int disp_y;
	Drawable drawable;

public:
	Drawable_Moved(int _disp_x, int _disp_y, Drawable _drawable) : disp_x(_disp_x), disp_y(_disp_y), drawable(_drawable) {}

public:
	void drawOn(Bitmap32& dst, int x, int y);
	void drawOn(Bitmap32& dst, int x, int y, double opacity);
};
#endif