#pragma once

#include "BaseScene.h"
#include "Clicker.h"
#include "SongBank.h"
#include "AndroidLike.h"

extern myw_buf wiibuf[2], oldwiibuf[2];
extern SongName SelectedSong;

//メニュー画面クラス
class SongSelect : public BaseScene {

public:
	SongSelect(ISceneChanger* changer);
	void Initialize() override;    //初期化処理をオーバーライド。
	void Finalize() override;        //終了処理をオーバーライド。
	void Update() override;        //更新処理をオーバーライド。
	void Draw() override;            //描画処理をオーバーライド。
	void Sound() override;
	RectClicker *Tulip, *Ontology;
	int SsIHandle[2], SsSHandle[2];
	CircleClicker* Back;
	int BIHandle, BSHandle;
	int scope;
	CMenuBack* MenuBack;
};