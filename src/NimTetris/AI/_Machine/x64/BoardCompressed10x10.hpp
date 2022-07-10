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
	uint64_t rows_l;
	uint64_t rows_h;

public:
	BoardCompressed10x10() : rows_l(0), rows_h(0) {}
	BoardCompressed10x10(int i) {
		if (i) rows_l = 0x0003FFFFFFFFFFFF, rows_h = 0x0003FFFFFFFFFFFF;
		else rows_l = 0, rows_h = 0;
	}
	BoardCompressed10x10(uint32_t row0, uint32_t row1, uint32_t row2, uint32_t row3, uint32_t row4, uint32_t row5, 
		uint32_t row6, uint32_t row7, uint32_t row8, uint32_t row9) :
		rows_l(row0 | (row1 << 10) | (row2 << 20) | (row3 << 30) | (row4 << 40)),
		rows_h(row5 | (row6 << 10) | (row7 << 20) | (row8 << 30) | (row9 << 40)) {};
	BoardCompressed10x10(const BoardCompressed10x10& other) : rows_l(other.rows_l), rows_h(other.rows_h) {};

public:
	bool is_full() const {
		if ((rows_l & 0x0003FFFFFFFFFFFF) != 0x0003FFFFFFFFFFFF) return false;
		if ((rows_h & 0x0003FFFFFFFFFFFF) != 0x0003FFFFFFFFFFFF) return false;
		return true;
	}
	unsigned long row(int i) const {
		switch (i) {
		case 0:
			return rows_l & 0x000003FF;
		case 1:
			return (rows_l >> 10) & 0x000003FF;
		case 2:
			return (rows_l >> 20) & 0x000003FF;
		case 3:
			return (rows_l >> 30) & 0x000003FF;
		case 4:
			return rows_l >> 40;
		case 5:
			return rows_h & 0x000003FF;
		case 6:
			return (rows_h >> 10) & 0x000003FF;
		case 7:
			return (rows_h >> 20) & 0x000003FF;
		case 8:
			return (rows_h >> 30) & 0x000003FF;
		case 9:
			return rows_h >> 40;
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
			rows_l |= form;
			return;
		case 1:
			rows_l |= form << 10;
			return;
		case 2:
			rows_l |= form << 20;
			return;
		case 3:
			rows_l |= form << 30;
			return;
		case 4:
			rows_l |= form << 40;
			return;
		case 5:
			rows_h |= form;
			return;
		case 6:
			rows_h |= form << 10;
			return;
		case 7:
			rows_h |= form << 20;
			return;
		case 8:
			rows_h |= form << 30;
			return;
		case 9:
			rows_h |= form << 40;
			return;
		}
		return; 
	}
	void merge_and(int i, uint32_t form) {
		switch (i) {
		case 0:
			rows_l ^= form;
			return;
		case 1:
			rows_l ^= form << 10;
			return;
		case 2:
			rows_l ^= form << 20;
			return;
		case 3:
			rows_l ^= form << 30;
			return;
		case 4:
			rows_l ^= form << 40;
			return;
		case 5:
			rows_h ^= form;
			return;
		case 6:
			rows_h ^= form << 10;
			return;
		case 7:
			rows_h ^= form << 20;
			return;
		case 8:
			rows_h ^= form << 30;
			return;
		case 9:
			rows_h ^= form << 40;
			return;
		}
		return;
	}
	void put(BlockCompressed10x10 obj) {
		rows_l |= obj.rows_l;
		rows_h |= obj.rows_h;
	}
	bool putable(BlockCompressed10x10 obj) const {
		return !(rows_l & obj.rows_l) && !(rows_h & obj.rows_h);
	}
};
#endif