#include "helloqt.h"
#include  <qmessagebox.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <qmessagebox.h>
#include "MatchStrlenFile.h"
#include "StorageModule.h"

helloqt::helloqt(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.pushButton->setVisible(false);
}

helloqt::~helloqt()
{

}
void helloqt::Btn_OpenClick()
{
	QMessageBox msg;
	msg.setText("helloworld");
	msg.exec();
}
char* helloqt::QStringToChar(QString QSOriginStr, char** StrArray)
{
	QByteArray QBStrArrayBuf = QSOriginStr.toLatin1();
	*StrArray = QBStrArrayBuf.data();
	return *StrArray;
}
void helloqt::Btn_MatchClick()
{
	QString  QSMatchStr;
	QSMatchStr = ui.InputStrLineEdit->text();
	QString QSInputFile = ui.InputFileLineEdit->text();
	QString QSOutputFile = ui.OutputFileLineEdit->text();
	QMessageBox msg_time;

	char* pInputStr;
	int   InputStrLength;
	char* pInputFile;
	char* pOutputFile;
	char* pStandardFile;

	clock_t clockStartTime, clockFinishTime;
	double  dRunTotalTime;
	clockStartTime = clock();

	///
	///change the QSstring to char array
	QByteArray QBStrArrayBuf = QSMatchStr.toLatin1();
	pInputStr = QBStrArrayBuf.data();

	QByteArray QBInputFileBuf = QSInputFile.toLatin1();
	pInputFile = QBInputFileBuf.data();

	QByteArray  QBOutputFileBuf = QSOutputFile.toLatin1();
	pOutputFile = QBOutputFileBuf.data();

	InputStrLength = strlen(pInputStr);

	pStandardFile = NULL;

	if (InputStrLength < (READ_SIZE - 1))
	{
		if (MatchLessLengthStrInFile(pInputStr, InputStrLength, pInputFile, pOutputFile, pStandardFile))
		{
			return;
		}
	}
	else
	{
		if (MatchMoreLengthStrInFile(pInputStr, InputStrLength, pInputFile, pOutputFile, pStandardFile))
		{
			return;
		}
	}
	
	clockFinishTime = clock();
	dRunTotalTime = (double)(clockFinishTime - clockStartTime) / CLOCKS_PER_SEC;
	QString msg_RunTime = QString::number(dRunTotalTime);
	msg_time.setText("use times is" + msg_RunTime + "s");
}