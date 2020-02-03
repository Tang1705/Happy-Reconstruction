#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include <math.h>

using namespace std;
using namespace cv;

class CoreAlgorithm
{
private:
	Mat image, tmp;
	vector<Mat> channel;
	const int neighborhood = 5;
	int minX = 0, maxX = 0, minY = 0, maxY = 0;
public:
	CoreAlgorithm(std::string path);
	~CoreAlgorithm();
	Mat OSTU(Mat src);
	void Rgb2Hsv(float r, float g, float b, float& h, float& s, float& v);
	void run();
};
