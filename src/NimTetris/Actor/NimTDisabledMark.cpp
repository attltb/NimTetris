#include "NimTDisabledMark.hpp"
void NimTDisabledMark::onFrame(int frameNo) {}

Drawable NimTDisabledMark::getScreen() const {
	return graphics.xMark;
}