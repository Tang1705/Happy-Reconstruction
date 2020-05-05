#include "Help.h"

Help::Help(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QPixmap *pixmap = new QPixmap(":/Reconstruction/image/reconstruction/help.png");
	pixmap->scaled(ui.label->size(), Qt::KeepAspectRatio);
	ui.label->setScaledContents(true);
	ui.label->setPixmap(*pixmap);
}

Help::~Help()
{
}
