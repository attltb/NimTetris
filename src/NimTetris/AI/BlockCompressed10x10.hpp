#ifndef _BlockCompressed10x10Header_
#define _BlockCompressed10x10Header_
#include <cstdint>
class BlockCompressed10x10 {
	friend class BoardCompressed10x10;

public:
	enum class At { R0__2, R0__5, R3__5, R3__8, R6__8, R6__9, R9__9 };

public:
	bool operator == (BlockCompressed10x10 other) const {
		if (kind != other.kind) return false;
		if (rows_l != other.rows_l) return false;
		if (rows_h != other.rows_h) return false;
		return true;
	}
	bool operator != (BlockCompressed10x10 other) const {
		if (kind != other.kind) return true;
		if (rows_l != other.rows_l) return true;
		if (rows_h != other.rows_h) return true;
		return false;
	}
	bool operator < (BlockCompressed10x10 other) const {
		if (kind < other.kind) return true;
		if (kind > other.kind) return false;
		if (rows_l < other.rows_l) return true;
		if (rows_l > other.rows_l) return false;
		if (rows_h < other.rows_h) return true;
		if (rows_h > other.rows_h) return false;
		return false;
	}

public:
	BlockCompressed10x10() : kind(At::R0__2), rows_l(0), rows_h(0) {}
	BlockCompressed10x10(uint32_t row0, uint32_t row1, uint32_t row2, uint32_t row3, uint32_t row4, uint32_t row5,
		uint32_t row6, uint32_t row7, uint32_t row8, uint32_t row9) {
		uint32_t row0_1_2 = row0 | (row1 << 10) | (row2 << 20);
		uint32_t row3_4_5 = row3 | (row4 << 10) | (row5 << 20);
		uint32_t row6_7_8 = row6 | (row7 << 10) | (row8 << 20);

		if (row0_1_2) {
			rows_l = row0_1_2;
			if (row3_4_5) kind = At::R0__5, rows_h = row3_4_5;
			else kind = At::R0__2, rows_h = 0;
		}
		else if (row3_4_5) {
			rows_l = row3_4_5;
			if (row6_7_8) kind = At::R3__8, rows_h = row6_7_8;
			else kind = At::R3__5, rows_h = 0;
		}
		else if (row6_7_8) {
			rows_l = row6_7_8;
			if (row9) kind = At::R6__9, rows_h = row9;
			else kind = At::R6__8, rows_h = 0;
		}
		else kind = At::R9__9, rows_l = row9, rows_h = 0;
	}

private:
	BlockCompressed10x10(At _kind, uint32_t _rows_l) : kind(_kind), rows_l(_rows_l), rows_h(0) {};
	BlockCompressed10x10(At _kind, uint32_t _rows_l, uint32_t _rows_h) : kind(_kind), rows_l(_rows_l), rows_h(_rows_h) {};

private:
	At kind;
	uint32_t rows_l;
	uint32_t rows_h;
};
#endif