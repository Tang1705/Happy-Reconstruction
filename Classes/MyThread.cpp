#include "MyThread.h"

MyThread::MyThread()
{

}

void MyThread::run()
{
	if(!pcd.empty())
	{
		PointCloud<PointXYZRGB>::Ptr cloudPtr(new PointCloud<PointXYZRGB>);
		if (QString::fromStdString(pcd).endsWith(".pcd", Qt::CaseInsensitive))
			io::loadPCDFile(pcd, *cloudPtr);
		else if (QString::fromStdString(pcd).endsWith(".ply", Qt::CaseInsensitive))
			io::loadPLYFile(pcd, *cloudPtr);
		cloud = *cloudPtr;
		cout << "hhhhhhhhhhhhhh," << cloud.size() << "\n";
	}

	auto pclData = PointCloudData::getInstance(cloud);
	pclData->setCloud(cloud);
	

}

void MyThread::setPcd(QString str)
{
	QTextCodec* code = QTextCodec::codecForName("GB2312");//解决中文路径问题
	pcd = code->fromUnicode(str).data();
	// pcd = str.toStdString();
}

PointCloud<PointXYZRGB> MyThread::getCloud()
{
	return cloud;
}
