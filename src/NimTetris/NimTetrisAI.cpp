#include "NimTetrisAI.hpp"
#include "Blocks.hpp"
#include "Randomizer.hpp"
#include "BlockCompressor.hpp"
#include "BoardCompressor.hpp"
#include "NimTetrisAIConfig.hpp"
#include "ConnectedComponentFinder.hpp"
using namespace std;
vector<BlockCompressed10x10> NimTetrisAI::allAllowedPlays;

vector<BlockCompressed10x10> NimTetrisAI::getShuffledAllAllowedPlays() {
	vector<BlockCompressed10x10> plays = allAllowedPlays;
	shuffle(plays.begin(), plays.end(), Randomizer().algorithm);
	return plays;
}
void NimTetrisAI::initialize() {
	OptimizedInformationSet::initialize();

	allAllowedPlays.clear();
	allAllowedPlays.reserve(1800);
	for (int blockNo = 0; blockNo < N_OF_TETROMINOFIXED; blockNo++) {
		const TetrominoFixedInfo& blockInfo = TetrominoFixedInfo::get(blockNo);
		int ymax = 10 - blockInfo.height;
		int xmax = 10 - blockInfo.width;
		TetrominoFixedID idFixed = blockInfo.idFixed;
		for (int y = 0; y <= ymax; y++) {
			for (int x = 0; x <= xmax; x++) {
				Tetromino10x10 block(idFixed, x, y);
				allAllowedPlays.push_back(BlockCompressor().compressAndMemorize(block));
			}
		}
	}
}

void NimTetrisAI::reset() {
	boardCompressed = BoardCompressed10x10();
	allowedPlays = getShuffledAllAllowedPlays();

	components = ConnectedComponentFinder(boardCompressed).getComponentsOver4();
	components.setAllowedPlaysToComponents(allowedPlays);
}
void NimTetrisAI::reset(const Board10x10& board) {
	boardCompressed = BoardCompressor().compress(board);

	vector<BlockCompressed10x10> allAllowedPlaysInGame = getShuffledAllAllowedPlays();
	allowedPlays.clear();
	allowedPlays.reserve(allAllowedPlaysInGame.size());
	for (unsigned int i = 0; i < allAllowedPlaysInGame.size(); i++) {
		BlockCompressed10x10 block = allAllowedPlaysInGame[i];
		if (boardCompressed.putable(block)) allowedPlays.push_back(block);
	}
	components = ConnectedComponentFinder(boardCompressed).getComponentsOver4();
	components.setAllowedPlaysToComponents(allowedPlays);
}
void NimTetrisAI::reset(const BoardCompressed10x10& _boardCompressed) {
	boardCompressed = _boardCompressed;

	vector<BlockCompressed10x10> allAllowedPlaysInGame = getShuffledAllAllowedPlays();
	allowedPlays.clear();
	allowedPlays.reserve(allAllowedPlaysInGame.size());
	for (unsigned int i = 0; i < allAllowedPlaysInGame.size(); i++) {
		BlockCompressed10x10 block = allAllowedPlaysInGame[i];
		if (boardCompressed.putable(block)) allowedPlays.push_back(block);
	}
	components = ConnectedComponentFinder(boardCompressed).getComponentsOver4();
	components.setAllowedPlaysToComponents(allowedPlays);
}

pair<BlockCompressed10x10, bool> NimTetrisAI::findSafePlay(CCWithAnalysis* component, CCWithAnalysis* component_op, OptimizedInformationSet set_others) {
	const vector<pair<BlockCompressed10x10, OptimizedInformationSet>>& plays = component->getAnalysedPlays();
	const vector<pair<BlockCompressed10x10, OptimizedInformationSet>>& plays_op = component_op->getAnalysedPlays();

	unsigned int i_min = (2 < plays.size()) ? (unsigned int)plays.size() - 2 : 0; //don't try this too much
	for (unsigned int i = (unsigned int)plays.size(); i != i_min; i--) {
		OptimizedInformationSet set_others_ = set_others * plays[i - 1].second;
		bool isSafe = true;
		for (unsigned int j = 0; j < plays_op.size(); j++) {
			if (!(set_others * plays_op[j].second).isWin()) {
				isSafe = false;
				break;
			}
		}
		if(isSafe) return make_pair(plays[i - 1].first, true);
	}
	return make_pair(BlockCompressed10x10(), false);
}
pair<BlockCompressed10x10, bool> NimTetrisAI::findWinningPlay(CCWithAnalysis* component, OptimizedInformationSet set_others) {
	const vector<pair<BlockCompressed10x10, OptimizedInformationSet>>& plays = component->getAnalysedPlays();
	for (unsigned int i = 0; i < plays.size(); i++) {
		if (!(set_others * plays[i].second).isWin()) return make_pair(plays[i].first, true);
	}
	return make_pair(BlockCompressed10x10(), false);
}

vector<OptimizedInformationSet> NimTetrisAI::getSetsOthersMultiplied() {
	vector<OptimizedInformationSet> setsAt(components.size());
	for (unsigned int i = 0; i != components.size(); i++) setsAt[i] = components[i]->getInformationSet();
	int i0, i1;
	for (i0 = 0; i0 != setsAt.size() && setsAt[i0] == OptimizedInformationSet::emptySet(); i0++);
	for (i1 = i0; i1 != setsAt.size() && setsAt[i1] == OptimizedInformationSet::emptySetSet(); i1++);

	OptimizedInformationSet setSmallMultiplied, setSmallMultiplied_e1;
	if ((i1 - i0) % 2) setSmallMultiplied = OptimizedInformationSet::emptySetSet(), setSmallMultiplied_e1 = OptimizedInformationSet::emptySet();
	else setSmallMultiplied = OptimizedInformationSet::emptySet(), setSmallMultiplied_e1 = OptimizedInformationSet::emptySetSet();

	vector<OptimizedInformationSet> setsOthersMultiplied(components.size());
	if (i1 == setsAt.size()) {
		for (unsigned int i = 0; i != i0; i++) setsOthersMultiplied[i] = setSmallMultiplied;
		for (unsigned int i = i0; i != i1; i++) setsOthersMultiplied[i] = setSmallMultiplied_e1;
		return setsOthersMultiplied;
	}

	OptimizedInformationSet setFrontMultiplied = OptimizedInformationSet::emptySet();
	vector<OptimizedInformationSet> setsFrontMultiplied(setsAt.size(), OptimizedInformationSet::emptySet());
	for (unsigned int i = i1; i != setsAt.size(); i++) {
		setsFrontMultiplied[i] = setFrontMultiplied;
		setFrontMultiplied = setFrontMultiplied * setsAt[i];
	}

	OptimizedInformationSet setBackMultiplied = OptimizedInformationSet::emptySet();
	vector<OptimizedInformationSet> setsBackMultiplied(setsAt.size(), OptimizedInformationSet::emptySet());
	for (unsigned int i = (unsigned int)setsAt.size() - 1; i != i1; i--) {
		setsBackMultiplied[i] = setBackMultiplied;
		setBackMultiplied = setBackMultiplied * setsAt[i];
	}
	setsBackMultiplied[i1] = setBackMultiplied;

	for (unsigned int i = 0; i != i0; i++) setsOthersMultiplied[i] = setSmallMultiplied * setFrontMultiplied;
	for (unsigned int i = i0; i != i1; i++) setsOthersMultiplied[i] = setSmallMultiplied_e1 * setFrontMultiplied;
	for (unsigned int i = i1; i != setsAt.size(); i++) setsOthersMultiplied[i] = setSmallMultiplied * setsFrontMultiplied[i] * setsBackMultiplied[i];
	return setsOthersMultiplied;
}
OptimizedInformationSet NimTetrisAI::getSetOthersMultiplied(unsigned int i_except) {
	OptimizedInformationSet setOthersMultiplied = OptimizedInformationSet::emptySet();
	for (unsigned int i = 0; i < components.size(); i++) {
		if (i != i_except) setOthersMultiplied = setOthersMultiplied * components[i]->getInformationSet();
	}
	return setOthersMultiplied;
}
OptimizedInformationSet NimTetrisAI::getSetOthersMultiplied(unsigned int i_except1, unsigned int i_except2) {
	OptimizedInformationSet setOthersMultiplied = OptimizedInformationSet::emptySet();
	for (unsigned int i = 0; i < components.size(); i++) {
		if (i != i_except1 && i != i_except2) setOthersMultiplied = setOthersMultiplied * components[i]->getInformationSet();
	}
	return setOthersMultiplied;
}

int NimTetrisAI::tryAnalyzeComponents() {
	int failcount = 0;
	for (unsigned int i = 0; i < components.size(); i++) {
		CCWithAnalysis* component = components[i];
		if (component->isUnanalysed()) {
			if (!config.analyzable(component)) return 3;
			component->tryAnalyse(config);
		}
		if (!component->isAnalysed()) {
			failcount++;
			if (failcount == 3) return 3;
		}
	}
	return failcount;
}
BlockCompressed10x10 NimTetrisAI::findArbitraryPlay() {
	return allowedPlays[Randomizer().getNumUnder((int)allowedPlays.size())];
}
BlockCompressed10x10 NimTetrisAI::findMostDifficultPlay() {
	return components[0]->getMostComplexPlay();
}
pair<BlockCompressed10x10, NimTetrisAI::GameState> NimTetrisAI::findBestPlay_uncertain() {
	if (config.isAvoidLosingPlay()) return make_pair(findMostDifficultPlay(), GameState::Uncertain);
	else return make_pair(findArbitraryPlay(), GameState::Uncertain);
}
pair<BlockCompressed10x10, NimTetrisAI::GameState> NimTetrisAI::findBestPlay_losing() {
	if (config.isDelayLosing()) return make_pair(findMostDifficultPlay(), GameState::Losing);
	else return make_pair(findArbitraryPlay(), GameState::Losing);
}
pair<BlockCompressed10x10, NimTetrisAI::GameState> NimTetrisAI::findBestPlay_failcount0() {
	if (!config.analyzable(components)) return findBestPlay_uncertain();

	vector<OptimizedInformationSet> setsOthersMultiplied = getSetsOthersMultiplied();
	OptimizedInformationSet infoSetCheckedBefore;
	for (int i = components.size() - 1; i >= 0; i--) {
		if (components[i]->getInformationSet() == infoSetCheckedBefore) continue;

		pair<BlockCompressed10x10, bool> playWinning = findWinningPlay(components[i], setsOthersMultiplied[i]);
		if (playWinning.second) return make_pair(playWinning.first, GameState::Winning);
		infoSetCheckedBefore = components[i]->getInformationSet();
	}
	return findBestPlay_losing();
}
pair<BlockCompressed10x10, NimTetrisAI::GameState> NimTetrisAI::findBestPlay_failcount1() {
	CCWithAnalysis* componentIncomplete = components[0];
	if (componentIncomplete->getInformationSet().isEmpty()) return make_pair(findArbitraryPlay(), GameState::Uncertain);
	if (!config.analyzable_except1(components)) return findBestPlay_uncertain();

	pair<BlockCompressed10x10, bool> playWinning = findWinningPlay(componentIncomplete, getSetOthersMultiplied(0));
	if (playWinning.second) return make_pair(playWinning.first, GameState::Winning);

	if (config.isAvoidLosingPlay()) {
		if (Randomizer().getBool()) return make_pair(componentIncomplete->getUnanalyzableAllowedPlay(), GameState::Uncertain);
		OptimizedInformationSet infoSetCheckedBefore;
		for (unsigned int i = 1; i < components.size(); i++) {
			if (components[i]->getInformationSet() == infoSetCheckedBefore) continue;

			pair<BlockCompressed10x10, bool> playSafe = findSafePlay(components[i], componentIncomplete, getSetOthersMultiplied(0, i));
			if (playSafe.second) return make_pair(playSafe.first, GameState::Uncertain);
			infoSetCheckedBefore = components[i]->getInformationSet();
		}
		return make_pair(componentIncomplete->getUnanalyzableAllowedPlay(), GameState::Uncertain);
	}
	else return findBestPlay_uncertain();
}
pair<BlockCompressed10x10, NimTetrisAI::GameState> NimTetrisAI::findBestPlay_failcount2() {
	if (config.isAvoidLosingPlay()) {
		int i_chosen = Randomizer().getNumUnder(components.size());
		if (i_chosen < 2) return make_pair(components[i_chosen]->getUnanalyzableAllowedPlay(), GameState::Uncertain);
		else return make_pair(components[i_chosen]->getArbitraryAllowedPlay(), GameState::Uncertain);
	}
	else return make_pair(findArbitraryPlay(), GameState::Uncertain);
}
pair<BlockCompressed10x10, NimTetrisAI::GameState> NimTetrisAI::findBestPlay() {
	int failcount = tryAnalyzeComponents();
	components.sortByStateOfAnalysis();
	switch (failcount) {
	case 0:
		return findBestPlay_failcount0();
	case 1:
		return findBestPlay_failcount1();
	case 2:
		return findBestPlay_failcount2();
	}
	return make_pair(findArbitraryPlay(), GameState::Uncertain);
}
std::pair<BlockCompressed10x10, NimTetrisAI::GameState> NimTetrisAI::testWith(int board[10][10]) {
	Board10x10 board_new;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			board_new.at[i][j] = (board[i][j]) ? PlaceState::EMPTY_MARKED : PlaceState::EMPTY;
		}
	}
	reset(board_new);
	return findBestPlay();
}

void NimTetrisAI::applyPlay(BlockCompressed10x10 play) {
	allowedPlays.clear();
	for (unsigned int i = 0; i < components.size(); i++) {
		if (components[i]->board.putable(play)) {
			components.replace(i, CCsWithAnalysis::fromSplit(components[i], play));
		}
	}
	for (unsigned int i = 0; i < components.size(); i++) {
		const vector<BlockCompressed10x10>& allowedPlaysComponent = components[i]->getAllowedPlays();
		allowedPlays.insert(allowedPlays.end(), allowedPlaysComponent.begin(), allowedPlaysComponent.end());
	}
}
void NimTetrisAI::applyAIPlay() {
	pair<BlockCompressed10x10, NimTetrisAI::GameState> bestplay = findBestPlay();
	lastAIPlay = BlockCompressor().decompressFromMemory(bestplay.first);
	lastAIPlayed = true;
	lastAIGameState = bestplay.second;
	applyPlay(bestplay.first);
}
void NimTetrisAI::applyOpponentPlay(Tetromino10x10 play) {
	applyPlay(BlockCompressor().compress(play));
	lastAIPlayed = false;
}