#pragma once

#include <qthread.h>
#include <pcl/point_types.h>
#include <pcl/io/vtk_lib_io.h>
#include "PointCloudData.h"

using namespace std;
using namespace pcl;

class YourThread :
	public QThread
{
public:
	YourThread(PointCloud<PointXYZRGB> *cloud);
	~YourThread(){}
	void setPath(string pathArg);
	

private:
	PointCloud<PointXYZRGB> *cloud;
	string path;
protected:
	void run();
};
