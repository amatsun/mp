#include "DxLib.h"
#include "AndroidLike.h"

#define PI2 (3.141592654f*2)

CMenuBack::CMenuBack(){
	//m_imgBack = LoadGraph("img/top_back.png");
	m_imgMask = LoadMask("image/menu_back_mask.png");
	m_imgOverLay = LoadGraph("image/menu_back_over.png");
	m_Count = 0;
}

CMenuBack::~CMenuBack(){
	//DeleteGraph(m_imgBack);
	DeleteGraph(m_imgMask);
	DeleteGraph(m_imgOverLay);
}

void CMenuBack::Calc(){
	m_Count++;
}

void CMenuBack::Graph(){
	//DrawGraph(0, 0, m_imgBack, FALSE);
	CreateMaskScreen();
	DrawMask(0, 0, m_imgMask, DX_MASKTRANS_BLACK);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawRotaGraph2(320, 240, 370, 370, 1.0, PI2 / 240 * m_Count, m_imgOverLay, TRUE);
	DrawRotaGraph2(320, 240, 370, 370, 1.0, PI2 / 240 * (m_Count - 120), m_imgOverLay, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DeleteMaskScreen();
}