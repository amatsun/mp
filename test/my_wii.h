#pragma once

#define WM_ASPECT_16_9_X 660
#define WM_ASPECT_16_9_Y 370
#define IR_OFFSET_X 0
#define IR_OFFSET_Y 115


typedef struct myw_buf{
	bool A;
	bool B;
	bool N_C;
	bool N_Z;
	//int Yaw;
	int Pitch;
	int Roll;
	float Stick_X;
	float Stick_Y;
	int IR_X;//-182~841
	int IR_Y;//-199~568
	__int16 DX_X;
	__int16 DX_Y;
};

static int ir_correct_for_bounds(int* x, int* y, int offset_x, int offset_y) {
	int x0, y0;
	int xs, ys;

	xs = WM_ASPECT_16_9_X;
	ys = WM_ASPECT_16_9_Y;

	x0 = ((1024 - xs) / 2) + offset_x;
	y0 = ((768 - ys) / 2) + offset_y;

	if ((*x >= x0)
		&& (*x <= (x0 + xs))
		&& (*y >= y0)
		&& (*y <= (y0 + ys)))
	{
		*x -= offset_x;
		*y -= offset_y;

		return 1;
	}

	return 0;
}

/*
static void fix_rotated_ir_dots(struct ir_dot_t* dot, float ang) {
	float s, c;
	int x, y;
	int i;

	if (!ang) {
		for (i = 0; i < 4; ++i) {
			dot[i].x = dot[i].rx;
			dot[i].y = dot[i].ry;
		}
		return;
	}

	s = sin(DEGREE_TO_RAD(ang));
	c = cos(DEGREE_TO_RAD(ang));

	*
	*	[ cos(theta)  -sin(theta) ][ ir->rx ]
	*	[ sin(theta)  cos(theta)  ][ ir->ry ]
	*

	for (i = 0; i < 4; ++i) {
		if (!dot[i].visible)
			continue;

		x = dot[i].rx - (1024 / 2);
		y = dot[i].ry - (768 / 2);

		dot[i].x = (c * x) + (-s * y);
		dot[i].y = (s * x) + (c * y);

		dot[i].x += (1024 / 2);
		dot[i].y += (768 / 2);
	}
}
*/
static void ir_convert_to_vres(int* x, int* y, int vx, int vy) {
	int xs, ys;

	xs = WM_ASPECT_16_9_X;
	ys = WM_ASPECT_16_9_Y;

	*x -= ((1024 - xs) / 2);
	*y -= ((768 - ys) / 2);

	*x = (*x / (float)xs) * vx;
	*y = (*y / (float)ys) * vy;
}

/*
float calc_yaw(struct ir_t* ir) {
	float x;

	x = ir->ax - 512;
	x = x * (ir->z / 1024.0f);

	return RAD_TO_DEGREE(atanf(x / ir->z));
}*/
/*
float ir_distance(struct ir_dot_t* dot) {
	int i1, i2;
	int xd, yd;

	for (i1 = 0; i1 < 4; ++i1)
		if (dot[i1].visible)
			break;
	if (i1 == 4)
		return 0.0f;

	for (i2 = i1 + 1; i2 < 4; ++i2)
		if (dot[i2].visible)
			break;
	if (i2 == 4)
		return 0.0f;

	xd = dot[i2].x - dot[i1].x;
	yd = dot[i2].y - dot[i1].y;

	return sqrt(xd*xd + yd*yd);
}*/