#include "Resources.hpp"
using namespace std;
Resource* Resource::of(ResourceKind kind, std::vector<void*> pdatas) {
	switch (kind) {
	case ResourceKind::Binary: return binary(pdatas);
	case ResourceKind::Bitmap32: return bitmap32(pdatas);
	}
	return nullptr;
}

Resourse_Binary* Resource::binary(vector<void*> pdatas) {
	std::vector<BinaryData*> binarys;
	binarys.resize(pdatas.size());
	for (unsigned int i = 0; i < pdatas.size(); i++) {
		int* pdata = (int*)(pdatas[i]);
		binarys[i] = new BinaryData(pdata[0], (uint8_t*)(pdata + 1));
	}
	return new Resourse_Binary(std::move(binarys));
}
Resourse_Bitmap32* Resource::bitmap32(vector<void*> pdatas) {
	std::vector<Bitmap32*> bitmaps;
	bitmaps.resize(pdatas.size());
	for (unsigned int i = 0; i < pdatas.size(); i++) {
		int* pdata = (int*)(pdatas[i]);
		bitmaps[i] = new Bitmap32(pdata[0], pdata[1], (Color32*)(pdata + 2));
	}
	return new Resourse_Bitmap32(std::move(bitmaps));
}