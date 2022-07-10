#include "Drawable_Translucent.hpp"
using namespace std;
Drawable Drawable::Translucent(double opacity, Drawable drawable) {
	return shared_ptr<Drawable_>(new Drawable_Translucent(opacity, drawable));
}

void Drawable_Translucent::drawOn(Bitmap32& dst, int x, int y) {
	return drawable.drawOn(dst, x, y, opacity);
}
void Drawable_Translucent::drawOn(Bitmap32& dst, int x, int y, double _opacity) {
	return drawable.drawOn(dst, x, y, opacity * _opacity);
}