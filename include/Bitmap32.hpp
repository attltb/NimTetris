#ifndef _Bitmap32Header_
#define _Bitmap32Header_
#include <stdint.h>

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

struct Color32 {
	uint8_t blue;
	uint8_t green;
	uint8_t red;
	uint8_t alpha;
};
class Bitmap32 {
private:
	int use_external_memory;

public:
	int width;
	int height;
	Color32* bits;

public:
	Bitmap32() : width(0), height(0), bits(nullptr), use_external_memory(0) {}
	Bitmap32(int _width, int _height) : width(_width), height(_height), use_external_memory(0) {
		if (width && height) bits = new Color32[width * height];
		else bits = nullptr;
	}
	Bitmap32(int _width, int _height, Color32 color) : width(_width), height(_height), use_external_memory(0) {
		if (width && height) {
			bits = new Color32[width * height];
			for (int i = 0; i < width * height; i++) bits[i] = color;
		}
		else bits = nullptr;
	}
	Bitmap32(int _width, int _height, Color32* _bits) : width(_width), height(_height), bits(_bits), use_external_memory(1) {}
	~Bitmap32() {
		if (!use_external_memory && bits) delete[] bits;
	}

public:
	const Color32* operator [] (int y) const {
		return (bits + width * y);
	}
	Color32* operator [] (int y) {
		return (bits + width * y);
	}

public:
	void reset(int _width, int _height) {
		if (use_external_memory && bits) delete[] bits;
		if (_width && _height) bits = new Color32[_width * _height];
		else bits = nullptr;

		use_external_memory = 0;
		width = _width;
		height = _height;
	}
	void reset(int _width, int _height, Color32 color) {
		if (use_external_memory && bits) delete[] bits;
		if (_width && _height) bits = new Color32[_width * _height];
		else bits = nullptr;

		use_external_memory = 0;
		width = _width;
		height = _height;

		for (int i = 0; i < width * height; i++) bits[i] = color;
	}
	void reset(int _width, int _height, Color32* _bits) {
		if (use_external_memory && bits) delete[] bits;
		use_external_memory = 1;
		bits = _bits;

		width = _width;
		height = _height;
	}
	void free() {
		if (use_external_memory && bits) delete[] bits;
		bits = nullptr;
	}
};
#endif