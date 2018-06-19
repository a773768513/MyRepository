#include "CFemtoMonitorcenter.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CFemtoMonitorcenter w;
	w.show();
	return a.exec();
}
