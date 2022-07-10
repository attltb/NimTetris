#ifndef _NimTPlayer_UserHeader_
#define _NimTPlayer_UserHeader_
#include "NimTPlayer.hpp"
class NimTPlayer_User : public NimTPlayer {
	NimTetrisPlayerInfo& playerInfo;
	Tetromino10x10 play;

public:
	bool showCursur() const {
		return true;
	}
	NimTetrisPlayerInfo& getPlayerInfo() const {
		return playerInfo;
	}

public:
	void initBoard(const Board10x10& board) {}
	void startTurn() {}
	void startTurn(Tetromino10x10 block) {}
	Tetromino10x10 endTurn() {
		return play;
	}

public:
	void onUserCursurMove(Tetromino10x10 block) {}
	bool onUserInput(Tetromino10x10 block) {
		play = block;
		return true;
	}
	bool onUserResign() {
		return true;
	}
	void onWin() {};
	void onLose() {};
	bool onFrame(int frameNo) {
		return false;
	}

public:
	NimTPlayer_User(NimTetrisPlayerInfo& _playerInfo) : playerInfo(_playerInfo) {};
};
#endif