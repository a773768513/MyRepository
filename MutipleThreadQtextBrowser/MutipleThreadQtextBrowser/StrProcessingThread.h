#pragma once
#include <qthread.h>
#include "QThreadTextBrowser.h"
///
///define the length to storage the package data
#ifndef __PACKAGE_LENGTH__
#define __PACKAGE_LENGTH__
#define PACKAGE_LENGTH  1024*64
#endif // !__PACKE_LENGTH__
///
///define the length to stack fgets the line data
#ifndef __READ_SIZE__
#define __READ_SIZE__
#define READ_SIZE  512
#endif // !__READ-SIZE__

class CStrProcessingThread :
	public QThread
{
	Q_OBJECT
public:
	CStrProcessingThread(QString  QSOpenFilePath, CQThreadTextBrowser *ThreadTextbrower);
	~CStrProcessingThread();
	CQThreadTextBrowser *CSTCQThreadTextBrowser;
	QString  CSTQSOpenFilePath;
protected:
	virtual void run();
private:
	QString  CSTQSTabText;
	FILE* pfDateBufFile;         /// buf the data real time 
	
	void ChangeQStringChar();
	void OpenOriginFile(char* pInputOriginFile);
	struct AppendDataCorrespond
	{
		char* LineData;
		CQThreadTextBrowser*  ThreadCorrespondTextbrowser;
	};

signals:
	void AppendData(AppendDataCorrespond *AppendDataCorespond);
};

