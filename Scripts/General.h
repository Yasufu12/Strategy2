#pragma once

#include"DxLib.h"
#include"Suken.h"

const int GRID_L = 50;
const int MAP_W = 700/GRID_L;//700と500の公約数
const int MAP_H = 500/GRID_L;//2,2,5,5を組み合わせる
const int UNIT_NUM = 4;
const int COUNTRY_NUM = 2;
const int RIGHT = 1;
const int LEFT = 2;
const int DOWN = 3;
const int UP = 4;
const int COMBAT = 22;
const int SHOT = 12;
const int BBOX = 0;//何もないマス
const int PLAIN = 1;
const int RIVER = 2;

class CTurn{
private:
	int turn;
	int country;
	bool skip;

public:
	CTurn();
	void SkipTurn();
	bool Getskip();
	int GetCountry();

};

class CCal{
public:
	int Absolute(int a);//絶対値

};

class CCommon{
private:
	bool rclick;

public:
	void CheckRClick();
	bool GetOnRClick();
	int GetNumKey();
	int CheckArrow();
}; 