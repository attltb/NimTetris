#ifndef _NimTetrisAIHeader_
#define _NimTetrisAIHeader_
#include "Blocks.hpp"
#include "Board10x10.hpp"
#include "NimTetrisAIConfig.hpp"
#include "ConnectedComponentsWithAnalysis.hpp"
class NimTetrisAI {
	static std::vector<BlockCompressed10x10> allAllowedPlays;

public:
	enum class GameState { Uncertain, Winning, Losing };

private:
	const NimTetrisAIConfig config;
	std::vector<BlockCompressed10x10> allowedPlays;
	BoardCompressed10x10 boardCompressed;
	CCsWithAnalysis components;
	bool lastAIPlayed;
	Tetromino10x10 lastAIPlay;
	GameState lastAIGameState;

public:
	static std::vector<BlockCompressed10x10> getShuffledAllAllowedPlays();
	static void initialize();

public:
	bool isEnd() {
		return components.empty();
	}
	bool isAIWinning() {
		return lastAIGameState == GameState::Winning;
	}
	bool isAILosing() {
		return lastAIGameState == GameState::Losing;
	}
	bool isAIPlayed() {
		return lastAIPlayed;
	}
	GameState getlastAIState() {
		return lastAIGameState;
	}
	Tetromino10x10 getlastAIPlay() {
		return lastAIPlay;
	};

public:
	void reset();
	void reset(const Board10x10& board);
	void reset(const BoardCompressed10x10& _boardCompressed);

private:
	static std::pair<BlockCompressed10x10, bool> findSafePlay(CCWithAnalysis* component, CCWithAnalysis* component_op, OptimizedInformationSet set_others);
	static std::pair<BlockCompressed10x10, bool> findWinningPlay(CCWithAnalysis* component, OptimizedInformationSet set_others);

private:
	std::vector<OptimizedInformationSet> getSetsOthersMultiplied();
	OptimizedInformationSet getSetOthersMultiplied(unsigned int i_except);
	OptimizedInformationSet getSetOthersMultiplied(unsigned int i_except1, unsigned int i_except2);

private:
	int tryAnalyzeComponents();
	BlockCompressed10x10 findArbitraryPlay();
	BlockCompressed10x10 findMostDifficultPlay();
	std::pair<BlockCompressed10x10, GameState> findBestPlay_uncertain();
	std::pair<BlockCompressed10x10, GameState> findBestPlay_losing();
	std::pair<BlockCompressed10x10, GameState> findBestPlay_failcount0();
	std::pair<BlockCompressed10x10, GameState> findBestPlay_failcount1();
	std::pair<BlockCompressed10x10, GameState> findBestPlay_failcount2();
	std::pair<BlockCompressed10x10, GameState> findBestPlay();

private:
	void applyPlay(BlockCompressed10x10 block);

public:
	void applyAIPlay();
	void applyOpponentPlay(Tetromino10x10 play);

public:
	std::pair<BlockCompressed10x10, GameState> testWith(int board[10][10]);

public:
	NimTetrisAI(int aiLevel) : config(aiLevel), lastAIPlayed(false) {};
};
#endif