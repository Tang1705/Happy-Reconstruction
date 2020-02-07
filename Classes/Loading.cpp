#include "Loading.h"

Loading::Loading(QWidget *parent)
	: QWidget(parent)
{
	// qss
	ui.setupUi(this); 
	QFile file("Resources/qss/aqua.qss");
	file.open(QFile::ReadOnly);
	QTextStream filetext(&file);
	QString stylesheet = filetext.readAll();
	this->setStyleSheet(stylesheet);
	file.close();

	ui.label_2->hide();
	ui.progressBar->setValue(0);

	// ±³¾°gif
	// QMovie *pic = new QMovie("Resources/image/loading.gif");
	// ui.label_4->setMovie(pic);
	// pic->start();

	// todo ¼ÓÔØ

	ui.progressBar->setValue(100);
	ui.label_2->show();
	ready2Enter = true;
}

Loading::~Loading()
{
}

void Loading::updateSlot()
{
	ui.progressBar->setValue(currentValue);
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
