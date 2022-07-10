#include <stddef.h>
#include "NimTetrisAutosaver.hpp"
using namespace std;
NimTetrisAutosaver::ERR_CODE NimTetrisAutosaver::load(NimTetrisAutosaveds& autosave, std::string filename) {
	FILE* file = fopen(filename.c_str(), "rb");
	if (!file) return NimTetrisAutosaver::ERR_CODE::FILE_NOT_EXIST;

	fseek(file, 0, SEEK_END);
	int filesize = ftell(file);
	fseek(file, 0, SEEK_SET);
	if (filesize < 2 * sizeof(NimTetrisPlayerInfo) + 2 * sizeof(int)) {
		fclose(file);
		return NimTetrisAutosaver::ERR_CODE::FILE_INVALID;
	}

	void* pdata = malloc(filesize);
	if (!pdata) {
		fclose(file);
		return NimTetrisAutosaver::ERR_CODE::OUT_OF_MEMORY;
	}

	size_t rdsize = fread(pdata, 1, filesize, file);
	fclose(file);

	int custumPlayerCount;
	size_t addr = (size_t)pdata;
	autosave.lastPlayer1Info = *((NimTetrisPlayerInfo*)addr), addr += sizeof(NimTetrisPlayerInfo);
	autosave.lastPlayer2Info = *((NimTetrisPlayerInfo*)addr), addr += sizeof(NimTetrisPlayerInfo);
	autosave.nextCustumPlayerID = *((int*)addr), addr += sizeof(int);
	custumPlayerCount = *((int*)addr), addr += sizeof(int);

	if (filesize != (2 + custumPlayerCount) * sizeof(NimTetrisPlayerInfo) + 2 * sizeof(int)) {
		free(pdata);
		fclose(file);
		return NimTetrisAutosaver::ERR_CODE::FILE_INVALID;
	}

	NimTetrisPlayerInfo* custumPlayers = (NimTetrisPlayerInfo*)addr;
	autosave.custumPlayers.reserve(custumPlayerCount);
	for (int i = 0; i < custumPlayerCount; i++) {
		autosave.custumPlayers.push_back(custumPlayers[i]);
	}
	free(pdata);
	fclose(file);
	return NimTetrisAutosaver::ERR_CODE::OK;
}
NimTetrisAutosaver::ERR_CODE NimTetrisAutosaver::save(NimTetrisAutosaveds& autosave, std::string filename) {
	size_t filesize = (2 + autosave.custumPlayers.size()) * sizeof(NimTetrisPlayerInfo) + 2 * sizeof(int);
	void* pdata = malloc(filesize);
	if (!pdata) return NimTetrisAutosaver::ERR_CODE::OUT_OF_MEMORY;

	size_t addr = (size_t)pdata;
	*((NimTetrisPlayerInfo*)addr) = autosave.lastPlayer1Info, addr += sizeof(NimTetrisPlayerInfo);
	*((NimTetrisPlayerInfo*)addr) = autosave.lastPlayer2Info, addr += sizeof(NimTetrisPlayerInfo);
	*((int*)addr) = autosave.nextCustumPlayerID, addr += sizeof(int);
	*((int*)addr) = (int)autosave.custumPlayers.size(), addr += sizeof(int);

	for (auto it = autosave.custumPlayers.begin(); it != autosave.custumPlayers.end(); it++) {
		*((NimTetrisPlayerInfo*)addr) = *it, addr += sizeof(NimTetrisPlayerInfo);
	}

	FILE* file = fopen(filename.c_str(), "wb");
	if (!file) {
		free(pdata);
		return NimTetrisAutosaver::ERR_CODE::FILE_NOT_EXIST;
	}

	size_t wtsize = fwrite(pdata, 1, filesize, file);
	free(pdata);
	fclose(file);
	return NimTetrisAutosaver::ERR_CODE::OK;
}