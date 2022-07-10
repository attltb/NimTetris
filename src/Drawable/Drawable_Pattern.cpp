#include "Drawable_Pattern.hpp"
using namespace std;
Drawable Drawable::Pattern(Drawable pattern, int interval_x, int interval_y, int count_x, int count_y) {
	return shared_ptr<Drawable_>(new Drawable_Pattern(pattern, interval_x, interval_y, count_x, count_y));
}

void Drawable_Pattern::drawOn(Bitmap32& dst, int x, int y) {
	for (int i = 0; i < count_y; i++) {
		int y_new = y + i * interval_y;
		for (int j = 0; j < count_x; j++) {
			int x_new = x + i * interval_x;
			pattern.drawOn(dst, x_new, y_new);
		}
	}
}
void Drawable_Pattern::drawOn(Bitmap32& dst, int x, int y, double opacity) {
	for (int i = 0; i < count_y; i++) {
		int y_new = y + i * interval_y;
		for (int j = 0; j < count_x; j++) {
			int x_new = x + i * interval_x;
			pattern.drawOn(dst, x_new, y_new, opacity);
		}
	}
}