#ifndef _NimTetrisAIConfigHeader_
#define _NimTetrisAIConfigHeader_
#include "ConnectedComponent.hpp"
#include "ConnectedComponentsWithAnalysis.hpp"
class NimTetrisAIConfig {
private:
	static bool avoidLosingPlays[11]; //if AI can't find winning move, it tries to avoid losing moves.
	static bool delayLosings[11]; //if there are no winning move, it tried to do most complex play for the opponent;
	static int analyzableComplexitys[11];
	static int partiallyAnalyzableComplexity_v1s[11];
	static int partiallyAnalyzableComplexity_v2s[11];
	static int analyzableComponentComplexitys[11];
	static int analyzableComponentSubsetComplexitys[11];

public:
	int aiLevel;

private:
	static double getComplexity(CCsWithAnalysis& components);
	static double getSetComplexity(CCsWithAnalysis& components);
	static double getComplexity_except1(CCsWithAnalysis& components);
	static double getComplexity(CCWithAnalysis* component);

public:
	bool isAvoidLosingPlay() const;
	bool isDelayLosing() const;
	bool analyzable(CCWithAnalysis* component) const;
	bool analyzable(CCsWithAnalysis& components) const;
	bool analyzable_except1(CCsWithAnalysis& components) const;
	bool analyzable_asSubset(CCsWithAnalysis& components) const;

public:
	NimTetrisAIConfig(int _aiLevel) : aiLevel(_aiLevel) {};
};
#endif