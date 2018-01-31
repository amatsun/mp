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
//�Q�[����ʃN���X
class Game : public BaseScene {

protected:
	char f[256];
	

public:
	Game::Game(ISceneChanger* changer);
	void Initialize() override;    //�������������I�[�o�[���C�h�B
	//void Finalize() override;        //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
	void Sound() override;

};
