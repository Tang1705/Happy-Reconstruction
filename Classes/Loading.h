#pragma once

#include <QWidget>
#include "ui_Loading.h"
#include "Reconstruction.h"
#include <QMouseEvent>
#include <QGraphicsOpacityEffect>
#include "Device.h"

class Loading : public QWidget
{
	Q_OBJECT

public:
	Loading(QWidget *parent = Q_NULLPTR);
	~Loading();

private:
	Ui::Loading ui;
	bool ready2Enter = false;
	Device* device;
	int currentValue = 0;
	void updateSlot();
	void setStyle();

protected:
	void mousePressEvent(QMouseEvent *);

};
