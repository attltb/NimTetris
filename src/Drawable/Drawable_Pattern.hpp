#ifndef _Drawable_PatternHeader_
#define _Drawable_PatternHeader_
#include "Drawable.hpp"
class Drawable_Pattern : public Drawable_ {
	Drawable pattern;
	int interval_x;
	int interval_y;
	int count_x;
	int count_y;

public:
	Drawable_Pattern(Drawable _pattern, int _interval_x, int _interval_y, int _count_x, int _count_y) :
		pattern(_pattern), interval_x(_interval_x), interval_y(_interval_y), count_x(_count_x), count_y(_count_y) {}

public:
	void drawOn(Bitmap32& dst, int x, int y);
	void drawOn(Bitmap32& dst, int x, int y, double opacity);
};
#endif