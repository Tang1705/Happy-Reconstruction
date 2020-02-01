#pragma once
#include <opencv2/opencv.hpp>

class CameraArguments
{
private:
	cv::Mat r12;
	cv::Mat t12;
	cv::Mat kc1;
	cv::Mat kp2;
	cv::Mat hc1;
	cv::Mat hp2;

public:
	CameraArguments();
	CameraArguments(cv::Mat r, cv::Mat t, cv::Mat kc, cv::Mat kp);
	~CameraArguments();
	cv::Mat getR() const;
	cv::Mat getT() const;
	cv::Mat getKc() const;
	cv::Mat getKp() const;
	cv::Mat getHc() const;
	cv::Mat getHp() const;
};
