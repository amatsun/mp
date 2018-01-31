#pragma once

#include "BaseScene.h"
#include "Clicker.h"


extern myw_buf wiibuf[2], oldwiibuf[2];

//���j���[��ʃN���X
class Menu : public BaseScene {

public:
	Menu(ISceneChanger* changer);
	void Initialize() override;    //�������������I�[�o�[���C�h�B
	void Finalize() override;        //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
	void Sound() override;
	RectClicker* ToSongSelect;
	int TSSIHandle, TSSSHandle;
	CircleClicker* ToConfig;
	int TCIHandle, TCSHandle;
	int scope;
	int mskahandle, commenthandle, stringhandle;
	int backhandle;
};