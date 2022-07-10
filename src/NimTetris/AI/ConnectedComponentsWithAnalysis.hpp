#ifndef _ConnectedComponentsWithAnalysisHeader_
#define _ConnectedComponentsWithAnalysisHeader_
#include "ConnectedComponent.hpp"
#include "OptimizedInformationSet.hpp"
#include <vector>
class CCsWithAnalysis {
public:
	enum class GameState { Uncertain, Winning, Losing };

private:
	std::vector<CCWithAnalysis*> components;

public:
	CCWithAnalysis*& operator[] (unsigned int i) {
		return components[i];
	}
	CCWithAnalysis* operator[] (unsigned int i) const {
		return components[i];
	}
	void operator= (CCsWithAnalysis&& other) noexcept {
		components = std::move(other.components);
	}
	unsigned int size() {
		return (unsigned int)components.size();
	}
	bool empty() const {
		return components.empty();
	}
	void replace(unsigned int i, CCsWithAnalysis&& other) {
		delete components[i];
		if (other.empty()) components.erase(components.begin() + i);
		else {
			components[i] = other[0];
			components.insert(components.end(), other.components.begin() + 1, other.components.end());
		}
		other.components.clear();
	}

public:
	static CCsWithAnalysis fromSplit(const CCWithAnalysis* component, BlockCompressed10x10 play);

public:
	void sortByStateOfAnalysis();
	void setAllowedPlaysToComponents(const std::vector<BlockCompressed10x10>& allowedPlays);

public:
	OptimizedInformationSet findInformationSet();
	std::pair<OptimizedInformationSet, bool> tryFindInformationSet(const NimTetrisAIConfig& config);

public:
	CCsWithAnalysis() {};
	CCsWithAnalysis(CCsWithAnalysis&& other) noexcept : components(std::move(other.components)) {};
	CCsWithAnalysis(std::vector<CCWithAnalysis*>&& _components) : components(_components) {};
	~CCsWithAnalysis() {
		for (unsigned int i = 0; i < components.size(); i++) {
			delete components[i];
		}
	};
};
#endif