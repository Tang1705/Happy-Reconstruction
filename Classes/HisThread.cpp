#include "HisThread.h"

HisThread::HisThread(PointCloud<PointXYZRGB>* cloudArg, PolygonMesh* meshArg)
{
	mesh = meshArg;
	cloud = cloudArg;
}

void HisThread::run()
{
	PointCloud<PointXYZRGB>::Ptr finalCloud = cloud->makeShared();
	NormalEstimation<PointXYZRGB, Normal> n;//法线估计对象
	PointCloud<Normal>::Ptr normals(new PointCloud<Normal>);//存储估计的法线的指针
	search::KdTree<PointXYZRGB>::Ptr tree(new search::KdTree<PointXYZRGB>);
	tree->setInputCloud(finalCloud);
	n.setInputCloud(finalCloud);
	n.setSearchMethod(tree);
	n.setKSearch(20);
	n.compute(*normals); //计算法线，结果存储在normals中

	//将点云和法线放到一起
	PointCloud<PointXYZRGBNormal>::Ptr cloud_with_normals(new PointCloud<PointXYZRGBNormal>);
	concatenateFields(*finalCloud, *normals, *cloud_with_normals);

	//创建搜索树
	search::KdTree<PointXYZRGBNormal>::Ptr tree2(new search::KdTree<PointXYZRGBNormal>);
	tree2->setInputCloud(cloud_with_normals);
	//创建Poisson对象，并设置参数
	Poisson<PointXYZRGBNormal> pn;
	pn.setConfidence(true); //是否使用法向量的大小作为置信信息。如果false，所有法向量均归一化。
	pn.setDegree(2); //设置参数degree[1,5],值越大越精细，耗时越久。
	pn.setDepth(8); //树的最大深度，求解2^d x 2^d x 2^d立方体元。由于八叉树自适应采样密度，指定值仅为最大深度。
	pn.setIsoDivide(8); //用于提取ISO等值面的算法的深度
	pn.setManifold(true); //是否添加多边形的重心，当多边形三角化时。 设置流行标志，如果设置为true，则对多边形进行细分三角话时添加重心，设置false则不添加
	pn.setManifold(false);
	pn.setOutputPolygons(false); //是否输出多边形网格（而不是三角化移动立方体的结果）
	//pn.setSamplesPerNode(3.0); //设置落入一个八叉树结点中的样本点的最小数量。无噪声，[1.0-5.0],有噪声[15.-20.]平滑
	pn.setSamplesPerNode(18); //设置落入一个八叉树结点中的样本点的最小数量。无噪声，[1.0-5.0],有噪声[15.-20.]平滑
	pn.setScale(1.25); //设置用于重构的立方体直径和样本边界立方体直径的比率。
	pn.setSolverDivide(8); //设置求解线性方程组的Gauss-Seidel迭代方法的深度
	//pn.setIndices();

	//设置搜索方法和输入点云
	pn.setSearchMethod(tree2);
	pn.setInputCloud(cloud_with_normals);
	
	//执行重构
	pn.performReconstruction(*mesh);
	// auto pclData = PointCloudData::getInstance(cloud);
	// pclData->getViewer()->removeAllPointClouds();
	// pclData->getViewer()->addPolygonMesh(mesh, "my");

}
