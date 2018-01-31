//�N���b�N�ɔ������ē������̂̎���
#pragma once

#include "my_wii.h"
#include "ISceneChanger.h"
#include "DxLib.h"

class Clicker{
public:
	unsigned __int16 x, y;//�摜�̕\�����S
	__int8 clicked;//�����ꂽ���ǂ����@1:�����ꂽ�@0:�����Ȃ��@-1:�������܂�Ă���
	unsigned __int16 counter;
	int ihandle;//�摜�̃n���h��
	int shandle;//�����̃n���h��
	eScene Next;//�����ꂽ�Ƃ��ɑJ�ڂ���V�[��
	bool waitflag;//���ꂪon�Ȃ瑼�̃N���b�N�𖳌�������
	bool nextflag;//������`�F�b�N���Ă����A���ꂪtrue�Ȃ炻�̃V�[���ɑJ��
	bool inside;//true:�J�[�\�������ɂ��� false:�O�ɂ���
	Clicker();
	~Clicker();
	void Update(myw_buf* wiibuf, myw_buf* oldwiibuf);
	void Draw(myw_buf* wiibuf, myw_buf* oldwiibuf);
	virtual bool CheckInside(unsigned __int16 _x, unsigned __int16 _y);
	int ViewNext();
};

class RectClicker : public Clicker{
public:
	unsigned __int16 width, height;//�摜�̉����A�c��
	RectClicker();
	~RectClicker();
	RectClicker(unsigned __int16 _x, unsigned __int16 _y, unsigned __int16 _w, unsigned __int16 _h, int _ihandle, int _shandle, eScene _next);
	bool CheckInside(unsigned __int16 _x, unsigned __int16 _y);
};

class CircleClicker : public Clicker{
public:
	unsigned __int16 radius;//�摜�̔��a
	CircleClicker();
	~CircleClicker();
	CircleClicker(unsigned __int16 _x, unsigned __int16 _y, unsigned __int16 _r, int _ihandle, int _shandle, eScene _next);
	bool CheckInside(unsigned __int16 _x, unsigned __int16 _y);
};