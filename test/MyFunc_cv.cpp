#include "MyFunc_cv.h"

int capcam(){
	cv::VideoCapture cap(0);
	if (!cap.isOpened()){
		return -1;
	}

	cv::Mat input_image;
	cv::Mat cap_image;
	cv::namedWindow("window1", 1);
	for (;;){
		cv::Mat frame;
		cap >> frame;
		input_image = frame;
		cap_image = frame;
		imshow("window1", input_image);
		if (cv::waitKey(30) == 's'){
			imwrite("image/test.jpg", cap_image);
		}
		else if (cv::waitKey(30) == 'q'){
			break;
		}
	}
	return 0;
}

int HSVtoRGB(int H, int S, int V,int val){
	int max, min;
	int r, g, b;
	max = V;
	min = max - (S / 255.0 * max);
	if (0 <= H && H <= 60){
		r = max; b = min;
		g = H / 60.0*(max - min) + min;
	}
	else if (60 < H&&H <= 120){
		g = max; b = min;
		r = (120 - H) / 60.0*(max - min) + min;
	}
	else if (120 < H&&H <= 180){
		r = min; g = max;
		b = (H - 120) / 60.0*(max - min) + min;
	}
	else if (180 < H&&H <= 240){
		r = min; b = max;
		g = (240 - H) / 60.0*(max - min) + min;
	}
	else if (240 < H&&H <= 300){
		g = min; b = max;
		r = (H - 240) / 60.0*(max - min) + min;
	}
	else{
		r = max; g = min;
		b = (360 - H) / 60.0*(max - min) + min;
	}
	switch (val){
	case CV_R:
		return r;
		break;
	case CV_G:
		return g;
		break;
	case CV_B:
		return b;
	default:
		return -1;
		break;
	}
}
