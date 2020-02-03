#include "DisplayPic.h"

DisplayPic::DisplayPic(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

}

DisplayPic::~DisplayPic()
{
}

void DisplayPic::setPicUrl(QString pic)
{
	picUrl = pic;
	if(picUrl.isEmpty())
	{
		ui.label->setText("No Photo Taken");
	}else
	{
		ui.label->setPixmap(QPixmap(picUrl));
	}
}

// 确定
void DisplayPic::on_pushButton_clicked()
{
	emit getPicAction("confirmed");
	this->close();
}

// 取消
void DisplayPic::on_pushButton_2_clicked()
{
	emit getPicAction("canceled");
	this->close();
}
