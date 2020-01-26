#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Reconstruction.h"

class Reconstruction : public QMainWindow
{
	Q_OBJECT

public:
	Reconstruction(QWidget *parent = Q_NULLPTR);

private:
	Ui::ReconstructionClass ui;
};
