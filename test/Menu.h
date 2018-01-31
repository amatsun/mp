#pragma once

#include "BaseScene.h"
#include "Clicker.h"


extern myw_buf wiibuf[2], oldwiibuf[2];

//メニュー画面クラス
class Menu : public BaseScene {

public:
	Menu(ISceneChanger* changer);
	void Initialize() override;    //初期化処理をオーバーライド。
	void Finalize() override;        //終了処理をオーバーライド。
	void Update() override;        //更新処理をオーバーライド。
	void Draw() override;            //描画処理をオーバーライド。
	void Sound() override;
	RectClicker* ToSongSelect;
	int TSSIHandle, TSSSHandle;
	CircleClicker* ToConfig;
	int TCIHandle, TCSHandle;
	int scope;
	int mskahandle, commenthandle, stringhandle;
	int backhandle;
};