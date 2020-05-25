#include "AboutDialog.h"
#include <QtWidgets/QDialog>
#include <QtWidgets/QtWidgets>

AboutDialog::AboutDialog(QWidget *parent)
	: QDialog(parent), ui(new Ui::AboutDialog)
{
	ui->setupUi(this);
	ui->textEdit->setReadOnly(true);
	auto w = ui->label->width();
	auto h = ui->label->height();
	ui->label->setPixmap(QPixmap(":/Reconstruction/image/common/logo.png").scaled(w, h, Qt::KeepAspectRatio));
}

AboutDialog::~AboutDialog()
{
}

void AboutDialog::on_pushButton_clicked() {
	QDialog::accept();
}
