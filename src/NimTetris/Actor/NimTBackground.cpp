#include "NimTBackground.hpp"
#include "Randomizer.hpp"
#include <algorithm>
void NimTBackground::onInitialize() {
	currentImageNo = 0;
	currentImageOpacity = 1.0;
	for (int i = 0; i < N_OF_BACKGROUNDS; i++) backgroundImages.push_back(graphics.backgrounds[i]);
	shuffle(backgroundImages.begin(), backgroundImages.end(), Randomizer().algorithm);
}
void NimTBackground::onKeyDown(KeyCode keycode) {
    switch (keycode) {
    case KeyCode::Q:
		if (1.0e-16 < abs(1.0 - currentImageOpacity)) return;
		prevImageNo = currentImageNo;
		currentImageNo = (currentImageNo + 1) % N_OF_BACKGROUNDS;
        return;
    }
}
void NimTBackground::onFrame(int frameNo) {
	for (; changer < frameNo / ImageChangeInterval;) {
		changer++;
		prevImageNo = currentImageNo;
		currentImageNo = (currentImageNo + 1) % N_OF_BACKGROUNDS;
		currentImageOpacity = 0.0;
	}
	if ((frameNo > ImageChangeInterval) && (frameNo % ImageChangeInterval <= OverlapAnimationLength)) {
		currentImageOpacity = (double)(frameNo % ImageChangeInterval) / (double)OverlapAnimationLength;
	}
}

Drawable NimTBackground::getScreen() const {
	if (abs(currentImageOpacity - 1.0) < 1.0 / 256.0) return backgroundImages[currentImageNo];
	else return Drawable::Composite({ backgroundImages[prevImageNo], Drawable::Translucent(currentImageOpacity, backgroundImages[currentImageNo]) });
}