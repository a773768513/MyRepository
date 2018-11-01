#include "Qtgrid.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Qtgrid w;
	w.show();
	return a.exec();
}
