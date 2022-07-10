#ifndef _NimTetrisAutosavedsHeader_
#define _NimTetrisAutosavedsHeader_
#include <stdlib.h>
#include <vector>
#include <map>
#include "NimTetrisPlayerInfo.hpp"
class NimTetrisAutosaveds {
public:
	static std::vector<NimTetrisPlayerInfo> standardPlayers;

public:
	NimTetrisPlayerInfo lastPlayer1Info;
	NimTetrisPlayerInfo lastPlayer2Info;
	int nextCustumPlayerID;
	std::vector<NimTetrisPlayerInfo> custumPlayers;

public:
	static void initialize() {
		standardPlayers.push_back(NimTetrisPlayerInfo(NimTetrisPlayerInfo::CONTROL::USER));
		standardPlayers.push_back(NimTetrisPlayerInfo(NimTetrisPlayerInfo::CONTROL::AI0));
		standardPlayers.push_back(NimTetrisPlayerInfo(NimTetrisPlayerInfo::CONTROL::AI1));
		standardPlayers.push_back(NimTetrisPlayerInfo(NimTetrisPlayerInfo::CONTROL::AI2));
		standardPlayers.push_back(NimTetrisPlayerInfo(NimTetrisPlayerInfo::CONTROL::AI3));
		standardPlayers.push_back(NimTetrisPlayerInfo(NimTetrisPlayerInfo::CONTROL::AI4));
		standardPlayers.push_back(NimTetrisPlayerInfo(NimTetrisPlayerInfo::CONTROL::AI5));
		standardPlayers.push_back(NimTetrisPlayerInfo(NimTetrisPlayerInfo::CONTROL::AI6));
		standardPlayers.push_back(NimTetrisPlayerInfo(NimTetrisPlayerInfo::CONTROL::AI7));
		standardPlayers.push_back(NimTetrisPlayerInfo(NimTetrisPlayerInfo::CONTROL::AI8));
		standardPlayers.push_back(NimTetrisPlayerInfo(NimTetrisPlayerInfo::CONTROL::AI9));
		standardPlayers.push_back(NimTetrisPlayerInfo(NimTetrisPlayerInfo::CONTROL::AI10));
	}

public:
	int findStandardPlayerPos(NimTetrisPlayerInfo::CONTROL control) {
		return int(control);
	}
	size_t findCustumPlayerPos(int id) {
		for (unsigned int i = 0; i < custumPlayers.size(); i++) {
			if (custumPlayers[i].custumPlayerID == id) return i;
		}
		return -1;
	}

public:
	void addCustumPlayer(const NimTetrisPlayerInfo& newCustumPlayerInfo) {
		custumPlayers.push_back(NimTetrisPlayerInfo(nextCustumPlayerID, newCustumPlayerInfo.control, newCustumPlayerInfo.name));
		nextCustumPlayerID++;
	}
	void addCustumPlayer(NimTetrisPlayerInfo::CONTROL control, const char* name) {
		custumPlayers.push_back(NimTetrisPlayerInfo(nextCustumPlayerID, control, name));
		nextCustumPlayerID++;
	}
	void removeCustumPlayerAt(size_t pos) {
		custumPlayers.erase(custumPlayers.begin() + pos);
	}

public:
	NimTetrisAutosaveds() : nextCustumPlayerID(1), lastPlayer1Info(NimTetrisPlayerInfo::CONTROL::USER), lastPlayer2Info(NimTetrisPlayerInfo::CONTROL::AI10) {};
};
#endif