#include "PointCloudData.h"

PointCloudData* PointCloudData::instance = nullptr;

PointCloudData::PointCloudData(PointCloud<PointXYZRGB> cloudArg)
{
	cloud = cloudArg;
	num = 0;
}

PointCloudData* PointCloudData::getInstance(PointCloud<PointXYZRGB> cloudArg)
{
	if (instance == nullptr) instance = new PointCloudData(cloudArg);
	return instance;
}

PointCloudData* PointCloudData::getInstance()
{
	return instance;
}

PointCloud<PointXYZRGB> PointCloudData::getCloud() const{
	return cloud;
}
	
void PointCloudData::setCloud(PointCloud<PointXYZRGB> cloudArg){
	cloud= cloudArg;
}

boost::shared_ptr<visualization::PCLVisualizer> PointCloudData::getViewer()
{
	return viewer;
}


void PointCloudData::setViewer(boost::shared_ptr<visualization::PCLVisualizer> viewerArg)
{
	viewer = viewerArg;
}

std::vector<int> PointCloudData::getIndices()
{
	return indices;
}

void PointCloudData::setIndices(std::vector<int> indicesArg)
{
	indices = indicesArg;
}

Ui::ReconstructionClass PointCloudData::getUI()
{
	return ui;
}

void PointCloudData::setUI(Ui::ReconstructionClass uiArg)
{
	ui = uiArg;
}

int PointCloudData::getNum()
{
	return num;
}

void PointCloudData::setNum()
{
	num++;
}

