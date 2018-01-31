#pragma once

#include "my_effect.h"

#include "DxLib.h"

DesEfc::DesEfc(){
	valid = 0;
}

DesEfc::~DesEfc(){
}

void DesEfc::Set(__int16 _x, __int16 _y, int* _iHandle, __int8 _judge){
	valid = 1;
	//frame = _frame;
	judge = _judge;
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			x[i * 4 + j] = _x - 48 + j * 32;
			y[i * 4 + j] = _y - 48 + i * 32;
			Sx[i * 4 + j] = GetRand(1) * 2 - 1;
			Sy[i * 4 + j] = GetRand(2) + 1;
			G[i * 4 + j] = 2;
			theta[i * 4 + j] = GetRand(359);
			w[i * 4 + j] = GetRand(1) * 2 - 1;
			handle[i * 4 + j] = *_iHandle;
			_iHandle++;
		}
	}
	Bright = 255;

}

void DesEfc::update(){
	for (int i = 0; i < 16; i++){
		x[i] += Sx[i];
		y[i] += Sy[i];
		Sy[i] += G[i];
		theta[i] += w[i];
	}
	Bright -= 1;
	if (Bright < 150)valid = 0;
}

void DesEfc::draw(){//valid==1‚ÌŽž‚Ì‚ÝŒÄ‚Ño‚·
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Bright);
	SetDrawBright(180, 80, 80);
	for (int i = 0; i < 16; i++){
		DrawRotaGraph(x[i], y[i], Bright / 255.0, theta[i]*3.14159265/180.0, handle[i], TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBright(255, 255, 255);
}

__int8 DesEfc::viewvalid(){
	return valid;
}

void DesEfc::SetValid(char _valid){
	valid = _valid;
}

int DesEfc::Handle(int i){
	return handle[i];
}

void ScoreToBoard(int score, __int8* scoreboard){
	__int8 val[7], i;
	for (i = 0; i < 7; i++){
		val[6 - i] = score % 10;
		score = (score - val[6 - i]) / 10;
	}
	for (i = 0; i < 7; i++){
		*(scoreboard + i) = val[i];
	}
}

void ComboToBoard(unsigned __int16 combo, __int8* comboboard){
	__int8 val[3], i;
	for (i = 0; i < 3; i++){
		val[2 - i] = combo % 10;
		combo = (combo - val[2 - i]) / 10;
	}
	for (i = 0; i < 3; i++){
		if (val[i] == 0){
			val[i] = -1;
		}
		else{
			break;
		}
	}
	for (i = 0; i < 3; i++){
		*(comboboard + i) = val[i];
	}
}
