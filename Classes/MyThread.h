#pragma once

#include <qthread.h>
#include <pcl/point_types.h>
#include <pcl/io/vtk_lib_io.h>

using namespace std;
using namespace pcl;

class MyThread :
	public QThread
{
public:
	MyThread();
	~MyThread();
	void setPcd(QString str);
	PointCloud<PointXYZRGB> getCloud();

private:
	string pcd;
	PointCloud<PointXYZRGB> cloud;

protected:
	void run();
};

