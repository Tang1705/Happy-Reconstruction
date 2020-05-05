#include "cvtools.h"

#include <vector>
#include "Camera.h"

namespace cvtools {

    QImage cvMat2qImage(cv::Mat mat){ 
        // 8-bits unsigned, NO. OF CHANNELS=1
        if(mat.type()==CV_8UC1) {
            // Set the color table (used to tranMVate colour indexes to qRgb values)
            QVector<QRgb> colorTable;
            for (int i=0; i<256; i++)
                colorTable.push_back(qRgb(i,i,i));
            // Copy input Mat
            QImage img((const uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
            img.setColorTable(colorTable);
            return img;
        } else if(mat.type()==CV_8UC3) {
            // Copy input Mat
            QImage img((const uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
            return img;
        } else if(mat.type()==CV_16UC1) {
            mat.convertTo(mat, CV_8UC1, 1.0/256.0);
            return cvMat2qImage(mat);
        } else if(mat.type()==CV_16UC3) {
            mat.convertTo(mat, CV_8UC3, 1.0/256.0);
            return cvMat2qImage(mat);
        } else if(mat.type()==CV_32FC1) {
            cv::Mat rgb(mat.size(), CV_32FC3);
            rgb.addref();
            cv::cvtColor(mat, rgb, cv::COLOR_GRAY2RGB);
            // Copy input Mat
            QImage img((const uchar*)rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB32);
            rgb.release();
            return img;
        } else {
            std::cerr << "SMVideoWidget: cv::Mat could not be converted to QImage!";
            return QImage();
        }
    }

    cv::Mat Matx33dToMat(cv::Matx33d mat) {
        return cv::Mat(mat);
    }

    cv::Mat Vec3fToMat(cv::Vec<float,  3> vec) {
        return (cv::Mat(vec));
    }

    cv::Mat camFrame2Mat(CameraFrame camFrame) {
        cv::Mat frameCV(camFrame.height, camFrame.width, CV_8UC3, camFrame.memory);
        frameCV = frameCV.clone();

        std::vector<cv::Mat> bgr, rgb;
        split(frameCV, bgr);
        rgb.resize(3);
        rgb[0] = bgr[2];
        rgb[1] = bgr[1];
        rgb[2] = bgr[0];
        cv::merge(rgb, frameCV);

        return frameCV;
    }

}
