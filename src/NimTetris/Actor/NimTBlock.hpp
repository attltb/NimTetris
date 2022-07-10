#ifndef _NimTBlockHeader_
#define _NimTBlockHeader_
#include "NimTetrisGraphics.hpp"
class NimTBlock {
private:
	const NimTetrisGraphics& graphics;
	TetrominoFixedID blockID;

public:
	void onFrame(int frameNo);

public:
	Drawable getScreen() const;

public:
	NimTBlock(const NimTetrisGraphics& _graphics, TetrominoFixedID _blockID) : graphics(_graphics), blockID(_blockID) {};
};
#endif