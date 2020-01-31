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
}
#pragma endregion 

#pragma region 相机标定-按钮

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
	}

	// todo 存储文件或文件路径
}

// 相机拍摄
void Reconstruction::on_pushButton_6_clicked()
{
	// todo 相机拍摄，存储照片集

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
	ui.textBrowser_5->append("");
	ui.textBrowser_6->append("");
}

// 保存结果
void Reconstruction::on_pushButton_8_clicked()
{
	QFileDialog fileDialog;
	QString fileName = fileDialog.getSaveFileName(this, "Open File", "", "Text File(*.txt)");	// todo 更改文件类型
	if (fileName == "")
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

#pragma region 图案投影-按钮

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

	// todo 然后出来一个界面 拍摄到的照片，然后下面三个按钮：确定 取消
}

// 保存照片
void Reconstruction::on_pushButton_10_clicked()
{
	// todo 保存照片
}
#pragma endregion 

#pragma region 三维重建-按钮

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
	QString fileName = QFileDialog::getOpenFileName(
		this, tr("open multiple image file"),
		"./", tr("Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)"));		// todo 文件类型待确认

	if (fileName.isEmpty())
	{
		QMessageBox mesg;
		mesg.warning(this, "WARNING", "Failed to open file");
		return;
	}

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
	// todo 保存截图
}

// 颜色选取
void Reconstruction::on_pushButton_16_clicked()
{
	QColor color = QColorDialog::getColor(Qt::black);
	if (color.isValid()){
		// qDebug("x:%f, %f, %f",color.redF(), color.greenF(), color.blueF());
		// todo 颜色选取框已选择颜色color，接下来对color进行处理
	}
}
#pragma endregion
