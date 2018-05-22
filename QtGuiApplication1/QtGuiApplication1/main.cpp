#include "QbarsetChartModule.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QbarsetChartModule w;
	w.show();
	return a.exec();
}
