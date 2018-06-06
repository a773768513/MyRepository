#pragma once
#include <qthread.h>
#include <Windows.h>

class CQThreadTextBrowser;
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
	CStrProcessingThread(CQThreadTextBrowser*  CSTCQThreadTextBrowser);
	~CStrProcessingThread();
	void  InputOpenFilePath(QString QSOpenFilePath);
	struct ManageThreadData
	{
		QString OpenFilePath;
		char* DataToManageThread;
	};

protected:
	virtual void run();
private:
	CQThreadTextBrowser*  CSTCQThreadTextBrowser;
	QString  CSTQSOpenFilePath;
	/// bool to force stop the thread
	bool  BStrForceStop;
	///flag to judge the thread is stop 
	HANDLE  HEndThreadFlag;

	QString  CSTQSTabText;
	FILE* pfDateBufFile;         /// buf the data real time 
	
	void ChangeQStringChar();
	void OpenOriginFile(char* pInputOriginFile);
	ManageThreadData  *pManageThreadData;
signals:
	void AppendData(char *AppendDataCorespond);
	void AppendDataManage(ManageThreadData* AppendDataManageThread);
};

