#ifndef _BlockCompressed10x10Header_
#define _BlockCompressed10x10Header_
#include <cstdint>
class BlockCompressed10x10 {
	friend class BoardCompressed10x10;

public:
	bool operator == (BlockCompressed10x10 other) const {
		if (rows_l != other.rows_l) return false;
		if (rows_h != other.rows_h) return false;
		return true;
	}
	bool operator != (BlockCompressed10x10 other) const {
		if (rows_l != other.rows_l) return true;
		if (rows_h != other.rows_h) return true;
		return false;
	}
	bool operator < (BlockCompressed10x10 other) const {
		if (rows_l < other.rows_l) return true;
		if (rows_l > other.rows_l) return false;
		if (rows_h < other.rows_h) return true;
		if (rows_h > other.rows_h) return false;
		return false;
	}

public:
	BlockCompressed10x10() : rows_l(0), rows_h(0) {}
	BlockCompressed10x10(uint32_t row0, uint32_t row1, uint32_t row2, uint32_t row3, uint32_t row4, uint32_t row5,
		uint32_t row6, uint32_t row7, uint32_t row8, uint32_t row9) :
		rows_l(row0 | (row1 << 10) | (row2 << 20) | (row3 << 30) | (row4 << 40)),
		rows_h(row5 | (row6 << 10) | (row7 << 20) | (row8 << 30) | (row9 << 40)) {};

private:
	BlockCompressed10x10(uint64_t _rows_l, uint64_t _rows_h) : rows_l(_rows_l), rows_h(_rows_h) {};

private:
	uint64_t rows_l;
	uint64_t rows_h;
};
#endif