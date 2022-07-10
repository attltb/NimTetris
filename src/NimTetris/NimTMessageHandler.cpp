#include "NimTMessageHandler.hpp"
#include "NimTetris.hpp"
bool NimTMessageHandler::onInitialize(WindowHandle wnd) {
	pGraphics = new NimTetrisGraphics(resources);
	pGraphics->initialize();

	pBackground = new NimTBackground(*pGraphics);
	pBoard = new NimTBoard(threadManager, autosaveds, *pGraphics);
	pBackground->onInitialize();
	pBoard->onInitialize();
	return true;
}
bool NimTMessageHandler::onFinalize(WindowHandle wnd) {
	delete pBoard;
	delete pBackground;

	pGraphics->finalize();
	delete pGraphics;
	return true;
}
void NimTMessageHandler::onFrame(WindowHandle wnd, int frameNo) {
	pBackground->onFrame(frameNo);
	pBoard->onFrame(frameNo);
}
void NimTMessageHandler::onKeyDown(WindowHandle wnd, KeyCode keycode) {
	pBackground->onKeyDown(keycode);
	pBoard->onKeyDown(keycode);
}
void NimTMessageHandler::onKeyUp(WindowHandle wnd, KeyCode keycode) {}
void NimTMessageHandler::onKeyInput(WindowHandle wnd, char charactor) {}
void NimTMessageHandler::onMouseMove(WindowHandle wnd, int xPos, int yPos) {
	if ((BOARD_POS_X < xPos && BOARD_POS_X + BOARD_WIDTH > xPos) && (BOARD_POS_Y < yPos && BOARD_POS_Y + BOARD_HEIGHT > yPos)) {
		pBoard->onMouseMove(xPos - BOARD_POS_X, yPos - BOARD_POS_Y);
	}
}
void NimTMessageHandler::onMouseLDown(WindowHandle wnd, int xPos, int yPos) {
	if ((BOARD_POS_X < xPos && BOARD_POS_X + BOARD_WIDTH > xPos) && (BOARD_POS_Y < yPos && BOARD_POS_Y + BOARD_HEIGHT > yPos)) {
		pBoard->onMouseLDown(xPos - BOARD_POS_X, yPos - BOARD_POS_Y);
	}
}
void NimTMessageHandler::onMouseLUp(WindowHandle wnd, int xPos, int yPos) {}
void NimTMessageHandler::onMouseLDouble(WindowHandle wnd, int xPos, int yPos) {}
void NimTMessageHandler::onMouseRDown(WindowHandle wnd, int xPos, int yPos) {}
void NimTMessageHandler::onMouseRUp(WindowHandle wnd, int xPos, int yPos) {}
void NimTMessageHandler::onMouseRDouble(WindowHandle wnd, int xPos, int yPos) {}
void NimTMessageHandler::onCustom(WindowHandle wnd, int kind, void* params) {}

Drawable NimTMessageHandler::onDraw() const {
	return Drawable::Composite({ pBackground->getScreen(), Drawable::Moved(BOARD_POS_X, BOARD_POS_Y, pBoard->getScreen()) });
}