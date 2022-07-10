#ifndef _ResourceCollectionHeader_
#define _ResourceCollectionHeader_
#include <string>
#include <vector>
#include <map>
#include "Resources.hpp"
class ResourceCollection {
public:
	enum class ERR_CODE { OK, FILE_NOT_EXIST, FILE_INVALID, OUT_OF_MEMORY };

private:
	void* pdata;
	std::map<std::string, Resource*> resources;

public:
	ResourceCollection() : pdata(nullptr) {}
	~ResourceCollection() {
		for (auto it = resources.begin(); it != resources.end(); it++) delete it->second;
		if (pdata) free(pdata);
		resources.clear();
	}

public:
	ERR_CODE load(std::string filename);
	void unload();

public:
	void setResource(std::string rssname, ResourceKind kind, std::vector<void*> pdatas) {
		resources[rssname] = Resource::of(kind, pdatas);
	}

public:
	const BinaryData* getBinaryResource(std::string rssname);
	const std::vector<BinaryData*> getBinaryResources(std::string rssname, int size);
	const Bitmap32* getBitmap32Resource(std::string rssname);
	const std::vector<Bitmap32*> getBitmap32Resources(std::string rssname, int size);
};
#endif