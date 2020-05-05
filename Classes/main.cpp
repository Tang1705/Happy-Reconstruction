#include <QtWidgets/QApplication>
#include "Loading.h"
#include "Reconstruction.h"
#include <windows.h>

int main(int argc, char *argv[])
{
	AllocConsole();//分配控制台
	freopen("CONOUT$", "w+t", stdout);//向控制台输出
	QApplication a(argc, argv);
	Loading l;
	l.show();
	return a.exec();
}
