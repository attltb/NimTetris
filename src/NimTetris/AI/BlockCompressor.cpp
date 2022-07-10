#include "BlockCompressor.hpp"
using namespace std; 
map<BlockCompressed10x10, Tetromino10x10> BlockCompressor::decompressor;

BlockCompressed10x10 BlockCompressor::compress(Tetromino10x10 block) {
	vector<pair<int, int>> coords = block.coordinates();
	uint32_t rows[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (unsigned int i = 0; i < coords.size(); i++) {
		rows[coords[i].first] |= ((uint32_t)1 << coords[i].second);
	}
	return BlockCompressed10x10(rows[0], rows[1], rows[2], rows[3], rows[4], rows[5], rows[6], rows[7], rows[8], rows[9]);
}
BlockCompressed10x10 BlockCompressor::compressAndMemorize(Tetromino10x10 block) {
	BlockCompressed10x10 ret = compress(block);
	decompressor[ret] = block;
	return ret;
}
Tetromino10x10 BlockCompressor::decompressFromMemory(BlockCompressed10x10 blockCompressed) {
	return decompressor[blockCompressed];
}