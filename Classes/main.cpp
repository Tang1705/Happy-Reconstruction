#include <QtWidgets/QApplication>
#include "Loading.h"
#include "Reconstruction.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Loading l;
	l.show();
	return a.exec();
}
