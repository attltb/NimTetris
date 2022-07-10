#include "NimTetrisGraphics.hpp"
using namespace std;
Bitmap32* NimTetrisGraphics::createBitmap32(int width, int height, Drawable content) {
	Bitmap32* ret = bitmap32Pool.newBitmap32(width, height);
	content.drawOn(*ret, 0, 0);
	return ret;
}

Drawable NimTetrisGraphics::loadBitmap(std::string rssName, BlendMode blendMode, int fix_opacity) {
	const Bitmap32* bitmap32 = resources.getBitmap32Resource(rssName);
	return Drawable::Bitmap(*bitmap32, blendMode, fix_opacity);
}
Drawable NimTetrisGraphics::createBitmap(int width, int height, Drawable content, BlendMode blendMode, int fix_opacity) {
	return Drawable::Bitmap(*createBitmap32(width, height, content), blendMode);
}
void NimTetrisGraphics::loadBitmaps(std::string rssName, Drawable arr[], int size, BlendMode blendMode, int fix_opacity) {
	vector<Bitmap32*> bitmap32s = resources.getBitmap32Resources(rssName, size);
	for (int i = 0; i < size; i++) {
		arr[i] = Drawable::Bitmap(*bitmap32s[i], blendMode, fix_opacity);
	}
}

void NimTetrisGraphics::initialize() {
	oldBackground = loadBitmap("IOld_Background");
	oldGameover = loadBitmap("IOld_GameOver", BlendMode::COVER, 1);
	loadBitmaps("IOld_Results", oldResult, 4, BlendMode::COVER, 1);
	loadBitmaps("IOld_Blocks", oldBlocks, N_OF_TETROMINO);
	loadBitmaps("IOld_Chs", oldCursers, N_OF_TETROMINO, BlendMode::MULTIPLY, 1);

	oldBlockDisabled = loadBitmap("IOld_blank_disabled");
	oldBlankDisabled = Drawable::Filter(BLOCK_WIDTH, BLOCK_HEIGHT, Color32{ (uint8_t)192, (uint8_t)192, (uint8_t)192, (uint8_t)255 }, BlendMode::MULTIPLY, 1);

	loadBitmaps("IBackgrounds", backgrounds, 8);

	leftTopFrame = Drawable::Composite({
		loadBitmap("IBoard_Frame_LT_Shadow", BlendMode::MULTIPLY, 1),
		loadBitmap("IBoard_Frame_LT_Highlight", BlendMode::ADD, 1)
		});
	leftBottomFrame = Drawable::Composite({
		loadBitmap("IBoard_Frame_LB_Shadow", BlendMode::MULTIPLY, 1),
		loadBitmap("IBoard_Frame_LB_Highlight", BlendMode::ADD, 1)
		});
	rightTopFrame = Drawable::Composite({
		loadBitmap("IBoard_Frame_RT_Shadow", BlendMode::MULTIPLY, 1),
		loadBitmap("IBoard_Frame_RT_Highlight", BlendMode::ADD, 1)
		});
	rightBottomFrame = Drawable::Composite({
		loadBitmap("IBoard_Frame_RB_Shadow", BlendMode::MULTIPLY, 1),
		loadBitmap("IBoard_Frame_RB_Highlight", BlendMode::ADD, 1)
		});
	leftFrame = Drawable::Composite({
		loadBitmap("IBoard_Frame_L_Shadow", BlendMode::MULTIPLY, 1),
		loadBitmap("IBoard_Frame_L_Highlight", BlendMode::ADD, 1)
		});
	rightFrame = Drawable::Composite({
		loadBitmap("IBoard_Frame_R_Shadow", BlendMode::MULTIPLY, 1),
		loadBitmap("IBoard_Frame_R_Highlight", BlendMode::ADD, 1)
		});
	topFrame = Drawable::Composite({
		loadBitmap("IBoard_Frame_T_Shadow", BlendMode::MULTIPLY, 1),
		loadBitmap("IBoard_Frame_T_Highlight", BlendMode::ADD, 1)
		});
	bottomFrame = Drawable::Composite({
		loadBitmap("IBoard_Frame_B_Shadow", BlendMode::MULTIPLY, 1),
		loadBitmap("IBoard_Frame_B_Highlight", BlendMode::ADD, 1)
		});

	place = Drawable::Composite({
		Drawable::Translucent(1.0, loadBitmap("IPlace_Shadow", BlendMode::MULTIPLY, 1)),
		Drawable::Translucent(1.0, loadBitmap("IPlace_Highlight", BlendMode::ADD, 1))
		});
	xMark = Drawable::Composite({
		loadBitmap("IDisable_Cover", BlendMode::COVER, 1),
		loadBitmap("IDisable_Shadow", BlendMode::MULTIPLY, 1),
		loadBitmap("IDisable_Highlight", BlendMode::ADD, 1)
		});
	block_x = loadBitmap("IBlock_X");

	Drawable blocks_transparency[N_OF_TETROMINO];
	Drawable blocks_cover[N_OF_TETROMINO];
	Drawable block_highlight;
	loadBitmaps("IBlocks_Mul", blocks_transparency, N_OF_TETROMINO, BlendMode::MULTIPLY, 1);
	loadBitmaps("IBlocks_Cover", blocks_cover, N_OF_TETROMINO, BlendMode::COVER, 1);

	block_highlight = loadBitmap("IBlock_Highlight", BlendMode::ADD, 1);
	for (int i = 0; i < N_OF_TETROMINO; i++) {
		blocks[i] = Drawable::Composite({ 
			blocks_transparency[i],
			blocks_cover[i],
			block_highlight 
			});
	}

	Drawable cursurs_highlight[N_OF_TETROMINOFIXED];
	loadBitmaps("ICursers_Highlight", cursurs_highlight, N_OF_TETROMINOFIXED, BlendMode::ADD);
	for (int i = 0; i < N_OF_TETROMINOFIXED; i++) {
		const TetrominoFixedInfo& info = TetrominoFixedInfo::get(i);
		tetrominos[i] = Drawable::Composite({
			Drawable::Moved(info.coordinates[0].second * BLOCK_INTERVAL_X, info.coordinates[0].first * BLOCK_INTERVAL_Y, blocks[int(info.id)]),
			Drawable::Moved(info.coordinates[1].second * BLOCK_INTERVAL_X, info.coordinates[1].first * BLOCK_INTERVAL_Y, blocks[int(info.id)]),
			Drawable::Moved(info.coordinates[2].second * BLOCK_INTERVAL_X, info.coordinates[2].first * BLOCK_INTERVAL_Y, blocks[int(info.id)]),
			Drawable::Moved(info.coordinates[3].second * BLOCK_INTERVAL_X, info.coordinates[3].first * BLOCK_INTERVAL_Y, blocks[int(info.id)])
			});

		Drawable cursur_cover = Drawable::Filter(BLOCK_WIDTH, BLOCK_HEIGHT, Color32{ (uint8_t)255, (uint8_t)255, (uint8_t)255, (uint8_t)64 }, BlendMode::COVER, 1);
		tetromino_cursurs[i] = Drawable::Composite({
			Drawable::Moved(info.coordinates[0].second * BLOCK_INTERVAL_X, info.coordinates[0].first * BLOCK_INTERVAL_Y, cursur_cover),
			Drawable::Moved(info.coordinates[1].second * BLOCK_INTERVAL_X, info.coordinates[1].first * BLOCK_INTERVAL_Y, cursur_cover),
			Drawable::Moved(info.coordinates[2].second * BLOCK_INTERVAL_X, info.coordinates[2].first * BLOCK_INTERVAL_Y, cursur_cover),
			Drawable::Moved(info.coordinates[3].second * BLOCK_INTERVAL_X, info.coordinates[3].first * BLOCK_INTERVAL_Y, cursur_cover),
			Drawable::Moved(-6, -6, cursurs_highlight[i])
			});
	}
}
void NimTetrisGraphics::finalize() {
	bitmap32Pool.releaseAll();
}