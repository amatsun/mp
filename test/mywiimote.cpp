#include "wiimote.h"
#include "mywiimote.h"
#include <math.h>

struct wiimote *cWiiRemote;
struct wiimote *wi2;

void wiiinit()
{
	int t = 0;
	cWiiRemote = new wiimote();
	wi2 = new wiimote();
	// 接続開始
	//for (t = 0; t<4; t++){
	while (!cWiiRemote->Connect(wiimote::FIRST_AVAILABLE)) Sleep(1);
	//while (!wi2->Connect(wiimote::FIRST_AVAILABLE)) Sleep(1);
	//Sleep(1000);

	//}
	// ボタン, 加速度, 赤外線センサ取得用
	cWiiRemote->SetReportType(wiimote::IN_BUTTONS_ACCEL_IR);
	//if (t == 4) return 0;
	//return 1;
}

 int wiidel()
 {
 // 接続を終了
 if (cWiiRemote){
 cWiiRemote->Disconnect();
 delete cWiiRemote;

}
 return 1;
 }


 void wiirumble(bool sw)
 {
 cWiiRemote->SetRumble(sw);
 }
 void wiibutton(WIISTATE &Wiistate)
 {
	 if (cWiiRemote->Button.One()) Wiistate.Button[WiiKeyNum::KEY1]++;
	 else Wiistate.Button[WiiKeyNum::KEY1] = -(Wiistate.Button[WiiKeyNum::KEY1] > 0);
	 if (cWiiRemote->Button.Two()) Wiistate.Button[WiiKeyNum::KEY2]++;
	 else Wiistate.Button[WiiKeyNum::KEY2] = -(Wiistate.Button[WiiKeyNum::KEY2] > 0);

	 if (cWiiRemote->Button.A()) Wiistate.Button[WiiKeyNum::A]++;
	 else Wiistate.Button[WiiKeyNum::A] = -(Wiistate.Button[WiiKeyNum::A] > 0);
	 if (cWiiRemote->Button.B()) Wiistate.Button[WiiKeyNum::B]++;
	 else Wiistate.Button[WiiKeyNum::B] = -(Wiistate.Button[WiiKeyNum::B] > 0);

	 if (cWiiRemote->Button.Minus()) Wiistate.Button[WiiKeyNum::MINUS]++;
	 else Wiistate.Button[WiiKeyNum::MINUS] = -(Wiistate.Button[WiiKeyNum::MINUS] > 0);
	 if (cWiiRemote->Button.Plus()) Wiistate.Button[WiiKeyNum::PLUS]++;
	 else Wiistate.Button[WiiKeyNum::PLUS] = -(Wiistate.Button[WiiKeyNum::PLUS] > 0);
	 if (cWiiRemote->Button.Home()) Wiistate.Button[WiiKeyNum::HOME]++;
	 else Wiistate.Button[WiiKeyNum::HOME] = -(Wiistate.Button[WiiKeyNum::HOME] > 0);

	 if (cWiiRemote->Button.Up()) Wiistate.Button[WiiKeyNum::UP]++;
	 else Wiistate.Button[WiiKeyNum::UP] = -(Wiistate.Button[WiiKeyNum::UP] > 0);
	 if (cWiiRemote->Button.Down()) Wiistate.Button[WiiKeyNum::DOWN]++;
	 else Wiistate.Button[WiiKeyNum::DOWN] = -(Wiistate.Button[WiiKeyNum::DOWN] > 0);
	 if (cWiiRemote->Button.Right()) Wiistate.Button[WiiKeyNum::RIGHT]++;
	 else Wiistate.Button[WiiKeyNum::RIGHT] = -(Wiistate.Button[WiiKeyNum::RIGHT] > 0);
	 if (cWiiRemote->Button.Left()) Wiistate.Button[WiiKeyNum::LEFT]++;
	 else Wiistate.Button[WiiKeyNum::LEFT] = -(Wiistate.Button[WiiKeyNum::LEFT] > 0);
 }
 void getwiistate(WIISTATE &Wiistate)
 {
	 if (cWiiRemote->RefreshState() != NO_CHANGE) wiibutton(Wiistate); // ボタンの状態取得
	 Wiistate.BatteryPercent = (char)cWiiRemote->BatteryPercent; // バッテリ残量取得
	 // 加速度センサのデータ取得
	 Wiistate.Acceleration.X = cWiiRemote->Acceleration.X; // x 座標
	 Wiistate.Acceleration.Y = cWiiRemote->Acceleration.Y; // y 座標
	 Wiistate.Acceleration.Z = cWiiRemote->Acceleration.Z; // z 座標
	 Wiistate.Acceleration.ABS = sqrt(Wiistate.Acceleration.X*Wiistate.Acceleration.X + Wiistate.Acceleration.Y*Wiistate.Acceleration.Y	 + Wiistate.Acceleration.Z*Wiistate.Acceleration.Z);
	 // 赤外線センサのデータ取得
	 for (int t = 0; t < 4; t++){
		 if (Wiistate.Ir[t].bVisible = cWiiRemote->IR.Dot[t].bVisible){
			 // L E D がセンサで捕らえられていれば
			 Wiistate.Ir[t].Size = cWiiRemote->IR.Dot[t].Size; // L E D の強さ
			 Wiistate.Ir[t].X = cWiiRemote->IR.Dot[t].X; // x 座標
			 Wiistate.Ir[t].Y = cWiiRemote->IR.Dot[t].Y; // y 座標

			 Wiistate.Ir[t].RawX = cWiiRemote->IR.Dot[t].RawX; // 生データX
			 Wiistate.Ir[t].RawY = cWiiRemote->IR.Dot[t].RawY; // 生データY

		 }

	 }
	 wiirumble(Wiistate.RumbleSwitch); // 振動を設定
	 cWiiRemote->SetLEDs((BYTE)Wiistate.LEDSwitch); // L E D を設定
 }
