#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "ResourceCollection.hpp"
using namespace std;
ResourceCollection::ERR_CODE ResourceCollection::load(std::string filename) {
	FILE* file = fopen(filename.c_str(), "rb");
	if (!file) return ResourceCollection::ERR_CODE::FILE_NOT_EXIST;

	fseek(file, 0, SEEK_END);
	size_t filesize = ftell(file);
	fseek(file, 0, SEEK_SET);
	if (8 > filesize) {
		fclose(file);
		return ResourceCollection::ERR_CODE::FILE_INVALID;
	}

	pdata = malloc(filesize);
	if (!pdata) {
		fclose(file);
		return ResourceCollection::ERR_CODE::OUT_OF_MEMORY;
	}

	size_t rdsize = fread(pdata, 1, filesize, file);
	fclose(file);

	if(*((int*)pdata) != 'rc') return ResourceCollection::ERR_CODE::FILE_INVALID;
	int offset_header = 4;
	int offset_header_end = *(int*)((size_t)pdata + 12);
	for (; offset_header < offset_header_end;) {
		int* pheader = (int*)((size_t)pdata + offset_header);
		ResourceKind kind = (ResourceKind)pheader[0];
		if (kind == ResourceKind::Invalid) break;
		int ele_size = pheader[1];

		int* pheader_offsets = pheader + 2;
		vector<void*> pdatas(ele_size);
		for (int i = 0; i < ele_size; i++) {
			pdatas[i] = (void*)((size_t)pdata + pheader_offsets[i]);
		}

		char* pheader_name = (char*)(pheader_offsets + ele_size);
		string name = string(pheader_name);
		setResource(name, kind, pdatas);

		int header_size = int(sizeof(int) * (2 + (size_t)ele_size) + (name.size() + 1) * sizeof(char));
		if (header_size % 4) header_size += 4 - (header_size % 4);
		offset_header += header_size;
	}
	return ResourceCollection::ERR_CODE::OK;
}
void ResourceCollection::unload() {
	for (auto it = resources.begin(); it != resources.end(); it++) delete it->second;
	if (pdata) free(pdata);
	resources.clear();
	pdata = nullptr;
}

const BinaryData* ResourceCollection::getBinaryResource(std::string rssname) {
	const Resource* rss = resources.at(rssname);
	const Resourse_Binary* rss_binary = dynamic_cast<const Resourse_Binary*>(rss);

	if (!rss_binary) return nullptr;
	if (rss_binary->binarys.size() != 1) return nullptr;
	return rss_binary->binarys[0];
}
const vector<BinaryData*> ResourceCollection::getBinaryResources(std::string rssname, int size) {
	const Resource* rss = resources.at(rssname);
	const Resourse_Binary* rss_binary = dynamic_cast<const Resourse_Binary*>(rss);

	if (!rss_binary) return vector<BinaryData*>();
	if (rss_binary->binarys.size() != size) return vector<BinaryData*>();
	return rss_binary->binarys;
}
const Bitmap32* ResourceCollection::getBitmap32Resource(std::string rssname) {
	const Resource* rss = resources.at(rssname);
	const Resourse_Bitmap32* rss_binary = dynamic_cast<const Resourse_Bitmap32*>(rss);

	if (!rss_binary) return nullptr;
	if (rss_binary->bitmaps.size() != 1) return nullptr;
	return rss_binary->bitmaps[0];
}
const vector<Bitmap32*> ResourceCollection::getBitmap32Resources(std::string rssname, int size) {
	const Resource* rss = resources.at(rssname);
	const Resourse_Bitmap32* rss_binary = dynamic_cast<const Resourse_Bitmap32*>(rss);

	if (!rss_binary) return vector<Bitmap32*>();
	if (rss_binary->bitmaps.size() != size) return vector<Bitmap32*>();
	return rss_binary->bitmaps;
}