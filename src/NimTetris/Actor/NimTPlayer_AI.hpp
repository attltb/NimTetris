#ifndef _NimTPlayer_AIHeader_
#define _NimTPlayer_AIHeader_
#include "NimTPlayer.hpp"
#include "NimTetrisAI.hpp"
#include "NimTetrisAIThreadRunner.hpp"
class NimTPlayer_AI : public NimTPlayer {
	NimTetrisPlayerInfo& playerInfo;
	NimTetrisAI ai;
	NimTetrisAIThreadRunner aiThreadRunner;

public:
	bool showCursur() const {
		return false;
	}
	NimTetrisPlayerInfo& getPlayerInfo() const {
		return playerInfo;
	}

public:
	void initBoard(const Board10x10& board) {
		ai.reset(board);
	}
	void startTurn() {
		aiThreadRunner.createAIThread(&ai);
	}
	void startTurn(Tetromino10x10 block) {
		ai.applyOpponentPlay(block);
		aiThreadRunner.createAIThread(&ai);
	}
	Tetromino10x10 endTurn() {
		aiThreadRunner.closeThreadHandle();
		return ai.getlastAIPlay();
	}

public:
	void onUserCursurMove(Tetromino10x10 block) {};
	bool onUserInput(Tetromino10x10 block) {
		return false;
	}
	bool onUserResign() {
		return false;
	}
	void onWin() {}
	void onLose() {}
	bool onFrame(int frameNo) {
		return ai.isAIPlayed();
	}

public:
	NimTPlayer_AI(NimTetrisPlayerInfo& _playerInfo, ThreadManager& threadManager) : playerInfo(_playerInfo), 
		ai(NimTetrisPlayerInfo::getAILevel(playerInfo.control)), aiThreadRunner(threadManager) {}
};
#endif