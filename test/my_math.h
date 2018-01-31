#pragma once
#include <stdlib.h>
#include <string.h>
#include <math.h>

//char型を第１引数から第２引数にコピーする
void copy(char*,char*);

//二つの数字をn分割したときのi番目の数字を返す 第１引数から数えた数
int div_2num(int, int, int, int);

//二つの座標からdlだけ第１引数の先端の座標から進んだ座標を返す 
//第３引数で0ならx座標を,1ならy座標を返す
//第１引数には４つの座標が格納されている必要がある
double go_dl_by2num(int*, float, int);