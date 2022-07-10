#ifndef _Drawable_CompositeHeader_
#define _Drawable_CompositeHeader_
#include "Drawable.hpp"
class Drawable_Composite : public Drawable_ {
	std::vector<Drawable> drawables;

public:
	Drawable_Composite(const std::vector<Drawable>& elements) : drawables(elements) {}
	Drawable_Composite(std::initializer_list<Drawable> elements) : drawables{ elements } {}

public:
	void drawOn(Bitmap32& dst, int x, int y);
	void drawOn(Bitmap32& dst, int x, int y, double opacity);
};
#endif