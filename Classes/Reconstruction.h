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

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
	void on_pushButton_5_clicked();
	void on_pushButton_6_clicked();
	void on_pushButton_7_clicked();
	void on_pushButton_8_clicked();
	void on_pushButton_9_clicked();
	void on_pushButton_10_clicked();
	void on_pushButton_11_clicked();
	void on_pushButton_12_clicked();
	void on_pushButton_13_clicked();
	void on_pushButton_14_clicked();
	void on_pushButton_15_clicked();
	void on_pushButton_16_clicked();
};
