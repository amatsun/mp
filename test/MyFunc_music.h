#pragma once

#include <DxLib.h>

#include <math.h>

#include "my_wii.h"

#include "my_math.h"

// DXの画面は場の設定 左上が原点,右にx軸,下にy軸が伸びている
#define MAX_X 640
#define MAX_Y 480

#define FPS 30

// ハンドルの総数 いろいろ確定したらぴったりの値にする
#define IM_MAX 100
#define SO_MAX 100

//ノーツの処理数の上限 フレームごとにこの数だけ出現、判定、描画などをやる
//処理が重ければ減少させる
#define loadnote 30

#define PI 3.141592654

//音声ハンドル用の値 ノーツ関係はsetsound_noteのため５刻みにしておく
#define signote 10
#define lnote 15
#define slinote 20
#define bullet 0

//モードの設定値 今のところマイクラだけ
#define MINECRAFT 0

//画面を４つに分割したときのそれぞれの中心座標
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

//判定の設定
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

// 判定のms幅
#define pd 33
#define gd 40
#define nd 50
#define bd 60

// ロングノーツの間の間隔
#define MAX_LENGTH 10

//特技倍率　スコアが物足りないならこれで調整
#define EXRATE 1.4

// ノーツの情報をまとめたもの 
// 譜面のファイルをこれに収められるような形式にする
class NoteInfo{
public:
	__int8 type; //single long slide
	__int8 destiny; //ノーツが４つのエリアのどこに向かうか
	__int8 destiny2;//long slideの場合のみ 終点のエリアの番号 longではdestinyと一致
	__int8 viewflag; // 1 0 -1
	int maketime; //出現するタイム
	int judgetime; //判定タイム
	int judgetime2; //long slide の終点 
	int allowjudge1, allowjudge2;//ジャッジ可能かどうかの区間設定 この値の分前後に判定幅がある
	__int8 judgeflag1, judgeflag2;//judge可能かどうか 1:active 0:negative -1:waiting
	__int8 result1, result2;//このノーツの判定結果の格納 これを元にコンボ数、スコアの更新を行う
	int handle;//描画用のハンドル
	int bloodhandle;//血痕のハンドル
	float deg;//血痕の描画角度
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

// 判定に必要なものをまとめたもの
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

//描画のためのノーツの判定からのカウント
typedef struct Count{
	unsigned __int8 type; //ノーツの種類
	__int16 count; //ノーツをたたいてからのカウント
};

//ホールド中の情報を格納
typedef struct holdInfo{
	__int8 type;//sli or l note
	//__int8 wr;//0 or 1 どちらのリモコンか  配列番号に対応
	__int16 number;//ノーツ番号
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

// ノーツの種類と判定から鳴らす音のハンドルを決定する
int setsound_note(int, int);

//ハンドルの値から鳴らす音を決める なくてもよい(わかりやすくするため) 重ければ削ってみる
int myplaysound(int, int*);

// 入力タイム(itime)と目標タイム(dtime)から判定を返す それぞれフレーム単位にするつもり
char judgenote(int, int, char);

//ノーツと現在のフレーム数からノーツを描画するべき位置を返す関数 要見直し
//void calc_note_point(NoteInfo, int,int*);
void calc_note_point(int* X, int* Y, int _frame, int* val, __int8 _destiny, int _maketime, int _judgetime);//singlenote
void calc_note_point(int* X, int* Y, int _frame, int* val, __int8 _destiny, int _maketime, int _judgetime, int _judgetime2);//longnote
void calc_note_point(int* X, int* Y, int _frame, int* val, __int8 _destiny, __int8 _destiny2, int _maketime, int _judgetime, int _judgetime2);//slidenote

int areajudge(myw_buf* wiibuf, int* X, int* Y);

void SigEfcSet(unsigned __int16, Effect*, myw_buf, int, int);

void ComboUpdate(__int8 judge, unsigned __int16 *combo, unsigned __int16 *maxcombo);

void ScoreUpdate(float basevalue, __int8 judge, unsigned __int16 combo, int* score, unsigned __int16 notenum);

float ComboRate(unsigned __int16 combo, unsigned __int16 notenum);