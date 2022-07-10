#include "Drawable_Moved.hpp"
using namespace std;
Drawable Drawable::Moved(int disp_x, int disp_y, Drawable drawable) {
	return shared_ptr<Drawable_>(new Drawable_Moved(disp_x, disp_y, drawable));
}

void Drawable_Moved::drawOn(Bitmap32& dst, int x, int y) {
	return drawable.drawOn(dst, x + disp_x, y + disp_y);
}
void Drawable_Moved::drawOn(Bitmap32& dst, int x, int y, double opacity) {
	return drawable.drawOn(dst, x + disp_x, y + disp_y, opacity);
}