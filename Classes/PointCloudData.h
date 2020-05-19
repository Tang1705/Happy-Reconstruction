#pragma once
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/io/vtk_lib_io.h>
#include "Reconstruction.h"

using namespace pcl;

class PointCloudData
{
private:
	PointCloudData(PointCloud<PointXYZRGB> cloudArg);
	~PointCloudData(){};
	PointCloud<PointXYZRGB> cloud;
	boost::shared_ptr<visualization::PCLVisualizer> viewer;
	std::vector<int> indices;
	Ui::ReconstructionClass ui;
	int num;// 用于框选删除点云的名称
	
public:
	static PointCloudData* getInstance();
	static PointCloudData* getInstance(PointCloud<PointXYZRGB> cloudArg);
	static PointCloudData* instance ;
	PointCloud<PointXYZRGB> getCloud() const;
	void setCloud(PointCloud<PointXYZRGB> cloudArg);
	boost::shared_ptr<visualization::PCLVisualizer> getViewer();
	void setViewer(boost::shared_ptr<visualization::PCLVisualizer> viewerArg);
	std::vector<int> getIndices();
	void setIndices(std::vector<int> indicesArg);
	Ui::ReconstructionClass getUI();
	void setUI(Ui::ReconstructionClass uiArg);
	int getNum();
	void setNum();
};
