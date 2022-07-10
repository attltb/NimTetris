#ifndef _OptimizedInformationSetHeader_
#define _OptimizedInformationSetHeader_
#include <map>
#include <set>
#include <string>
class OptimizedInformationSet {
	class More_Complex {
	public:
		bool operator() (OptimizedInformationSet l, OptimizedInformationSet r) const {
			if (l == r) return false;

			int depth_l = l.depth();
			int depth_r = r.depth();
			if (depth_l < depth_r) return false;
			if (depth_l > depth_r) return true;
			if (!depth_l) return false;

			auto it1 = l.shared->elementsOrderdByComplexity.begin();
			auto it2 = r.shared->elementsOrderdByComplexity.begin();
			for (;; it1++, it2++) {
				if (it1 == l.shared->elementsOrderdByComplexity.end()) return false;
				if (it2 == r.shared->elementsOrderdByComplexity.end()) return true;
				if ((*it1) != (*it2)) return (*this)((*it1), (*it2));
			}
			return false;
		}
	};
	class Info {
	public:
		int depth;
		int win;
		int win_r;
		Info* factor0;
		std::set<OptimizedInformationSet> elements;
		std::set<OptimizedInformationSet, More_Complex> elementsOrderdByComplexity;
		std::map<OptimizedInformationSet, OptimizedInformationSet> poolProduct;

	public:
		Info(const std::set<OptimizedInformationSet>& _elements) : elements(_elements), win(0), win_r(0), factor0(nullptr) {
			for (auto it = elements.begin(); it != elements.end(); it++) {
				elementsOrderdByComplexity.insert(*it);
			}
			depth = (elements.empty()) ? 0 : elementsOrderdByComplexity.begin()->depth() + 1;
		}
		Info(const std::set<OptimizedInformationSet>& _elements, OptimizedInformationSet _factor0) : elements(_elements), win(0), win_r(0), factor0(_factor0.shared) {
			for (auto it = elements.begin(); it != elements.end(); it++) {
				elementsOrderdByComplexity.insert(*it);
			}
			depth = (elements.empty()) ? 0 : elementsOrderdByComplexity.begin()->depth() + 1;
		}
	};

private:
	static std::map<std::set<OptimizedInformationSet>, OptimizedInformationSet> pool;
	static OptimizedInformationSet setEmpty; //0
	static OptimizedInformationSet setSetEmpty; //{0}
	static OptimizedInformationSet setFullDepth2; //{{0}, 0}
	static OptimizedInformationSet setFullDepth3; //{{{0}, 0}, {0}, 0}

public:
	static void initialize() {
		std::set<OptimizedInformationSet> elements_empty = {};
		setEmpty = OptimizedInformationSet(elements_empty);
		setEmpty.shared->win = 1;
		setEmpty.shared->win_r = -1;
		pool[elements_empty] = setEmpty;

		std::set<OptimizedInformationSet> elements_full_depth_1 = { setEmpty };
		setSetEmpty = OptimizedInformationSet(elements_full_depth_1, setEmpty);
		setSetEmpty.shared->win = -1;
		setSetEmpty.shared->win_r = 1;
		pool[elements_full_depth_1] = setSetEmpty;

		std::set<OptimizedInformationSet> elements_empty_set_set_set = { setSetEmpty };
		pool[elements_empty_set_set_set] = setEmpty; //{{{ }}} is practically equivalent to { }

		std::set<OptimizedInformationSet> elements_full_depth_2 = { setSetEmpty, setEmpty };
		setFullDepth2 = OptimizedInformationSet(elements_full_depth_2);
		pool[elements_full_depth_2] = setFullDepth2;

		std::set<OptimizedInformationSet> elements_full_depth_3 = { setFullDepth2, setSetEmpty, setEmpty };
		setFullDepth3 = OptimizedInformationSet(elements_full_depth_3, setFullDepth2);
		pool[elements_full_depth_3] = setFullDepth3;
	}
	static OptimizedInformationSet emptySet() {
		return setEmpty;
	}
	static OptimizedInformationSet emptySetSet() {
		return setSetEmpty;
	}
	static OptimizedInformationSet depth2FullSet() {
		return setFullDepth2;
	}
	static OptimizedInformationSet depth3FullSet() {
		return setFullDepth3;
	}

private:
	Info* shared;

private:
	OptimizedInformationSet(Info* _shared) : shared(_shared) {}

public:
	OptimizedInformationSet() : shared(nullptr) {}
	OptimizedInformationSet(const OptimizedInformationSet& other) : shared(other.shared) {}
	OptimizedInformationSet(const std::set<OptimizedInformationSet>& elements) {
		OptimizedInformationSet& result = pool[elements];
		if (!result.isValid()) result = new Info(elements);
		shared = result.shared;
	}
	OptimizedInformationSet(const std::set<OptimizedInformationSet>& elements, OptimizedInformationSet factor0) {
		OptimizedInformationSet& result = pool[elements];
		if (!result.isValid()) result = new Info(elements, factor0);
		shared = result.shared;
	}

public:
	int size() const {
		return (int)shared->elements.size();
	}
	int depth() const {
		return shared->depth;
	}

public:
	bool isValid() const {
		return shared;
	}
	bool isEmpty() const {
		return shared->elements.empty();
	}
	bool isWin() const {
		int win = shared->win;
		if (!win) {
			win = -1;
			std::set<OptimizedInformationSet>& elements = shared->elements;
			for (auto it = elements.begin(); it != elements.end(); it++) {
				if (!it->isWin()) {
					win = 1;
					break;
				}
			}
			shared->win = win;
		}
		return win == 1;
	}
	bool isWinReverse() const {
		int win_r = shared->win_r;
		if (!win_r) {
			win_r = -1;
			std::set<OptimizedInformationSet>& elements = shared->elements;
			for (auto it = elements.begin(); it != elements.end(); it++) {
				if (!it->isWinReverse()) {
					win_r = 1;
					break;
				}
			}
			shared->win_r = win_r;
		}
		return win_r == 1;
	}
	bool isLessComplex(OptimizedInformationSet other) const {
		return More_Complex()(other, *this);
	}
	OptimizedInformationSet getFactor0() const {
		return shared->factor0;
	}
	OptimizedInformationSet multiplyWithEmptySetSet() const {
		std::set<OptimizedInformationSet>& elements = shared->elements;
		std::set<OptimizedInformationSet> res_elements;
		res_elements.insert(*this);
		for (auto it = elements.begin(); it != elements.end(); it++) {
			res_elements.insert(it->multiplyWithEmptySetSet());
		}
		return OptimizedInformationSet(res_elements, *this);
	}

public:
	void operator =(OptimizedInformationSet other) {
		shared = other.shared;
	}
	bool operator ==(OptimizedInformationSet other) const {
		return shared == other.shared;
	}
	bool operator !=(OptimizedInformationSet other) const {
		return shared != other.shared;
	}
	bool operator <(OptimizedInformationSet other) const {
		return shared < other.shared;
	}
	OptimizedInformationSet operator *(OptimizedInformationSet other) const {
		if(other < *this) return other * (*this);
		if (isEmpty()) return other;
		if (other.isEmpty()) return (*this);

		OptimizedInformationSet& result = shared->poolProduct[other];
		if (result.isValid()) return result;
		if (getFactor0().isValid()) {
			if (other.getFactor0().isValid()) result = getFactor0() * other.getFactor0();
			else result = (getFactor0() * other).multiplyWithEmptySetSet();
			return result;
		}
		if (other.getFactor0().isValid()) {
			result = ((*this) * other.getFactor0()).multiplyWithEmptySetSet();
			return result;
		}

		std::set<OptimizedInformationSet>& elements = shared->elements;
		std::set<OptimizedInformationSet> res_elements;
		if (*this == other) {
			for (auto it = elements.begin(); it != elements.end(); it++) {
				OptimizedInformationSet res_element = (*it) * (*this);
				res_elements.insert(res_element);
			}
		}
		else {
			std::set<OptimizedInformationSet>& other_elements = other.shared->elements;
			for (auto it = elements.begin(); it != elements.end(); it++) {
				OptimizedInformationSet res_element = (*it) * other;
				res_elements.insert(res_element);
			}
			for (auto it = other_elements.begin(); it != other_elements.end(); it++) {
				OptimizedInformationSet res_element = (*it) * (*this);
				res_elements.insert(res_element);
			}
		}
		result = OptimizedInformationSet(res_elements);
		return result;
	}

public:
	std::string print() const {
		if (isEmpty()) return "0";

		std::string str = "{";
		std::set<OptimizedInformationSet, More_Complex> elements = shared->elementsOrderdByComplexity;
		auto it = elements.begin();
		str += it->print();
		it++;
		for (; it != elements.end(); it++) str += ", " + it->print();
		return str + "}";
	}
};
#endif