#pragma once

#include <DxLib.h>

#include <math.h>

#include "my_wii.h"

#include "my_math.h"

// DX�̉�ʂ͏�̐ݒ� ���オ���_,�E��x��,����y�����L�тĂ���
#define MAX_X 640
#define MAX_Y 480

#define FPS 30

// �n���h���̑��� ���낢��m�肵����҂�����̒l�ɂ���
#define IM_MAX 100
#define SO_MAX 100

//�m�[�c�̏������̏�� �t���[�����Ƃɂ��̐������o���A����A�`��Ȃǂ����
//�������d����Ό���������
#define loadnote 30

#define PI 3.141592654

//�����n���h���p�̒l �m�[�c�֌W��setsound_note�̂��߂T���݂ɂ��Ă���
#define signote 10
#define lnote 15
#define slinote 20
#define bullet 0

//���[�h�̐ݒ�l ���̂Ƃ���}�C�N������
#define MINECRAFT 0

//��ʂ��S�ɕ��������Ƃ��̂��ꂼ��̒��S���W
#define LU_X 100
#define LU_Y 80
#define LD_X 100
#define LD_Y 400
#define RU_X 540
#define RU_Y 80
#define RD_X 540
#define RD_Y 400
#define C_X 320
#define C_Y 240

#define LU 0
#define LD 1
#define RU 2
#define RD 3
#define M 4

//����̐ݒ�
#define perfect 30
#define great 31
#define nice 32
#define bad 33
#define miss 34

//imagehandle
#define COMBO 50
#define SCOPE1 51
#define SCOPE2 52
#define BLOOD 53
#define IMPACT 54
#define FIREFLOWER 55
#define BLACK 56
#define JUDGEAREA 57//57~60
#define BACK 61
#define MAXCOMBO 62

// �����ms��
#define pd 33
#define gd 40
#define nd 50
#define bd 60

// �����O�m�[�c�̊Ԃ̊Ԋu
#define MAX_LENGTH 10

//���Z�{���@�X�R�A��������Ȃ��Ȃ炱��Œ���
#define EXRATE 1.4

// �m�[�c�̏����܂Ƃ߂����� 
// ���ʂ̃t�@�C��������Ɏ��߂���悤�Ȍ`���ɂ���
class NoteInfo{
public:
	__int8 type; //single long slide
	__int8 destiny; //�m�[�c���S�̃G���A�̂ǂ��Ɍ�������
	__int8 destiny2;//long slide�̏ꍇ�̂� �I�_�̃G���A�̔ԍ� long�ł�destiny�ƈ�v
	__int8 viewflag; // 1 0 -1
	int maketime; //�o������^�C��
	int judgetime; //����^�C��
	int judgetime2; //long slide �̏I�_ 
	int allowjudge1, allowjudge2;//�W���b�W�\���ǂ����̋�Ԑݒ� ���̒l�̕��O��ɔ��蕝������
	__int8 judgeflag1, judgeflag2;//judge�\���ǂ��� 1:active 0:negative -1:waiting
	__int8 result1, result2;//���̃m�[�c�̔��茋�ʂ̊i�[ ��������ɃR���{���A�X�R�A�̍X�V���s��
	int handle;//�`��p�̃n���h��
	int bloodhandle;//�����̃n���h��
	float deg;//�����̕`��p�x
	int vx, vy;
	unsigned int oldframe;
	unsigned __int16 counter;
	NoteInfo();
	~NoteInfo();
	void SetNote(int _maketime, int _judgetime, int _allowjudge1, __int8 _destiny, int _handle, int _bloodhandle);
	void SetNote(int _maketime, int _judgetime, int _judgetime2, int _allowjudge1, int _allowjudge2, __int8 _destiny, int _handle, int _bloodhandle);
	void SetNote(int _maketime, int _judgetime, int _judgetime2, int _allowjudge1, int _allowjudge2, __int8 _destiny, __int8 _destiny2, int _handle, int _bloodhandle);
	void update(int _frame, unsigned __int16 *combo, unsigned __int16 *maxcombo);
	void draw(int* X, int* Y, int _frame);
	void damageddraw(int* X, int* Y, int _frame);
	__int8 rview();
	__int8 jview(int s);
	int holdjudge(int* X, int* Y, int _frame, myw_buf* wiibuf);
};

// ����ɕK�v�Ȃ��̂��܂Ƃ߂�����
class Judge{
private:
	unsigned __int16 counter;
	__int8 view;
	unsigned __int16 jresult;
	int handle;
public:
	Judge();
	void SetJudge(int _handle);
	~Judge();
	void draw();
	__int8 rview();
	void setview(__int8 sview);
};

//�`��̂��߂̃m�[�c�̔��肩��̃J�E���g
typedef struct Count{
	unsigned __int8 type; //�m�[�c�̎��
	__int16 count; //�m�[�c���������Ă���̃J�E���g
};

//�z�[���h���̏����i�[
typedef struct holdInfo{
	__int8 type;//sli or l note
	//__int8 wr;//0 or 1 �ǂ���̃����R����  �z��ԍ��ɑΉ�
	__int16 number;//�m�[�c�ԍ�
};

class Effect
{
private:
	__int8 view;
	__int8 etype;
	int ebtype;
	int eframe;
	int bloodhandle;
	float deg, deg2;
	int x, y;
	unsigned int counter;
public:
	Effect();
	void SetEffect(__int8 type, int frame, int btype, int x, int y, int _bloodhandle);
	void SetEffect(__int8 type, int frame, int btype, int _bloodhandle);
	~Effect();
	void setview(__int8 sview);
	__int8 rview();
	__int8 rtype();
	void drawEffect(int frame);
	void drawEffect(int frame, myw_buf* wiibuf);
};

// �m�[�c�̎�ނƔ��肩��炷���̃n���h�������肷��
int setsound_note(int, int);

//�n���h���̒l����炷�������߂� �Ȃ��Ă��悢(�킩��₷�����邽��) �d����΍���Ă݂�
int myplaysound(int, int*);

// ���̓^�C��(itime)�ƖڕW�^�C��(dtime)���画���Ԃ� ���ꂼ��t���[���P�ʂɂ������
char judgenote(int, int, char);

//�m�[�c�ƌ��݂̃t���[��������m�[�c��`�悷��ׂ��ʒu��Ԃ��֐� �v������
//void calc_note_point(NoteInfo, int,int*);
void calc_note_point(int* X, int* Y, int _frame, int* val, __int8 _destiny, int _maketime, int _judgetime);//singlenote
void calc_note_point(int* X, int* Y, int _frame, int* val, __int8 _destiny, int _maketime, int _judgetime, int _judgetime2);//longnote
void calc_note_point(int* X, int* Y, int _frame, int* val, __int8 _destiny, __int8 _destiny2, int _maketime, int _judgetime, int _judgetime2);//slidenote

int areajudge(myw_buf* wiibuf, int* X, int* Y);

void SigEfcSet(unsigned __int16, Effect*, myw_buf, int, int);

void ComboUpdate(__int8 judge, unsigned __int16 *combo, unsigned __int16 *maxcombo);

void ScoreUpdate(float basevalue, __int8 judge, unsigned __int16 combo, int* score, unsigned __int16 notenum);

float ComboRate(unsigned __int16 combo, unsigned __int16 notenum);