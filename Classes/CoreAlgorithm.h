#pragma once

#include <opencv2/opencv.hpp>
#include  <opencv2/highgui.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <unordered_map>
#include <numeric>
#include "cwt.h"
#include "cwt_emxAPI.h"
#include "cwt_terminate.h"
#include "rt_nonfinite.h"
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "cwt_types.h"
#include "CameraArguments.h"

using namespace std;
using namespace cv;

typedef unsigned char byte;

# define PI acos(-1)

class CoreAlgorithm {
private:
    Mat image, tmp, hsv, lab;
    vector<Mat> rgbChannel, hsvChannel;
    int minX = 0, maxX = 0, minY = 0, maxY = 0;
    int rows, cols;
    CameraArguments *cArg;
    vector<Mat> coordinate;
    vector<float> color;
private:
    static Mat OtsuAlgThreshold(Mat &src);

    static vector<int> DeBruijn(int k, int n);

    void Reconstruction(vector<vector<float>> maximas, vector<vector<float>> minimas, vector<vector<float>> colorLabel,
                        vector<vector<float>> phases,const Mat &Hc1, Mat Hp2, const double *map);

public:
    CoreAlgorithm(const std::string &path, CameraArguments *cArgs);

    ~CoreAlgorithm();

    void run();

    void saveCoordinate();
};
