#pragma once

#include "BaseScene.h"
#include "MyFunc_cv.h"
#include "MyFunc_music.h"
#include "my_wii.h"
#include "wiimote.h"
#include "my_effect.h"
#include "SongBank.h"

extern wiimote remote[2];
extern myw_buf wiibuf[2];
extern myw_buf oldwiibuf[2];
extern SongName SelectedSong;

// ���j���[��ʃN���X
class Music : public BaseScene{

protected:
	unsigned int frame;
	unsigned int counter;
	__int8 mode;
	unsigned int Cr;
	Judge judge;
	int viewnote[1][4];
	int i, j, k, l;
	__int8 stopflag;
	char oldspace[256];
	char nowspace[256];
	__int8 init;
	NoteInfo mynote;
	int X[4], Y[4];
	int VX[4], VY[4];
	int OX[4], OY[4];
	char f[256];
	char g[256];
	__int16 dl;
	int x, y;
	unsigned __int16 notenum;
	char num;
	double dx, dy;
	bool exec;
	FILE *fp, *sm_fp;
	__int8 buft, bufd1, bufd2;
	int bufj1, bufj2, bufa1, bufa2;
	int bufom, bufoj, om;// maketime, judgetime�@���ꂼ��̃I�t�Z�b�g
	NoteInfo *note;
	NoteInfo *dn;
	int starter;
	__int8 dtx, dty;
	wiimote_sample gun_sample;
	holdInfo HInfo[2];
	Effect effect[20];//�P���ł��p
	Effect heffect[2];//�z�[���h�p
	bool finished;
	__int8 guncount[2];
	int notedivhandle[3][16];
	//int notedivhandle1[16];
	//int notedivhandle2[16];
	DesEfc deffect[10];
	int score;
	unsigned __int16 combo, maxcombo;
	__int8 scoreboard[7], comboboard[3];
	float basevalue;//�Ȃɂ���Č��܂�X�R�A�v�Z�̂��߂̊�b�l
	__int8 resultbuf;
	int Ar;
	unsigned __int8 ecount,decount;
	unsigned __int16 c;
	int playfinish;

	/*
	IplImage image;
	cv::Mat im;
	int GrHandle;
	BASEIMAGE BaseImage;
	cv::VideoCapture cap;*/

	//�L�[�{�[�h����,����,�摜�n���h�� �O���[�o���ϐ����g�����Ƃɂ��Ă���
	//�t�@�C�����������Ȃ炢��Ȃ�����
	char buf[256];
	int sHandle[SO_MAX];
	int iHandle[IM_MAX];

	//�R���{���̉摜�̃n���h�� ���������̂܂ܕ`�悾�Əd���\��������̂�
	//�ő�X�X�X�R���{
	int image_number[10];

public:
	Music(ISceneChanger* changer);
	void Initialize() override;   //�������������I�[�o�[���C�h�B
	void Finalize() override ;        //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
	void Sound() override;

};