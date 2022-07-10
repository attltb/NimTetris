#ifndef _BoardCompressed10x10Header_
#define _BoardCompressed10x10Header_
#include "BlockCompressed10x10.hpp"
#include <cstdint>
class BoardLogic {
public:
	int at[10][10];
};
class BoardCompressed10x10 {
	//bit-compressed 10x10 board data

private:
	uint32_t row0_1_2;
	uint32_t row3_4_5;
	uint32_t row6_7_8;
	uint32_t row9;

public:
	BoardCompressed10x10() : row0_1_2(0), row3_4_5(0), row6_7_8(0), row9(0) {}
	BoardCompressed10x10(int i) {
		if (i) row0_1_2 = 0x3FFFFFFF, row3_4_5 = 0x3FFFFFFF, row6_7_8 = 0x3FFFFFFF, row9 = 0x000003FF;
		else row0_1_2 = 0, row3_4_5 = 0, row6_7_8 = 0, row9 = 0;
	}
	BoardCompressed10x10(uint32_t _row0, uint32_t _row1, uint32_t _row2, uint32_t _row3, uint32_t _row4, uint32_t _row5, 
		uint32_t _row6, uint32_t _row7, uint32_t _row8, uint32_t _row9) :
		row0_1_2(_row0 | (_row1 << 10) | (_row2 << 20)), row3_4_5(_row3 | (_row4 << 10) | (_row5 << 20)), 
		row6_7_8(_row6 | (_row7 << 10) | (_row8 << 20)), row9(_row9) {};
	BoardCompressed10x10(const BoardCompressed10x10& other) : 
		row0_1_2(other.row0_1_2), row3_4_5(other.row3_4_5), row6_7_8(other.row6_7_8), row9(other.row9) {};

public:
	bool is_full() const {
		if ((row0_1_2 & 0x3FFFFFFF) != 0x3FFFFFFF) return false;
		if ((row3_4_5 & 0x3FFFFFFF) != 0x3FFFFFFF) return false;
		if ((row6_7_8 & 0x3FFFFFFF) != 0x3FFFFFFF) return false;
		if ((row9 & 0x000003FF) != 0x000003FF) return false;
		return true;
	}
	unsigned long row(int i) const {
		switch (i) {
		case 0:
			return row0_1_2 & 0x000003FF;
		case 1:
			return (row0_1_2 >> 10) & 0x000003FF;
		case 2:
			return row0_1_2 >> 20;
		case 3:
			return row3_4_5 & 0x000003FF;
		case 4:
			return (row3_4_5 >> 10) & 0x000003FF;
		case 5:
			return row3_4_5 >> 20;
		case 6:
			return row6_7_8 & 0x000003FF;
		case 7:
			return (row6_7_8 >> 10) & 0x000003FF;
		case 8:
			return row6_7_8 >> 20;
		case 9:
			return row9;
		}
		return 0;
	}


public:
	BoardLogic test() {
		BoardLogic ret;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (row(i) & (1 << j)) ret.at[i][j] = 1;
				else ret.at[i][j] = 0;
			}
		}
		return ret;
	}

public:
	void merge_or(int i, uint32_t form) {
		switch (i) {
		case 0:
			row0_1_2 |= form;
			return;
		case 1:
			row0_1_2 |= form << 10;
			return;
		case 2:
			row0_1_2 |= form << 20;
			return;
		case 3:
			row3_4_5 |= form;
			return;
		case 4:
			row3_4_5 |= form << 10;
			return;
		case 5:
			row3_4_5 |= form << 20;
			return;
		case 6:
			row6_7_8 |= form;
			return;
		case 7:
			row6_7_8 |= form << 10;
			return;
		case 8:
			row6_7_8 |= form << 20;
			return;
		case 9:
			row9 |= form;
			return;
		}
		return; 
	}
	void merge_and(int i, uint32_t form) {
		switch (i) {
		case 0:
			row0_1_2 ^= form;
			return;
		case 1:
			row0_1_2 ^= form << 10;
			return;
		case 2:
			row0_1_2 ^= form << 20;
			return;
		case 3:
			row3_4_5 ^= form;
			return;
		case 4:
			row3_4_5 ^= form << 10;
			return;
		case 5:
			row3_4_5 ^= form << 20;
			return;
		case 6:
			row6_7_8 ^= form;
			return;
		case 7:
			row6_7_8 ^= form << 10;
			return;
		case 8:
			row6_7_8 ^= form << 20;
			return;
		case 9:
			row9 ^= form;
			return;
		}
		return;
	}
	void put(BlockCompressed10x10 obj) {
		switch (obj.kind) {
		case BlockCompressed10x10::At::R0__2:
			row0_1_2 |= obj.rows_l;
			return;
		case BlockCompressed10x10::At::R0__5:
			row0_1_2 |= obj.rows_l;
			row3_4_5 |= obj.rows_h;
			return;
		case BlockCompressed10x10::At::R3__5:
			row3_4_5 |= obj.rows_l;
			return;
		case BlockCompressed10x10::At::R3__8:
			row3_4_5 |= obj.rows_l;
			row6_7_8 |= obj.rows_h;
			return;
		case BlockCompressed10x10::At::R6__8:
			row6_7_8 |= obj.rows_l;
			return;
		case BlockCompressed10x10::At::R6__9:
			row6_7_8 |= obj.rows_l;
			row9 |= obj.rows_h;
			return;
		case BlockCompressed10x10::At::R9__9:
			row9 |= obj.rows_l;
			return;
		}
	}
	bool putable(BlockCompressed10x10 obj) const {
		switch (obj.kind) {
		case BlockCompressed10x10::At::R0__2:
			return !(row0_1_2 & obj.rows_l);
		case BlockCompressed10x10::At::R0__5:
			return !(row0_1_2 & obj.rows_l) && !(row3_4_5 & obj.rows_h);
		case BlockCompressed10x10::At::R3__5:
			return !(row3_4_5 & obj.rows_l);
		case BlockCompressed10x10::At::R3__8:
			return !(row3_4_5 & obj.rows_l) && !(row6_7_8 & obj.rows_h);
		case BlockCompressed10x10::At::R6__8:
			return !(row6_7_8 & obj.rows_l);
		case BlockCompressed10x10::At::R6__9:
			return !(row6_7_8 & obj.rows_l) && !(row9 & obj.rows_h);
		case BlockCompressed10x10::At::R9__9:
			return !(row9 & obj.rows_l);
		}
		return false;
	}
};
#endif