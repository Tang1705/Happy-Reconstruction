#include "Reconstruction.h"

Reconstruction::Reconstruction(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	calibData = new CalibrationData();
	calibrator = new Calibrator();
	dirModel = new TreeModel(this);
	td = new YourThread(&cloud);
	t = new MyThread;
	connect(td, SIGNAL(finished()), this, SLOT(setCloud()));
	connect(t, SIGNAL(finished()), this, SLOT(setCloud()));
	device = Device::getInstance();
	setStyle();
}

#pragma region Style
void Reconstruction::setStyle()
{
	this->setContentsMargins(0, 0, 0, 0);
	// this->setFixedSize(1240, 680);
	// ui.centralWidget->setGeometry(0, 40, 1240, 680);
	ui.centralWidget->show();

	// qss
	QFile file(":/qss/qss/flat.qss");
	file.open(QFile::ReadOnly);
	QTextStream filetext(&file);
	QString stylesheet = filetext.readAll();
	this->setStyleSheet(stylesheet);
	file.close();

	QPalette palette1;
	palette1.setColor(QPalette::Background, qRgba(62, 71, 128, 100)); //左侧
	ui.widget->setPalette(palette1);

	QPalette palette2;
	palette2.setColor(QPalette::Background, qRgba(255, 255, 255, 100)); //白色
	// palette2.setColor(QPalette::Background, qRgba(204, 213, 240, 100));	//背景
	ui.stackedWidget->setPalette(palette2);

	ui.stackedWidget->setCurrentIndex(0);
	setPicStyle();
	setButtonStyle();
}

void Reconstruction::setPicStyle()
{
	ui.label_9->setPixmap(QPixmap(":/icon/image/reconstruction/loading.png"));
	if (device->getHasCamera())
	{
		auto w = ui.label_11->width();
		auto h = ui.label_11->height();
		Mat blackImg(h, w, CV_8UC1, cv::Scalar::all(0));
		QImage qimage = cvtools::cvMat2qImage(blackImg);
		QPixmap pixmap = QPixmap::fromImage(qimage);
		ui.label_11->setPixmap(pixmap.scaled(w, h, Qt::KeepAspectRatio));
		liveViewTimer = startTimer(100);
	}
	else
	{
		ui.label_11->setPixmap(QPixmap(":/icon/image/calibration/novideo.png"));
		ui.pushButton_5->setEnabled(false);
		ui.pushButton_6->setEnabled(false);
		ui.pushButton_7->setEnabled(false);
		ui.pushButton_8->setEnabled(false);
	}

	ui.label_21->setPixmap(QPixmap(":/icon/image/projection/novideo.jpg"));
}

void Reconstruction::setButtonStyle()
{
	QString buttonStyle = "QPushButton{background-color:white;color: black;}"
		"QPushButton:hover{background-color:#e5ebfb; color: black;}"
		"QPushButton:pressed{background-color:rgb(204,213,240);border - style: inset; }";
	ui.pushButton->setStyleSheet(buttonStyle);
	ui.pushButton_2->setStyleSheet(buttonStyle);
	ui.pushButton_3->setStyleSheet(buttonStyle);
	// 给Button添加图标
	ui.pushButton->setIcon(QIcon(":/icon/image/common/camera.png"));
	ui.pushButton_2->setIcon(QIcon(":/icon/image/common/projection.png"));
	ui.pushButton_3->setIcon(QIcon(":/icon/image/common/3D.png"));

	// 相机标定界面
	ui.pushButton_5->setIcon(QIcon(":/icon/image/calibration/pics.png"));
	ui.pushButton_6->setIcon(QIcon(":/icon/image/calibration/camera.png"));
	ui.pushButton_7->setIcon(QIcon(":/icon/image/calibration/cal.png"));
	ui.pushButton_8->setIcon(QIcon(":/icon/image/calibration/save.png"));

	// 图案投影界面
	ui.pushButton_4->setIcon(QIcon(":/icon/image/projection/file.png"));

	// 三维重建界面
	ui.pushButton_13->setIcon(QIcon(":/icon/image/reconstruction/import.png"));
	ui.pushButton_14->setIcon(QIcon(":/icon/image/reconstruction/export.png"));
	ui.pushButton_15->setIcon(QIcon(":/icon/image/reconstruction/save2.png"));
	ui.pushButton_16->setIcon(QIcon(":/icon/image/reconstruction/color.png"));
}
#pragma endregion

#pragma region 界面菜单
void Reconstruction::on_pushButton_clicked()
{
	ui.stackedWidget->setCurrentIndex(0);
	// imgCount = 0;
	// dirModel = new TreeModel(this);
	// dirModel->clear();
	// ui.treeView->setModel(dirModel);
	// ui.stackedWidget->setCurrentIndex(0);
}

void Reconstruction::on_pushButton_2_clicked()
{
	ui.stackedWidget->setCurrentIndex(1);
}

void Reconstruction::on_pushButton_3_clicked()
{
	ui.stackedWidget->setCurrentIndex(2);
	updateQVTK(cloud, color);
	if (loadingStatus || reconstructStatus)
	{
		ui.label_9->setVisible(true);
	}
	else
	{
		ui.label_9->setVisible(false);
	}
}
#pragma endregion

#pragma region 多线程
void Reconstruction::setCloud()
{
	cout << cloud.width;
	ui.label_9->setVisible(false);
	
	if(loadingStatus)
	{
		cloud = t->getCloud();
		loadingStatus = false;
	}

	if(reconstructStatus)
	{
		reconstructStatus = false;
	}
	cout << cloud[0].r;
	
	updateQVTK(cloud, color);
}

void Reconstruction::updateQVTK(PointCloud<PointXYZRGB> cloud, QColor color)
{
	boost::shared_ptr<visualization::PCLVisualizer> viewer(new visualization::PCLVisualizer("3D Viewer"));
	viewer->setBackgroundColor(0.458, 0.529, 0.844);
	viewer->setPointCloudRenderingProperties(visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud");
	if (cloud.size() != 0)
	{
		PointCloud<PointXYZRGB>::Ptr cloudPtr(new PointCloud<PointXYZRGB>);
		cloudPtr = cloud.makeShared();

		int x = int(color.redF() * 255);
		int y = int(color.greenF() * 255);
		int z = int(color.blueF() * 255);
		visualization::PointCloudColorHandlerCustom<PointXYZRGB> cloud_color(cloudPtr, x, y, z);// 统一处理点云颜色
		viewer->addPointCloud(cloudPtr, cloud_color, "cloud");
		viewer->setPointCloudRenderingProperties(visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud");
	}
	ui.qvtkWidget->SetRenderWindow(viewer->getRenderWindow());
	ui.qvtkWidget->update();
}
#pragma endregion

#pragma region 系统标定-按钮

// 添加图像
void Reconstruction::on_pushButton_5_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(
		this, tr("open multiple image file"),
		"./", tr("Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)")); // todo 文件类型待确认

	if (fileName.isEmpty())
	{
		QMessageBox mesg;
		mesg.warning(this, "WARNING", "Failed to open picture");
		return;
	}
	else
	{
		calPath = fileName;
	}
}

// 相机拍摄
void Reconstruction::on_pushButton_6_clicked()
{
	killTimer(liveViewTimer);
	ui.pushButton_5->setEnabled(false);
	ui.pushButton_6->setEnabled(false);
	ui.pushButton_7->setEnabled(false);
	ui.pushButton_8->setEnabled(false);

	char path[100];
	sprintf(path, "calib%.2d", imgCount);
	fstools::mkDir(tr("./config/calib"), tr(path));

	device->getProjector()->displayPattern(0);
	//QTest::qSleep(500);
	for (unsigned int i = 0; i < 44; i++)
	{
		// Project pattern
		device->getProjector()->displayPattern(i);
		//QTest::qSleep(200);
		// Effectuate sleep (necessary with some camera implementations)
		QApplication::processEvents();

		// Aquire frame
		auto frame = device->getCamera()->getFrame();
		auto frameCV = cvtools::camFrame2Mat(frame);
		cvtColor(frameCV, frameCV, COLOR_BGR2GRAY);
		//parameter
		std::cout << cv::format("./config/calib/calib%.2d/%.2d.bmp", imgCount, i) << std::endl;
		imwrite(cv::format("./config/calib/calib%.2d/%.2d.bmp", imgCount, i), frameCV);

		auto qimage = cvtools::cvMat2qImage(frameCV);
		auto w = ui.label_11->width();
		auto h = ui.label_11->height();
		auto pixmap = QPixmap::fromImage(qimage);
		ui.label_11->setPixmap(pixmap.scaled(w, h, Qt::KeepAspectRatio));
	}

	imgCount++;
	liveViewTimer = startTimer(100);
	//parameter
	setDirModel(tr("./config/calib"));
	ui.treeView->setModel(dirModel);

	ui.pushButton_5->setEnabled(true);
	ui.pushButton_6->setEnabled(true);
	ui.pushButton_7->setEnabled(true);
	ui.pushButton_8->setEnabled(true);
	// if (calPath.isEmpty())
	// {
	// 	QMessageBox mesg;
	// 	mesg.warning(this, "WARNING", "Haven't uploaded calibration pictures!");
	// }
	// else
	// {
	// 	// todo 相机拍摄，存储照片集
	// }
	// 标定日志：显示拍摄照片集存储路径
	// ui.textBrowser_7->append("");
}

// 相机标定
void Reconstruction::on_pushButton_7_clicked()
{
	auto size = ui.spinBox->value();
	auto row = ui.spinBox_2->value();
	auto col = ui.spinBox_3->value();

	calibrator->setCornerSize(size);
	calibrator->setBoardRows(row);
	calibrator->setBoardCols(col);
	// todo 相机标定
	killTimer(liveViewTimer);
	calibrator->reset();

	std::vector<Mat> imgList;
	for (auto i = 0; i < dirModel->rowCount(); i++)
	{
		auto parent = dirModel->index(i, 0);
		auto imgNum = dirModel->rowCount(parent);
		for (auto j = 0; j < imgNum; j++)
		{
			imgList.push_back(getImage(i, j, GrayImageRole));
		}
		calibrator->addFrameSequence(imgList);
		imgList.clear();
	}
	calibData = calibrator->calibrate();
	std::cout << "calibration success!!!" << std::endl;
	calibData->print();
	ui.pushButton_6->setEnabled(true);

	if (device->getCamera()->isConnecting()) liveViewTimer = startTimer(100);

	// 相机参数栏：显示标定结果
	ui.textBrowser->append("");
	ui.textBrowser_2->append("");
	ui.textBrowser_3->append("");
	ui.textBrowser_4->append("");
}

// 保存结果
void Reconstruction::on_pushButton_8_clicked()
{
	QFileDialog fileDialog;
	QString fileName = fileDialog.getSaveFileName(this, "Open File", "", "Text File(*.txt)"); // todo 更改文件类型
	if (fileName.isEmpty())
	{
		return;
	}
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) // todo 更改文件类型
	{
		QMessageBox::warning(this, "error", "open file failure!");
		return;
	}
	else
	{
		// todo 保存结果
		QString selectedFilter;
		QString fileName = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("保存标定文件"), QString(), "*.xml",
		                                                &selectedFilter);
		calibData->saveXML(fileName);
	}
}

void Reconstruction::closeEvent(QCloseEvent*)
{
	killTimer(liveViewTimer);
	delete calibData;
	delete calibrator;
	delete dirModel;
}

void Reconstruction::timerEvent(QTimerEvent* event)
{
	if (event->timerId() != liveViewTimer)
	{
		std::cerr << "Something fishy..." << std::endl << std::flush;
		return;
	}

	auto frame = device->getCamera()->getFrame();

	auto frameCV = cvtools::camFrame2Mat(frame);
	cvtColor(frameCV, frameCV, cv::COLOR_BGR2GRAY);
	if (frameCV.rows == 0 || frameCV.cols == 0)
	{
		return;
	}

	frameCV = frameCV.clone();
	auto qimage = cvtools::cvMat2qImage(frameCV);

	// correct size only if label has no borders/frame!
	auto w = ui.label_11->width();
	auto h = ui.label_11->height();

	auto pixmap = QPixmap::fromImage(qimage);
	ui.label_11->setPixmap(pixmap.scaled(w, h, Qt::KeepAspectRatio));
}

void Reconstruction::setDirModel(const QString& dirname)
{
	QDir root_dir(dirname);

	//reset internal data
	dirModel->clear();

	auto dirlist = root_dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
	foreach(const QString & item, dirlist)
	{
		QDir dir(root_dir.filePath(item));

		QStringList filters;
		filters << "*.jpg" << "*.bmp" << "*.png";

		auto filelist = dir.entryList(filters, QDir::Files, QDir::Name);
		auto path = dir.path();

		//setup the model
		auto filecount = filelist.count();

		if (filecount < 1)
		{
			//no images  skip
			continue;
		}

		unsigned row = dirModel->rowCount();
		if (!dirModel->insertRow(row))
		{
			std::cout << "Failed model insert " << item.toStdString() << "(" << row << ")" << std::endl;
			continue;
		}

		// add the childrens
		auto parent = dirModel->index(row, 0);
		dirModel->setData(parent, item, Qt::DisplayRole);

		for (auto i = 0; i < filecount; i++)
		{
			const auto& filename = filelist.at(i);
			if (!dirModel->insertRow(i, parent))
			{
				std::cout << "Failed model insert " << filename.toStdString() << "(" << row << ")" << std::endl;
				break;
			}

			auto index = dirModel->index(i, 0, parent);
			dirModel->setData(index, QString("#%1 %2").arg(i, 2, 10, QLatin1Char('0')).arg(filename), Qt::DisplayRole);

			//additional data
			dirModel->setData(index, path + "/" + filename, ImageFilenameRole);
		}
	}

	if (dirModel->rowCount() >= 3)
	{
		ui.pushButton_7->setEnabled(true);
	}
	else
	{
		ui.pushButton_7->setEnabled(false);
	}
}

Mat Reconstruction::getImage(unsigned level, unsigned n, Role role)
{
	if (role != GrayImageRole && role != ColorImageRole)
	{
		//invalid args
		return Mat();
	}

	//try to load
	if (dirModel->rowCount() < static_cast<int>(level))
	{
		//out of bounds
		return cv::Mat();
	}
	auto parent = dirModel->index(level, 0);
	if (dirModel->rowCount(parent) < static_cast<int>(n))
	{
		//out of bounds
		return Mat();
	}

	auto index = dirModel->index(n, 0, parent);
	if (!index.isValid())
	{
		//invalid index
		return Mat();
	}

	auto filename = dirModel->data(index, ImageFilenameRole).toString();
	//    std::cout << "[" << (role==GrayImageRole ? "gray" : "color") << "] Filename: " << filename.toStdString() << std::endl;

	//load image
	auto rgb_image = imread(filename.toStdString());


	if (rgb_image.rows > 0 && rgb_image.cols > 0)
	{
		//color
		if (role == ColorImageRole)
		{
			return rgb_image;
		}

		//gray scale
		if (role == GrayImageRole)
		{
			Mat gray_image;
			cvtColor(rgb_image, gray_image, cv::COLOR_BGR2GRAY);
			return gray_image;
		}
	}

	return Mat();
}

#pragma endregion

#pragma region 三维重建-按钮

// 选择文件
void Reconstruction::on_pushButton_4_clicked()
{
	// 选择投影图案
	QString fileName = QFileDialog::getOpenFileName(
		this, tr("open image file"),
		"./", tr("Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)"));

	if (fileName.isEmpty())
	{
		QMessageBox mesg;
		mesg.warning(this, "WARNING", "Failed to open file");
		return;
	}

	ui.lineEdit->setText(fileName);

	// todo 接着进行投影操作
}

// 相机拍照
void Reconstruction::on_pushButton_9_clicked()
{
	// todo 相机拍照
	picPath = "Resources/image/test.png"; // 该行仅做测试使用	
	DisplayPic* picDlg = new DisplayPic();
	picDlg->setPicPath(picPath);
	connect(picDlg, SIGNAL(getPicAction(QString)), this, SLOT(setPicAction(QString)));
	picDlg->show();
}

void Reconstruction::setPicAction(QString action)
{
	if (action == "confirmed")
	{
		qDebug("confirmed");
		confirmPic = true;
	}
	else if (action == "canceled")
	{
		qDebug("canceled");
		confirmPic = false;
	}
}

// 保存照片
void Reconstruction::on_pushButton_10_clicked()
{
	// todo 保存照片
	if (confirmPic)
	{
		QString fileName = QFileDialog::getSaveFileName(this,
		                                                tr("save image"),
		                                                "",
		                                                tr("*.png;; *.jpg;; *.bmp;; All files(*.*)"));

		if (!fileName.isNull())
		{
			QImage iim(picPath); //创建一个图片对象,存储源图片
			QPainter painter(&iim); //设置绘画设备
			QFile file(fileName); //创建一个文件对象，存储用户选择的文件
			if (!file.open(QIODevice::ReadWrite))
			{
				return;
			}
			QByteArray ba;
			QBuffer buffer(&ba);
			buffer.open(QIODevice::WriteOnly);
			iim.save(&buffer, "JPG"); //把图片以流方式写入文件缓存流中
			file.write(ba); //将流中的图片写入文件对象当中
		}
	}
	else
	{
		QMessageBox mesg;
		mesg.warning(this, "WARNING", "Haven't taken picture!");
	}
}

// 开始重建
void Reconstruction::on_pushButton_17_clicked()
{
	// todo 开始重建
	reconstructStatus = true;
	on_pushButton_3_clicked();
	ui.label_9->setVisible(true);
	QCoreApplication::processEvents();
	td->start();
}

#pragma endregion

#pragma region 点云渲染-按钮

// 异常点选择
void Reconstruction::on_pushButton_11_clicked()
{
	// todo 异常点选择
}

// 异常点剔除
void Reconstruction::on_pushButton_12_clicked()
{
	// todo 异常点剔除
}

// 导入点云
void Reconstruction::on_pushButton_13_clicked()
{
	if (loadingStatus)
	{
		QMessageBox mesg;
		mesg.warning(this, "WARNING", "正在加载… ");
		return;
	}

	QString fileName = QFileDialog::getOpenFileName(
		this, tr("open multiple image file"),
		"./", tr("PCD files(*.pcd);;All files (*.*)")); // todo 文件类型待确认

	if (fileName.isEmpty())
	{
		QMessageBox mesg;
		mesg.warning(this, "WARNING", "Failed to open file");
		return;
	}

	ui.label_9->setVisible(true);
	QCoreApplication::processEvents();
	t->setPcd(fileName);
	t->start();
	loadingStatus = true;

	// todo 存储文件或文件路径
}

// 导出结果
void Reconstruction::on_pushButton_14_clicked()
{
	// todo 导出结果
}

// 保存截图
void Reconstruction::on_pushButton_15_clicked()
{
	QString fileName = QFileDialog::getSaveFileName(this,
	                                                tr("save screen shot"),
	                                                "",
	                                                tr("*.png;; *.jpg;; *.bmp;; All files(*.*)"));

	if (!fileName.isNull())
	{
		// 截图所选的控件暂时用 label_17 替代
		QPixmap pix = QPixmap::grabWidget(ui.qvtkWidget);
		pix.save(fileName);
	}
}

// 颜色选取
void Reconstruction::on_pushButton_16_clicked()
{
	QColor colortmp = QColorDialog::getColor(Qt::black);
	if (colortmp.isValid()) {
		color = colortmp;
		updateQVTK(cloud, color);
	}
}

// 帮助
void Reconstruction::on_pushButton_18_clicked()
{
	Help* help = new Help();
	help->show();
}
#pragma endregion
