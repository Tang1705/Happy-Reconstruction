#ifndef CALIBRATIONDATA_H
#define CALIBRATIONDATA_H

#include <QString>
#include <opencv2/core/core.hpp>
#include <QFileInfo>
#include <QDateTime>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <opencv2/calib3d/calib3d.hpp>
#include <qstring.h>
#include "cvtools.h"
#include "CameraArguments.h"

using namespace cv;

class CalibrationData{
    public:
        CalibrationData();
        CalibrationData(cv::Matx33d _Kc, cv::Vec<double, 5> _kc, double _cam_error, cv::Matx33d _Kp, cv::Vec<double, 5> _kp,
                        double _proj_error,  cv::Matx33d _Rp,  cv::Vec3f _Tp,  double _stereo_error);
        bool load(const QString& filename);
        bool save(const QString& filename);
        bool loadXML(const QString& filename);
        bool saveXML(const QString& filename);
        bool saveMatlab(const QString& filename);
        bool saveSLCALIB(const QString& filename);
        void print();

        Matx33d Kc; // Intrinsic camera matrix
        Vec<double , 5> kc; // Camera distortion coefficients
        double cam_error;

        Matx33d Kp; // Intrinsic projector matrix
        Vec<double , 5> kp; // Projector distortion coefficients
        double proj_error;

        Matx33d Rp; // Extrinsic camera rotation matrix
        Vec3f Tp; // Extrinsic camera rotation matrix

        double stereo_error;

        int frameWidth , frameHeight;
        int screenResX , screenResY;
        std::string calibrationDateTime;
};

#endif
