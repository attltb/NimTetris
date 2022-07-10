#include "Blocks.hpp"
using namespace std; 
const TetrominoInfo TetrominoInfo::booster[N_OF_TETROMINO]{
	TetrominoInfo(TetrominoID::I, TetrominoID::Z, TetrominoID::O, {{0, 0}, {0, 1}, {0, 2}, {0, 3}}),
	TetrominoInfo(TetrominoID::O, TetrominoID::I, TetrominoID::L, {{0, 0}, {0, 1}, {1, 0}, {1, 1}}),
	TetrominoInfo(TetrominoID::L, TetrominoID::O, TetrominoID::J, {{0, 0}, {0, 1}, {0, 2}, {1, 0}}),
	TetrominoInfo(TetrominoID::J, TetrominoID::L, TetrominoID::T, {{0, 0}, {0, 1}, {0, 2}, {1, 2}}),
	TetrominoInfo(TetrominoID::T, TetrominoID::J, TetrominoID::S, {{0, 0}, {0, 1}, {0, 2}, {1, 1}}),
	TetrominoInfo(TetrominoID::S, TetrominoID::T, TetrominoID::Z, {{0, 1}, {0, 2}, {1, 0}, {1, 1}}),
	TetrominoInfo(TetrominoID::Z, TetrominoID::S, TetrominoID::I, {{0, 0}, {0, 1}, {1, 1}, {1, 2}}),
};
const TetrominoFixedID TetrominoFixedInfo::fix[N_OF_TETROMINO][4]{
		{TetrominoFixedID::I0, TetrominoFixedID::I1, TetrominoFixedID::I0, TetrominoFixedID::I1},
		{TetrominoFixedID::O, TetrominoFixedID::O, TetrominoFixedID::O, TetrominoFixedID::O},
		{TetrominoFixedID::L0, TetrominoFixedID::L1, TetrominoFixedID::L2, TetrominoFixedID::L3},
		{TetrominoFixedID::J0, TetrominoFixedID::J1, TetrominoFixedID::J2, TetrominoFixedID::J3},
		{TetrominoFixedID::T0, TetrominoFixedID::T1, TetrominoFixedID::T2, TetrominoFixedID::T3},
		{TetrominoFixedID::S0, TetrominoFixedID::S1, TetrominoFixedID::S0, TetrominoFixedID::S1},
		{TetrominoFixedID::Z0, TetrominoFixedID::Z1, TetrominoFixedID::Z0, TetrominoFixedID::Z1},
};
const TetrominoFixedInfo TetrominoFixedInfo::booster[N_OF_TETROMINOFIXED]{
	TetrominoFixedInfo(TetrominoFixedID::I0, TetrominoID::I, 0),
	TetrominoFixedInfo(TetrominoFixedID::I1, TetrominoID::I, 1),
	TetrominoFixedInfo(TetrominoFixedID::O, TetrominoID::O, 0),
	TetrominoFixedInfo(TetrominoFixedID::L0, TetrominoID::L, 0),
	TetrominoFixedInfo(TetrominoFixedID::L1, TetrominoID::L, 1),
	TetrominoFixedInfo(TetrominoFixedID::L2, TetrominoID::L, 2),
	TetrominoFixedInfo(TetrominoFixedID::L3, TetrominoID::L, 3),
	TetrominoFixedInfo(TetrominoFixedID::J0, TetrominoID::J, 0),
	TetrominoFixedInfo(TetrominoFixedID::J1, TetrominoID::J, 1),
	TetrominoFixedInfo(TetrominoFixedID::J2, TetrominoID::J, 2),
	TetrominoFixedInfo(TetrominoFixedID::J3, TetrominoID::J, 3),
	TetrominoFixedInfo(TetrominoFixedID::T0, TetrominoID::T, 0),
	TetrominoFixedInfo(TetrominoFixedID::T1, TetrominoID::T, 1),
	TetrominoFixedInfo(TetrominoFixedID::T2, TetrominoID::T, 2),
	TetrominoFixedInfo(TetrominoFixedID::T3, TetrominoID::T, 3),
	TetrominoFixedInfo(TetrominoFixedID::S0, TetrominoID::S, 0),
	TetrominoFixedInfo(TetrominoFixedID::S1, TetrominoID::S, 1),
	TetrominoFixedInfo(TetrominoFixedID::Z0, TetrominoID::Z, 0),
	TetrominoFixedInfo(TetrominoFixedID::Z1, TetrominoID::Z, 1),
};

TetrominoInfo::TetrominoInfo(TetrominoID _id, TetrominoID _prev, TetrominoID _next, vector<pair<int, int>> _coordinates)
	: id(_id), prev(_prev), next(_next), coordinates(_coordinates) {
	int ymax = 0;
	int xmax = 0;
	for (unsigned int i = 0; i < coordinates.size(); i++) {
		int y = coordinates[i].first;
		int x = coordinates[i].second;
		if (ymax < y) ymax = y;
		if (xmax < x) xmax = x;
	}

	width = xmax + 1;
	height = ymax + 1;
}
TetrominoFixedInfo::TetrominoFixedInfo(TetrominoFixedID _idFixed, TetrominoID _id, int _rot) : idFixed(_idFixed), id(_id), rot(_rot) {
	const TetrominoInfo& shapeinfo_unfixed = TetrominoInfo::get(_id);

	if (rot % 2) width = shapeinfo_unfixed.height, height = shapeinfo_unfixed.width;
	else width = shapeinfo_unfixed.width, height = shapeinfo_unfixed.height;
	int xmax = width - 1;
	int ymax = height - 1;

	if (width + 1 < height) rotation_interpolation_y = 1, rotation_interpolation_x = -1;
	if (height + 1 < width) rotation_interpolation_y = -1, rotation_interpolation_x = 1;

	coordinates = shapeinfo_unfixed.coordinates;
	switch (rot % 4) {
	case 1:
		for (unsigned int i = 0; i < coordinates.size(); i++) coordinates[i] = { coordinates[i].second, xmax - coordinates[i].first };
		break;
	case 2:
		for (unsigned int i = 0; i < coordinates.size(); i++) coordinates[i] = { ymax - coordinates[i].first, xmax - coordinates[i].second };
		break;
	case 3:
		for (unsigned int i = 0; i < coordinates.size(); i++) coordinates[i] = { ymax - coordinates[i].second, coordinates[i].first };
		break;
	}

	int xsum = 0;
	int ysum = 0;
	for (unsigned int i = 0; i < coordinates.size(); i++) {
		ysum += coordinates[i].first;
		xsum += coordinates[i].second;
	}
	centerOfMass_x = ((double)xsum / (double)coordinates.size()) + 0.5;
	centerOfMass_y = ((double)ysum / (double)coordinates.size()) + 0.5;
}

TetrominoFixedID Tetromino10x10::tetrominoFixedID() const {
	return TetrominoFixedInfo::getID(tetrominoID, rot);
}
const TetrominoInfo& Tetromino10x10::tetrominoInfo() const {
	return TetrominoInfo::get(tetrominoID);
}
const TetrominoFixedInfo& Tetromino10x10::tetrominoFixedInfo() const {
	return TetrominoFixedInfo::get(tetrominoID, rot);
}

int Tetromino10x10::pos_x_max() const {
	return 10 - tetrominoFixedInfo().width;
}
int Tetromino10x10::pos_y_max() const {
	return 10 - tetrominoFixedInfo().height;
}

vector<pair<int, int>> Tetromino10x10::coordinates() const {
	vector<pair<int, int>> ret = tetrominoFixedInfo().coordinates;
	for (unsigned int i = 0; i < ret.size(); i++) {
		ret[i].first += pos_y;
		ret[i].second += pos_x;
	}
	return ret;
}

bool Tetromino10x10::move_l() {
	if (pos_x == 0) return false;
	pos_x--;
	return true;
}
bool Tetromino10x10::move_r() {
	if (pos_x == pos_x_max()) return false;
	pos_x++;
	return true;
}
bool Tetromino10x10::move_u() {
	if (pos_y == 0) return false;
	pos_y--;
	return true;
}
bool Tetromino10x10::move_d() {
	if (pos_y == pos_y_max()) return false;
	pos_y++;
	return true;
}
bool Tetromino10x10::setPos(int new_x, int new_y) {
	if (new_x < 0) new_x = 0;
	if (new_y < 0) new_y = 0;
	pos_x = (new_x <= pos_x_max()) ? new_x : pos_x_max();
	pos_y = (new_y <= pos_y_max()) ? new_y : pos_y_max();
	return new_x <= pos_x_max() && new_y <= pos_y_max();
}
bool Tetromino10x10::rotate_left() {
	rot = (rot + 3) % 4;
	const TetrominoFixedInfo& info = tetrominoFixedInfo();

	pos_x -= info.rotation_interpolation_x;
	pos_y -= info.rotation_interpolation_y;

	if (pos_x < 0) pos_x = 0;
	if (pos_y < 0) pos_y = 0;
	if (pos_y + info.height > 10) pos_y = 10 - info.height;
	if (pos_x + info.width > 10) pos_x = 10 - info.width;
	return true;
}
bool Tetromino10x10::rotate_right() {
	rot = (rot + 1) % 4;
	const TetrominoFixedInfo& info = tetrominoFixedInfo();

	pos_x -= info.rotation_interpolation_x;
	pos_y -= info.rotation_interpolation_y;

	if (pos_x < 0) pos_x = 0;
	if (pos_y < 0) pos_y = 0;
	if (pos_y + info.height > 10) pos_y = 10 - info.height;
	if (pos_x + info.width > 10) pos_x = 10 - info.width;
	return true;
}
bool Tetromino10x10::change_shape_left() {
	tetrominoID = tetrominoInfo().prev;
	const TetrominoFixedInfo& info = tetrominoFixedInfo();

	if (pos_y + info.height > 10) pos_y = 10 - info.height;
	if (pos_x + info.width > 10) pos_x = 10 - info.width;
	return true;
}
bool Tetromino10x10::change_shape_right() {
	tetrominoID = tetrominoInfo().next;
	const TetrominoFixedInfo& info = tetrominoFixedInfo();

	if (pos_y + info.height > 10) pos_y = 10 - info.height;
	if (pos_x + info.width > 10) pos_x = 10 - info.width;
	return true;
}