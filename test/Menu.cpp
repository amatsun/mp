#include "Menu.h"

#include <iostream>

#include <DxLib.h>

#include "my_math.h"

Menu::Menu(ISceneChanger* changer) : BaseScene(changer) {
}

//初期化
void Menu::Initialize(){
	mImageHandle = LoadGraph("image/Scene_Menu.png");    //画像のロード
	TSSIHandle = LoadGraph("image/live.png");
	TSSSHandle = LoadSoundMem("sound/ToSS.mp3");
	ToSongSelect = new RectClicker(500, 120, 200, 120, TSSIHandle, TSSSHandle, eScene_SongSelect);
	TCIHandle = LoadGraph("image/config.png");
	TCSHandle = LoadSoundMem("sound/どこへ行こうというのかね？.mp3");
	ToConfig = new CircleClicker(540, 440, 80, TCIHandle, TCSHandle, eScene_Config);
	scope = LoadGraph("image/scope.png");
	mskahandle = LoadGraph("image/ムスカ.png");
	commenthandle = LoadGraph("image/comment.png");
	//stringhandle = LoadGraph("image/string.png");
	stringhandle = LoadGraph("image/string.png");
	backhandle = LoadGraph("image/backs/346pro_outline.jpg");
}

//更新
void Menu::Update(){
	if (CheckHitKey(KEY_INPUT_G) != 0){//Gキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Game);//シーンをゲーム画面に変更
	}
	if (CheckHitKey(KEY_INPUT_C) != 0){//Cキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Config);//シーンを設定画面に変更
	}
	if (CheckHitKey(KEY_INPUT_M) != 0){//Mキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Music);//シーンを音ゲー画面に変更
	}
	if (CheckHitKey(KEY_INPUT_S) != 0){//Sキーが押されていたら
		mSceneChanger->ChangeScene(eScene_SongSelect);//シーンを曲選択画面に変更
	}
	ToSongSelect->Update(wiibuf, oldwiibuf);
	ToConfig->Update(wiibuf, oldwiibuf);
	if (ToSongSelect->nextflag){
		mSceneChanger->ChangeScene(ToSongSelect->Next);
	}
	if (ToConfig->nextflag){
		mSceneChanger->ChangeScene(ToConfig->Next);
	}
}

//描画
void Menu::Draw(){
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	//DrawString(0, 0, "メニュー画面です。", GetColor(255, 255, 255));
	//DrawString(0, 20, "Gキーを押すとゲーム画面に進みます。", GetColor(255, 255, 255));
	//DrawString(0, 40, "Cキーを押すと　設定画面に進みます。", GetColor(255, 255, 255));
	//DrawString(0, 60, "Mキーを押すと音ゲー画面に進みます。", GetColor(255, 255, 255));
	DrawRotaGraph(320, 240, 1.3, 0.0, backhandle, TRUE);
	DrawGraph(10, 200, mskahandle, TRUE);
	DrawRotaGraph3(240, 100, 240, 100, 1.0, 1.0, 0.0, commenthandle, TRUE);
	DrawRotaGraph(170, 70, 0.45, 0.0, stringhandle, TRUE);
	ToSongSelect->Draw(wiibuf, oldwiibuf);
	ToConfig->Draw(wiibuf, oldwiibuf);
	myw_buf* buf = wiibuf;
	DrawRotaGraph(buf->DX_X, buf->DX_Y, 0.35, 0.0, scope, TRUE);
	buf++;
	DrawRotaGraph(buf->DX_X, buf->DX_Y, 0.35, 0.0, scope, TRUE);
}

void Menu::Sound(){
}

void Menu::Finalize(){
	delete ToSongSelect;
	delete ToConfig;
	InitSoundMem();
	InitGraph();
}