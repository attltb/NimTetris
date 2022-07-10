#ifndef _Bitmap32PoolHeader_
#define _Bitmap32PoolHeader_
#include "Bitmap32.hpp"
#include <vector>
class Bitmap32Pool {
	std::vector<Bitmap32*> bitmaps;

private:
	Bitmap32* push(Bitmap32* bitmap) {
		bitmaps.push_back(bitmap);
		return bitmap;
	}

public:
	Bitmap32* newBitmap32(int width, int height) {
		return push(new Bitmap32(width, height));
	}
	Bitmap32* newBitmap32(int width, int height, Color32 color) {
		return push(new Bitmap32(width, height, color));
	}
	Bitmap32* newBitmap32_fromBuffer(int width, int height, Color32* buffer) {
		return push(new Bitmap32(width, height, buffer));
	}

public:
	void releaseAll() {
		for (unsigned int i = 0; i < bitmaps.size(); i++) delete bitmaps[i];
	}
};
#endif