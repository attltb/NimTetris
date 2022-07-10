#ifndef _NimTetrisGraphicComponentsHeader_
#define _NimTetrisGraphicComponentsHeader_
#include "ResourceCollection.hpp"
#include "Blocks.hpp"
#include "Drawable.hpp"
#include "Bitmap32Pool.hpp"
#define N_OF_BACKGROUNDS 8
#define BLOCK_INTERVAL_X 40
#define BLOCK_INTERVAL_Y 40
#define BLOCK_WIDTH 40
#define BLOCK_HEIGHT 40
#define BOARD_POS_X 15
#define BOARD_POS_Y 15
#define BOARD_WIDTH 420
#define BOARD_HEIGHT 420
#define BOARD_FRAME_WIDTH 10
#define BOARD_FRAME_HEIGHT 10
#define BOARD_BODY_WIDTH ((BOARD_WIDTH)-(2*(BOARD_FRAME_WIDTH)))
#define BOARD_BODY_HEIGHT ((BOARD_HEIGHT)-(2*(BOARD_FRAME_HEIGHT)))
class NimTetrisGraphics {
private:
	ResourceCollection& resources;
	Bitmap32Pool bitmap32Pool;

public:
	Drawable oldBackground;
	Drawable oldGameover;
	Drawable oldResult[4];

	Drawable oldBlocks[N_OF_TETROMINO];
	Drawable oldCursers[N_OF_TETROMINO];
	Drawable oldBlockDisabled;
	Drawable oldBlankDisabled;

	Drawable backgrounds[N_OF_BACKGROUNDS];

	Drawable leftTopFrame;
	Drawable leftBottomFrame;
	Drawable rightTopFrame;
	Drawable rightBottomFrame;
	Drawable leftFrame;
	Drawable rightFrame;
	Drawable topFrame;
	Drawable bottomFrame;

	Drawable place;
	Drawable xMark;
	Drawable block_x;
	Drawable blocks[N_OF_TETROMINO];
	Drawable tetrominos[N_OF_TETROMINOFIXED];
	Drawable tetromino_cursurs[N_OF_TETROMINOFIXED];

private:
	Bitmap32* createBitmap32(int width, int height, Drawable content);

public:
	Drawable loadBitmap(std::string rssName, BlendMode blendMode = BlendMode::COPY, int fix_opacity = 0);
	Drawable createBitmap(int width, int height, Drawable content, BlendMode blendMode = BlendMode::COPY, int fix_opacity = 0);
	void loadBitmaps(std::string rssName, Drawable arr[], int size, BlendMode blendMode = BlendMode::COPY, int fix_opacity = 0);

public:
	void initialize();
	void finalize();

public:
	NimTetrisGraphics(ResourceCollection& _resources) : resources(_resources) {};
};
#endif