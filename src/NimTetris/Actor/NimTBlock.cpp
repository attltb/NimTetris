#include "NimTBlock.hpp"
void NimTBlock::onFrame(int frameNo) {}

Drawable NimTBlock::getScreen() const {
	return graphics.tetrominos[(int)blockID];
}