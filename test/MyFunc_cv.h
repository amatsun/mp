#pragma once

#include <opencv2/core.hpp>    

#include <opencv/cv.h>

#include <opencv2/highgui.hpp> 

//#include <ctype.h>

#include <iostream>

#define CV_R 0
#define CV_G 1
#define CV_B 2

// �e�X�g�֐��@Webcam�g���Ă悩�����I �����ɃL���v�`���摜�̕ۑ��@�\���ǉ�
int capcam(void);

int HSVtoRGB(int H, int S, int V, int val);//val:0,1,2
