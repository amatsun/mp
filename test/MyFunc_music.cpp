#include "MyFunc_music.h"

NoteInfo::NoteInfo(){
}

NoteInfo::~NoteInfo(){
}

//singlenote用のセット関数
void NoteInfo::SetNote(int _maketime, int _judgetime, int _allowjudge1, __int8 _destiny, int _handle, int _bloodhandle){
	type = signote;
	viewflag = -1;
	destiny = _destiny;
	destiny2 = -1;
	maketime = _maketime;
	judgetime = _judgetime;
	allowjudge1 = _allowjudge1;
	judgeflag1 = -1;
	judgeflag2 = 0;
	handle = _handle;
	bloodhandle = _bloodhandle;
	deg = GetRand(359) / 360.0 * PI;
	result1 = 0; result2 = 0;
}

//longnote用のセット関数
void NoteInfo::SetNote(int _maketime, int _judgetime, int _judgetime2, int _allowjudge1, int _allowjudge2, __int8 _destiny, int _handle, int _bloodhandle){
	type = lnote;
	viewflag = -1;
	destiny = _destiny;
	destiny2 = _destiny;
	maketime = _maketime;
	judgetime = _judgetime;
	judgetime2 = _judgetime2;
	allowjudge1 = _allowjudge1;
	allowjudge2 = _allowjudge2;
	judgeflag1 = -1;
	judgeflag2 = -1;
	handle = _handle;
	bloodhandle = _bloodhandle;
	deg = GetRand(359) / 360.0 * PI;
	result1 = result2 = 0;
}

//slidenote用のセット関数
void NoteInfo::SetNote(int _maketime, int _judgetime, int _judgetime2, int _allowjudge1, int _allowjudge2, __int8 _destiny, __int8 _destiny2, int _handle, int _bloodhandle){
	type = slinote;
	viewflag = -1;
	destiny = _destiny;
	destiny2 = _destiny2;
	maketime = _maketime;
	judgetime = _judgetime;
	judgetime2 = _judgetime2;
	allowjudge1 = _allowjudge1;
	allowjudge2 = _allowjudge2;
	judgeflag1 = -1;
	judgeflag2 = -1;
	handle = _handle;
	bloodhandle = _bloodhandle;
	deg = GetRand(359) / 360.0 * PI;
	result1 = result2 = 0;
}

void NoteInfo::update(int _frame, unsigned __int16 *combo, unsigned __int16* maxcombo){
	if (maketime < _frame&&viewflag == -1){
		viewflag = 1;
	}
	if (judgeflag1 == 1 && (judgetime + allowjudge1) < _frame){
		*maxcombo = *combo;
		viewflag = 0;
		result1 = miss;
		judgeflag1 = 0;
		*combo = 0;
	}
	if ((type == lnote || type == slinote) && judgeflag2 == 1 && (judgetime2 + allowjudge2) < _frame){
		viewflag = 0;
		result2 = miss;
		judgeflag2 = 0;
		*maxcombo = *combo;
		*combo = 0;
	}
	if (viewflag == 1){
		if (judgeflag1 == -1){
			if (abs((int)(_frame - judgetime)) < allowjudge1){
				judgeflag1 = 1;
			}
		}
		else if (judgeflag2 == -1){
			if (abs((int)(_frame - judgetime2)) < allowjudge2){
				judgeflag2 = 1;
			}
		}
	}
}


void NoteInfo::draw(int* X, int* Y, int _frame){
	if (viewflag == 1){
		int viewnote[1][4];
		__int16 dl;
		double dx, dy;
		int j, x, y;
		char num;
		switch (type){
		case signote:
			calc_note_point(X, Y, _frame, viewnote[0], destiny, maketime, judgetime);
			DrawRotaGraph(viewnote[0][0], viewnote[0][1], 1.0, 0.0, handle, TRUE, FALSE);
			break;
		case lnote:
			calc_note_point(X, Y, _frame, viewnote[0], destiny, maketime, judgetime, judgetime2);
			break;
		case slinote:
			calc_note_point(X, Y, _frame, viewnote[0], destiny, destiny2, maketime, judgetime, judgetime2);
			break;
		}
		if (type == lnote || type == slinote){
			dl = (int)sqrt(pow(float(viewnote[0][0] - viewnote[0][2]), 2) + pow(float(viewnote[0][1] - viewnote[0][3]), 2));
			j = 0;
			num = dl / MAX_LENGTH;
			dx = go_dl_by2num(viewnote[0], MAX_LENGTH, 0);
			dy = go_dl_by2num(viewnote[0], MAX_LENGTH, 1);
			while (num > j){
				x = viewnote[0][2] - j*dx;
				y = viewnote[0][3] - j*dy;
				DrawRotaGraph(x, y, 1.0, 0.0, handle, TRUE);
				j++;
			}
			DrawRotaGraph(viewnote[0][0], viewnote[0][1], 1.0, 0.0, handle, TRUE);
		}
		vx = viewnote[0][0]; vy = viewnote[0][1];
	}
}

void NoteInfo::damageddraw(int* X, int* Y, int _frame){
	int viewnote[1][4];
	switch (type){
	case lnote:
		calc_note_point(X, Y, _frame, viewnote[0], destiny, maketime, judgetime, judgetime2);
		break;
	case slinote:
		calc_note_point(X, Y, _frame, viewnote[0], destiny, destiny2, maketime, judgetime, judgetime2);
		break;
	}
	SetDrawBright(sin((counter) % 20 / 20.0 * 2 * PI) * 0 + 127, 0, 0);
	DrawRotaGraph(viewnote[0][0], viewnote[0][1], 1.0, 0.0, handle, TRUE);
	SetDrawBright(255, 255, 255);
	if (_frame-oldframe>75){
		deg = GetRand(359) / 180.0*PI;
		oldframe = _frame;
	}
	DrawRotaGraph(viewnote[0][0], viewnote[0][1], 1.4, deg, bloodhandle, TRUE);
}

__int8 NoteInfo::rview(){
	return viewflag;
}

__int8 NoteInfo::jview(int s){
	switch (s){
	case 1:
		return judgeflag1;
	case 2:
		return judgeflag2;
	}
}

//カーソル位置とノーツの情報からそれらが離れているかいないかを判定
//1:holding
//0:unholding
int NoteInfo::holdjudge(int* X, int* Y, int _frame, myw_buf* wiibuf){
	int judge = 0;
	__int16 x, y;
	switch (type){
	case lnote:
		x = *(X + destiny);
		y = *(Y + destiny);
		break;
	case slinote:
		x = *(X + destiny) + (*(X + destiny2) - *(X + destiny))*(_frame - judgetime) / (float)(judgetime2 - judgetime);
		y = *(Y + destiny) + (*(Y + destiny2) - *(Y + destiny))*(_frame - judgetime) / (float)(judgetime2 - judgetime);
		break;
	}
	float dl = sqrt((float)((x - wiibuf->DX_X)*(x - wiibuf->DX_X) + (y - wiibuf->DX_Y)*(y - wiibuf->DX_Y)));
	if (dl < 150){
		judge = 1;
	}
	else{
		judge = 0;
	}
	return judge;
}


Judge::Judge(){
	view = 0;
}
void Judge::SetJudge(int _handle){
	counter = 20;
	view = 1;
	handle = _handle;
}
Judge::~Judge(){
}
void Judge::draw(){
	if (view){
		if (counter > 0){
			DrawRotaGraph(C_X, 120, 1.0, 0.0, handle, TRUE);
			counter--;
		}
		else{
			view = 0;
		}
	}
}
__int8 Judge::rview(){
	return view;
}
void Judge::setview(__int8 sview){
	view = sview;
}



Effect::Effect(){
	view = 0;
}

void Effect::SetEffect(__int8 type, int frame, int btype, int _x, int _y, int _bloodhandle){
	eframe = frame;
	etype = type;
	view = 1;
	x = _x;
	y = _y;
	ebtype = btype;
	bloodhandle = _bloodhandle;
	deg = GetRand(359) / 360.0 * PI;
	deg2 = GetRand(359) / 360.0 * PI;
}
void Effect::SetEffect(__int8 type, int frame, int btype,int _bloodhandle){
	eframe = frame;
	etype = type;
	view = 1;
	ebtype = btype;
	bloodhandle = _bloodhandle;
	counter = 0;
	deg = GetRand(359) / 360.0 * PI;
	deg2 = GetRand(359) / 360.0 * PI;
}
Effect::~Effect(){
}
void Effect::setview(__int8 sview){
	view = sview;
}
__int8 Effect::rview(){
	return view;
}
__int8 Effect::rtype(){
	return etype;
}
void Effect::drawEffect(int frame){
	if (view){
		if ((frame - eframe) <= 800){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (800 - (frame - eframe)) * 255 / 900.0);
			DrawRotaGraph(x, y, (1.0 + (frame - eframe) / 900.0)*0.6, deg, ebtype, TRUE);
			DrawRotaGraph(x, y, (1.0 + (frame - eframe) / 900.0)*0.8, deg2, bloodhandle, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else {
			view = 0;
		}
	}
}
void Effect::drawEffect(int frame, myw_buf* wiibuf){
	if (view){
		__int8 dtx, dty;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, counter % 7 * 255 / 8.0);
		if ((frame - eframe) > 70){
			eframe = frame;
			SRand(frame);
			dtx = GetRand(15)- 8;
			dty = GetRand(15) - 8;
			deg = GetRand(359) / 360.0 * PI;
			deg2 = GetRand(359) / 360.0 * PI;
		}
		DrawRotaGraph(wiibuf->DX_X, wiibuf->DX_Y, (1.0 + (counter % 5) / 20.0)*0.6, deg, ebtype, TRUE);
		DrawRotaGraph(wiibuf->DX_X , wiibuf->DX_Y , (1.0 + (counter % 5) / 20.0)*0.8, deg2, bloodhandle, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		counter++;
	}
}

// ノーツの種類と判定から鳴らす音のハンドルを決定する
int setsound_note(int notetype, int judge){

	int handle = signote;//ここの数字はsHandleによって変える必要あり signoteの番号が適切
	//提案　前半のswitch文で数字を５刻みでセットし、後半で０～４の値を足していく。
	
	handle += notetype;
	//↑もnotetypeを足すだけですむようにできると思う
	handle += judge;

	return handle;
}

//ハンドルの値から鳴らす音を決める　なくてもよい（わかりやすくするため）　重ければ削ってみる
int myplaysound(int handle, int* sHandle){
	int val = PlaySoundMem(sHandle[handle], DX_PLAYTYPE_BACK);
	return val;
}

// 入力タイム(itime)と目標タイム(dtime)から判定を返す それぞれフレーム単位にするつもり
char judgenote(int itime, int dtime, char type){

	int df;
	df = abs(itime - dtime);
	switch (type){
	case signote:
		if (df <= pd){
			return perfect;
		}
		else if (df <= gd){
			return great;
		}
		else if (df <= nd){
			return nice;
		}
		else if (df <= bd){
			return bad;
		}
		else{
			return miss;
		}
		break;
	case lnote:
	case slinote:
		if (df <= pd + 10){
			return perfect;
		}
		else if (df <= gd + 10){
			return great;
		}
		else if (df <= nd + 10){
			return nice;
		}
		else if (df <= bd + 10){
			return bad;
		}
		else{
			return miss;
		}
		break;
	}
}


//ノーツと現在のフレーム数からノーツを描画するべき位置を返す関数　要見直し
void calc_note_point(int *X, int *Y, int _frame, int *val, __int8 _destiny, int _maketime, int _judgetime){
	val[0] = C_X + (*(X + _destiny) - C_X)*(_frame - _maketime) / (float)(_judgetime - _maketime);
	val[1] = C_Y + (*(Y + _destiny) - C_Y)*(_frame - _maketime) / (float)(_judgetime - _maketime);
	val[2] = 0;
	val[3] = 0;
}

void calc_note_point(int* X, int* Y, int _frame, int* val, __int8 _destiny, int _maketime, int _judgetime, int _judgetime2){
	int dt;
	if (_judgetime > _frame){
		val[0] = C_X + (*(X + _destiny) - C_X)*(_frame - _maketime) / (float)(_judgetime - _maketime);
		val[1] = C_Y + (*(Y + _destiny) - C_Y)*(_frame - _maketime) / (float)(_judgetime - _maketime);
	}
	else{
		val[0] = *(X + _destiny);
		val[1] = *(Y + _destiny);
	}
	dt = _judgetime2 - _judgetime + _maketime;
	if (dt < _frame){
		val[2] = C_X + (*(X + _destiny) - C_X)*(_frame - dt) / (float)(_judgetime - _maketime);
		val[3] = C_Y + (*(Y + _destiny) - C_Y)*(_frame - dt) / (float)(_judgetime - _maketime);
	}
	else{
		val[2] = C_X; val[3] = C_Y;
	}
}

void calc_note_point(int* X, int* Y, int _frame, int* val, __int8 _destiny, __int8 _destiny2, int _maketime, int _judgetime, int _judgetime2){
	int dx, dy, dx2, dy2;
	int dt;
	dx = *(X + _destiny);
	dy = *(Y + _destiny);
	dx2 = *(X + _destiny2);
	dy2 = *(Y + _destiny2);
	if (_judgetime > _frame){
		val[0] = C_X + (dx - C_X)*(_frame - _maketime) / (float)(_judgetime - _maketime);
		val[1] = C_Y + (dy - C_Y)*(_frame - _maketime) / (float)(_judgetime - _maketime);
	}
	else{
		val[0] = dx + (dx2 - dx)*(_frame - _judgetime) / (float)(_judgetime2 - _judgetime);
		val[1] = dy + (dy2 - dy)*(_frame - _judgetime) / (float)(_judgetime2 - _judgetime);
	}
	dt = _judgetime2 - _judgetime + _maketime;
	if (dt < _frame){
		val[2] = C_X + (val[0] - C_X)*(_frame - dt) / (float)(_judgetime - _maketime);
		val[3] = C_Y + (val[1] - C_Y)*(_frame - dt) / (float)(_judgetime - _maketime);
	}
	else{
		val[2] = C_X; val[3] = C_Y;
	}
}

int areajudge(myw_buf* wiibuf,int* X,int* Y){
	float ds[4],shortest;
	shortest = 1000000;
	int id = -1;
	//int x = wiibuf->DX_X, y = wiibuf->DX_Y;
	for (int i = 0; i < 4; i++){
		int dx, dy;
		ds[i] = pow(float(*(X + i) - wiibuf->DX_X), 2) + pow(float(*(Y + i) - wiibuf->DX_Y), 2);
		if (ds[i] < shortest){
			shortest = ds[i];
			id = i;
		}
	}
	return id;
}

void SigEfcSet(unsigned int frame, Effect* effect, myw_buf wiibuf,int btype, int _bloodhandle){
	for (__int8 j = 0; j < 20; j++){
		if (!effect->rview()){
			effect->SetEffect(signote, frame, wiibuf.DX_X, wiibuf.DX_Y, btype, _bloodhandle);
		}
		if (j = 19){
			effect[0].SetEffect(signote, frame, wiibuf.DX_X, wiibuf.DX_Y, btype, _bloodhandle);
		}
		effect++;
	}
}

void ComboUpdate(__int8 judge, unsigned __int16 *combo, unsigned __int16* maxcombo){
	switch (judge){
	case perfect:
	case great:
	case nice:
		*combo = *combo + 1;
		*maxcombo = *combo;
		break;
	case bad:
	case miss:
		*maxcombo = *combo;
		*combo = 0;
		break;
	}
}

void ScoreUpdate(float basevalue, __int8 judge, unsigned __int16 combo, int* score, unsigned __int16 notenum){
	if (judge != miss){
		float judgerate, comborate;
		comborate = ComboRate(combo, notenum);
		switch (judge){
		case perfect:
			judgerate = 1.0;
			break;
		case great:
			judgerate = 0.7;
			break;
		case nice:
			judgerate = 0.4;
			break;
		case bad:
			judgerate = 0.1;
			break;
		}
		*score += basevalue * judgerate * comborate * EXRATE;
	}
}

float ComboRate(unsigned __int16 combo, unsigned __int16 notenum){
	float comborate;
	if (combo / (float)notenum < 0.05){
		comborate = 1.0;
	}
	else if (combo / (float)notenum < 0.1){
		comborate = 1.1;
	}
	else if (combo / (float)notenum < 0.25){
		comborate = 1.2;
	}
	else if (combo / (float)notenum < 0.5){
		comborate = 1.3;
	}
	else if (combo / (float)notenum < 0.7){
		comborate = 1.4;
	}
	else if (combo / (float)notenum < 0.8){
		comborate = 1.5;
	}
	else if (combo / (float)notenum < 0.9){
		comborate = 1.7;
	}
	else{
		comborate = 2.0;
	}
	return comborate;
}