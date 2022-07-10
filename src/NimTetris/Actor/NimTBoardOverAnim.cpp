#include "NimTBoardOverAnim.hpp"
using namespace std;
void NimTBoardOverAnim::reset() {
	internalFrameNo = -1;
	processedTargetsSize = 0;
	targets.clear();
}
void NimTBoardOverAnim::start() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (board.at[i][j] != PlaceState::EMPTY_MARKED) {
				targets.push_back(make_pair(i, j));
			}
		}
	}
}
void NimTBoardOverAnim::skip() {
	processedTargetsSize = (int)targets.size();
}
bool NimTBoardOverAnim::onFrame(int frameNo) {
	internalFrameNo++;
	if (processedTargetsSize == targets.size()) return true;
	else processedTargetsSize++;
	return false;
}

Drawable NimTBoardOverAnim::getScreen() const {
	vector<Drawable> drawables;
	for (int i = 0; i < processedTargetsSize; i++) {
		int y = targets[i].first;
		int x = targets[i].second;
		drawables.push_back(Drawable::Moved(x * BLOCK_INTERVAL_X, y * BLOCK_INTERVAL_Y, graphics.block_x));
	}
	return Drawable::Composite(drawables);
}