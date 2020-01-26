#include "Reconstruction.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Reconstruction w;
	w.show();
	return a.exec();
}
