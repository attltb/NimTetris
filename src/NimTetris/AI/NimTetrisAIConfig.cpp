#include "NimTetrisAIConfig.hpp"
bool NimTetrisAIConfig::avoidLosingPlays[11] = { false, false, false, false, false, true, true, true, true, true, true };
bool NimTetrisAIConfig::delayLosings[11] = { false, false, false, false, false, false, false, false, true, true, true };
int NimTetrisAIConfig::analyzableComplexitys[11] = { 0, 8, 11, 22, 42, 65, 125, 210, 480, 1200, 2400 };
int NimTetrisAIConfig::partiallyAnalyzableComplexity_v1s[11] = { 0, 7, 9, 15, 28, 42, 90, 130, 300, 800, 1600 };
int NimTetrisAIConfig::analyzableComponentComplexitys[11] = { 0, 20, 24, 48, 92, 170, 350, 700, 1500, 4000, 8000 };
int NimTetrisAIConfig::analyzableComponentSubsetComplexitys[11] = { 0, 2, 3, 5, 9, 15, 28, 42, 90, 220, 400 };

double NimTetrisAIConfig::getComplexity(CCWithAnalysis* component) {
	int size = component->size;
	int depth = size / 4;
	double margin = size % 4;
	if (depth == 0) return 0;
	return (double)((__int64)1 << ((depth - 1) * 2)) * ((4.0 + margin) / 4.0);
}
double NimTetrisAIConfig::getSetComplexity(CCsWithAnalysis& components) {
	int depthTotal = 0;
	for (unsigned int i = 0; i < components.size(); i++) {
		CCWithAnalysis* component = components[i];
		OptimizedInformationSet infoSet = component->getInformationSet();
		int depth = (infoSet.isValid()) ? infoSet.depth() : (component->size / 4);
		if (depth > 1) depthTotal += depth;
	}
	if (depthTotal == 0) return 0;
	return (double)((__int64)1 << depthTotal) / 20.0;
}
double NimTetrisAIConfig::getComplexity(CCsWithAnalysis& components) {
	double groupComplexity_total = 0.0;
	for (unsigned int i = 0; i < components.size(); i++) {
		groupComplexity_total += getComplexity(components[i]);
	}
	return groupComplexity_total + getSetComplexity(components);
}
double NimTetrisAIConfig::getComplexity_except1(CCsWithAnalysis& components) {
	double groupComplexity_total = 0;
	for (unsigned int i = 1; i < components.size(); i++) {
		groupComplexity_total += getComplexity(components[i]);
	}
	return groupComplexity_total + getSetComplexity(components);
}

bool NimTetrisAIConfig::isAvoidLosingPlay() const {
	return avoidLosingPlays[aiLevel];
}
bool NimTetrisAIConfig::isDelayLosing() const {
	return delayLosings[aiLevel];
}
bool NimTetrisAIConfig::analyzable(CCWithAnalysis* component) const {
	return getComplexity(component) <= analyzableComponentComplexitys[aiLevel];
}
bool NimTetrisAIConfig::analyzable(CCsWithAnalysis& components) const {
	return getComplexity(components) <= analyzableComplexitys[aiLevel];
}
bool NimTetrisAIConfig::analyzable_except1(CCsWithAnalysis& components) const {
	return getComplexity_except1(components) <= partiallyAnalyzableComplexity_v1s[aiLevel];
}
bool NimTetrisAIConfig::analyzable_asSubset(CCsWithAnalysis& components) const {
	return getComplexity(components) <= analyzableComponentSubsetComplexitys[aiLevel];
}