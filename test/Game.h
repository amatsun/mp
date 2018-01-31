#pragma once

#include "BaseScene.h"
#include "ISceneChanger.h"

#include "MyFunc_cv.h"

#include "MyFunc_music.h"
#include "my_wii.h"
#include "wiimote.h"

extern myw_buf wiibuf[2];
extern myw_buf oldwiibuf[2];
extern __int8 n_w;
//ゲーム画面クラス
class Game : public BaseScene {

protected:
	char f[256];
	

public:
	Game::Game(ISceneChanger* changer);
	void Initialize() override;    //初期化処理をオーバーライド。
	//void Finalize() override;        //終了処理をオーバーライド。
	void Update() override;        //更新処理をオーバーライド。
	void Draw() override;            //描画処理をオーバーライド。
	void Sound() override;

};
