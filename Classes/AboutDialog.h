#pragma once

#include "ui_aboutdialog.h"
#include <QtWidgets/QDialog>

namespace Ui {
	class AboutDialog;
}

class AboutDialog : public QDialog
{
	Q_OBJECT

public:
	AboutDialog(QWidget *parent = Q_NULLPTR);
	~AboutDialog();

public slots:
	void on_pushButton_clicked();

private:
	Ui::AboutDialog *ui;
};
