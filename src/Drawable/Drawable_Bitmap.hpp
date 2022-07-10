#ifndef _Drawable_BitmapHeader_
#define _Drawable_BitmapHeader_
#include "Drawable.hpp"
class Drawable_Bitmap : public Drawable_ {
	const Bitmap32& src;
	BlendMode blendMode;
	int fix_opacity;
public:
	Drawable_Bitmap(const Bitmap32& _src, BlendMode _blendMode, int _fix_opacity) : src(_src), blendMode(_blendMode), fix_opacity(_fix_opacity) {}
public:
	void drawOn(Bitmap32& dst, int x, int y);
	void drawOn(Bitmap32& dst, int x, int y, double opacity);
};
#endif