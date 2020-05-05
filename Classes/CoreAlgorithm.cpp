#include "CoreAlgorithm.h"

CoreAlgorithm::CoreAlgorithm(const std::string& path, CameraArguments* cArgs)
{
	image = imread(path, IMREAD_COLOR);
	rows = image.rows;
	cols = image.cols;
	split(image, rgbChannel); //b,g,r
	hsv = image.clone();
	cvtColor(image, hsv, COLOR_BGR2HSV, 3);
	split(hsv, hsvChannel);
	cvtColor(image, lab, COLOR_BGR2Lab);
	cArg = cArgs;
}

CoreAlgorithm::~CoreAlgorithm()
= default;

Mat CoreAlgorithm::OtsuAlgThreshold(Mat& src)
{
	if (src.channels() != 1)
	{
		cout << "Please input Gray-src!" << endl;
	}

	auto T = 0;
	double varValue = 0;
	double w0 = 0;
	double w1 = 0;
	double u0 = 0;
	double u1 = 0;
	double Histogram[256] = {0};
	uchar* data = src.data;

	double totalNum = src.rows * src.cols;

	for (auto i = 0; i < src.rows; i++)
	{
		for (auto j = 0; j < src.cols; j++)
		{
			if (src.at<float>(i, j) != 0) Histogram[data[i * src.step + j]]++;
		}
	}

	auto minpos = 0, maxpos = 0;
	for (auto i = 0; i < 255; i++)
	{
		if (Histogram[i] != 0)
		{
			minpos = i;
			break;
		}
	}

	for (auto i = 255; i > 0; i--)
	{
		if (Histogram[i] != 0)
		{
			maxpos = i;
			break;
		}
	}

	for (auto i = minpos; i <= maxpos; i++)
	{
		w1 = 0;
		u1 = 0;
		w0 = 0;
		u0 = 0;
		for (auto j = 0; j <= i; j++)
		{
			w1 += Histogram[j];
			u1 += j * Histogram[j];
		}
		if (w1 == 0)
		{
			break;
		}
		u1 = u1 / w1;
		w1 = w1 / totalNum;
		for (auto k = i + 1; k < 255; k++)
		{
			w0 += Histogram[k];
			u0 += k * Histogram[k];
		}
		if (w0 == 0)
		{
			break;
		}
		u0 = u0 / w0;
		w0 = w0 / totalNum;

		auto varValueI = w0 * w1 * (u1 - u0) * (u1 - u0);
		if (varValue < varValueI)
		{
			varValue = varValueI;
			T = i;
		}
	}
	//    cout << T << endl;
	Mat dst = src.clone();
	for (auto i = 0; i < src.rows; i++)
		for (auto j = 0; j < src.cols; j++)
			dst.at<float>(i, j) = src.at<float>(i, j) > T ? 255 : 0;
	return dst;
}

vector<int> CoreAlgorithm::DeBruijn(int k, int n)
{
	std::vector<byte> a(k * n, 0);
	std::vector<byte> seq;

	std::function<void(int, int)> db;
	db = [&](int t, int p)
	{
		if (t > n)
		{
			if (n % p == 0)
			{
				for (int i = 1; i < p + 1; i++)
				{
					seq.push_back(a[i]);
				}
			}
		}
		else
		{
			a[t] = a[t - p];
			db(t + 1, p);
			auto j = a[t - p] + 1;
			while (j < k)
			{
				a[t] = j & 0xFF;
				db(t + 1, t);
				j++;
			}
		}
	};

	db(1, 1);
	std::string buf;
	for (auto i : seq)
	{
		buf.push_back('0' + i);
	}

	std::vector<int> res;
	std::string tmp = buf + buf.substr(0, n - 1);
	for (char i : tmp)
	{
		res.push_back(i - '0');
	}
	return res;
}

void CoreAlgorithm::Reconstruction(vector<vector<float>> maximas, vector<vector<float>> minimas,
                                   vector<vector<float>> colorLabel, vector<vector<float>> phases, const Mat& Hc1,
                                   Mat Hp2, const double* map)
{
	for (auto i = 0; i < maximas.size(); i++)
	{
		if (maximas[i].empty())continue;
		if (maximas[i].size() < 4)continue;
		auto mark = 0;
		//        double pc = 0;
		for (auto j = 0; j < maximas[i].size(); j++)
		{
			double position;
			if (j < maximas[i].size() - 3)
			{
				position = map[int(pow(3, 3) * colorLabel[i].at(j) + pow(3, 2) * colorLabel[i].at(j + 1) +
					3 * colorLabel[i].at(j + 2) + colorLabel[i].at(j + 3))];
			}
			else
			{
				auto fix = maximas[i].size() - 4;
				auto index = j - maximas[i].size() + 4;
				position = map[int(pow(3, 3) * colorLabel[i].at(fix) + pow(3, 2) * colorLabel[i].at(fix + 1) +
					3 * colorLabel[i].at(fix + 2) + colorLabel[i].at(fix + 3))] + 14.0 * index;
			}
			
			Mat matrix = Mat::zeros(cv::Size(3, 3), CV_32FC1);
			matrix.row(0) = Hc1(Rect(0, 2, 3, 1)) * (maximas[i][j]) - Hc1(Rect(0, 0, 3, 1));
			matrix.row(1) = Hc1(Rect(0, 2, 3, 1)) * (float(i + minX)) - Hc1(Rect(0, 1, 3, 1));
			matrix.row(2) = Hp2(Rect(0, 2, 3, 1)) * position - Hp2(Rect(0, 0, 3, 1));
			Mat tang = Mat::zeros(cv::Size(3, 1), CV_32FC1);
			Mat b = Mat::zeros(cv::Size(1, 3), CV_32FC1);
			b.row(0) = Hc1.at<float>(0, 3) - Hc1.at<float>(2, 3) * (maximas[i][j]);
			b.row(1) = Hc1.at<float>(1, 3) - Hc1.at<float>(2, 3) * (float(i + minX));
			b.row(2) = Hp2.at<float>(0, 3) - Hp2.at<float>(2, 3) * position;
			solve(matrix, b, tang);
			
			if (tang.at<float>(2, 0) > 750 && tang.at<float>(2, 0) < 1500)
			{
				coordinate.push_back(tang.t());

				int r = (int)rgbChannel[2].at<uchar>(i + minX, maximas[i][j]),
				    g = rgbChannel[1].at<uchar>(i + minX, maximas[i][j]),
				    b = rgbChannel[0].at<uchar>(i + minX, maximas[i][j]);
				int rgb = ((int)r << 16 | (int)g << 8 | (int)b);
				float frgb = *reinterpret_cast<float*>(&rgb);
				color.push_back(frgb);
			}
			//            if (i == 200)cout << maximas[i][j] << "," << 0 << "," << position << endl;
			if (phases[i].empty())continue;
			auto pi = false;
			auto start = minimas[i][0];
			if (start > maximas[i][j]) continue;
			if (j == 0)
			{
				for (auto k = mark; k + start < maximas[i][j]; k++)
				{
					if ((start + k) < maximas[i][j] && phases[i][k] < 0)continue;
					if ((start + k) < maximas[i][j] && phases[i][k] > 0)
					{
						if (maximas[i][j] - (start + k) < 1)
						{
							continue;
						}
						mark = k + 1;
					}
					else if ((start + k) > maximas[i][j]) break;
				}
			}
			
			for (auto k = mark; k < phases[i].size()-1; k++)
			{
				mark++;
				double newPosition;
				if ((start + k) < maximas[i][j] && phases[i][k] < 0) newPosition = position + phases[i][k];
				else if ((maximas[i][j] - (start + k)) > 1 && phases[i][k] > 0)
					newPosition = position + phases[i][k] - 7;
				else if ((start + k) > maximas[i][j] && phases[i][k] > 0)newPosition = position + phases[i][k];
				else if (((start + k) - maximas[i][j]) > 1 && phases[i][k] < 0)
					newPosition = position + phases[i][k] + 7;
				else continue;

				matrix.row(0) = Hc1(Rect(0, 2, 3, 1)) * (start + k) - Hc1(Rect(0, 0, 3, 1));
				matrix.row(2) = Hp2(Rect(0, 2, 3, 1)) * newPosition - Hp2(Rect(0, 0, 3, 1));
				b.row(0) = Hc1.at<float>(0, 3) - Hc1.at<float>(2, 3) * (start + k);
				b.row(2) = Hp2.at<float>(0, 3) - Hp2.at<float>(2, 3) * newPosition;
				solve(matrix, b, tang);
				if (tang.at<float>(2, 0) > 750 && tang.at<float>(2, 0) < 1500)
				{
					coordinate.push_back(tang.t());
					int r = (int)rgbChannel[2].at<uchar>(i + minX, (start + k)),
					    g = rgbChannel[1].at<uchar>(i + minX, (start + k)),
					    b = rgbChannel[0].at<uchar>(i + minX, (start + k));
					int rgb = ((int)r << 16 | (int)g << 8 | (int)b);
					float frgb = *reinterpret_cast<float*>(&rgb);
					color.push_back(frgb);
				}

				if ((start + k) > maximas[i][j] && !pi && phases[i][k] > 0) pi = true;

				if ((start + k) > maximas[i][j] && phases[i][k] < 0 && phases[i][k + 1] > 0 && pi)break;
				
			}
			
		}
	}
}


void CoreAlgorithm::run()
{
	Mat mask = Mat::zeros(Size(cols, rows), CV_32FC1);
	for (auto i = 0; i < rows; i++)
	{
		for (auto j = 0; j < cols; j++)
		{
			mask.at<float>(i, j) = (int)rgbChannel[0].at<uchar>(i, j) > (int)rgbChannel[1].at<uchar>(i, j)
				                       ? (
					                       (int)rgbChannel[0].at<uchar>(i, j) > (int)rgbChannel[2].at<uchar>(i, j)
						                       ? (int)rgbChannel[0].at<uchar>(i, j)
						                       : (int)rgbChannel[2].at<uchar>(i, j))
				                       : (
					                       (int)rgbChannel[1].at<uchar>(i, j) > (int)rgbChannel[2].at<uchar>(i, j)
						                       ? (int)rgbChannel[1].at<uchar>(i, j)
						                       : (int)rgbChannel[2].at<uchar>(i, j));
		}
	}

	tmp = OtsuAlgThreshold(mask);

	auto kernel = getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
	morphologyEx(tmp, tmp, MORPH_OPEN, kernel);
	auto min = false;
	for (auto i = 0; i < rows; i++)
	{
		for (auto j = 0; j < cols; j++)
		{
			if (tmp.at<float>(i, j) == 255)
			{
				if (!min)
				{
					minX = i;
					minY = j;
					min = true;
				}

				if (j < minY) minY = j;
				if (i > maxX) maxX = i;
				if (j > maxY) maxY = j;
			}
		}
	}

	minX -= 50;
	minY -= 50;
	maxX += 50;
	maxY += 50;

	// cout << minX << "," << minY;
	// cout << maxX << "," << maxY;
	// cout<<rows<<","<<cols<<endl;

	// auto rec = image(Rect(minY, minX, maxY - minY, maxX - minX));

	Mat img = Mat::zeros(Size(cols, rows), CV_32FC1);
	for (auto i = minX; i < maxX; i++)
	{
		for (auto j = minY; j < maxY; j++)
		{
			img.at<float>(i, j) = 0.2989 * (int)rgbChannel.at(2).at<uchar>(i, j) +
				0.5907 * (int)rgbChannel.at(1).at<uchar>(i, j) +
				0.1140 * (int)rgbChannel.at(0).at<uchar>(i, j);
		}
	}

	kernel = getStructuringElement(MORPH_RECT, cv::Size(3, 3));
	morphologyEx(img, img, MORPH_CLOSE, kernel);

	GaussianBlur(img, img, Size(5, 5), 0, 0);

	Mat derivative1 = Mat::zeros(Size(cols, rows), CV_32FC1);
	Mat derivative2 = Mat::zeros(Size(cols, rows), CV_32FC1);

	for (auto i = 0; i < rows; i++)
	{
		for (auto j = 1; j < cols - 1; j++)
		{
			derivative1.at<float>(i, j) = img.at<float>(i, j + 1) - img.at<float>(i, j);
			derivative2.at<float>(i, j) = img.at<float>(i, j + 1) + img.at<float>(i, j - 1) - 2 * img.at<float>(i, j);
		}
	}

	vector<vector<float>> maximas(0, vector<float>(0, 0));
	vector<vector<float>> minimas(0, vector<float>(0, 0));
	vector<vector<float>> colorLabel(0, vector<float>(0, 0));
	for (auto i = minX; i < maxX; i++)
	{
		maximas.resize(i - minX + 1);
		minimas.resize(i - minX + 1);
		colorLabel.resize(i - minX + 1);
		vector<double> tmpMin;
		for (auto j = minY; j < maxY; j++)
		{
			// cout << i << endl;
			if (derivative1.at<float>(i, j) > 0 && derivative1.at<float>(i, j + 1) < 0)
			{
				double k = derivative1.at<float>(i, j + 1) - derivative1.at<float>(i, j);
				double b = derivative1.at<float>(i, j) - k * j;
				double zero = -b / k;
				double k2 = derivative2.at<float>(i, j + 1) - derivative2.at<float>(i, j);
				double b2 = derivative2.at<float>(i, j) - k2 * j;
				double value = k2 * zero + b2;
				if (value < 0 && lab.at<Vec3b>(i, zero)[0] > 5)
				{
					maximas[i - minX].push_back(zero);
					if (lab.at<Vec3b>(i, zero)[2] < 126)
					{
						colorLabel[i - minX].push_back(2); //blue
					}
					else
					{
						if (lab.at<Vec3b>(i, zero)[1] >= 128)
						{
							colorLabel[i - minX].push_back(0); //red
						}
						else
						{
							colorLabel[i - minX].push_back(1); //green
						}
					}
				}
			}
			
			if (derivative1.at<float>(i, j) < 0 && derivative1.at<float>(i, j + 1) > 0)
			{
				double k = derivative1.at<float>(i, j + 1) - derivative1.at<float>(i, j);
				double b = derivative1.at<float>(i, j) - k * j;
				double zero = -b / k;
				double k2 = derivative2.at<float>(i, j + 1) - derivative2.at<float>(i, j);
				double b2 = derivative2.at<float>(i, j) - k2 * j;
				double value = k2 * zero + b2;
				if (value > 0)
				{
					tmpMin.push_back(zero);
				}
			}
		}
		if (!tmpMin.empty() && !maximas[i - minX].empty())
		{
			auto pos = 0;
			for (auto j = 0; j < tmpMin.size()-1; j++)
			{
				
				if (tmpMin[j + 1] < maximas[i - minX][pos])
				{
					continue;
				}
				minimas[i - minX].push_back(tmpMin[j]);
				pos++;
				if (pos >= maximas[i - minX].size())break;
			}

		}
	}
	
	vector<vector<float>> phases(0, vector<float>(0, 0));
	emxArray_real_T* phase;
	double x_data[1280] = {0};
	int x_size[2] = {0};
	emxInitArray_real_T(&phase, 2);
	x_size[0] = 1;
	for (auto i = minX; i < maxX; i++)
	{
		phases.resize(i - minX + 1);
		if (minimas[i - minX].empty())continue;
		int start = minimas[i - minX][0];
		int end = minimas[i - minX][minimas[i - minX].size() - 1];
		x_size[1] = end - start;
		for (auto j = start; j < end; j++)
		{
			x_data[j - start] = (float)lab.at<Vec3b>(i, j)[0];
			//            if (i -minX== 300)
			//            cout<<x_data[j - start]<<",";
		}
		cwt(x_data, x_size, phase);

		for (auto j = 0; j < x_size[1]; j++)
		{
			phases[i - minX].push_back(*(phase->data + j) / PI * 7);
			//            if (i - minX == 300)
			//                cout << j + start << "," << *(phase->data + j) << endl;
		}
		//        if (i == 300) {
		//            for (auto j = 0; j < maximas[i - minX].size(); j++) {
		//                cout <<j+start<<","<< *(phase->data + int(maximas[i - minX][j] - start)) << endl;
		//
		//            }
		//        }
	}
	auto db = DeBruijn(3, 4);
	double map[76]{0};
	for (auto i = 0; i < 61; i++)
	{
		int index = int(pow(3, 3) * db.at(i) + pow(3, 2) * db.at(i + 1) + 3 * db.at(i + 2) + db.at(i + 3));
		map[index] = 7.5 + 14 * i;
	}

	Reconstruction(maximas, minimas, colorLabel, phases, cArg->getHc(), cArg->getHp(), map);
	ofstream destFile("./Data/result/result.txt", ios::out); //以文本模式打开out.txt备写
	for (auto i = 0; i < coordinate.size(); i++)
	{
		if (i == coordinate.size() - 1)
		{
			destFile << coordinate[i].at<float>(0, 0) << " " << coordinate[i].at<float>(0, 1) << " "
				<< coordinate[i].at<float>(0, 2);
		}
		else
		{
			destFile << coordinate[i].at<float>(0, 0) << " " << coordinate[i].at<float>(0, 1) << " "
				<< coordinate[i].at<float>(0, 2) << endl; //可以像用cout那样用ofstream对象
		}
	}

	destFile.close();
	saveCoordinate();
}

void CoreAlgorithm::saveCoordinate()
{
	ofstream destFile("./Data/result/result.pcd", ios::out); //以文本模式打开out.txt备写
	destFile << "# .PCD v0.7 - Point Cloud Data file format" << endl;
	destFile << "VERSION 0.7" << endl;
	destFile << "FIELDS x y z rgb" << endl;
	destFile << "SIZE 4 4 4 4" << endl;
	destFile << "TYPE F F F F" << endl;
	destFile << "COUNT 1 1 1 1" << endl;
	destFile << "WIDTH " << coordinate.size() << endl;
	destFile << "HEIGHT 1" << endl;
	destFile << "VIEWPOINT 0 0 0 1 0 0 0" << endl;
	destFile << "POINTS " << coordinate.size() << endl;
	destFile << "DATA ascii" << endl;
	for (auto i = 0; i < coordinate.size(); i++)
	{
		//        cout << i << endl;
		if (i == coordinate.size() - 1)
		{
			destFile << coordinate[i].at<float>(0, 0) << " " << coordinate[i].at<float>(0, 1) << " "
				<< coordinate[i].at<float>(0, 2) << " " << color[i];
		}
		else
		{
			destFile << coordinate[i].at<float>(0, 0) << " " << coordinate[i].at<float>(0, 1) << " "
				<< coordinate[i].at<float>(0, 2) << " " << color[i] << endl; //可以像用cout那样用ofstream对象
		}
	}
	destFile.close();
}
