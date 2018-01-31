#pragma once

#include "BaseScene.h"
#include "Clicker.h"
#include "SongBank.h"
#include "AndroidLike.h"

extern myw_buf wiibuf[2], oldwiibuf[2];
extern SongName SelectedSong;

//���j���[��ʃN���X
class SongSelect : public BaseScene {

public:
	SongSelect(ISceneChanger* changer);
	void Initialize() override;    //�������������I�[�o�[���C�h�B
	void Finalize() override;        //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
	void Sound() override;
	RectClicker *Tulip, *Ontology;
	int SsIHandle[2], SsSHandle[2];
	CircleClicker* Back;
	int BIHandle, BSHandle;
	int scope;
	CMenuBack* MenuBack;
};