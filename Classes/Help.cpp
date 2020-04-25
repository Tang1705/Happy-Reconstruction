#include "Help.h"

Help::Help(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	// QTextCodec *codec = QTextCodec::codecForName("utf-8");	//不起作用
	// QTextCodec::setCodecForLocale(codec);
	ui.textBrowser->setText(QString::fromUtf8("help"));	// 暂时不能写显示中文
}

Help::~Help()
{
}
