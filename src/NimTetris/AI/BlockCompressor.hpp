#ifndef _BlockCompressorHeader_
#define _BlockCompressorHeader_
#include "Blocks.hpp"
#include "BlockCompressed10x10.hpp"
#include <map>
class BlockCompressor {
	static std::map<BlockCompressed10x10, Tetromino10x10> decompressor;

public:
	BlockCompressed10x10 compress(Tetromino10x10 block);
	BlockCompressed10x10 compressAndMemorize(Tetromino10x10 block);
	Tetromino10x10 decompressFromMemory(BlockCompressed10x10 obj);
};
#endif