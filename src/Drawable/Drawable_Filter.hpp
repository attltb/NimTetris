#ifndef _Drawable_FilterHeader_
#define _Drawable_FilterHeader_
#include "Drawable.hpp"
class Drawable_Filter : public Drawable_ {
	int width;
	int height;
	Color32 color;
	BlendMode blendMode;
	int fix_opacity;

public:
	Drawable_Filter(int _width, int _height, Color32 _color, BlendMode _blendMode, int _fix_opacity)
		: width(_width), height(_height), color(_color), blendMode(_blendMode), fix_opacity(_fix_opacity) {}
public:
	void drawOn(Bitmap32& dst, int x, int y);
	void drawOn(Bitmap32& dst, int x, int y, double opacity);
};
#endif