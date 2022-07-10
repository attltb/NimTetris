#ifndef _NimTPlayerHeader_
#define _NimTPlayerHeader_
#include "Blocks.hpp"
#include "Board10x10.hpp"
#include "NimTetrisPlayerInfo.hpp"
#include "ThreadManager.hpp"
class NimTPlayer {
public:
	static NimTPlayer* create(NimTetrisPlayerInfo& info, ThreadManager& threadManager);

public:
	virtual bool showCursur() const = 0;
	virtual NimTetrisPlayerInfo& getPlayerInfo() const = 0;

public:
	virtual void initBoard(const Board10x10& board) = 0;
	virtual void startTurn() = 0;
	virtual void startTurn(Tetromino10x10 block) = 0;
	virtual Tetromino10x10 endTurn() = 0;

public:
	virtual void onUserCursurMove(Tetromino10x10 block) = 0;
	virtual bool onUserInput(Tetromino10x10 block) = 0;
	virtual bool onUserResign() = 0;
	virtual void onWin() = 0;
	virtual void onLose() = 0;
	virtual bool onFrame(int frameNo) = 0;

public:
	virtual ~NimTPlayer() {};
};
#endif