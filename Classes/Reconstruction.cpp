#include "Reconstruction.h"
#include <QMessageBox>
#include <QFileDialog>

Reconstruction::Reconstruction(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.stackedWidget->setCurrentIndex(0);
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
	// todo 添加图像
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
	// 选择投影图案 todo 为什么要选两次？
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
#pragma endregion 