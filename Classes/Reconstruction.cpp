#include "Reconstruction.h"

Reconstruction::Reconstruction(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.stackedWidget->setCurrentIndex(0);
	this->setContentsMargins(0, 0, 0, 0);
	this->setFixedSize(1110, 580);
	ui.centralWidget->setGeometry(0, 40, 1110, 400);
	ui.centralWidget->show();

	/* 如果用on_XXX_clicked()定义槽，Qt的元对象QMetaObject会自动的寻找相关的信号并链接，不能再用connect()链接了，否则就会连接两次。
	 connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
	*/
	// qss
	QFile file("Resources/qss/lightindigo.qss");
	file.open(QFile::ReadOnly);
	QTextStream filetext(&file);
	QString stylesheet = filetext.readAll();
	this->setStyleSheet(stylesheet);
	this->setStyle(QStyleFactory::create("Fusion"));
	file.close();
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
	ui.textBrowser_5->append("");
	ui.textBrowser_6->append("");
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
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("save screen shot"),
		"",
		tr("*.png;; *.jpg;; *.bmp;; All files(*.*)"));

	if (!fileName.isNull())
	{
		// 截图所选的控件暂时用 label_17 替代
		QPixmap pix = QPixmap::grabWidget(ui.label_17);
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
