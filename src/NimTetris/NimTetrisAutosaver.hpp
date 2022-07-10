#ifndef _NimTetrisAutosaverHeader_
#define _NimTetrisAutosaverHeader_
#include "NimTetrisAutosaveds.hpp"
#include <string>
class NimTetrisAutosaver {
public:
	enum class ERR_CODE { OK, FILE_NOT_EXIST, FILE_INVALID, OUT_OF_MEMORY };

public:
	ERR_CODE load(NimTetrisAutosaveds& autosave, std::string filename);
	ERR_CODE save(NimTetrisAutosaveds& autosave, std::string filename);
};
#endif