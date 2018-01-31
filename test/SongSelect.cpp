#include "SongSelect.h"
#include "DxLib.h"

SongSelect::SongSelect(ISceneChanger* changer) : BaseScene(changer) {
}

//初期化
void SongSelect::Initialize(){
	mImageHandle = LoadGraph("image/Scene_Menu.png");    //画像のロード
	SsIHandle[TULIP] = LoadGraph("image/jacket/Tulip_mod.jpg");
	SsSHandle[TULIP] = LoadSoundMem("sound/時間だ、答えを聞こう.wav");
	Tulip = new RectClicker(110, 110, 150, 150, SsIHandle[TULIP], SsSHandle[TULIP], eScene_Music);
	SsIHandle[ONTOLOGY] = LoadGraph("image/jacket/Ontology_mod.jpg");
	SsSHandle[ONTOLOGY] = LoadSoundMem("sound/時間だ、答えを聞こう.wav");
	Ontology = new RectClicker(300, 110, 150, 150, SsIHandle[ONTOLOGY], SsSHandle[ONTOLOGY], eScene_Music);

	BIHandle = LoadGraph("image/back.png");
	BSHandle = LoadSoundMem("sound/どこへ行こうというのかね？.mp3");
	Back = new CircleClicker(80, 420, 50, BIHandle, BSHandle, eScene_Menu);
	scope = LoadGraph("image/scope.png");
	MenuBack = new CMenuBack();
}

//更新
void SongSelect::Update(){
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0){//Escキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Music);//シーンをメニュー画面に変更
		SelectedSong = Debug;
	}
	if (CheckHitKey(KEY_INPUT_M) != 0){//Mキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Music);//シーンをメニュー画面に変更
		SelectedSong = Debug;
	}
	MenuBack->Calc();
	
	Tulip->Update(wiibuf, oldwiibuf);
	Ontology->Update(wiibuf, oldwiibuf);
	Back->Update(wiibuf, oldwiibuf);
	if (Tulip->nextflag){
		mSceneChanger->ChangeScene(Tulip->Next);
		SelectedSong = TULIP;
	}
	if (Ontology->nextflag){
		mSceneChanger->ChangeScene(Ontology->Next);
		SelectedSong = ONTOLOGY;
	}
	if (Back->nextflag){
		mSceneChanger->ChangeScene(Back->Next);
	}
}

//描画
void SongSelect::Draw(){
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	MenuBack->Graph();
	Tulip->Draw(wiibuf, oldwiibuf);
	Ontology->Draw(wiibuf, oldwiibuf);
	Back->Draw(wiibuf, oldwiibuf);
	myw_buf* buf = wiibuf;
	DrawRotaGraph(buf->DX_X, buf->DX_Y, 0.35, 0.0, scope, TRUE);
	buf++;
	DrawRotaGraph(buf->DX_X, buf->DX_Y, 0.35, 0.0, scope, TRUE);
}

void SongSelect::Sound(){
}

void SongSelect::Finalize(){
	delete Tulip;
	delete Ontology;
	delete Back;
	delete MenuBack;
	InitSoundMem();
	InitGraph();
}