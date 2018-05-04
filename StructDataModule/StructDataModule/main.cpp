#include "CStructDataModule.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CStructDataModule w;
	w.show();
	return a.exec();
}
