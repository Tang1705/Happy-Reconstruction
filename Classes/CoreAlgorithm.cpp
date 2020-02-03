#include "CoreAlgorithm.h"

CoreAlgorithm::CoreAlgorithm(std::string path = "../Data/image/reconstruction/tq.png")
{
	image = cv::imread(path, cv::IMREAD_COLOR);
	tmp = image.clone(); // Éî¿½±´
	split(image, channel); //b,g,r
}

CoreAlgorithm::~CoreAlgorithm()
{
}

Mat CoreAlgorithm::OSTU(Mat src)
{
	const auto width = src.cols;
	const auto height = src.rows;
	int hisData[256] = {0};

	for (auto j = 0; j < height; j++)
	{
		auto* data = src.ptr<uchar>(j);
		for (auto i = 0; i < width; i++)
			hisData[data[i]]++;
	}

	auto t0 = 0;

	for (auto i = 0; i < 256; i++)
	{
		t0 += i * hisData[i];
	}

	t0 /= width * height;

	auto t1 = 0, t2 = 0;
	auto num1 = 0, num2 = 0;
	auto t = 0;

	while (true)
	{
		for (auto i = 0; i < t0 + 1; i++)
		{
			t1 += i * hisData[i];
			num1 += hisData[i];
		}

		if (num1 == 0) continue;

		for (auto i = t0 + 1; i < 256; i++)
		{
			t2 += i * hisData[i];
			num2 += hisData[i];
		}

		if (num2 == 0) continue;

		t = (t1 / num1 + t2 / num2) / 2;

		if (t != t0) t0 = t;
		else break;
	}

	Mat dst;

	threshold(src, dst, t, 255, 0);

	return dst;
}

void CoreAlgorithm::Rgb2Hsv(float r, float g, float b, float& h, float& s, float& v)
{
	// r,g,b values are from 0 to 1
	// h = [0,360], s = [0,1], v = [0,1]
	// if s == 0, then h = -1 (undefined)
	float min, max, delta, temp;
	temp = r > g ? g : r;
	min = temp > b ? b : temp;
	temp = r > g ? r : g;
	max = temp > b ? temp : b;
	v = max; // v
	delta = max - min;
	if (max != 0)
		s = delta / max; // s
	else
	{
		// r = g = b = 0 // s = 0, v is undefined
		s = 0;
		h = 0;
		return;
	}
	if (delta == 0)
	{
		h = 0;
		return;
	}
	else if (r == max)
	{
		if (g >= b)
			h = (g - b) / delta; // between yellow & magenta
		else
			h = (g - b) / delta + 6.0;
	}
	else if (g == max)
		h = (b - r) / delta + 2.0; // between cyan & yellow
	else if (b == max)
		h = (r - g) / delta + 4.0; // between magenta & cyan
	h *= 60.0; // degrees
}

void CoreAlgorithm::run()
{
	tmp = OSTU(image);
	auto min = false;
	for (auto i = 0; i < 1024; i++)
	{
		for (auto j = 0; j < 1280; j++)
		{
			if (!min)
			{
				if (tmp.at<Vec3b>(i, j)[0] == 255)
				{
					minX = i;
					minY = j;
					min = true;
				}
			}

			if (tmp.at<Vec3b>(i, j)[0] == 255)
			{
				if (i > maxX) maxX = i;
				if (j > maxY) maxY = j;
			}
		}
	}

	Mat grayImage = Mat::zeros(cv::Size(1024, 1280), CV_32FC1);
	for (auto i = 0; i < 1024; i++)
	{
		for (auto j = 0; j < 1280; j++)
		{
			grayImage.at<Vec3b>(i, j) = 0.2989 * channel.at(2).at<Vec3b>(i, j) +
				0.5907 * channel.at(1).at<Vec3b>(i, j) +
				0.1140 * channel.at(0).at<Vec3b>(i, j);
		}
	}

	Mat featurePoint = Mat::zeros(cv::Size(1024, 1280), CV_32FC1);

	for (auto i = minX; i < maxX; i++)
	{
		for (auto j = minY; j < maxY; j++)
		{
		}
	}
}
