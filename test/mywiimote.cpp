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
	// �ڑ��J�n
	//for (t = 0; t<4; t++){
	while (!cWiiRemote->Connect(wiimote::FIRST_AVAILABLE)) Sleep(1);
	//while (!wi2->Connect(wiimote::FIRST_AVAILABLE)) Sleep(1);
	//Sleep(1000);

	//}
	// �{�^��, �����x, �ԊO���Z���T�擾�p
	cWiiRemote->SetReportType(wiimote::IN_BUTTONS_ACCEL_IR);
	//if (t == 4) return 0;
	//return 1;
}

 int wiidel()
 {
 // �ڑ����I��
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
	 if (cWiiRemote->RefreshState() != NO_CHANGE) wiibutton(Wiistate); // �{�^���̏�Ԏ擾
	 Wiistate.BatteryPercent = (char)cWiiRemote->BatteryPercent; // �o�b�e���c�ʎ擾
	 // �����x�Z���T�̃f�[�^�擾
	 Wiistate.Acceleration.X = cWiiRemote->Acceleration.X; // x ���W
	 Wiistate.Acceleration.Y = cWiiRemote->Acceleration.Y; // y ���W
	 Wiistate.Acceleration.Z = cWiiRemote->Acceleration.Z; // z ���W
	 Wiistate.Acceleration.ABS = sqrt(Wiistate.Acceleration.X*Wiistate.Acceleration.X + Wiistate.Acceleration.Y*Wiistate.Acceleration.Y	 + Wiistate.Acceleration.Z*Wiistate.Acceleration.Z);
	 // �ԊO���Z���T�̃f�[�^�擾
	 for (int t = 0; t < 4; t++){
		 if (Wiistate.Ir[t].bVisible = cWiiRemote->IR.Dot[t].bVisible){
			 // L E D ���Z���T�ŕ߂炦���Ă����
			 Wiistate.Ir[t].Size = cWiiRemote->IR.Dot[t].Size; // L E D �̋���
			 Wiistate.Ir[t].X = cWiiRemote->IR.Dot[t].X; // x ���W
			 Wiistate.Ir[t].Y = cWiiRemote->IR.Dot[t].Y; // y ���W

			 Wiistate.Ir[t].RawX = cWiiRemote->IR.Dot[t].RawX; // ���f�[�^X
			 Wiistate.Ir[t].RawY = cWiiRemote->IR.Dot[t].RawY; // ���f�[�^Y

		 }

	 }
	 wiirumble(Wiistate.RumbleSwitch); // �U����ݒ�
	 cWiiRemote->SetLEDs((BYTE)Wiistate.LEDSwitch); // L E D ��ݒ�
 }
