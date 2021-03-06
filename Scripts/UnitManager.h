#pragma once

#include"Suken.h"
#include"Unit.h"
#include"Country.h"
#include"Picture.h"
#include"Cursor.h"
#include"General.h"

class CUnitManager{
private:
	CUnit unit[UNIT_NUM+1];
	CCal cal;
	CCursor cursor;
	CPicture picture;
	CTurn turn;
	CCommon common;
	int selectingC;
	int selectingU;
	int GetX(int _country,int _unit);
	int GetY(int _country,int _unit);
	int GetRoute(int _country,int _unit,int _x,int _y);
	bool screen;
	bool Moveable(int dir /*direction*/);
	bool onemove; //一マス動いた
	void Select(int _unit);
	void Setselecting();
	bool Selecting(); //ユニットのいずれかを選んでいるか
	void Move();
	void SetUnit();
	void PaintUnit();
	bool CheckLCOn(int _country, int _unit);
	bool CheckRCOn(int _country, int _unit);

public:
	CCountry country[COUNTRY_NUM+1];
	CUnitManager();
	int GetselectingU();
	void ProductScr(bool open1,bool open2);//生産画面が開いているか
	void DrawUnit();
	void MoveUnit();
	void Moveend();
	void Awake();

};
