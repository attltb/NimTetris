#include "Drawable_Composite.hpp"
using namespace std;
Drawable Drawable::Composite(const std::vector<Drawable>& elements) {
	return shared_ptr<Drawable_>(new Drawable_Composite(elements));
}
Drawable Drawable::Composite(std::initializer_list<Drawable> elements) {
	return shared_ptr<Drawable_>(new Drawable_Composite(elements));
}

void Drawable_Composite::drawOn(Bitmap32& dst, int x, int y) {
	for (auto it = drawables.begin(); it != drawables.end(); it++) {
		it->drawOn(dst, x, y);
	}
}
void Drawable_Composite::drawOn(Bitmap32& dst, int x, int y, double opacity) {
	for (auto it = drawables.begin(); it != drawables.end(); it++) {
		it->drawOn(dst, x, y, opacity);
	}
}