#pragma once
#include <stdlib.h>
#include <string.h>
#include <math.h>

//char�^���P���������Q�����ɃR�s�[����
void copy(char*,char*);

//��̐�����n���������Ƃ���i�Ԗڂ̐�����Ԃ� ��P�������琔������
int div_2num(int, int, int, int);

//��̍��W����dl������P�����̐�[�̍��W����i�񂾍��W��Ԃ� 
//��R������0�Ȃ�x���W��,1�Ȃ�y���W��Ԃ�
//��P�����ɂ͂S�̍��W���i�[����Ă���K�v������
double go_dl_by2num(int*, float, int);