#ifndef _NimTetrisCustumPlayerInfoHeader_
#define _NimTetrisCustumPlayerInfoHeader_
#include <string.h>
#include <math.h>
class NimTetrisPlayerInfo {
public:
	enum class CONTROL { USER, AI0, AI1, AI2, AI3, AI4, AI5, AI6, AI7, AI8, AI9, AI10 };

public:
	int custumPlayerID;
	CONTROL control;
	int ELO;
	char name[24];

public:
	static int getAILevel(CONTROL control) {
		return (int)control - 1;
	}

public:
	void operator= (const NimTetrisPlayerInfo& other) {
		custumPlayerID = other.custumPlayerID;
		control = other.control;
		ELO = other.ELO;
		strcpy(name, other.name);
	}

public:
	bool isCustum() const {
		return custumPlayerID;
	}
	int getCustumPlayerID() const {
		return custumPlayerID;
	}

public:
	void updateELO(NimTetrisPlayerInfo& loserInfo) {
		if (custumPlayerID == loserInfo.custumPlayerID) return;
		if (!isCustum() && !loserInfo.isCustum()) return;

		double AQ, BQ, exValue, Kvalue;
		int changer;
		Kvalue = 100;
		AQ = pow(10, (double)this->ELO / 400);
		BQ = pow(10, (double)loserInfo.ELO / 400);
		exValue = AQ / (AQ + BQ);
		changer = (int)ceil(100 * (1 - exValue));
		ELO += changer;

		if(isCustum()) ELO += changer;
		if (loserInfo.isCustum()) loserInfo.ELO -= changer;
	}

public:
	NimTetrisPlayerInfo(CONTROL _control) : custumPlayerID(0), control(_control) {
		switch (control) {
		case CONTROL::USER:
			strcpy(name, "NoSave");
			ELO = 0;
			break;
		case CONTROL::AI0:
			strcpy(name, "Lv0");
			ELO = 0;
			break;
		case CONTROL::AI1:
			strcpy(name, "Lv1");
			ELO = 100;
			break;
		case CONTROL::AI2:
			strcpy(name, "Lv2");
			ELO = 200;
			break;
		case CONTROL::AI3:
			strcpy(name, "Lv3");
			ELO = 300;
			break;
		case CONTROL::AI4:
			strcpy(name, "Lv4");
			ELO = 400;
			break;
		case CONTROL::AI5:
			strcpy(name, "Lv5");
			ELO = 500;
			break;
		case CONTROL::AI6:
			strcpy(name, "Lv6");
			ELO = 600;
			break;
		case CONTROL::AI7:
			strcpy(name, "Lv7");
			ELO = 700;
			break;
		case CONTROL::AI8:
			strcpy(name, "Lv8");
			ELO = 800;
			break;
		case CONTROL::AI9:
			strcpy(name, "Lv9");
			ELO = 900;
			break;
		case CONTROL::AI10:
			strcpy(name, "Lv10");
			ELO = 1000;
			break;
		}
	}
	NimTetrisPlayerInfo(int _id) : custumPlayerID(_id), control(CONTROL::USER), ELO(0) {
		strcpy(name, "");
	}
	NimTetrisPlayerInfo(int _id, CONTROL _control, const char* _name) : custumPlayerID(_id), control(_control), ELO(0) {
		strcpy(name, _name);
	}
	NimTetrisPlayerInfo(const NimTetrisPlayerInfo& other) : custumPlayerID(other.custumPlayerID), control(other.control), ELO(other.ELO) {
		strcpy(name, other.name);
	}
};
#endif