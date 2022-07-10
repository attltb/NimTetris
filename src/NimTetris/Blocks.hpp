#ifndef _BlocksHeader_
#define _BlocksHeader_
#include <stdint.h>
#include <vector>
#define N_OF_TETROMINO 7
#define N_OF_TETROMINOFIXED 19
enum class TetrominoID : int8_t { I, O, L, J, T, S, Z };
enum class TetrominoFixedID : int8_t { I0, I1, O, L0, L1, L2, L3, J0, J1, J2, J3, T0, T1, T2, T3, S0, S1, Z0, Z1 };

struct TetrominoInfo {
private:
	static const TetrominoInfo booster[N_OF_TETROMINO];
	
public:
	TetrominoID id;
	TetrominoID prev;
	TetrominoID next;
	int width;
	int height;
	std::vector<TetrominoFixedID> fixed;
	std::vector<std::pair<int, int>> coordinates;

public:
	static const TetrominoInfo& get(int i) {
		return booster[i];
	}
	static const TetrominoInfo& get(TetrominoID id) {
		return booster[(int)id];
	}

public:
	TetrominoInfo(TetrominoID _id, TetrominoID _prev, TetrominoID _next, std::vector<std::pair<int, int>> _coordinates);
};
struct TetrominoFixedInfo {
private:
	static const TetrominoFixedID fix[N_OF_TETROMINO][4];
	static const TetrominoFixedInfo booster[N_OF_TETROMINOFIXED];

public:
	TetrominoFixedID idFixed;
	TetrominoID id;
	int rot;
	int width;
	int height;
	int rotation_interpolation_x;
	int rotation_interpolation_y;
	double centerOfMass_x;
	double centerOfMass_y;
	std::vector<std::pair<int, int>> coordinates;

public:
	static TetrominoFixedID getID(TetrominoID id, int _rot) {
		return fix[(int)id][_rot];
	}
	static const TetrominoFixedInfo& get(int i) {
		return booster[i];
	}
	static const TetrominoFixedInfo& get(TetrominoFixedID id) {
		return booster[(int)id];
	}
	static const TetrominoFixedInfo& get(TetrominoID id, int _rot) {
		return booster[int(getID(id, _rot))];
	}

public:
	TetrominoFixedInfo(TetrominoFixedID _idFixed, TetrominoID _id, int _rot);
};

struct Tetromino10x10
{
public:
	TetrominoID tetrominoID;
	int8_t rot;
	int8_t pos_x;
	int8_t pos_y;

public:
	Tetromino10x10() : tetrominoID(TetrominoID::L), rot(0), pos_x(0), pos_y(0) {}
	Tetromino10x10(const Tetromino10x10& other)
		: tetrominoID(other.tetrominoID), rot(other.rot), pos_x(other.pos_x), pos_y(other.pos_y) {}
	Tetromino10x10(TetrominoID _tetrominoID, int8_t _rot, int8_t _pos_x, int8_t _pos_y)
		: tetrominoID(_tetrominoID), rot(_rot), pos_x(_pos_x), pos_y(_pos_y) {}
	Tetromino10x10(TetrominoFixedID _tetrominoFixedID, int8_t _pos_x, int8_t _pos_y) : pos_x(_pos_x), pos_y(_pos_y) {
		const TetrominoFixedInfo& tetrominoFixedInfo = TetrominoFixedInfo::get(_tetrominoFixedID);
		tetrominoID = tetrominoFixedInfo.id;
		rot = tetrominoFixedInfo.rot;
	}

private:
	int pos_x_max() const;
	int pos_y_max() const;

public:
	TetrominoFixedID tetrominoFixedID() const;
	const TetrominoInfo& tetrominoInfo() const;
	const TetrominoFixedInfo& tetrominoFixedInfo() const;

public:
	std::vector<std::pair<int, int>> coordinates() const;

public:
	bool move_l();
	bool move_r();
	bool move_u();
	bool move_d();
	bool setPos(int new_x, int new_y);
	bool rotate_left();
	bool rotate_right();
	bool change_shape_left();
	bool change_shape_right();
};
#endif