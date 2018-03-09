#include "helloqt.h"
#include <QtWidgets/QApplication>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "MatchStrlenFile.h"
#include "StorageModule.h"


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	helloqt w;
	w.show();
	return a.exec();
}
