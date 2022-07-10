#ifndef _ResourcesHeader_
#define _ResourcesHeader_
#include <vector>
#include "ResourceKind.hpp"
#include "BinaryData.hpp"
#include "Bitmap32.hpp"
class Resourse_Binary;
class Resourse_Bitmap32;
class Resource {
public:
	ResourceKind kind;

public:
	Resource(ResourceKind _kind) : kind(_kind) {};
	virtual ~Resource() {};

public:
	static Resource* of(ResourceKind kind, std::vector<void*> pdatas);
	static Resourse_Binary* binary(std::vector<void*> pdatas);
	static Resourse_Bitmap32* bitmap32(std::vector<void*> pdatas);
};

class Resourse_Binary : public Resource {
public:
	std::vector<BinaryData*> binarys;

public:
	Resourse_Binary(std::vector<BinaryData*>&& _binarys) : Resource(ResourceKind::Binary), binarys(_binarys) {};
	~Resourse_Binary() {
		for (auto it = binarys.begin(); it != binarys.end(); it++) delete* it;
	};
};
class Resourse_Bitmap32 : public Resource {
public:
	std::vector<Bitmap32*> bitmaps;

public:
	Resourse_Bitmap32(std::vector<Bitmap32*>&& _bitmaps) : Resource(ResourceKind::Binary), bitmaps(_bitmaps) {};
	~Resourse_Bitmap32() {
		for (auto it = bitmaps.begin(); it != bitmaps.end(); it++) delete* it;
	};
};
#endif