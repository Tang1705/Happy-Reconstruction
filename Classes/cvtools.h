#ifndef CVTOOLS_H
#define CVTOOLS_H


#include <opencv2/opencv.hpp>
#include <QtGui/qimage.h>
#include "Camera.h"
// struct CameraFrame;

namespace cvtools
{
    QImage cvMat2qImage(cv::Mat mat);
    cv::Mat Matx33dToMat(cv::Matx33d mat);
    cv::Mat Vec3fToMat(cv::Vec<float,  3> vec);
    cv::Mat camFrame2Mat(CameraFrame camFrame);
}

#endif // CVTOOLS_H
