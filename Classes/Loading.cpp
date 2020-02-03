#include "Loading.h"

Loading::Loading(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.label_2->hide();
	ui.progressBar->setValue(0);
	
	// todo ╪сть

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
