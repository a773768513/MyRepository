#pragma once

#include <qthread.h>


#ifndef  __READ_LINE_LENGTH__
#define  __READ_LINE_LENGTH__  1024*8
#endif
class CQReadDataThread :
	public QThread
{
public:
	CQReadDataThread();
	~CQReadDataThread();
public:
	void  WriteOpenFilePath(QString QSWriteOpenFilePath);
protected:
	virtual void run();
private:
	FILE* fpOpenFile;
	char* pReadLineData = (char*)malloc(sizeof(char)*__READ_LINE_LENGTH__);
	bool  bForceStop;
private:
	QString  QSOpenFilePath;
	void OpenFileAndRead();
	void CycleReadData();
signals:
	void emitdata(char* pData);
};

