#include "CMutipleThreadQtextBrowser.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CMutipleThreadQtextBrowser w;
	w.show();
	return a.exec();
}
