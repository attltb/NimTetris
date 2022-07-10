#ifndef _NimTBoardHeader_
#define _NimTBoardHeader_
#include "KeyCode.hpp"
#include "ThreadManager.hpp"
#include "Blocks.hpp"
#include "Board10x10.hpp"
#include "NimTetrisAutosaveds.hpp"
#include "NimTBlock.hpp"
#include "NimTDisabledMark.hpp"
#include "NimTBoardFrame.hpp"
#include "NimTBoardOverAnim.hpp"
#include "NimTPlayer.hpp"
class NimTBoard {
public:
	enum class Status : int { INITIALIZING, SETTING, PREPARED, PLAYING, GAMEOVERANIM, GAMEOVER };
	enum class ResultSign : int { NON, P1RESIGN, P2RESIGN, P1WIN, P2WIN };

private:
	ThreadManager& threadManager;
	NimTetrisAutosaveds& autosaveds;
	const NimTetrisGraphics& graphics;
	Thread* takePlayerInfoThread;

private:
	Status status;
	ResultSign resultSign;
	int turn;
	int animFrameNo;
	Board10x10 board;
	NimTBoardFrame frame;
	NimTBoardOverAnim overAnim;
	NimTPlayer* player1;
	NimTPlayer* player2;
	Tetromino10x10 cursur;
	std::vector<std::pair<std::pair<int, int>, NimTBlock>> blocks;
	std::vector<std::pair<std::pair<int, int>, NimTDisabledMark>> disabledMarks;

private:
	static void takePlayerInfoCallback(void* param);

private:
	NimTPlayer* getPlayingPlayer() {
		if (turn == 1) return player1;
		else return player2;
	}
	const NimTPlayer* getPlayingPlayer() const {
		if (turn == 1) return player1;
		else return player2;
	}
	NimTPlayer* getWaitingPlayer() {
		if (turn == 1) return player2;
		else return player1;
	}
	const NimTPlayer* getWaitingPlayer() const {
		if (turn == 1) return player2;
		else return player1;
	}

private:
	void addDisabledMarks(const std::vector<std::pair<int, int>>& coodinates);
	void addBlock(Tetromino10x10 block);

private:
	void input(Tetromino10x10 block);
	void startGameOverAnim();
	void skipGameOverAnim();
	void proceed();
	void endGame(ResultSign _resultSign);
	void applyPlay();
	void applyResign();
	void askPlayerInfoAndReset();
	void resetBoard();
	void startGame();
	void changePlayingPlayer();

public:
	void onInitialize();
	void onFrame(int frameNo);
	void onKeyDown(KeyCode keycode);
	void onMouseMove(int xPos, int yPos);
	void onMouseLDown(int xPos, int yPos);

private:
	Drawable getScreen_Backlight() const;
	Drawable getScreen_Places() const;
	Drawable getScreen_DisabledMarks() const;
	Drawable getScreen_Blocks() const;
	Drawable getScreen_LightAnim() const;
	Drawable getScreen_Cursur() const;
	Drawable getScreen_insideFrame() const;

public:
	Drawable getScreen() const;

public:
	NimTBoard(ThreadManager& _threadManager, NimTetrisAutosaveds& _autosaveds, const NimTetrisGraphics& _graphics) :
		threadManager(_threadManager), autosaveds(_autosaveds), graphics(_graphics), status(Status::INITIALIZING), resultSign(ResultSign::NON),
		frame(_graphics), overAnim(_graphics, board), player1(nullptr), player2(nullptr) {
		blocks.reserve(25);
		disabledMarks.reserve(50);
	}
};
#endif