#include "cpackageinput.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CPackageInput w;
	w.show();
	return a.exec();
}
