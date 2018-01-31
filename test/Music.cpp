#include "Music.h"

#include <iostream>

//#include "wiimote.h"

#include <DxLib.h>

#include "my_math.h"


Music::Music(ISceneChanger* changer) :BaseScene(changer){
}
	
//初期化
void Music::Initialize(){
	frame = 0;
	counter = 0;
	stopflag = 0;
	init = 1;
	c = 0;
	playfinish = 0;
	mode = MINECRAFT;
	sHandle[signote] = LoadSoundMem("sound/gun/gun.wav");
	ChangeVolumeSoundMem(255 * 90 / 100.0, sHandle[signote]);
	sHandle[lnote] = LoadSoundMem("sound/machin/machin_loop.mp3");
	sHandle[lnote + 1] = LoadSoundMem("sound/machin/machin_loop.mp3");
	sHandle[slinote] = LoadSoundMem("sound/machin/machin_loop.mp3");
	sHandle[slinote + 1] = LoadSoundMem("sound/machin/machin_loop.mp3");
	sHandle[50] = LoadSoundMem("sound/バルス！.wav");
	ChangeVolumeSoundMem(255 * 80 / 100, sHandle[lnote]);
	fp = fopen("frame.txt", "w");
	if (fp == NULL)DebugBreak();
	fprintf(fp, "frame=\n");
	finished = false;
	starter = 0;
	ecount = 0;
	switch (mode){
	case MINECRAFT:
		iHandle[signote] = LoadGraph("image/zombie.jpg");
		iHandle[lnote] = LoadGraph("image/skelton.jpg");
		iHandle[slinote] = LoadGraph("image/creeper.jpg");
		char a[50] = "asuka.jpg";
		for (i = 0; i < 16; i++){
			sprintf(a, "image/zombie/zombie%d.jpg", i);
			notedivhandle[0][i] = LoadGraph(a);
			sprintf(a, "image/skelton/skelton%d.jpg", i);
			notedivhandle[1][i] = LoadGraph(a);
			sprintf(a, "image/creeper/creeper%d.jpg", i);
			notedivhandle[2][i] = LoadGraph(a);
		}
		break;
	}
	iHandle[bullet] = LoadGraph("image/b_mod.png");
	iHandle[perfect] = LoadGraph("image/judge/perfect.png");
	iHandle[great] = LoadGraph("image/judge/great.png");
	iHandle[nice] = LoadGraph("image/judge/nice.png");
	iHandle[bad] = LoadGraph("image/judge/bad.png");
	iHandle[miss] = LoadGraph("image/judge/miss.png");
	iHandle[COMBO] = LoadGraph("image/combo.png");
	iHandle[SCOPE1] = LoadGraph("image/scope.png");
	iHandle[SCOPE2] = LoadGraph("image/lock_scope_mod.png");
	iHandle[BLOOD] = LoadGraph("image/blood_mod.png");
	iHandle[IMPACT] = LoadGraph("image/impact.png");
	iHandle[FIREFLOWER] = LoadGraph("image/fireflower.png");
	iHandle[BLACK] = LoadGraph("image/black_area/black_area3.png");
	iHandle[JUDGEAREA] = LoadGraph("image/faces/Icon_Asuka.png");
	iHandle[JUDGEAREA + 1] = LoadGraph("image/faces/Icon_Ranko.png");
	iHandle[JUDGEAREA + 2] = LoadGraph("image/faces/Icon_TakeuchiP.png");
	iHandle[JUDGEAREA + 3] = LoadGraph("image/faces/Icon_Mska.png");
	iHandle[BACK] = LoadGraph("image/backs/346pro_entrance.jpg");
	iHandle[MAXCOMBO] = LoadGraph("image/maxcombo.png");
	for (i = 0; i < 10; i++){
		sprintf(g, "image/number/%d.png", i);
		image_number[i] = LoadGraph(g);
		deffect[i].SetValid(0);
	}
	for (i = 0; i < 20; i++){
		effect[i].setview(0);
	}
	for (i = 0; i < 2; i++){
		heffect[i].setview(0);
	}
	//ノーツの設定
	notenum = 0;
	switch (SelectedSong){
	case TULIP:
		sHandle[0] = LoadSoundMem("sound/song/Tulip_mod5.mp3");
		sm_fp = fopen("sheet_music/Tulip_mod.txt", "r");
		if (sm_fp == NULL)DebugBreak();
		break;
	case ONTOLOGY:
		sHandle[0] = LoadSoundMem("sound/song/Ontology2.mp3");
		sm_fp = fopen("sheet_music/Ontology.txt", "r");
		if (sm_fp == NULL)DebugBreak();
		break;
	case Debug:
		sHandle[0] = LoadSoundMem("sound/song/Ontology2.mp3");
		sm_fp = fopen("sheet_music/Ontology.txt", "r");
		if (sm_fp == NULL)DebugBreak();
		break;
	default:DebugBreak();
		break;
	}
	ChangeVolumeSoundMem(255 * 85 / 100.0, sHandle[0]);
	fscanf(sm_fp, "%s %d", buf, &notenum);
	basevalue = 800;
	note = (NoteInfo*)malloc(notenum*sizeof(NoteInfo));
	fscanf(sm_fp, "%d %d", &bufom, &bufoj);
	om = bufom;
	//notenum = 0;
	for (i = 0;i<notenum; i++){
		buft = bufd1 = bufd2 = bufa1 = bufa2 = bufj1 = bufj2 = 0;
		fscanf(sm_fp, "%d", &buft);
		switch (buft){
		case signote:
			fscanf(sm_fp, "%d %d %d", &bufd1, &bufj1, &bufa1);
			if (!bufa1){
				bufa1 = bd + 10;
			}
			
			note[i].SetNote(bufj1 + om, bufj1 + bufoj, bufa1, bufd1, iHandle[signote], iHandle[BLOOD]);
			break;
		case lnote:
			fscanf(sm_fp, "%d %d %d %d %d", &bufd1, &bufj1, &bufj2, &bufa1, &bufa2);
			if (!bufa1){
				bufa1 = bd + 10;
			}
			if (!bufa2){
				bufa2 = bd + 10;
			}
			
			note[i].SetNote(bufj1 + om, bufj1 + bufoj, bufj2 + bufoj, bufa1, bufa2, bufd1, iHandle[lnote], iHandle[BLOOD]);
			break;
		case slinote:
			fscanf(sm_fp, "%d %d %d %d %d %d", &bufd1, &bufd2, &bufj1, &bufj2, &bufa1, &bufa2);
			if (!bufa1){
				bufa1 = bd + 10;
			}
			if (!bufa2){
				bufa2 = bd + 10;
			}
			
			note[i].SetNote(bufj1 + om, bufj1 + bufoj, bufj2 + bufoj, bufa1, bufa2, bufd1, bufd2, iHandle[slinote], iHandle[BLOOD]);
			break;
		default:DebugBreak();
			//bufom = 0;
			break;
		}
	}
	fclose(sm_fp);

	HInfo[0].number = HInfo[1].number = -1;
	Cr = GetColor(0, 0, 255);
	exec = false;
	X[0] = LU_X; Y[0] = LU_Y;
	X[1] = LD_X; Y[1] = LD_Y;
	X[2] = RU_X; Y[2] = RU_Y;
	X[3] = RD_X; Y[3] = RD_Y;
	for (i = 0; i < 4; i++){
		OX[i] = X[i]; OY[i] = Y[i];
		VX[i] = GetRand(4); VY[i] = GetRand(4);
	}
	//sprintf(g, "frame=");
	guncount[0] = guncount[1] = 0;
	//wiimote::Load16bitMonoSampleWAV(_T("sound/gun/gun.wav"), gun_sample);
	score = 0;
	for (i = 0; i < 7; i++)scoreboard[i] = 0;
	combo = 0;
	for (i = 0; i < 3; i++)comboboard[i] = -1;

	/*
	// カメラからのビデオキャプチャを初期化する
	cap.open(0);

	// BASEIMAGE 構造体を０で初期化
	memset(&BaseImage, 0, sizeof(BASEIMAGE));

	// カラーフォーマットは変化しないので最初に設定
	CreateFullColorData(&BaseImage.ColorData);

	// ミップマップではないので０
	BaseImage.MipMapCount = 0;

	// 空のグラフィックハンドルの値を初期化
	GrHandle = -1;*/
	
}

void Music::Update(){
	SRand(frame);
	GetHitKeyStateAll(buf);
	memcpy(oldspace, nowspace, sizeof(char) * 256);
	memcpy(nowspace, buf, sizeof(char) * 256);
	//X,Yの位置更新
	if (counter % 3 == 0){
		for (i = 0; i < 4; i++){
			X[i] += VX[i] - 2; Y[i] += VY[i] - 2;
			if (X[i] - OX[i] > 10){
				X[i] = OX[i] + 10;	VX[i] = 1;
			}
			else if (X[i] - OX[i] < -10){
				X[i] = OX[i] - 10;	VX[i] = 3;
			}
			else{
				VX[i] += (GetRand(2) - 1) % 4;
			}
			if (Y[i] - OY[i] > 10){
				Y[i] = OY[i] + 10; VY[i] = 1;
			}
			else if (Y[i] - OY[i] < -10){
				Y[i] = OY[i] - 10; VY[i] = 3;
			}
			else{
				VY[i] += (GetRand(2) - 1) % 4;
			}
		}
	}
	if (init){
		PlaySoundMem(sHandle[0], DX_PLAYTYPE_LOOP, FALSE);
		PlaySoundMem(sHandle[signote], DX_PLAYTYPE_BACK);
		while (CheckSoundMem(sHandle[0]) == 0){}
		init = 0;
		frame = GetSoundCurrentTime(sHandle[0]);
	}

	for (k = 0; k < 2; k++){
		Ar = areajudge(&wiibuf[k], X, Y);
		if (wiibuf[k].B != oldwiibuf[k].B){
			if (wiibuf[k].B == true){//signoteとlnote、slinoteの始点、空打ちで場合わけ
				for (i = 0; i < notenum; i++){
					if (note[i].judgeflag1 == 1 && note[i].destiny == Ar){
						exec = true;	//judge はクラスにして判定の描画をし、すでに存在するときに呼び出されたときは今までのをリセットして新しいのを作って描画する
						judge.SetJudge(iHandle[judgenote(frame, note[i].judgetime, note[i].type)]);
						resultbuf = judgenote(frame, note[i].judgetime, note[i].type);
						ComboUpdate(resultbuf, &combo, &maxcombo);
						ScoreUpdate(basevalue, resultbuf, combo, &score, notenum);
						note[i].judgeflag1 = 0;
						if (note[i].type == signote){
							note[i].viewflag = 0;
							effect[ecount++ % 20].SetEffect(signote, frame, iHandle[bullet], wiibuf[k].DX_X, wiibuf[k].DX_Y, iHandle[BLOOD]);
							PlaySoundMem(sHandle[note[i].type], DX_PLAYTYPE_BACK);
							guncount[k] = 15;
							deffect[decount++ % 10].Set(note[i].vx, note[i].vy, notedivhandle[0], resultbuf);
							effect[ecount++ % 20].SetEffect(1, frame, 1, X[Ar], Y[Ar], iHandle[IMPACT]);
						}
						else if (note[i].type == lnote || note[i].type == slinote){
							//判定により後のノーツを描画するかを設定　コンボ数を参照してもよさそう
							if (combo > 0){
								HInfo[k].type = note[i].type;
								HInfo[k].number = i;
								heffect[k].SetEffect(note[i].type, frame, iHandle[bullet], iHandle[FIREFLOWER]);//raser
								PlaySoundMem(sHandle[note[i].type + k], DX_PLAYTYPE_LOOP);
							}
							else{
								note[i].viewflag = 0;
								effect[ecount++ % 20].SetEffect(note[i].type, frame, iHandle[bullet], wiibuf[k].DX_X, wiibuf[k].DX_Y, iHandle[BLOOD]);
								PlaySoundMem(sHandle[signote], DX_PLAYTYPE_BACK);
								guncount[k] = 15;
							}
						}
					}
				}
				if (!exec){	//Effect new;ここで空打ち時のエフェクトのインスタンスを生成
					effect[ecount++ % 20].SetEffect(signote, frame, iHandle[bullet], wiibuf[k].DX_X, wiibuf[k].DX_Y, -1);
					PlaySoundMem(sHandle[signote], DX_PLAYTYPE_BACK);
					guncount[k] = 15;
				}
				else{
					exec = false;
				}
			}
			else{//ボタンを離したとき　slinote、lnoteの終点と空打ち、ホールド中に離した時で場合わけ
				for (i = 0; i < notenum; i++){
					if (HInfo[k].number == i){
						if (note[i].judgeflag2 == 1 && note[i].destiny2 == Ar){
							judge.SetJudge(iHandle[judgenote(frame, note[i].judgetime2, note[i].type)]);
							resultbuf = judgenote(frame, note[i].judgetime2, note[i].type);
							ComboUpdate(resultbuf, &combo, &maxcombo);
							ScoreUpdate(basevalue, resultbuf, combo, &score, notenum);
							effect[ecount++ % 20].SetEffect(note[i].type, frame, iHandle[bullet], wiibuf[k].DX_X, wiibuf[k].DX_Y, iHandle[BLOOD]);
							deffect[decount++ % 10].Set(note[i].vx, note[i].vy, notedivhandle[note[i].type / 5 - 2], resultbuf);
							effect[ecount++ % 20].SetEffect(1, frame, 1, X[Ar], Y[Ar], iHandle[IMPACT]);
						}
						else {
							judge.SetJudge(iHandle[miss]);
							note[i].result2 = miss;
							combo = 0;
							//ScoreUpdate(note[i].result2, combo, &score);
							effect[ecount++ % 20].SetEffect(note[i].type, frame, iHandle[bullet], wiibuf[k].DX_X, wiibuf[k].DX_Y, iHandle[BLOOD]);
						}
						StopSoundMem(sHandle[note[i].type + k]);
						note[i].judgeflag2 = 0;
						note[i].viewflag = 0;
						PlaySoundMem(sHandle[signote], DX_PLAYTYPE_BACK);
						guncount[k] = 20;
						HInfo[k].number = -1;
						heffect[k].setview(0);
					}
				}
			}
		}
	}

	for (i = 0; i < 2; i++){
		if (HInfo[i].number != -1){//ホールド中カーソルが離れていなければスコア加算　離れることによるコンボ切れはなし
			__int16 hnum = HInfo[i].number;
			if (note[hnum].holdjudge(X, Y, frame, &wiibuf[i])){//コンボ数に応じてホールド中のスコア加算
				score += basevalue * 2 * EXRATE * ComboRate(combo, notenum) / 30.0;
			}
			//if (frame - note[hnum].judgetime2 > 80){
			//HInfo[i].number = -1;
			//heffect[i].setview(0);
			//}
			if (counter % 6 == 0){
				effect[ecount++ % 20].SetEffect(signote, frame, -1, note[hnum].vx, note[hnum].vy, iHandle[FIREFLOWER]);
			}
		}
	}
	frame = GetSoundCurrentTime(sHandle[0]);
	counter++;
	if (nowspace[KEY_INPUT_ESCAPE] != oldspace[KEY_INPUT_ESCAPE] && nowspace[KEY_INPUT_ESCAPE] == 0){
		mSceneChanger->ChangeScene(eScene_Menu);//シーンをメニューに変更
	}
	if (note[notenum - 1].viewflag == 0){
		if (!CheckSoundMem(sHandle[0])){//曲が終わったとき
			finished = true;
			playfinish = 1;
		}
	}
	if (finished == true && playfinish == 1){//stage clear
		PlaySoundMem(sHandle[50], DX_PLAYTYPE_LOOP);
		playfinish = 0;
	}
}



void Music::Draw(){
	/*
	cap >> im;
	cv::flip(im, im, 1);
	image = im;
	BaseImage.GraphData = image.imageData;
	BaseImage.Width = image.width;
	BaseImage.Height = image.height;
	BaseImage.Pitch = image.widthStep;

	// グラフィックハンドルを作成しているかどうかで処理を分岐
	if (GrHandle == -1)
	{
		// 最初の場合はグラフィックハンドルの作成と映像の転送を一度に行う
		GrHandle = CreateGraphFromBaseImage(&BaseImage);
	}
	else
	{
		// ２回目以降はグラフィックハンドルへ映像を転送
		ReCreateGraphFromBaseImage(&BaseImage, GrHandle);
	}*/
	//DrawGraph(0, 0, GrHandle, FALSE);

	//DrawString(C_X, C_Y, f, Cr);
	//DrawString(C_X, C_Y*1.5, g, Cr);

	/*
	if (stopflag==1){
	}
	else{*/
	SetDrawBright(127, 127, 127);
	DrawRotaGraph(C_X, C_Y, 1.5, 0.0, iHandle[BACK], TRUE);
	SetDrawBright(255, 255, 255);
	

	for (i = 0; i < 4; i++) {//判定エリアの描画
		DrawRotaGraph(X[i], Y[i], 1.0, 0.0, iHandle[JUDGEAREA + i], TRUE);
	}
	for (i = 0; i < notenum; i++){
		note[i].update(frame, &combo, &maxcombo);
		if (note[i].result1>0){
			judge.SetJudge(iHandle[miss]);
			note[i].result1 = 0;
			c = note[i].result1;
		}
		if (note[i].result2>0) {
			judge.SetJudge(iHandle[miss]);
			note[i].result2 = 0;
			c = note[i].result2;
			for (j = 0; j < 2; j++){
				if (HInfo[j].number == i){
					heffect[j].setview(0);
					HInfo[j].number = -1;
					StopSoundMem(sHandle[note[i].type + j]);
					break;
				}
			}
		}
		note[i].draw(X, Y, frame);
		//DrawFormatString(10, 10 + i * 20, GetColor(0, 0, 255), "vf=%d jf=%d mt=%d jt=%d aj=%d", note[i].viewflag, note[i].judgeflag1, note[i].maketime, note[i].judgetime, note[i].allowjudge1);
	}
	for (i = 0; i < 2; i++){
		if (HInfo[i].number >= 0){//ホールド中は先頭の顔を赤く点滅させる　ここでなくともよさそう
			note[HInfo[i].number].damageddraw(X, Y, frame);
		}
	}

	for (i = 0; i < 20; i++){//単発打ちについての描画
		effect[i].drawEffect(frame);
	}

	for (i = 0; i < 2; i++){//ホールド中の血の描画
		heffect[i].drawEffect(frame, &wiibuf[i]);
	}
	for (i = 0; i < 10; i++){
		deffect[i].update();
		if (deffect[i].viewvalid() == 1)	deffect[i].draw();
	}
	/*
	i = 0;
	DrawFormatString(10, 10 + i * 20, GetColor(0, 0, 255), "vf=%d jf=%d mt=%d jt=%d aj=%d", note[i].viewflag, note[i].judgeflag1, note[i].maketime, note[i].judgetime, note[i].allowjudge1);
	i = 1;
	DrawFormatString(10, 10 + i * 20, GetColor(0, 0, 255), "vf=%d jf=%d mt=%d jt1=%d jt2=%d aj=%d", note[i].viewflag, note[i].judgeflag1, note[i].maketime, note[i].judgetime,note[i].judgetime2, note[i].allowjudge1);
	i = 2;
	DrawFormatString(10, 10 + i * 20, GetColor(0, 0, 255), "vf=%d jf=%d mt=%d jt1=%d jt2=%d aj=%d", note[i].viewflag, note[i].judgeflag1, note[i].maketime, note[i].judgetime, note[i].judgetime2, note[i].allowjudge1);
	i = 3;
	DrawFormatString(10, 10 + i * 20, GetColor(0, 0, 255), "vf=%d jf=%d mt=%d jt1=%d jt2=%d aj=%d aj2=%d", note[i].viewflag, note[i].judgeflag1, note[i].maketime, note[i].judgetime, note[i].judgetime2, note[i].allowjudge1,note[i].allowjudge2);
	i = 4;
	DrawFormatString(10, 10 + i * 20, GetColor(0, 0, 255), "bufom=%d bufoj=%d om=%d", bufom, bufoj,om);

	i = 0;
	DrawFormatString(10, 110 + i * 20, GetColor(0, 0, 255), "vx=%d vy=%d d=%d", note[i].vx, note[i].vy, note[i].destiny);
	i = 1;
	DrawFormatString(10, 110 + i * 20, GetColor(0, 0, 255), "vx=%d vy=%d d=%d", note[i].vx, note[i].vy, note[i].destiny);
	i = 2;
	DrawFormatString(10, 110 + i * 20, GetColor(0, 0, 255), "vx=%d vy=%d d=%d", note[i].vx, note[i].vy, note[i].destiny);
	i = 3;
	DrawFormatString(10, 110 + i * 20, GetColor(0, 0, 255), "vx=%d vy=%d d=%d", note[i].vx, note[i].vy, note[i].destiny);
	i = 4;
	DrawFormatString(10, 110 + i * 20, GetColor(0, 0, 255), "0=%d 1=%d", HInfo[0].number,HInfo[1].number);
	*/

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 170);
	int color = combo * 37 % 360;
	SetDrawBright(HSVtoRGB(color, 70, 100, CV_R), HSVtoRGB(color, 70, 100, CV_G), HSVtoRGB(color, 70, 100, CV_B));
	DrawRotaGraph(C_X, C_Y, 0.85, 0.0, iHandle[BLACK], TRUE);
	SetDrawBright(255, 255, 255);

	judge.draw();//判定結果の描画
	ScoreToBoard(score, scoreboard);
	
	for (i = 0; i < 7; i++){//スコアの描画
		DrawRotaGraph(C_X-60 + i * 20, C_Y-40, 0.25, 0.0, image_number[scoreboard[i]], TRUE);
	}
	
	ComboToBoard(combo, comboboard);

	if (frame < 3000){
		DrawRotaGraph(C_X, C_Y, 1.0, 0.0, image_number[(4000 - frame) / 1000], TRUE);
	}
	if (finished != true){
		for (i = 0; i < 3; i++){//コンボ数の描画
			if (comboboard[i] != -1){
				DrawRotaGraph(C_X - 40 + i * 40, C_Y, 0.5, 0.0, image_number[comboboard[i]], TRUE);
			}
		}
		if (combo) DrawRotaGraph(C_X, C_Y + 40, 1.0, 0.0, iHandle[COMBO], TRUE);
	}
	else{
		ComboToBoard(maxcombo, comboboard);
		for (i = 0; i < 3; i++){//コンボ数の描画
			if (comboboard[i] != -1){
				DrawRotaGraph(C_X - 40 + i * 40, C_Y, 0.5, 0.0, image_number[comboboard[i]], TRUE);
			}
		}
		DrawRotaGraph(C_X, C_Y + 40, 1.0, 0.0, iHandle[MAXCOMBO], TRUE);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	for (i = 0; i < 2; i++){//スコープの描画
		if (!heffect[i].rview()){
			DrawRotaGraph(wiibuf[i].DX_X, wiibuf[i].DX_Y, 0.35, 0.0, iHandle[SCOPE1], TRUE);
		}
		else{
			DrawRotaGraph(wiibuf[i].DX_X, wiibuf[i].DX_Y, 0.40, (counter % 24) / 24.0 * 2 * PI, iHandle[SCOPE2], TRUE);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//ComboUpdate(perfect, &c);
	//if (frame % 50 == 0) {
		//deffect[0].Set(C_X, C_Y, notedivhandle[0], perfect);
		//guncount[0] = 20;
	//}
	//deffect[0].draw();
	/*
	DrawGraph(LU_X, LU_Y, notedivhandle0[0], TRUE);
	DrawGraph(C_X, C_Y, deffect[0].Handle(0), TRUE);
	DrawFormatString(C_X, C_Y, GetColor(0, 255, 255), "Ar=%dfr=%dcb=%d %d%d%d c=%d", Ar, frame, combo, comboboard[0], comboboard[1], comboboard[2],c);
	DrawFormatString(C_X, C_Y + 20, GetColor(0, 255, 0), "njf=%d HIt=%d de=%d gc=%d ef=%d", note[0].judgeflag1, note[0].viewflag, note[0].allowjudge1, note[0].result1, deffect[0].valid);
	DrawFormatString(C_X, C_Y + 40, GetColor(0, 255, 0), "HIn=%d HIt=%d de=%d gc=%d ef=%d", HInfo[0].number, HInfo[0].type, deffect[0].x[1], deffect[0].y[1], deffect[0].valid);
	*/
	DrawFormatString(C_X, C_Y + 100, GetColor(0, 0, 255), "frame=%d", frame);
	DrawFormatString(C_X-20, C_Y + 120, GetColor(0, 0, 255), "%dms", GetSoundCurrentTime(sHandle[0]));
	
}

void Music::Finalize(){
	fclose(fp);
	InitSoundMem();
	InitGraph();
}

void Music::Sound(){
	
	for (k = 0; k < 2; k++){
		if (guncount[k]==15){
			remote[k].EnableSpeaker(true);
			remote[k].PlaySample(gun_sample);
			guncount[k]--;
		}
		else if (guncount[k] > 0){
			guncount[k]--;
		}
		else if (guncount[k] == 0){
			remote[k].EnableSpeaker(false);
		}
	}
}