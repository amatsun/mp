#include "my_wii.h"
#include "DxLib.h"

#include "SceneMgr.h"
#include "wiimote.h"
#include <opencv2/core.hpp>    

#include "SongBank.h"

#include <opencv2/highgui.hpp> 
#include <opencv2/imgproc.hpp>
//#include <opencv/cv.h>
//#include <opencv/highgui.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/objdetect.hpp>

#include <ctype.h>

#include <vector>



//#pragma comment(lib, "wiiuse.lib")

//#include "wiiuse.h"

#include <iostream>
//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define PI 3.14159265
//osc


myw_buf wiibuf[2], oldwiibuf[2];

wiimote remote[2];

SongName SelectedSong;

__int8 n_w;

int oldIR[2][10][2];


void UpdateWii(){

	memcpy(oldwiibuf, wiibuf, sizeof(myw_buf) * 2);

	int i;
	float val_x[2], val_y[2];
	for (i = 0; i < 2; i++){
		remote[i].RefreshState();
		wiibuf[i].A = remote[i].Button.A();
		wiibuf[i].B = remote[i].Button.B();
		if (n_w == i){
			wiibuf[i].N_C = remote[i].Nunchuk.C;
			wiibuf[i].N_Z = remote[i].Nunchuk.Z;
			wiibuf[i].Stick_X = remote[i].Nunchuk.Joystick.X;
			wiibuf[i].Stick_Y = remote[i].Nunchuk.Joystick.Y;
		}
		wiibuf[i].Pitch = (int)remote[i].Acceleration.Orientation.Pitch;
		wiibuf[i].Roll = (int)remote[i].Acceleration.Orientation.Roll;
		//remote.Acceleration.Orientation.X
		//remote.Acceleration.Orientation.Y
		//remote.Acceleration.Orientation.Z
		int count = 0;
		int irflag1 = 0, irflag2 = 0;
		for (unsigned index = 0; index < 4; index++){
			wiimote_state::ir::dot &dot = remote[i].IR.Dot[index];
			if (dot.bVisible) {
				count++;
				if (!irflag1){
					irflag1 = index + 1;
				}
				else if (!irflag2){
					irflag2 = index + 1;
				}
			}
		}
		if (count >= 2){
			int avgx = 0, avgy = 0;
			int x, y;
			float s, c;
			s = sin(wiibuf[i].Roll*PI / 180.0);
			c = cos(wiibuf[i].Roll*PI / 180.0);
			for (unsigned index = 0; index < 4; index++){
				wiimote_state::ir::dot &dot = remote[i].IR.Dot[index];
				if (!dot.bVisible){
					continue;
				}
				x = dot.RawX - 512;
				y = dot.RawY - 384;
				dot.X = c*x + (-s*y);
				dot.Y = s*x + c*y;
				dot.X += 512;
				dot.Y += 384;
				avgx += dot.X;
				avgy += dot.Y;
				break;
			}	
			avgx /= count;
			avgy /= count;
			if (ir_correct_for_bounds(&avgx, &avgy, IR_OFFSET_X, IR_OFFSET_Y)){
				ir_convert_to_vres(&avgx, &avgy, WM_ASPECT_16_9_X, WM_ASPECT_16_9_Y);
				wiibuf[i].IR_X = -1 * avgx + 659;
				wiibuf[i].IR_Y = avgy;
			}else{
			wiibuf[i].IR_X = oldwiibuf[i].IR_X;
			wiibuf[i].IR_Y = oldwiibuf[i].IR_Y;
		}
		}
		else if (count == 1){
			int x, y;
			float s, c;
			s = sin(wiibuf[i].Roll*PI / 180.0);
			c = cos(wiibuf[i].Roll*PI / 180.0);
			for (unsigned index = 0; index < 4; index++){
				wiimote_state::ir::dot &dot = remote[i].IR.Dot[index];
				if (!dot.bVisible){
					continue;
				}
				x = dot.RawX - 512;
				y = dot.RawY - 384;
				dot.X = c*x + (-s*y);
				dot.Y = s*x + c*y;
				dot.X += 512;
				dot.Y += 384;
				wiibuf[i].IR_X = dot.X;
				wiibuf[i].IR_Y = dot.Y;
				ir_convert_to_vres(&wiibuf[i].IR_X, &wiibuf[i].IR_Y, WM_ASPECT_16_9_X, WM_ASPECT_16_9_Y);
				wiibuf[i].IR_X = -1 * wiibuf[i].IR_X + 659;
				break;
			}
		}
		else{
			wiibuf[i].IR_X = oldwiibuf[i].IR_X;
			wiibuf[i].IR_Y = oldwiibuf[i].IR_Y;
		}
		for (int j = 0; j < 9; j++){
			oldIR[i][j + 1][0] = oldIR[i][j][0];
			oldIR[i][j + 1][1] = oldIR[i][j][1];
		}
		oldIR[i][0][0] = wiibuf[i].IR_X;
		oldIR[i][0][1] = wiibuf[i].IR_Y;
		int x = 0, y = 0;
		for (int j = 0; j < 10; j++){
			x += oldIR[i][j][0];
			y += oldIR[i][j][1];
		}
		x /= 10; y /= 10;
		wiibuf[i].DX_X = (x + 182) / 1024.0 * 1280 - 640;
		wiibuf[i].DX_Y = (y + 199) / 768.0 * 960 - 480;
		//DrawFormatString(0, 240, GetColor(255, 255, 255), "%d %d %d", wiibuf[0].DX_X, wiibuf[0].DX_Y, count);
	}
	//DrawFormatString(0, 240, GetColor(255, 255, 255), "%d %d", wiibuf[0].IR_X, wiibuf[0].IR_Y);
}

class Fps{
	int mStartTime;         //測定開始時刻
	int mCount;             //カウンタ
	float mFps;             //fps
	static const int N = 60;//平均を取るサンプル数
	static const int FPS = 30;	//設定したFPS

public:
	Fps(){
		mStartTime = 0;
		mCount = 0;
		mFps = 0;
	}

	bool Update(){
		if (mCount == 0){ //1フレーム目なら時刻を記憶
			mStartTime = GetNowCount();
		}
		if (mCount == N){ //60フレーム目なら平均を計算する
			int t = GetNowCount();
			mFps = 1000.f / ((t - mStartTime) / (float)N);
			mCount = 0;
			mStartTime = t;
		}
		mCount++;
		return true;
	}

	void Draw(){
		DrawFormatString(0, 450, GetColor(255, 0, 0), "%.1f", mFps);
	}

	void Wait(){
		int tookTime = GetNowCount() - mStartTime;	//かかった時間
		int waitTime = mCount * 1000 / FPS - tookTime;	//待つべき時間
		if (waitTime > 0){
			Sleep(waitTime);	//待機
		}
	}
};


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
	char s[256];
	
	
	while (!remote[0].Connect(wiimote::FIRST_AVAILABLE));
	while (!remote[1].Connect(wiimote::FIRST_AVAILABLE));
	if (remote[0].NunchukConnected()){
		remote[0].SetReportType(wiimote::IN_BUTTONS_ACCEL_IR_EXT);
		remote[1].SetReportType(wiimote::IN_BUTTONS_ACCEL_IR);
		remote[0].SetLEDs((BYTE)(1 << 0));
		remote[1].SetLEDs((BYTE)(1 << 1));
		n_w = 0;
	}
	else if (remote[1].NunchukConnected()){
		remote[0].SetReportType(wiimote::IN_BUTTONS_ACCEL_IR);
		remote[1].SetReportType(wiimote::IN_BUTTONS_ACCEL_IR_EXT);
		remote[0].SetLEDs((BYTE)(1 << 1));
		remote[1].SetLEDs((BYTE)(1 << 0));
		n_w = 1;
	}
	else{
		return -1;
	}
	
	

	ChangeWindowMode(TRUE), DxLib_Init() ,SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

	SceneMgr sceneMgr;
	sceneMgr.Initialize();

	/*
	//CvCapture *capture;
	IplImage image;
	cv::Mat im;
	//im = cv::imread("image/test.jpg", -1);
	int GrHandle;
	BASEIMAGE BaseImage;
	
	// カメラからのビデオキャプチャを初期化する
	//capture = cvCreateCameraCapture(-1);
	cv::VideoCapture cap(0);

	
	// BASEIMAGE 構造体を０で初期化
	memset(&BaseImage, 0, sizeof(BASEIMAGE));

	// カラーフォーマットは変化しないので最初に設定
	CreateFullColorData(&BaseImage.ColorData);
	
	// ミップマップではないので０
	BaseImage.MipMapCount = 0;

	// 空のグラフィックハンドルの値を初期化
	GrHandle = -1;
	
	//顔検出器
	
	
	std::vector<cv::Rect> faces;
	cv::CascadeClassifier cascade;
	if (cascade.load("lbpcascade_frontalface.xml") == NULL){
		return -1;
	}
	
	IplImage *src_gray = 0;
	const char *cascade_name = "haarcascade_frontalface_default.xml";
	CvHaarClassifierCascade *cascade = 0;
	CvMemStorage *storage = 0;
	CvSeq *faces;
	cascade = (CvHaarClassifierCascade *)cvLoad("haarcascade_frontalface_default.xml", 0, 0, 0);
	static CvScalar colors[] = {
		{ { 0, 0, 255 } }, { { 0, 128, 255 } },
		{ { 0, 255, 255 } }, { { 0, 255, 0 } },
		{ { 255, 128, 0 } }, { { 255, 255, 0 } },
		{ { 255, 0, 0 } }, { { 255, 0, 255 } }
	};
	*/

	Fps fps;

	
	
	while (CheckHitKey(KEY_INPUT_Q)==0 && ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0){//画面更新 & メッセージ処理 & 画面消去
		
		
		/*
		if (remote[n_w].ExtensionType == wiimote_state::NONE){

			while (!remote[n_w].ExtensionType == wiimote_state::NUNCHUK&&ScreenFlip() && ClearDrawScreen()){
				DrawString(320, 240, "ヌンチャクを差し込んでください", (unsigned int)GetColor(255, 0, 0));
			}
			for (int i = 0; i < 3; i++){
				//sprintf(s, "%d", i);
				DrawString(320, 240, s, (unsigned int)GetColor(255, 0, 0));
				Sleep(1000);
			}
		}*/
		
		/*
		//image = cvQueryFrame(capture);
		cap >> im;
		cv::flip(im, im, 1);
		image = im;
		
		cascade.detectMultiScale(im, faces, 1.1, 2, 2);
		auto it = faces.begin();
		std::vector<cv::Rect>::const_iterator r = faces.begin();
		for (; r != faces.end(); r++){
			cv::Point center;
			int radius;
			double scale = 1.0;
			center.x = cv::saturate_cast<int>((r->x + r->width*0.5)*scale);
			center.y = cv::saturate_cast<int>((r->y + r->height*0.5)*scale);
			radius = cv::saturate_cast<int>((r->width + r->height)*0.25*scale);
			cv::circle(im, center, radius, cv::Scalar(80, 80, 255), 3, 8, 0);

		//cv::rectangle(im, it->tl(), it->br(), cv::Scalar(0, 255, 255), 2, 8, 0);
		}
		int x = faces.begin()->x;
		int y = faces.begin()->y;
		cv::Point x1(x - 1, y - 1), x2(x + 1, y + 1);
		cv::rectangle(im, x1, x2, cv::Scalar(0, 255, 255), 2, 8, 0);
		
		
		
		
		src_gray = cvCreateImage(cvGetSize(&image), IPL_DEPTH_8U, 1);
		storage = cvCreateMemStorage(0);
		cvClearMemStorage(storage);
		cvCvtColor(&image, src_gray, CV_BGR2GRAY);
		cvEqualizeHist(src_gray, src_gray);
		faces = cvHaarDetectObjects(src_gray, cascade, storage, 1.11, 4, 0, cvSize(40, 40));
				
		for (int i = 0; i < (faces ? faces->total : 0); i++) {
			CvRect *r = (CvRect *)cvGetSeqElem(faces, i);
			CvPoint center;
			int radius;
			center.x = cvRound(r->x + r->width * 0.5);
			center.y = cvRound(r->y + r->height * 0.5);
			radius = cvRound((r->width + r->height) * 0.25);
			cvCircle(&image, center, radius, colors[i % 8], 3, 8, 0);
		}
		

		BaseImage.GraphData = image.imageData;
		BaseImage.Width = image.width;
		BaseImage.Height = image.height;
		BaseImage.Pitch = image.widthStep;

		// グラフィックハンドルを作成しているかどうかで処理を分岐
		if (GrHandle == -1)
		{
			// 最初の場合はグラフィックハンドルの作成と映像の転送を一度に行う
			GrHandle = CreateGraphFromBaseImage(&BaseImage);
		}
		else
		{
			// ２回目以降はグラフィックハンドルへ映像を転送
			ReCreateGraphFromBaseImage(&BaseImage, GrHandle);
		}
		DrawGraph(0, 0, GrHandle, FALSE);
		
		*/
		

		UpdateWii();
		sceneMgr.Update();  //更新
		sceneMgr.Draw();    //描画
		sceneMgr.Sound();
		fps.Update();	//更新
		fps.Draw();		//描画
		fps.Wait();		//待機

	}
	//cvReleaseCapture(&capture);

	sceneMgr.Finalize();

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}

