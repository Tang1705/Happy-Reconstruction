#include "MyThread.h"

MyThread::MyThread()
{

}

void MyThread::run()
{
	if(!pcd.empty())
	{
		PointCloud<PointXYZRGB>::Ptr cloudPtr(new PointCloud<PointXYZRGB>);
		io::loadPCDFile(pcd, *cloudPtr);
		cloud = *cloudPtr;
	}
}

void MyThread::setPcd(QString str)
{
	pcd = str.toStdString();
}

PointCloud<PointXYZRGB> MyThread::getCloud()
{
	return cloud;
}

MyThread::~MyThread()
{
}
