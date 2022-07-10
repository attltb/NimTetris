#ifndef _RandomizerHeader_
#define _RandomizerHeader_
#include <random>
class Randomizer {
public:
	static std::mt19937 algorithm;

public:
	static void initialize() {
		std::random_device rd;
		algorithm = std::mt19937(rd());
	}

public:
	bool getBool() {
		return algorithm() % 2 == 0;
	}
	int getNumUnder(int i) {
		std::uniform_int_distribution<int> dis(0, i - 1);
		return dis(algorithm);
	}
};
#endif