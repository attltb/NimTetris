#ifndef _Drawable_TranslucentHeader_
#define _Drawable_TranslucentHeader_
#include "Drawable.hpp"
class Drawable_Translucent : public Drawable_ {
	double opacity;
	Drawable drawable;

public:
	Drawable_Translucent(double _opacity, Drawable _drawable) : opacity(_opacity), drawable(_drawable) {}

public:
	void drawOn(Bitmap32& dst, int x, int y);
	void drawOn(Bitmap32& dst, int x, int y, double opacity);
};
#endif