class DesEfc{
public:
	__int8 valid;
	__int16 x[16];
	__int16 y[16];
	int handle[16];
	float Sx[16], Sy[16];
	__int16 G[16];
	__int16 theta[16];
	__int16 w[16];
	 unsigned __int8 Bright;
	__int8 judge;
	//unsigned __int16 frame;
//public:
	DesEfc();
	~DesEfc();
	void Set(__int16 _x,__int16 _y,int* _iHandle, __int8 _judge);
	void update();
	void draw();
	__int8 viewvalid();
	void SetValid(char _valid);
	int Handle(int i);
};

void ScoreToBoard(int score, __int8* scoreboard);
void ComboToBoard(unsigned __int16 combo, __int8* comboboard);