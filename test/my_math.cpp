#include "my_math.h"

void copy(char* now,char* old){
	int s = sizeof(now) / sizeof(char);
	for (int i = 0; i < s; i++){
		old[i] = now[i];
	}
}

int div_2num(int x1, int x2, int n, int i){
	int val;
	val = x1 + (x2 - x1)*i / (float)n;
	return val;
}

double go_dl_by2num(int* x, float length, int s){
	float dx = x[2] - x[0];
	float dy = x[3] - x[1];
	double val[2] = { 0 };
	double r;
	val[0] = length*dx / sqrt(pow(dx, 2) + pow(dy, 2));
	val[1] = length*dy / sqrt(pow(dx, 2) + pow(dy, 2));
	r = val[s];
	return r;
}