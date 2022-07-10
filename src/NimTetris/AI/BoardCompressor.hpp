#ifndef _BoardCompressorHeader_
#define _BoardCompressorHeader_
#include "Board10x10.hpp"
#include "BoardCompressed10x10.hpp"
class BoardCompressor {
	const Board10x10* pBoard;

private:
	uint32_t getBitsInRow(int rowNo) {
		const PlaceState* ptr = pBoard->at[rowNo];
		uint32_t row = 0;
		if (ptr[0] != PlaceState::EMPTY) row |= (uint32_t)0x00000001;
		if (ptr[1] != PlaceState::EMPTY) row |= (uint32_t)0x00000002;
		if (ptr[2] != PlaceState::EMPTY) row |= (uint32_t)0x00000004;
		if (ptr[3] != PlaceState::EMPTY) row |= (uint32_t)0x00000008;
		if (ptr[4] != PlaceState::EMPTY) row |= (uint32_t)0x00000010;
		if (ptr[5] != PlaceState::EMPTY) row |= (uint32_t)0x00000020;
		if (ptr[6] != PlaceState::EMPTY) row |= (uint32_t)0x00000040;
		if (ptr[7] != PlaceState::EMPTY) row |= (uint32_t)0x00000080;
		if (ptr[8] != PlaceState::EMPTY) row |= (uint32_t)0x00000100;
		if (ptr[9] != PlaceState::EMPTY) row |= (uint32_t)0x00000200;
		return row;
	}

public:
	BoardCompressed10x10 compress(const Board10x10& board) {
		pBoard = &board;
		return BoardCompressed10x10(
			getBitsInRow(0), getBitsInRow(1), getBitsInRow(2), 
			getBitsInRow(3), getBitsInRow(4), getBitsInRow(5), 
			getBitsInRow(6), getBitsInRow(7), getBitsInRow(8), 
			getBitsInRow(9));
	}
};
#endif