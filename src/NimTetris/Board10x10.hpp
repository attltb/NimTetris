#ifndef _Board10x10Header_
#define _Board10x10Header_
#include "Blocks.hpp"
enum class PlaceState : int { EMPTY, EMPTY_MARKED, I, O, L, J, T, S, Z };
struct Board10x10 {
	static PlaceState getPlaceState(TetrominoID tetrominoID);

public:
	PlaceState at[10][10];

private:
	std::vector<std::pair<int, int>> markDisabled();

public:
	bool isFull() const;
	bool isPutable(Tetromino10x10 block) const;

public:
	void clear();
	void copy(const Board10x10& other);
	void put(Tetromino10x10 block);
	std::vector<std::pair<int, int>> putAndMarkDisabled(Tetromino10x10 block);
};
#endif