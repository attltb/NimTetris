#include "OptimizedInformationSet.hpp"
std::map<std::set<OptimizedInformationSet>, OptimizedInformationSet> OptimizedInformationSet::pool;
OptimizedInformationSet OptimizedInformationSet::setEmpty;
OptimizedInformationSet OptimizedInformationSet::setSetEmpty;
OptimizedInformationSet OptimizedInformationSet::setFullDepth2;
OptimizedInformationSet OptimizedInformationSet::setFullDepth3;