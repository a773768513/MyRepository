#pragma once
#include "qthread.h"

#include <Windows.h>



#ifndef __PACKAGE_LENGTH__
#define __PACKAGE_LENGTH__
#define PACKAGE_LENGTH 1024*64
#endif

#ifndef  __READ_SIZE__
#define  __READ_SIZE__
#define  READ_SIZE 1024
#endif

class CReadDataThread :
	public QThread
{
	Q_OBJECT
public:
	CReadDataThread(QObject *parent = Q_NULLPTR);
	~CReadDataThread();

	void InputOpenFilePath(QString QSOpenFilePath);
	bool BThreadForceStop;
	HANDLE HEndThreadFlag;

protected:
	virtual void run();

private:
	QString OpenFilePath;

	void OpenOriginFile();

signals :
	void EmitErrorMessage(QString QSErrorMessage);
	void EmitDataManageThread(char* pDataManageThread);


};

