#include "Reconstruction.h"

Reconstruction::Reconstruction(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	t = new MyThread;
	connect(t, SIGNAL(finished()), this, SLOT(setCloud()));

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
	palette1.setColor(QPalette::Background, qRgba(62, 71, 128, 100));	//左侧
	ui.widget->setPalette(palette1);

	QPalette palette2;
	palette2.setColor(QPalette::Background, qRgba(255, 255, 255, 100));	//白色
	// palette2.setColor(QPalette::Background, qRgba(204, 213, 240, 100));	//背景
	ui.stackedWidget->setPalette(palette2);

	ui.stackedWidget->setCurrentIndex(0);
	setPicStyle();
	setButtonStyle();
}
void Reconstruction::setPicStyle()
{
	ui.label_9->setPixmap(QPixmap(":/icon/image/reconstruction/loading.png"));
	ui.label_11->setPixmap(QPixmap(":/icon/image/calibration/novideo.png"));
	ui.label_21->setPixmap(QPixmap(":/icon/image/projection/novideo.jpg"));
}
void Reconstruction::setButtonStyle()
{
	QString buttonStyle = "QPushButton{background-color:white;color: black;}"
		"QPushButton:hover{background-color:#cceeff; color: black;}"
		"QPushButton:pressed{background-color:rgb(85, 170, 255);border - style: inset; }";
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
}

void Reconstruction::on_pushButton_2_clicked()
{
	ui.stackedWidget->setCurrentIndex(1);
}

void Reconstruction::on_pushButton_3_clicked()
{
	ui.stackedWidget->setCurrentIndex(2);
	updateQVTK(cloud);
	if(loadingStatus)
	{
		ui.label_9->setVisible(true);
	}else
	{
		ui.label_9->setVisible(false);
	}
}
#pragma endregion 

#pragma region 多线程
void Reconstruction::setCloud()
{
	ui.label_9->setVisible(false);
	loadingStatus = false;
	cloud = t->getCloud();
	updateQVTK(cloud);
}
void Reconstruction::updateQVTK(PointCloud<PointXYZRGB> cloud)
{
	boost::shared_ptr<visualization::PCLVisualizer> viewer(new visualization::PCLVisualizer("3D Viewer"));
	viewer->setBackgroundColor(0.458, 0.529, 0.844);
	viewer->setPointCloudRenderingProperties(visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud");
	if (cloud.size() != 0)
	{
		PointCloud<PointXYZRGB>::Ptr cloudPtr(new PointCloud<PointXYZRGB>);
		cloudPtr = cloud.makeShared();
		viewer->addPointCloud(cloudPtr, "cloud");
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
		"./", tr("Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)"));		// todo 文件类型待确认

	if (fileName.isEmpty())
	{
		QMessageBox mesg;
		mesg.warning(this, "WARNING", "Failed to open picture");
		return;
	}else
	{
		calPath = fileName;
	}
}

// 相机拍摄
void Reconstruction::on_pushButton_6_clicked()
{
	if(calPath.isEmpty())
	{
		QMessageBox mesg;
		mesg.warning(this, "WARNING", "Haven't uploaded calibration pictures!");
	}else
	{
		// todo 相机拍摄，存储照片集
	}
	// 标定日志：显示拍摄照片集存储路径
	ui.textBrowser_7->append("");
}

// 相机标定
void Reconstruction::on_pushButton_7_clicked()
{
	int size = ui.spinBox->value();
	int row = ui.spinBox_2->value();
	int col = ui.spinBox_3->value();
	// todo 相机标定


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
	QString fileName = fileDialog.getSaveFileName(this, "Open File", "", "Text File(*.txt)");	// todo 更改文件类型
	if (fileName.isEmpty())
	{
		return;
	}
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))	// todo 更改文件类型
	{
		QMessageBox::warning(this, "error", "open file failure!");
		return;
	}
	else
	{
		// todo 保存结果
	}
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
	picPath = "Resources/image/test.png";		// 该行仅做测试使用	
	DisplayPic *picDlg = new DisplayPic();
	picDlg->setPicPath(picPath);
	connect(picDlg, SIGNAL(getPicAction(QString)), this, SLOT(setPicAction(QString)));
	picDlg->show();
}

void Reconstruction::setPicAction(QString action)
{
	if(action=="confirmed")
	{
		qDebug("confirmed");
		confirmPic = true;
	}else if(action=="canceled")
	{
		qDebug("canceled");
		confirmPic = false;
	}
}

// 保存照片
void Reconstruction::on_pushButton_10_clicked()
{
	// todo 保存照片
	if(confirmPic)
	{
		QString fileName = QFileDialog::getSaveFileName(this,
		tr("save image"),
		"",
		tr("*.png;; *.jpg;; *.bmp;; All files(*.*)"));

		if (!fileName.isNull())
		{
			QImage iim(picPath);//创建一个图片对象,存储源图片
			QPainter painter(&iim);//设置绘画设备
			QFile file(fileName);//创建一个文件对象，存储用户选择的文件
			if (!file.open(QIODevice::ReadWrite)) {
					return;
			}
			QByteArray ba;
			QBuffer buffer(&ba);
			buffer.open(QIODevice::WriteOnly);
			iim.save(&buffer, "JPG");//把图片以流方式写入文件缓存流中
			file.write(ba);//将流中的图片写入文件对象当中
		}
	}else
	{
		QMessageBox mesg;
		mesg.warning(this, "WARNING", "Haven't taken picture!");
	}
}

// 开始重建
void Reconstruction::on_pushButton_17_clicked()
{
	// todo 开始重建
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
	if(loadingStatus)
	{
		QMessageBox mesg;
		mesg.warning(this, "WARNING", "正在加载… ");
		return;
	}

	QString fileName = QFileDialog::getOpenFileName(
	this, tr("open multiple image file"),
	"./", tr("PCD files(*.pcd);;All files (*.*)"));		// todo 文件类型待确认

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
	color = QColorDialog::getColor(Qt::black);
	if (color.isValid()){
		// qDebug("x:%f, %f, %f",color.redF(), color.greenF(), color.blueF());
		// todo 颜色选取框已选择颜色color，接下来对color进行处理
	}
}
#pragma endregion
