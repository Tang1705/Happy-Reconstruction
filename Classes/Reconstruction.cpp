#include "Reconstruction.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>

Reconstruction::Reconstruction(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.stackedWidget->setCurrentIndex(0);
	/* 如果用on_XXX_clicked()定义槽，Qt的元对象QMetaObject会自动的寻找相关的信号并链接，不能再用connect()链接了，否则就会连接两次。
	 connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
	 connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_2_clicked()));
	 connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(on_pushButton_3_clicked()));
	 connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(on_pushButton_4_clicked()));
	 connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(on_pushButton_5_clicked()));
	 connect(ui.pushButton_6, SIGNAL(clicked()), this, SLOT(on_pushButton_6_clicked()));
	 connect(ui.pushButton_7, SIGNAL(clicked()), this, SLOT(on_pushButton_7_clicked()));
	 connect(ui.pushButton_8, SIGNAL(clicked()), this, SLOT(on_pushButton_8_clicked()));
	 connect(ui.pushButton_9, SIGNAL(clicked()), this, SLOT(on_pushButton_9_clicked()));
	 connect(ui.pushButton_10, SIGNAL(clicked()), this, SLOT(on_pushButton_10_clicked()));
	 connect(ui.pushButton_11, SIGNAL(clicked()), this, SLOT(on_pushButton_11_clicked()));
	 connect(ui.pushButton_12, SIGNAL(clicked()), this, SLOT(on_pushButton_12_clicked()));
	 connect(ui.pushButton_13, SIGNAL(clicked()), this, SLOT(on_pushButton_13_clicked()));
	 connect(ui.pushButton_14, SIGNAL(clicked()), this, SLOT(on_pushButton_14_clicked()));
	 connect(ui.pushButton_15, SIGNAL(clicked()), this, SLOT(on_pushButton_15_clicked()));
	 connect(ui.pushButton_16, SIGNAL(clicked()), this, SLOT(on_pushButton_16_clicked()));
	*/
}

#pragma region 相机标定按钮
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
}

void Reconstruction::on_pushButton_5_clicked()
{
	// 添加图像
	QString fileName = QFileDialog::getOpenFileName(
		this, tr("open multiple image file"),
		"./", tr("Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)"));		// todo 文件类型待确认

	if (fileName.isEmpty())
	{
		QMessageBox mesg;
		mesg.warning(this, "WARNING", "Failed to open picture");
		return;
	}

	// todo 将文件存储在某变量中
}

void Reconstruction::on_pushButton_6_clicked()
{
	// todo 相机拍摄
}

void Reconstruction::on_pushButton_7_clicked()
{
	// todo 相机标定
}

void Reconstruction::on_pushButton_8_clicked()
{
	// todo 保存结果
}
#pragma endregion 

#pragma region 图案投影按钮
void Reconstruction::on_pushButton_4_clicked()
{
	// 选择投影图案
	QString fileName = QFileDialog::getOpenFileName(
		this, tr("open image file"),
		"./", tr("Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)"));

	if (fileName.isEmpty())
	{
		QMessageBox mesg;
		mesg.warning(this, "WARNING", "Failed to open picture");
		return;
	}

	ui.lineEdit->setText(fileName);

	// todo 接着进行投影操作
}
void Reconstruction::on_pushButton_9_clicked()
{
	// todo 相机拍照
}

void Reconstruction::on_pushButton_10_clicked()
{
	// todo 保存照片
}
#pragma endregion 

#pragma region 三维重建按钮
void Reconstruction::on_pushButton_11_clicked()
{
	// todo 异常点选择
}

void Reconstruction::on_pushButton_12_clicked()
{
	// todo 异常点剔除
}

void Reconstruction::on_pushButton_13_clicked()
{
	// todo 导入点云
}

void Reconstruction::on_pushButton_14_clicked()
{
	// todo 导出结果
}

void Reconstruction::on_pushButton_15_clicked()
{
	// todo 保存截图
}

void Reconstruction::on_pushButton_16_clicked()
{
	// 颜色选取
	QColor color = QColorDialog::getColor(Qt::black);
	if (color.isValid()){
		// qDebug("x:%f, %f, %f",color.redF(), color.greenF(), color.blueF());
		// todo 颜色选取框已选择颜色color，接下来对color进行处理
	}
}
#pragma endregion 