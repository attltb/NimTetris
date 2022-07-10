#include "Board10x10.hpp"
#include "BoardCompressor.hpp"
#include "ConnectedComponentFinder.hpp"
#include <vector>
using namespace std;
PlaceState Board10x10::getPlaceState(TetrominoID tetrominoID) {
	switch (tetrominoID) {
	case TetrominoID::I:
		return PlaceState::I;
	case TetrominoID::O:
		return PlaceState::O;
	case TetrominoID::L:
		return PlaceState::L;
	case TetrominoID::J:
		return PlaceState::J;
	case TetrominoID::T:
		return PlaceState::T;
	case TetrominoID::S:
		return PlaceState::S;
	case TetrominoID::Z:
		return PlaceState::Z;
	}
	return PlaceState::EMPTY;
}
vector<pair<int, int>> Board10x10::markDisabled() {
	vector<pair<int, int>> coordinates = ConnectedComponentFinder(BoardCompressor().compress(*this)).getComponentCoordinatesUnder4();
	for (unsigned int i = 0; i < coordinates.size(); i++) {
		at[coordinates[i].first][coordinates[i].second] = PlaceState::EMPTY_MARKED;
	}
	return coordinates;
}

bool Board10x10::isFull() const {
	for (unsigned int i=0;i<10;i++) {
		for (unsigned int j = 0; j < 10; j++) {
			if (at[i][j] == PlaceState::EMPTY) return false;
		}
	}
	return true;
}
bool Board10x10::isPutable(Tetromino10x10 block) const {
	vector<pair<int, int>> coords = block.coordinates();
	for (unsigned int i = 0; i < coords.size(); i++) {
		if (at[coords[i].first][coords[i].second] != PlaceState::EMPTY) return false;
	}
	return true;
}

void Board10x10::clear() {
	for (unsigned int i = 0; i < 10; i++) {
		for (unsigned int j = 0; j < 10; j++) {
			at[i][j] = PlaceState::EMPTY;
		}
	}
}
void Board10x10::copy(const Board10x10& other) {
	for (unsigned int i = 0; i < 10; i++) {
		for (unsigned int j = 0; j < 10; j++) {
			at[i][j] = other.at[i][j];
		}
	}
}
void Board10x10::put(Tetromino10x10 block) {
	vector<pair<int, int>> coords = block.coordinates();
	for (unsigned int i = 0; i < coords.size(); i++) {
		at[coords[i].first][coords[i].second] = getPlaceState(block.tetrominoID);
	}
}
vector<pair<int, int>> Board10x10::putAndMarkDisabled(Tetromino10x10 block) {
	put(block);
	return markDisabled();
}