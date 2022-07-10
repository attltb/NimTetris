#ifndef _ConnectedComponentFinderHeader_
#define _ConnectedComponentFinderHeader_
#include "BitScanner.h"
#include "ConnectedComponent.hpp"
#include <vector>
class ConnectedComponentFinder {
	//generates groups using a CCL algorithm (BRTS) specialized for bit-compressed data 

	struct Label {
		Label* link;
		CCWithAnalysis* cc;
		unsigned int size;
		unsigned int padding;
	};
	struct Run {
		uint32_t form;
		Label* label;
	};

private:
	BoardCompressed10x10 board;
	Run runss[10][6];
	Label labels[50];
	Label* label_next;

private:
	static Label* equivLabel(Label* label) {
		if (label->link == label) return label;
		return equivLabel(label->link);
	}

private:
	void findRuns() {
		//generate runs for the last row
		Run* runs = runss[9];
		unsigned long bits = board.row(9) | (~0x000003FF);
		unsigned long bits_r = ~bits;
		for (;; runs++) {
			//find starting position
			unsigned long bit_start;
			while (!myBitScanForward32(&bit_start, bits_r)) {
				runs->form = 0;
				runs->label = nullptr;
				goto out;
			}
			unsigned long bit_start_mask = 0xFFFFFFFF << bit_start;
			bits &= bit_start_mask;

			//find ending position
			unsigned long bit_end;
			myBitScanForward32(&bit_end, bits); //never returns false (last bits are guaranteed to be 1)
			unsigned long bit_end_mask = 0xFFFFFFFF << bit_end;
			bits_r &= bit_end_mask;

			runs->form = bit_start_mask ^ bit_end_mask;
			runs->label = label_next;
			label_next->link = label_next;
			label_next->size = bit_end - bit_start, label_next++;
		}
	out:;

		//generate runs for the rest rows
		for (int i = 8; i >= 0; i--) {
			Run* runs_up = runss[i + 1];
			Run* runs = runss[i];
			unsigned long bits = board.row(i) | (~0x000003FF);
			unsigned long bits_r = ~bits;
			for (;; runs++) {
				//find starting position
				unsigned long bit_start;
				while (!_BitScanForward(&bit_start, bits_r)) {
					runs->form = 0;
					runs->label = nullptr;
					goto out2;
				}
				unsigned long bit_start_mask = 0xFFFFFFFF << bit_start;
				bits &= bit_start_mask;

				//find ending position
				unsigned long bit_end;
				_BitScanForward(&bit_end, bits); //never returns false (last bits are guaranteed to be 1)
				unsigned long bit_end_mask = 0xFFFFFFFF << bit_end;
				bits_r &= bit_end_mask;

				unsigned long form = bit_start_mask ^ bit_end_mask;
				unsigned long size = bit_end - bit_start;
				runs->form = form;
				runs->label = nullptr;
				for (; runs_up->label; runs_up++) {
					unsigned long upform = runs_up->form;
					if (!(upform & form)) {
						if (upform < form) continue;
						else {
							//this cut does not overlaps with upper cuts
							runs->label = label_next;
							label_next->link = label_next;
							label_next->size = bit_end - bit_start, label_next++;
							break;
						}
					}

					Label* label = equivLabel(runs_up->label);
					Run* runs_upnext = runs_up + 1;
					if (runs_upnext->form & form) {
						for (;;) {
							Label* label_other = equivLabel(runs_upnext->label);
							if (label != label_other) {
								if (label < label_other) label_other->link = label;
								else label->link = label_other, label = label_other;
							}
							runs_upnext++;
							if (runs_upnext->form & form) continue;
							runs_up = runs_upnext - 1;
							break;
						}
					}
					runs->label = label->link;
					runs->label->size += size;
					break;
				}
				if (!runs->label) {
					runs->label = label_next;
					label_next->link = label_next;
					label_next->size = bit_end - bit_start, label_next++;
				}
			}
		out2:;
		}
	}
	void optimizeLink() {
		for (Label* lb = labels; lb < label_next; lb++) {
			Label* lb_linked = lb->link;
			if (lb == lb_linked) continue;

			Label* lb_linked_linked = lb_linked->link;
			lb->link = lb_linked_linked;
			lb_linked_linked->size += lb->size;
		}
	}

public:
	ConnectedComponentFinder(BoardCompressed10x10 _board) : board(_board), label_next(labels) {}

public:
	std::vector<CCWithAnalysis*> getComponentsOver4() {
		std::vector<CCWithAnalysis*> groups;

		//generate run data
		findRuns();
		optimizeLink();

		//create groups  
		groups.reserve(16);
		for (Label* lb = labels; lb < label_next; lb++) {
			if (lb->link == lb && 4 <= lb->size) {
				CCWithAnalysis* cc = new CCWithAnalysis(lb->size);
				groups.push_back(cc);
				lb->cc = cc;
			}
			else lb->cc = nullptr;
		}

		//generate group form
		for (int i = 0; i < 10; i++) {
			Run* runs = runss[i];
			for (; runs->label; runs++) {
				CCWithAnalysis* cc = runs->label->link->cc;
				if (!cc) continue;
				cc->board.merge_and(i, runs->form);
			}
		}
		return groups;
	}
	std::vector<std::pair<int, int>> getComponentCoordinatesUnder4() {
		std::vector<std::pair<int, int>> ret;

		//generate run data
		findRuns();
		optimizeLink();

		//merge only valid label groups of size >= 4
		for (int i = 0; i < 10; i++) {
			Run* runs = runss[i];
			for (; runs->label; runs++) {
				int size = runs->label->link->size;
				if (4 <= size) continue;

				unsigned long j_start;
				myBitScanForward32(&j_start, runs->form);
				unsigned long j_end;
				myBitScanForward32(&j_end, (~runs->form) & ((0xFFFFFFFF) << j_start));
				for (unsigned long j = j_start; j < j_end; j++) ret.push_back(std::make_pair(i, j));
			}
		}
		return ret;
	}
};
#endif