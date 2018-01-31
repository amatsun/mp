//クリックに反応して動くものの実装
#pragma once

#include "my_wii.h"
#include "ISceneChanger.h"
#include "DxLib.h"

class Clicker{
public:
	unsigned __int16 x, y;//画像の表示中心
	__int8 clicked;//押されたかどうか　1:押された　0:何もなし　-1:押し込まれている
	unsigned __int16 counter;
	int ihandle;//画像のハンドル
	int shandle;//音声のハンドル
	eScene Next;//押されたときに遷移するシーン
	bool waitflag;//これがonなら他のクリックを無効化する
	bool nextflag;//これをチェックしておき、これがtrueならそのシーンに遷移
	bool inside;//true:カーソルが中にある false:外にある
	Clicker();
	~Clicker();
	void Update(myw_buf* wiibuf, myw_buf* oldwiibuf);
	void Draw(myw_buf* wiibuf, myw_buf* oldwiibuf);
	virtual bool CheckInside(unsigned __int16 _x, unsigned __int16 _y);
	int ViewNext();
};

class RectClicker : public Clicker{
public:
	unsigned __int16 width, height;//画像の横幅、縦幅
	RectClicker();
	~RectClicker();
	RectClicker(unsigned __int16 _x, unsigned __int16 _y, unsigned __int16 _w, unsigned __int16 _h, int _ihandle, int _shandle, eScene _next);
	bool CheckInside(unsigned __int16 _x, unsigned __int16 _y);
};

class CircleClicker : public Clicker{
public:
	unsigned __int16 radius;//画像の半径
	CircleClicker();
	~CircleClicker();
	CircleClicker(unsigned __int16 _x, unsigned __int16 _y, unsigned __int16 _r, int _ihandle, int _shandle, eScene _next);
	bool CheckInside(unsigned __int16 _x, unsigned __int16 _y);
};