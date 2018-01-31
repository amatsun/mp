#include "Menu.h"

#include <iostream>

#include <DxLib.h>

#include "my_math.h"

Menu::Menu(ISceneChanger* changer) : BaseScene(changer) {
}

//������
void Menu::Initialize(){
	mImageHandle = LoadGraph("image/Scene_Menu.png");    //�摜�̃��[�h
	TSSIHandle = LoadGraph("image/live.png");
	TSSSHandle = LoadSoundMem("sound/ToSS.mp3");
	ToSongSelect = new RectClicker(500, 120, 200, 120, TSSIHandle, TSSSHandle, eScene_SongSelect);
	TCIHandle = LoadGraph("image/config.png");
	TCSHandle = LoadSoundMem("sound/�ǂ��֍s�����Ƃ����̂��ˁH.mp3");
	ToConfig = new CircleClicker(540, 440, 80, TCIHandle, TCSHandle, eScene_Config);
	scope = LoadGraph("image/scope.png");
	mskahandle = LoadGraph("image/���X�J.png");
	commenthandle = LoadGraph("image/comment.png");
	//stringhandle = LoadGraph("image/string.png");
	stringhandle = LoadGraph("image/string.png");
	backhandle = LoadGraph("image/backs/346pro_outline.jpg");
}

//�X�V
void Menu::Update(){
	if (CheckHitKey(KEY_INPUT_G) != 0){//G�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Game);//�V�[�����Q�[����ʂɕύX
	}
	if (CheckHitKey(KEY_INPUT_C) != 0){//C�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Config);//�V�[����ݒ��ʂɕύX
	}
	if (CheckHitKey(KEY_INPUT_M) != 0){//M�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Music);//�V�[�������Q�[��ʂɕύX
	}
	if (CheckHitKey(KEY_INPUT_S) != 0){//S�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_SongSelect);//�V�[�����ȑI����ʂɕύX
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

//�`��
void Menu::Draw(){
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	//DrawString(0, 0, "���j���[��ʂł��B", GetColor(255, 255, 255));
	//DrawString(0, 20, "G�L�[�������ƃQ�[����ʂɐi�݂܂��B", GetColor(255, 255, 255));
	//DrawString(0, 40, "C�L�[�������Ɓ@�ݒ��ʂɐi�݂܂��B", GetColor(255, 255, 255));
	//DrawString(0, 60, "M�L�[�������Ɖ��Q�[��ʂɐi�݂܂��B", GetColor(255, 255, 255));
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