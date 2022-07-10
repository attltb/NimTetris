#include "Drawable_Filter.hpp"
using namespace std;
Drawable Drawable::Filter(int width, int height, Color32 color, BlendMode blendMode, int fix_opacity) {
	return shared_ptr<Drawable_>(new Drawable_Filter(width, height, color, blendMode, fix_opacity));
}

void Drawable_Filter::drawOn(Bitmap32& dst, int x, int y) {
	if (dst.width <= x || dst.height <= y) return;
	if (x + width < 0 || y + height < 0) return;

	int _x_start = max(x, 0);
	int _y_start = max(y, 0);
	int _x_end = min(width + x, dst.width);
	int _y_end = min(height + y, dst.height);
	if (fix_opacity) {
		switch (blendMode) {
		case BlendMode::COPY:
			for (int _y = _y_start; _y < _y_end; _y++) {
				Color32* pdest = dst[_y];
				for (int _x = _x_start; _x < _x_end; _x++) pdest[_x] = Blender::blend_copy_fix(pdest[_x], color);
			}
			break;
		case BlendMode::COVER: //draw with opacity
			for (int _y = _y_start; _y < _y_end; _y++) {
				Color32* pdest = dst[_y];
				for (int _x = _x_start; _x < _x_end; _x++) pdest[_x] = Blender::blend_cover_fix(pdest[_x], color);
			}
			break;
		case BlendMode::ADD: //draw light with opacity
			for (int _y = _y_start; _y < _y_end; _y++) {
				Color32* pdest = dst[_y];
				for (int _x = _x_start; _x < _x_end; _x++) pdest[_x] = Blender::blend_add_fix(pdest[_x], color);
			}
			break;
		case BlendMode::MULTIPLY: //draw shadow with opacity
			for (int _y = _y_start; _y < _y_end; _y++) {
				Color32* pdest = dst[_y];
				for (int _x = _x_start; _x < _x_end; _x++) pdest[_x] = Blender::blend_mul_fix(pdest[_x], color);
			}
			break;
		}
	}
	else {
		switch (blendMode) {
		case BlendMode::COPY:
			for (int _y = _y_start; _y < _y_end; _y++) {
				Color32* pdest = dst[_y];
				for (int _x = _x_start; _x < _x_end; _x++) pdest[_x] = Blender::blend_copy(pdest[_x], color);
			}
			break;
		case BlendMode::COVER: //draw with opacity
			for (int _y = _y_start; _y < _y_end; _y++) {
				Color32* pdest = dst[_y];
				for (int _x = _x_start; _x < _x_end; _x++) pdest[_x] = Blender::blend_cover(pdest[_x], color);
			}
			break;
		case BlendMode::ADD: //draw light with opacity
			for (int _y = _y_start; _y < _y_end; _y++) {
				Color32* pdest = dst[_y];
				for (int _x = _x_start; _x < _x_end; _x++) pdest[_x] = Blender::blend_add(pdest[_x], color);
			}
			break;
		case BlendMode::MULTIPLY: //draw shadow with opacity
			for (int _y = _y_start; _y < _y_end; _y++) {
				Color32* pdest = dst[_y];
				for (int _x = _x_start; _x < _x_end; _x++) pdest[_x] = Blender::blend_mul(pdest[_x], color);
			}
			break;
		}
	}
}
void Drawable_Filter::drawOn(Bitmap32& dst, int x, int y, double opacity) {
	if (dst.width <= x || dst.height <= y) return;
	if (x + width < 0 || y + height < 0) return;

	int _x_start = max(x, 0);
	int _y_start = max(y, 0);
	int _x_end = min(width + x, dst.width);
	int _y_end = min(height + y, dst.height);

	if (1 < opacity) opacity = 1.0;
	int opa256 = int(opacity * 256);
	if (fix_opacity) {
		switch (blendMode) {
		case BlendMode::COPY:
			for (int _y = _y_start; _y < _y_end; _y++) {
				Color32* pdest = dst[_y];
				for (int _x = _x_start; _x < _x_end; _x++) pdest[_x] = Blender::blend_copy_fix(pdest[_x], color, opa256);
			}
			break;
		case BlendMode::COVER: //draw with opacity
			for (int _y = _y_start; _y < _y_end; _y++) {
				Color32* pdest = dst[_y];
				for (int _x = _x_start; _x < _x_end; _x++) pdest[_x] = Blender::blend_cover_fix(pdest[_x], color, opa256);
			}
			break;
		case BlendMode::ADD: //draw light with opacity
			for (int _y = _y_start; _y < _y_end; _y++) {
				Color32* pdest = dst[_y];
				for (int _x = _x_start; _x < _x_end; _x++) pdest[_x] = Blender::blend_add_fix(pdest[_x], color, opa256);
			}
			break;
		case BlendMode::MULTIPLY: //draw shadow with opacity
			for (int _y = _y_start; _y < _y_end; _y++) {
				Color32* pdest = dst[_y];
				for (int _x = _x_start; _x < _x_end; _x++) pdest[_x] = Blender::blend_mul_fix(pdest[_x], color, opa256);
			}
			break;
		}
	}
	else {
		switch (blendMode) {
		case BlendMode::COPY:
			for (int _y = _y_start; _y < _y_end; _y++) {
				Color32* pdest = dst[_y];
				for (int _x = _x_start; _x < _x_end; _x++) pdest[_x] = Blender::blend_copy(pdest[_x], color, opa256);
			}
			break;
		case BlendMode::COVER: //draw with opacity
			for (int _y = _y_start; _y < _y_end; _y++) {
				Color32* pdest = dst[_y];
				for (int _x = _x_start; _x < _x_end; _x++) pdest[_x] = Blender::blend_cover(pdest[_x], color, opa256);
			}
			break;
		case BlendMode::ADD: //draw light with opacity
			for (int _y = _y_start; _y < _y_end; _y++) {
				Color32* pdest = dst[_y];
				for (int _x = _x_start; _x < _x_end; _x++) pdest[_x] = Blender::blend_add(pdest[_x], color, opa256);
			}
			break;
		case BlendMode::MULTIPLY: //draw shadow with opacity
			for (int _y = _y_start; _y < _y_end; _y++) {
				Color32* pdest = dst[_y];
				for (int _x = _x_start; _x < _x_end; _x++) pdest[_x] = Blender::blend_mul(pdest[_x], color, opa256);
			}
			break;
		}
	}
}