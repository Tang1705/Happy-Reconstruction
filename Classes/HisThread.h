#pragma once

#include <qthread.h>
#include <pcl/point_types.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <pcl/surface/poisson.h>
#include <pcl/PolygonMesh.h>
#include <pcl/features/normal_3d.h>  
#include <pcl/features/normal_3d_omp.h>

using namespace std;
using namespace pcl;

class HisThread :
	public QThread
{
public:
	HisThread(PointCloud<PointXYZRGB>* cloud,PolygonMesh* meshArg);
	~HisThread(){};
	

private:
	PolygonMesh* mesh;// 多变形网格，用于存储结果
	PointCloud<PointXYZRGB>* cloud;

protected:
	void run();
};
