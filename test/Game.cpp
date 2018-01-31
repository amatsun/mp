#include "Game.h"
#include <iostream>

#include <DxLib.h>
#include "my_math.h"

Game::Game(ISceneChanger* changer) : BaseScene(changer) {
}

//初期化
void Game::Initialize(){
	mImageHandle = LoadGraph("images/Scene_Game.png");    //画像のロード
	
}

//更新
void Game::Update(){
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0){ //Escキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Menu);//シーンをメニューに変更
	}
	
}

//描画
void Game::Draw(){
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	DrawString(0, 0, "ゲーム画面です。", GetColor(255, 255, 255));
	DrawString(0, 20, "Escキーを押すとメニュー画面に戻ります。", GetColor(255, 255, 255));
	
	for (int i = 0; i < 2; i++){
		sprintf(f, "A=%dB=%dN_C=%d[X Y]=[%lf %lf]", wiibuf[i].A, wiibuf[i].B, wiibuf[i].N_C, 960 * wiibuf[i].IR_X - 320, 720 * wiibuf[i].IR_Y - 240);
		DrawString(10, 100 + 20 * i, f, (unsigned int)GetColor(255, 0, 0));
		sprintf(f, "A=%dB=%dN_C=%d[X Y]=[%lf %lf]", oldwiibuf[i].A, oldwiibuf[i].B, oldwiibuf[i].N_C, 960 * oldwiibuf[i].IR_X - 320, 720 * oldwiibuf[i].IR_Y - 240);
		DrawString(10, 140 + 20 * i, f, (unsigned int)GetColor(255, 0, 0));
		DrawCircle(wiibuf[i].IR_X * 960 - 320, wiibuf[i].IR_Y * 720 - 240, 12, (unsigned int)GetColor(0, 255, 255));
		DrawCircle(320, 240, 12, (unsigned int)GetColor(0, 255, 255));
	}

}

void Game::Sound(){
}
