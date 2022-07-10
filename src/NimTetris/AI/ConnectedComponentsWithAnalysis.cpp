#include "ConnectedComponentsWithAnalysis.hpp"
#include "ConnectedComponentFinder.hpp"
#include "NimTetrisAIConfig.hpp"
#include <algorithm>
using namespace std;
CCsWithAnalysis CCsWithAnalysis::fromSplit(const CCWithAnalysis* component, BlockCompressed10x10 play) {
	BoardCompressed10x10 board_n = component->board;
	board_n.put(play);
	CCsWithAnalysis ret = CCsWithAnalysis(ConnectedComponentFinder(board_n).getComponentsOver4());
	ret.setAllowedPlaysToComponents(component->getAllowedPlays());
	return ret;
}

void CCsWithAnalysis::sortByStateOfAnalysis() {
	sort(components.begin(), components.end(), CCWithAnalysis::sorter);
}
void CCsWithAnalysis::setAllowedPlaysToComponents(const std::vector<BlockCompressed10x10>& allowedPlays) {
	vector<vector<BlockCompressed10x10>> temp;
	temp.resize(components.size());
	for (unsigned int i = 0; i < allowedPlays.size(); i++) {
		BlockCompressed10x10 block = allowedPlays[i];
		for (unsigned int j = 0; j < components.size(); j++) {
			if (components[j]->isPutable(block)) {
				temp[j].push_back(block);
				break;
			}
		}
	}
	for (unsigned int j = 0; j < components.size(); j++) components[j]->setAllowedPlays(std::move(temp[j]));
}

OptimizedInformationSet CCsWithAnalysis::findInformationSet() {
	OptimizedInformationSet infoSet = OptimizedInformationSet::emptySet();
	for (unsigned int j = 0; j < components.size(); j++) {
		CCWithAnalysis* pComponent = components[j];
		infoSet = infoSet * pComponent->findInformationSet();
	}
	return infoSet;
}
std::pair<OptimizedInformationSet, bool> CCsWithAnalysis::tryFindInformationSet(const NimTetrisAIConfig& config) {
	if (!config.analyzable_asSubset(*this)) return make_pair(OptimizedInformationSet::emptySet(), false);
	return make_pair(findInformationSet(), true);
}