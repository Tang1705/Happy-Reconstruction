#pragma once

#include <qthread.h>
#include <pcl/point_types.h>
#include <pcl/io/vtk_lib_io.h>
#include "CoreAlgorithm.h"

using namespace std;
using namespace pcl;

class YourThread :
	public QThread
{
public:
	YourThread(PointCloud<PointXYZRGB> *cloud);
	~YourThread(){};

private:
	PointCloud<PointXYZRGB> *cloud;
protected:
	void run();
};
