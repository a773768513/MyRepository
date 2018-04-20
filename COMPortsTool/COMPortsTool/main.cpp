#include "CCOMPortsTool.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CCOMPortsTool w;
	w.show();
	return a.exec();
}
