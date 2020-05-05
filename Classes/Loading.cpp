#include "Loading.h"

Loading::Loading(QWidget *parent)
	: QWidget(parent)
{
	
	setStyle();
	setWindowFlags(Qt::FramelessWindowHint);
	ui.label_2->hide();
	// ui.progressBar->setValue(0);
	// QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
	// ui.progressBar->setGraphicsEffect(opacityEffect);
	// opacityEffect->setOpacity(0.9);

	// todo ¼ÓÔØ
	// ui.progressBar->setValue(100);

	ui.label->hide();
	ui.label_2->show();
	ready2Enter = true;
}

Loading::~Loading()
{
}

void Loading::setStyle()
{
	// qss
	ui.setupUi(this);
	QFile file(":/qss/qss/aqua.qss");
	file.open(QFile::ReadOnly);
	QTextStream filetext(&file);
	QString stylesheet = filetext.readAll();
	this->setStyleSheet(stylesheet);
	file.close();

	// Press any key to continue
	QPixmap *pixmap_press = new QPixmap(":/icon/image/loading/press.png");
	pixmap_press->scaled(ui.label_2->size(), Qt::KeepAspectRatio);
	ui.label_2->setScaledContents(true);
	ui.label_2->setPixmap(*pixmap_press);

	//3D reconstruction
	QPixmap *pixmap_label = new QPixmap(":/icon/image/loading/label.png");
	pixmap_label->scaled(ui.label_3->size(), Qt::KeepAspectRatio);
	ui.label_3->setScaledContents(true);
	ui.label_3->setPixmap(*pixmap_label);

	// ±³¾°
	QPixmap *pixmap = new QPixmap(":/Reconstruction/image/loading/loading.png");
	pixmap->scaled(ui.label_4->size(), Qt::KeepAspectRatio);
	ui.label_4->setScaledContents(true);
	ui.label_4->setPixmap(*pixmap);
}


void Loading::updateSlot()
{
	// ui.progressBar->setValue(currentValue);
}

void Loading::mousePressEvent(QMouseEvent *event)
{
	if(ready2Enter)
	{
		if (event->button() == Qt::LeftButton)
		{	
			this->hide();
			Reconstruction *w = new Reconstruction();
			w->show();
		}
	}
}
