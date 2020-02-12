#include "CoreAlgorithm.h"
#include <unordered_map>

CoreAlgorithm::CoreAlgorithm(std::string path = "../Data/image/reconstruction/tq.png")
{
	image = cv::imread(path, cv::IMREAD_COLOR);
	tmp = image.clone(); // 深拷贝
	split(image, channel); //b,g,r
	cvtColor(image, hsv, COLOR_BGR2HSV);
	cArg = CameraArguments::getInstance();
}

CoreAlgorithm::~CoreAlgorithm()
= default;

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

vector<int> CoreAlgorithm::Debruijn(int k, int n)
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

vector<int> CoreAlgorithm::Hsv(int r, int g, int b)
{
	vector<int> h = {0, 0, 0, 0};
	h[0] = (2 * r - g - b) / (2 * sqrt(pow((r - g), 2) + (r - b) * (g - b)));
	h[1] = (2 * g - r - b) / (2 * sqrt(pow((g - r), 2) + (g - b) * (r - b)));
	h[2] = (2 * b - g - r) / (2 * sqrt(pow((b - g), 2) + (b - r) * (g - r)));
	h[3] = sqrt(1 - ((r * g + g * b + r * b) / (pow(r, 2) + pow(g, 2) + pow(b, 2)))); // 色彩强度
	return h;
}

Mat CoreAlgorithm::Reconstruction(Mat featurePoint, int num, Mat Hc1, Mat Hp2, Mat map)
{
	auto numOfCoord = 0;
	Mat coordinate = Mat::zeros(cv::Size(num, 3), CV_32FC1);
	for (auto column = minX; column < maxX; column++)
	{
		Mat rowPosition = Mat::zeros(cv::Size(700, 1), CV_32FC1);
		auto counter = 0;
		for (auto row = minY; row < maxY; row++)
		{
			if (featurePoint.at<uchar>(row, column) >= 0)
			{
				rowPosition.at<uchar>(0, counter) = row;
				counter++;
			}

			if (counter < 4)
			{
				continue;
			}

			for (auto c = 0; c < counter - 3; c++)
			{
				Mat matrix = Mat::zeros(cv::Size(3, 3), CV_32FC1);
				matrix.row(0) = Hc1.row(2) * (rowPosition.at<uchar>(0, c) + 1) - Hc1.row(0);
				matrix.row(1) = Hc1.row(2) * (column + 1) - Hc1.row(1);

				auto p1 = rowPosition.at<uchar>(0, c);
				auto p2 = rowPosition.at<uchar>(0, c + 1);
				auto p3 = rowPosition.at<uchar>(0, c + 2);
				auto p4 = rowPosition.at<uchar>(0, c + 3);

				auto id = map.step[0] * featurePoint.at<uchar>(column, p1)
					+ map.step[1] * featurePoint.at<uchar>(column, p2)
					+ map.step[2] * featurePoint.at<uchar>(column, p3)
					+ map.step[3] * featurePoint.at<uchar>(column, p4);

				matrix.row(2) = Hp2.row(2) * (*reinterpret_cast<int*>(map.data + id)
					- Hp2.row(0));
				Mat tang = Mat::zeros(cv::Size(3, 1), CV_32FC1);
				Mat tmpMat = Mat::zeros(cv::Size(3, 1), CV_32FC1);
				tmpMat.row(0) = Hc1.row(0) - Hc1.row(2) * (rowPosition.at<uchar>(0, c) + 1);
				tmpMat.row(1) = Hc1.row(1) - Hc1.row(2) * (column + 1);
				tmpMat.row(2) = Hp2.row(0) - Hp2.at<uchar>(2, 3) * (*reinterpret_cast<int*>(map.data + id));
				tmpMat = tmpMat.t();
				solve(matrix, tmpMat, tang);

				if (tang.at<uchar>(2, 0) > 750 && tang.at<uchar>(2, 0) < 1500)
				{
					coordinate.row(numOfCoord) = tang.t();
					numOfCoord++;
				}
			}
		}
	}
	return coordinate;
}

template <class ForwardIterator>
size_t CoreAlgorithm::argmin(ForwardIterator first, ForwardIterator last)
{
	return std::distance(first, std::min_element(first, last));
}


template <class ForwardIterator>
size_t CoreAlgorithm::argmax(ForwardIterator first, ForwardIterator last)
{
	return std::distance(first, std::max_element(first, last));
}


template <typename Tp>
vector<Tp> CoreAlgorithm::convertMat2Vector(const cv::Mat& mat)
{
	return (vector<Tp>)(mat.reshape(1, 1)); //通道数不变，按行转为一行
}

void CoreAlgorithm::run()
{
	tmp = OSTU(image);
	auto min = false;
	for (auto i = 0; i < 1024; i++)
	{
		for (auto j = 0; j < 1280; j++)
		{
			if (tmp.at<Vec3b>(i, j)[0] == 255)
			{
				if (!min)
				{
					minX = i;
					min = true;
				}

				if (j < minY) minY = j;
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
			grayImage.at<uchar>(i, j) = 0.2989 * channel.at(2).at<uchar>(i, j) +
				0.5907 * channel.at(1).at<uchar>(i, j) +
				0.1140 * channel.at(0).at<uchar>(i, j);
		}
	}

	Mat featurePoint = Mat::zeros(cv::Size(1024, 1280), CV_32FC1);

	for (auto i = minX; i < maxX; i++)
	{
		for (auto j = minY; j < maxY; j++)
		{
			auto temp = grayImage(Rect(i, j - neighborhood, 2 * neighborhood + 1, 1));
			auto v = convertMat2Vector<uchar>(temp);

			const auto tmpPosition1 = argmax(v.begin(), v.end());
			const auto tmpPosition2 = argmin(v.begin(), v.end());
			const auto position1 = static_cast<int>(tmpPosition1);
			const auto position2 = static_cast<int>(tmpPosition2);

			if (position1 == neighborhood)
			{
				featurePoint.at<uchar>(i, j) = 1;
			}
			if (position2 == neighborhood)
			{
				featurePoint.at<uchar>(i, j) = -1;
			}
		}
	}

	for (auto i = minX; i < maxX; i++)
	{
		Mat temp = Mat::zeros(cv::Size(100, 1), CV_32FC1);
		auto num = 0;
		for (auto j = minY; j < maxY; j++)
		{
			if (featurePoint.at<uchar>(i, j) == 1)
			{
				temp.at<uchar>(num, 0) = j;
				int rh = channel.at(2).at<uchar>(i, j);
				int gh = channel.at(1).at<uchar>(i, j);
				int bh = channel.at(0).at<uchar>(i, j);

				if (rh == gh || gh == bh || rh == bh)
				{
					featurePoint.at<uchar>(i, j) = -2;
					continue;
				}

				auto h = Hsv(rh, gh, bh);
				auto result = max_element(begin(h), end(h));
				auto nPos = static_cast<int>(max_element(h.begin(), h.end()) - (h.begin()));

				if (nPos == 0)
				{
					featurePoint.at<uchar>(i, j) = 0;
				}
				else if (nPos == 1)
				{
					featurePoint.at<uchar>(i, j) = 1;
				}
				else if (nPos == 2)
				{
					featurePoint.at<uchar>(i, j) = 2;
				}
				num = num + 1;
			}
			else if (featurePoint.at<uchar>(i, j) != -1)
			{
				featurePoint.at<uchar>(i, j) = -2;
			}
		}
	}

	auto number = 0;
	for (auto i = minX; i < maxX; i++)
	{
		for (auto j = minY; j < maxY; j++)
		{
			if (featurePoint.at<uchar>(i, j) != -2) number++;
		}
	}

	auto db = Debruijn(3, 4);

	int p, q, t, u;
	p = q = t = u = 3;
	int sizes[] = {p, q, t, u};
	auto all = p * q * t * u;
	auto d1 = new float[all];
	for (auto i = 0; i < all; i++)
	{
		d1[i] = i * 1;
	}

	auto map = Mat(4, sizes, CV_32S, d1);

	for (auto i = 0; i < 61; i++)
	{
		auto id = map.step[0] * db[i] + map.step[1] * db[i + 1]
			+ map.step[2] * db[i + 2] + map.step[3] * db[i + 3];
		auto* stub = reinterpret_cast<int*>(map.data + id);
		*stub = 7.5 + 14 * i;
	}

	auto coordinate = Reconstruction(featurePoint, number, cArg->getHc(), cArg->getHp(), map);
}
