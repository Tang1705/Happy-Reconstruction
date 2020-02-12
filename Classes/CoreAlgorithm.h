#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include "CameraArguments.h"

using namespace std;
using namespace cv;

typedef unsigned char byte;

class CoreAlgorithm
{
private:
	Mat image, tmp;
	vector<Mat> channel,hsv;
	const int neighborhood = 5;
	int minX = 0, maxX = 0, minY = 1280, maxY = 0;
	CameraArguments* cArg;
private:
	CoreAlgorithm(std::string path);
	~CoreAlgorithm();
	Mat OSTU(Mat src);
	vector<int> Debruijn(int k, int n);
	vector<int> Hsv(int r,int g,int b);
	Mat Reconstruction(Mat featurePoint, int num,Mat Hc1,Mat Hp2,Mat map);
	template <class ForwardIterator>
	size_t argmin(ForwardIterator first, ForwardIterator last);
	template <class ForwardIterator>
	size_t argmax(ForwardIterator first, ForwardIterator last);
	template <typename Tp>
	std::vector<Tp> convertMat2Vector(const cv::Mat& mat);
public:
	void run();
};
