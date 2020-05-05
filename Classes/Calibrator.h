#ifndef CALIBRATOR_H
#define CALIBRATOR_H

#include <opencv2/opencv.hpp>
#include <vector>

#include "CalibrationData.h"

class Calibrator
{
public:
    Calibrator();
    ~Calibrator();
    void addFrameSequence(std::vector<cv::Mat> &frameSeq);
    void reset();
    CalibrationData * calibrate();
    std::vector<cv::Point2f> extract_board_corners(cv::Mat &gray_image);
    bool decode_gray_set(int i , cv::Mat & pattern_image,  cv::Mat & min_max_image);
    void setBoardRows(int rows);
    void setBoardCols(int cols);
    void setCornerSize(double cornerSize);
    void setDotDiameter(double dotDiameter);
    void setCalibBoard(unsigned board);

    const static unsigned Chessboard = 0x00;
    const static unsigned Circular = 0x01;

protected:
    std::vector< std::vector<cv::Mat> > frameSeqs;
    std::vector< std::vector<cv::Point2f> > board_corners;
    std::vector< std::vector<cv::Point2f> > projector_corners;
    std::vector<cv::Mat> pattern_list;

    cv::Size2f corner_size = cv::Size2f(20.f , 20.f);
    cv::Size board_size = cv::Size(8 , 6);
    int board_rows = 8;
    int board_cols = 6;
    double dot_dis = 20.0;

    double dot_diameter = 7.5;

    unsigned board_type = Chessboard;

    unsigned threshold = 10;
    float b = 0.5;
    unsigned m = 5;

};

#endif // CALIBRATOR_H
