#pragma once

#include <QWidget>
#include "ui_Loading.h"
#include "Reconstruction.h"
#include <QMouseEvent>

class Loading : public QWidget
{
	Q_OBJECT

public:
	Loading(QWidget *parent = Q_NULLPTR);
	~Loading();

private:
	Ui::Loading ui;
	bool ready2Enter = false;
	int currentValue = 0;
	void updateSlot();

protected:
	void mousePressEvent(QMouseEvent *);

};
