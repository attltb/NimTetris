#ifndef _DrawableHeader_
#define _DrawableHeader_
#include "Bitmap32.hpp"
#include "Blender32.hpp"
#include <memory>
#include <vector>
class Drawable_ {
public:
	virtual void drawOn(Bitmap32& dst, int x, int y) = 0;
	virtual void drawOn(Bitmap32& dst, int x, int y, double opacity) = 0;

public:
	virtual ~Drawable_() {};
};
class Drawable {
	std::shared_ptr<Drawable_> ptr;
	Drawable(std::shared_ptr<Drawable_> _ptr) : ptr(_ptr) {}

public:
	Drawable() : ptr() {}
	Drawable(const Drawable& other) : ptr(other.ptr) {}

public:
	static Drawable Null();
	static Drawable Filter(int width, int height, Color32 color, BlendMode blendMode, int fix_transparency = 0);
	static Drawable Bitmap(const Bitmap32& src, BlendMode blendMode = BlendMode::COPY, int fix_transparency = 0);
	static Drawable Translucent(double opacity, Drawable drawable);
	static Drawable Moved(int disp_x, int disp_y, Drawable drawable);
	static Drawable Pattern(Drawable pattern, int interval_x, int interval_y, int count_x, int count_y);
	static Drawable Composite(const std::vector<Drawable>& elements);
	static Drawable Composite(std::initializer_list<Drawable> elements);

public:
	void drawOn(Bitmap32& dst, int x, int y) {
		ptr->drawOn(dst, x, y);
	}
	void drawOn(Bitmap32& dst, int x, int y, double opacity) {
		ptr->drawOn(dst, x, y, opacity);
	}
};
#endif