#include "NimTBoardFrame.hpp"
void NimTBoardFrame::onFrame(int frameNo) {};

Drawable NimTBoardFrame::getScreen() const {
	int base_x_0 = 0;
	int base_x_1 = BOARD_FRAME_WIDTH;
	int base_x_2 = BOARD_FRAME_WIDTH + BOARD_BODY_WIDTH;
	int base_y_0 = 0;
	int base_y_1 = BOARD_FRAME_HEIGHT;
	int base_y_2 = BOARD_FRAME_HEIGHT + BOARD_BODY_HEIGHT;
	return Drawable::Composite({
		Drawable::Moved(base_x_0, base_y_0, graphics.leftTopFrame),
		Drawable::Moved(base_x_1, base_y_0, graphics.topFrame),
		Drawable::Moved(base_x_2, base_y_0, graphics.rightTopFrame),
		Drawable::Moved(base_x_0, base_y_1, graphics.leftFrame),
		Drawable::Moved(base_x_2, base_y_1, graphics.rightFrame),
		Drawable::Moved(base_x_0, base_y_2, graphics.leftBottomFrame),
		Drawable::Moved(base_x_1, base_y_2, graphics.bottomFrame),
		Drawable::Moved(base_x_2, base_y_2, graphics.rightBottomFrame)
		});
}