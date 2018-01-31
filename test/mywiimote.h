#pragma once

 // �{�^���p�񋓑�
 enum WiiKeyNum{
	 KEY1 = 0,
	 KEY2,
	 A,
	 B,
	 MINUS,
	 PLUS,
	 HOME,
	 UP,
	 DOWN,
	 RIGHT,
	 LEFT,
	 KEYMAX
	
};

 // W i i �R���g���[���p��ԕۑ��\���̂̐錾
 struct WIISTATE{
	 int Button[WiiKeyNum::KEYMAX];
	 struct accel{
		 float X;
		 float Y;
		 float Z;
		 float ABS;
		
	}Acceleration;
	 struct ir{
		 bool bVisible;
		 int Size;
		 float X;
		 float Y;
		 int RawX;
		 int RawY;
		
	}Ir[4];
		 char BatteryPercent;
		 bool RumbleSwitch;
		 char LEDSwitch;
		
};
 // �֐��̃G�N�X�^�[��
 extern void wiiinit();
 extern int wiidel();
 extern void getwiistate(WIISTATE &wiistate);