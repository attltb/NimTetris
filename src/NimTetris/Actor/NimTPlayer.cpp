#include "NimTPlayer.hpp"
#include "NimTPlayer_AI.hpp"
#include "NimTPlayer_User.hpp"
NimTPlayer* NimTPlayer::create(NimTetrisPlayerInfo& playerInfo, ThreadManager& threadManager) {
	if (playerInfo.control == NimTetrisPlayerInfo::CONTROL::USER) return new NimTPlayer_User(playerInfo);
	return new NimTPlayer_AI(playerInfo, threadManager);
}