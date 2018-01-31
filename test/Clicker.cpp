#include "Clicker.h"
#include <math.h>

#define PI 3.14159265

Clicker::Clicker(){}

Clicker::~Clicker(){}

void Clicker::Update(myw_buf* wiibuf, myw_buf* oldwiibuf){
	if (waitflag){
		counter++;
		if (!CheckSoundMem(shandle)){
			nextflag = true;
		}
	}
	else if (clicked == 1){
		PlaySoundMem(shandle, DX_PLAYTYPE_BACK);
		waitflag = true;
		counter = 0;
	}
	inside = CheckInside(wiibuf->DX_X, wiibuf->DX_Y);
	if (inside){
		counter++;
		switch (clicked){
		case 1:		
			break;
		case 0:
			if (wiibuf->B != oldwiibuf->B&&wiibuf->B == true){
				clicked = -1;
			}
			break;
		case -1:
			if (wiibuf->B != oldwiibuf->B&&wiibuf->B == false){
				clicked = 1;
			}
			break;
		}
	}
	else{
		counter = 0;
		if (clicked == -1) clicked = 0;
	}
}

void Clicker::Draw(myw_buf* wiibuf,myw_buf* oldwiibuf){
	if (clicked == 1){
		SetDrawBright(255, sin((counter % 13) / 12.0 * 2 * PI)*127.5 + 127.5, 255);
		DrawRotaGraph(x, y, 1.2, 0.0, ihandle, TRUE);
		SetDrawBright(255, 255, 255);
		DrawRotaGraph(x, y, 1.1, 0.0, ihandle, TRUE);
	}
	else{
		if (inside){
			SetDrawBright(sin((counter % 30) / 12.0 * 2 * PI)*127.5 + 127.5, 255, sin((counter % 30) / 12.0 * 2 * PI)*127.5 + 127.5);
			DrawRotaGraph(x, y, 1.2, 0.0, ihandle, TRUE);
			SetDrawBright(255, 255, 255);
			DrawRotaGraph(x, y, 1.1, 0.0, ihandle, TRUE);
		}
		else{
			DrawRotaGraph(x, y, 1.0, 0.0, ihandle, TRUE);
		}
	}
	//DrawFormatString(10, y, GetColor(255, 255, 255), "N_C=%d old=%d nf=%d clk=%d wf=%d cs=%d ih=%d sh=%d", wiibuf->N_C, oldwiibuf->N_C, nextflag, clicked, waitflag, CheckSoundMem(shandle), ihandle, shandle);
}

bool Clicker::CheckInside(unsigned __int16 _x, unsigned __int16 _y){
	return true;
}

int Clicker::ViewNext(){
	return Next;
}

RectClicker::RectClicker(){}

RectClicker::~RectClicker(){}

RectClicker::RectClicker(unsigned __int16 _x, unsigned __int16 _y, unsigned __int16 _w, unsigned __int16 _h, int _ihandle, int _shandle, eScene _next){
	x = _x; y = _y;
	width = _w; height = _h;
	ihandle = _ihandle; shandle = _shandle;
	Next = _next;
	inside = false; nextflag = false; waitflag = false;
	clicked = 0;
}

bool RectClicker::CheckInside(unsigned __int16 _x, unsigned __int16 _y){
	//DrawFormatString(320, 240, GetColor(255, 255, 255), "CheckInside");
	if (abs(x - _x) < width / 2 && abs(y - _y) < height / 2){
		return true;
	}
	else{
		return false;
	}
}

CircleClicker::CircleClicker(){}

CircleClicker::~CircleClicker(){}

CircleClicker::CircleClicker(unsigned __int16 _x, unsigned __int16 _y, unsigned __int16 _r, int _ihandle, int _shandle, eScene _next){
	x = _x; y = _y;
	radius = _r;
	ihandle = _ihandle; shandle = _shandle;
	Next = _next;
	inside = false; nextflag = false; waitflag = false;
	clicked = 0;
}

bool CircleClicker::CheckInside(unsigned __int16 _x, unsigned __int16 _y){
	//DrawFormatString(320, 240, GetColor(255, 255, 255), "CheckInside");
	if (sqrt((float)(x - _x)*(x - _x) + (y - _y)*(y - _y)) <= radius){
		return true;
	}
	else {
		return false;
	}
}