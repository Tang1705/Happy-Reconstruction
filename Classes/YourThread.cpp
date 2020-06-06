#include "YourThread.h"

YourThread::YourThread(PointCloud<PointXYZRGB> *cloudRef)
{
	cloud = cloudRef;
}

void YourThread::run()
{
	// auto cArg = CameraArguments::getInstance();
	Mat r(3, 3, CV_32F);
	double m0[3][3] = {
		{9.7004457782050868e-001, 1.3447278830863673e-002, 2.4255450466457243e-001},
		{-8.7082927494022376e-003, 9.9974988338843274e-001, -2.0599424802792338e-002},
		{-2.4277084396282392e-001, 1.7870124701864658e-002, 9.6991905639837694e-001}
	};
	for (auto i = 0; i < r.rows; i++)
		for (auto j = 0; j < r.cols; j++)
			r.at<float>(i, j) = m0[i][j];

	Mat t(1, 3, CV_32F);
	double m1[1][3] = {
		{-1.9511179496234658e+002, 1.2627509817628756e+001, -5.9345885017522171e+001}
	};

	for (auto i = 0; i < t.rows; i++)
		for (auto j = 0; j < t.cols; j++)
			t.at<float>(i, j) = m1[i][j];

	Mat kc(3, 3, CV_32F);
	double m2[3][3] = {
		{2.1536653255083029e+003, 0., 6.1886776197116581e+002},
		{0., 2.1484363899666910e+003, 5.0694898820460787e+002},
		{0., 0., 1.}
	};
	for (auto i = 0; i < kc.rows; i++)
		for (auto j = 0; j < kc.cols; j++)
			kc.at<float>(i, j) = m2[i][j];

	Mat kp(3, 3, CV_32F);
	double m3[3][3] = {
		{1.7235093158297350e+003, 0., 4.4128195628736904e+002},
		{0., 3.4533404000869359e+003, 5.7316457428558715e+002},
		{0., 0., 1.}
	};
	for (auto i = 0; i < kp.rows; i++)
		for (auto j = 0; j < kp.cols; j++)
			kp.at<float>(i, j) = m3[i][j];

	auto cArg = CameraArguments::getInstance(r, t, kc, kp);
	CoreAlgorithm testCase = CoreAlgorithm(path, cArg);
	testCase.run();
	vector<Mat> coordinates=testCase.getCoordinates();
	cloud->width = coordinates.size();
	cloud->height = 1;
	cloud->is_dense = false;
	cloud->points.resize(cloud->width * cloud->height);
	auto index = 0;
	for (size_t i = 0; i < cloud->points.size(); ++i)
	{
		cloud->points[i].x = coordinates[index].at<float>(0, 0);
		cloud->points[i].y = coordinates[index].at<float>(0, 1);
		cloud->points[i].z = coordinates[index].at<float>(0, 2);
		index++;
	}
	
	auto pclData = PointCloudData::getInstance(*cloud);
	pclData->setCloud(*cloud);
	// cout << "over" << "\n";
}

void YourThread::setPath(string pathArg)
{
	path = pathArg;
}