#ifndef _NimTBoardAnimHeader_
#define _NimTBoardAnimHeader_
#include "Board10x10.hpp"
#include "NimTetrisGraphics.hpp"
#include <vector>
class NimTBoardOverAnim {
private:
	const NimTetrisGraphics& graphics;
	Board10x10& board;
	int internalFrameNo;
	int processedTargetsSize;
	std::vector<std::pair<int, int>> targets;

public:
	void reset();
	void start();
	void skip();
	bool onFrame(int frameNo);

public:
	Drawable getScreen() const;

public:
	NimTBoardOverAnim(const NimTetrisGraphics& _graphics, Board10x10& _board) : graphics(_graphics), board(_board), internalFrameNo(-1), processedTargetsSize(0) {};
};
#endif