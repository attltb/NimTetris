#ifndef _NimTBoardFrameHeader_
#define _NimTBoardFrameHeader_
#include "NimTetrisGraphics.hpp"
class NimTBoardFrame {
private:
	const NimTetrisGraphics& graphics;

public:
	void onFrame(int frameNo);

public:
	Drawable getScreen() const;

public:
	NimTBoardFrame(const NimTetrisGraphics& _graphics) : graphics(_graphics) {};
};
#endif