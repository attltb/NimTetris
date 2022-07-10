#include "ConnectedComponent.hpp"
#include "ConnectedComponentFinder.hpp"
#include "ConnectedComponentsWithAnalysis.hpp"
#include "NimTetrisAIConfig.hpp"
#include "Randomizer.hpp"
#include <algorithm>
using namespace std;
BlockCompressed10x10 CCWithAnalysis::getArbitraryAllowedPlay() const {
	return analysis.allowedPlays[Randomizer().getNumUnder((int)analysis.allowedPlays.size())];
}
BlockCompressed10x10 CCWithAnalysis::getMostComplexPlay() const {
	if (isPartiallyAnalysed()) return getUnanalyzableAllowedPlay();
	else return analysis.analysedPlays[analysis.analysedPlays.size() - 1].first;
}

OptimizedInformationSet CCWithAnalysis::findInformationSet() const {
	if (size < 8) return OptimizedInformationSet::emptySetSet();

	const vector<BlockCompressed10x10>& allPossiblePlays = getAllowedPlays();
	int i_max = (int)allPossiblePlays.size();
	if (size < 12) {
		if (CCsWithAnalysis::fromSplit(this, allPossiblePlays[0]).empty()) {
			for (int i = 1; i < i_max; i++) {
				if (!CCsWithAnalysis::fromSplit(this, allPossiblePlays[i]).empty()) return OptimizedInformationSet::depth2FullSet();
			}
			return OptimizedInformationSet::emptySetSet();
		}
		else {
			for (int i = 1; i < i_max; i++) {
				if (CCsWithAnalysis::fromSplit(this, allPossiblePlays[i]).empty()) return OptimizedInformationSet::depth2FullSet();
			}
			return OptimizedInformationSet::emptySet();
		}
	}

	set<OptimizedInformationSet> elements;
	if (size < 16) {
		for (int i = 0; i < i_max; i++) {
			CCsWithAnalysis components = CCsWithAnalysis::fromSplit(this, allPossiblePlays[i]);
			if (elements.insert(components.findInformationSet()).second) {
				if (elements.size() == 3) return OptimizedInformationSet::depth3FullSet();
			}
		}
	}
	else {
		for (int i = 0; i < i_max; i++) {
			CCsWithAnalysis components = CCsWithAnalysis::fromSplit(this, allPossiblePlays[i]);
			elements.insert(components.findInformationSet());
		}
	}
	return OptimizedInformationSet(elements);
}
CCWithAnalysis::StateOfAnalysis CCWithAnalysis::finishAnalysis(OptimizedInformationSet infoSet, StateOfAnalysis state) {
	analysis.infoSet = infoSet;
	analysis.state = state;
	sort(analysis.analysedPlays.begin(), analysis.analysedPlays.end(),
		[](pair<BlockCompressed10x10, OptimizedInformationSet> l, pair<BlockCompressed10x10, OptimizedInformationSet> r) {
			return l.second.isLessComplex(r.second);
		});
	return state;
}
CCWithAnalysis::StateOfAnalysis CCWithAnalysis::tryAnalyse(const NimTetrisAIConfig& config) {
	if (size < 8) {
		notifyAnAnalyzedPlay(getArbitraryAllowedPlay(), OptimizedInformationSet::emptySet());
		return finishAnalysis(OptimizedInformationSet::emptySetSet(), StateOfAnalysis::Analysed);
	}

	StateOfAnalysis res_state = StateOfAnalysis::Analysed;
	const vector<BlockCompressed10x10>& allPossiblePlays = getAllowedPlays();
	int i_max = (int)allPossiblePlays.size();
	set<OptimizedInformationSet> elements;
	unsigned int rd = Randomizer().getNumUnder(i_max);

	for (int i = 0; i < i_max; i++) {
		BlockCompressed10x10 play = allPossiblePlays[(i + rd) % i_max];
		CCsWithAnalysis components = CCsWithAnalysis::fromSplit(this, play);
		pair<OptimizedInformationSet, bool> res = components.tryFindInformationSet(config);
		if (!res.second) {
			notifyUnanalyzablePlay(play);
			res_state = StateOfAnalysis::Analysed_Partially;
			continue;
		}
		if (elements.insert(res.first).second) {
			notifyAnAnalyzedPlay(play, res.first);
			if (size < 12 && elements.size() == 2) return finishAnalysis(OptimizedInformationSet::depth2FullSet(), res_state);
			if (size < 16 && elements.size() == 3) return finishAnalysis(OptimizedInformationSet::depth3FullSet(), res_state);
		}
	}
	return finishAnalysis(OptimizedInformationSet(elements), res_state);
}