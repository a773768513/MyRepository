#include "QReadDataThread.h"
#include <qdebug.h>

CQReadDataThread::CQReadDataThread()
{
	QSOpenFilePath.clear();
	bForceStop = false;
}


CQReadDataThread::~CQReadDataThread()
{
	free(pReadLineData);
}
void CQReadDataThread::run()
{
	if(QSOpenFilePath.isEmpty())
	{
		qDebug("FailReadQSOpenFilePAath");
		return;
	}
	OpenFileAndRead();
	CycleReadData();
}

void CQReadDataThread::OpenFileAndRead()
{
	QByteArray  QBOpenFilePathBuf = QSOpenFilePath.toLatin1();
	char *pOpenFile=QBOpenFilePathBuf.data();
	fpOpenFile = fopen(pOpenFile, "r+");
	if (fpOpenFile == NULL)
	{
		return;
	}
}
void CQReadDataThread::CycleReadData()
{
	while (!feof(fpOpenFile))
	{
		if (bForceStop)
		{
			return;
		}
		pReadLineData[__READ_LINE_LENGTH__ - 2] = '\0';
		fgets(pReadLineData, __READ_LINE_LENGTH__, fpOpenFile);
		emit  emitdata(pReadLineData);
	}
	return;
}