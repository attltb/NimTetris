#ifndef _BinaryDataHeader_
#define _BinaryDataHeader_
#include <stdint.h>
class BinaryData {
private:
	int use_external_memory;

public:
	int size;
	uint8_t* bits;

public:
	BinaryData(int _size) : size(_size), use_external_memory(1) {
		if (size) {
			bits = new uint8_t[size];
		}
		else bits = nullptr;
	}
	BinaryData(int _size, uint8_t* _bits) : size(_size), bits(_bits), use_external_memory(1) {}
	~BinaryData() {
		if (!use_external_memory && bits) delete[] bits;
	}
};
#endif