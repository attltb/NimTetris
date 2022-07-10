#ifndef _ConnectedComponentHeader_
#define _ConnectedComponentHeader_
#include "BoardCompressed10x10.hpp"
#include "BlockCompressed10x10.hpp"
#include "OptimizedInformationSet.hpp"
#include <vector>
class NimTetrisAIConfig;
class ConnectedComponent {
public:
	BoardCompressed10x10 board;
	unsigned int size;

public:
	ConnectedComponent(unsigned int _size) : size(_size), board(1) {}
	ConnectedComponent() : size(0), board(1) {}
};

class CCWithAnalysis : public ConnectedComponent {
public:
	enum class StateOfAnalysis { Unanalysed, Analysed_Partially, Analysed };

private:
	class Analysis {
	public:
		BlockCompressed10x10 unanalyzableAllowedPlay;
		std::vector<BlockCompressed10x10> allowedPlays;

	public:
		StateOfAnalysis state;
		OptimizedInformationSet infoSet;
		std::vector<std::pair<BlockCompressed10x10, OptimizedInformationSet>> analysedPlays;

	public:
		Analysis() : state(StateOfAnalysis::Unanalysed) {}
	};

private:
	Analysis analysis;

public:
	static bool sorter(const CCWithAnalysis* l, const CCWithAnalysis* r) {
		if (l->analysis.state != r->analysis.state) return l->analysis.state < r->analysis.state;
		if (l->analysis.state == StateOfAnalysis::Unanalysed) return false;
		return l->getInformationSet().isLessComplex(r->getInformationSet());
	}

public:
	void setAllowedPlays(std::vector<BlockCompressed10x10>&& allowedPlays) {
		analysis.allowedPlays = allowedPlays;
	}

public:
	bool isUnanalysed() const {
		return analysis.state == StateOfAnalysis::Unanalysed;
	}
	bool isAnalysed() const {
		return analysis.state == StateOfAnalysis::Analysed;
	}
	bool isPartiallyAnalysed() const {
		return analysis.state == StateOfAnalysis::Analysed_Partially;
	}
	bool isPutable(BlockCompressed10x10 blockCompressed) const {
		return board.putable(blockCompressed);
	}

public:
	StateOfAnalysis getStateOfAnalysis() const {
		return analysis.state;
	}
	BlockCompressed10x10 getUnanalyzableAllowedPlay() const {
		return analysis.unanalyzableAllowedPlay;
	}
	BlockCompressed10x10 getArbitraryAllowedPlay() const;
	BlockCompressed10x10 getMostComplexPlay() const;
	const std::vector<BlockCompressed10x10>& getAllowedPlays() const {
		return analysis.allowedPlays;
	}
	const std::vector<std::pair<BlockCompressed10x10, OptimizedInformationSet>>& getAnalysedPlays() const {
		return analysis.analysedPlays;
	}
	OptimizedInformationSet getInformationSet() const {
		return analysis.infoSet;
	}

private:
	void notifyAnAnalyzedPlay(BlockCompressed10x10 play, OptimizedInformationSet subInfoSet) {
		analysis.analysedPlays.push_back(std::make_pair(play, subInfoSet));
	}
	void notifyUnanalyzablePlay(BlockCompressed10x10 play) {
		analysis.unanalyzableAllowedPlay = play;
	}

public:
	OptimizedInformationSet findInformationSet() const;
	StateOfAnalysis finishAnalysis(OptimizedInformationSet infoSet, StateOfAnalysis state);
	StateOfAnalysis tryAnalyse(const NimTetrisAIConfig& config);

public:
	CCWithAnalysis(int size) : ConnectedComponent(size) {}
	CCWithAnalysis() : ConnectedComponent() {}
};
#endif