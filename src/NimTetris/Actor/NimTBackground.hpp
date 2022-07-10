#ifndef _NimTBackgroundHeader_
#define _NimTBackgroundHeader_
#include "KeyCode.hpp"
#include "NimTetrisGraphics.hpp"
class NimTBackground {
private:
	const NimTetrisGraphics& graphics;
	const int ImageChangeInterval;
	const int OverlapAnimationLength;
	std::vector<Drawable> backgroundImages;

private:
	int changer;
	int currentImageNo;
	int prevImageNo;
	double currentImageOpacity;

public:
	void onInitialize();
	void onKeyDown(KeyCode keycode);
	void onFrame(int frameNo);

public:
	Drawable getScreen() const;

public:
	NimTBackground(const NimTetrisGraphics& _graphics) : graphics(_graphics), ImageChangeInterval(9000), OverlapAnimationLength(30), changer(0) {};
};
#endif