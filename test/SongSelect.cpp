#include "SongSelect.h"
#include "DxLib.h"

SongSelect::SongSelect(ISceneChanger* changer) : BaseScene(changer) {
}

//������
void SongSelect::Initialize(){
	mImageHandle = LoadGraph("image/Scene_Menu.png");    //�摜�̃��[�h
	SsIHandle[TULIP] = LoadGraph("image/jacket/Tulip_mod.jpg");
	SsSHandle[TULIP] = LoadSoundMem("sound/���Ԃ��A�����𕷂���.wav");
	Tulip = new RectClicker(110, 110, 150, 150, SsIHandle[TULIP], SsSHandle[TULIP], eScene_Music);
	SsIHandle[ONTOLOGY] = LoadGraph("image/jacket/Ontology_mod.jpg");
	SsSHandle[ONTOLOGY] = LoadSoundMem("sound/���Ԃ��A�����𕷂���.wav");
	Ontology = new RectClicker(300, 110, 150, 150, SsIHandle[ONTOLOGY], SsSHandle[ONTOLOGY], eScene_Music);

	BIHandle = LoadGraph("image/back.png");
	BSHandle = LoadSoundMem("sound/�ǂ��֍s�����Ƃ����̂��ˁH.mp3");
	Back = new CircleClicker(80, 420, 50, BIHandle, BSHandle, eScene_Menu);
	scope = LoadGraph("image/scope.png");
	MenuBack = new CMenuBack();
}

//�X�V
void SongSelect::Update(){
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0){//Esc�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Music);//�V�[�������j���[��ʂɕύX
		SelectedSong = Debug;
	}
	if (CheckHitKey(KEY_INPUT_M) != 0){//M�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Music);//�V�[�������j���[��ʂɕύX
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

//�`��
void SongSelect::Draw(){
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
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