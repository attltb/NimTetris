#ifndef _NimTDisabledMarkHeader_
#define _NimTDisabledMarkHeader_
#include "NimTetrisGraphics.hpp"
class NimTDisabledMark {
private:
	const NimTetrisGraphics& graphics;

public:
	void onFrame(int frameNo);

public:
	Drawable getScreen() const;

public:
	NimTDisabledMark(const NimTetrisGraphics& _graphics) : graphics(_graphics) {};
};
#endif