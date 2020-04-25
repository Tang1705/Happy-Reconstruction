#pragma once

#include <QWidget>
#include "ui_Help.h"
#include <QTextCodec>

class Help : public QWidget
{
	Q_OBJECT

public:
	Help(QWidget *parent = Q_NULLPTR);
	~Help();

private:
	Ui::Help ui;
};
