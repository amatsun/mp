/*
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat detectFaceInImage(Mat &image, string &cascade_file){
	CascadeClassifier cascade;
	if (!cascade.load(cascade_file)){
		return image;
	}

	vector<Rect> faces;
	cascade.detectMultiScale(image, faces, 1.1, 3, 0, Size(20, 20));

	for (int i = 0; i < faces.size(); i++){
		rectangle(image, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar(0, 200, 0), 3, CV_AA);
	}
	return image;
}

int WinMain(int argc, char const *argv[]){
	Mat image = imread("c:\\test.jpg",1);
	string filename = "c:\\haarcascade_frontalface_default.xml";
	
	Mat detectFaceImage = detectFaceInImage(image, filename);
	imshow("detect face", detectFaceImage);
	
	//imshow("test", image);
	waitKey(0);

	return 0;
}
*/