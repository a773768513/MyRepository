
#include "QThreadTextBrowser.h"
#include <Windows.h>
#include <qcolor.h>
#include "AssertModule.h"
#include <process.h>
CStrProcessingThread::CStrProcessingThread(CQThreadTextBrowser*  CCQThreadTextBrowser)
{
	BStrForceStop = false;
	HEndThreadFlag = CreateEvent(NULL, TRUE, FALSE, NULL);
	ResetEvent(HEndThreadFlag);
	CSTCQThreadTextBrowser = CCQThreadTextBrowser;
	pManageThreadData = new ManageThreadData;
}
void  CStrProcessingThread::InputOpenFilePath(QString QSOpenFilePath)
{
	this->CSTQSOpenFilePath = QSOpenFilePath;
	pManageThreadData->OpenFilePath = QSOpenFilePath;
}
CStrProcessingThread::~CStrProcessingThread()
{
	BStrForceStop = TRUE;
	WaitForSingleObject(HEndThreadFlag, INFINITE);
	CloseHandle(HEndThreadFlag);
	delete pManageThreadData;
}
void CStrProcessingThread::run()
{
	ChangeQStringChar();
	SetEvent(HEndThreadFlag);
}
void CStrProcessingThread::ChangeQStringChar()
{
	char* pInputOriginFile;                 
	QByteArray pInputOriginFileBuf = CSTQSOpenFilePath.toLatin1();
	pInputOriginFile = pInputOriginFileBuf.data();
	OpenOriginFile(pInputOriginFile);
}
void CStrProcessingThread::OpenOriginFile(char* pInputOriginFile)
{
	FILE *fpReadFile;          ///<file pointer to open read file 
	FILE *fpWriteFile;         ///<file pointer to open write in file 
	///fpWriteFile = CSTCQThreadTextBrowser->GetTextBrowserCorFile();
	///record the thread correspond main widget information
	

	char *pGetPackage = (char*)malloc(sizeof(char)* PACKAGE_LENGTH); ///malloc a enough space to store all the data of a package
	JudgeMemory(pGetPackage);
	char pDataBuf[READ_SIZE];
	int  ReadedPackageLength(0);                                    ///judge the total length append to data                                ///
	///QString   QStrTextBrowser;
	///
	///write in file param
	///QString  QSWriteFileBuf;
	///char* pWriteFile;
	memset(pDataBuf, 0, READ_SIZE);
	///fopen file to read data 
	fpReadFile = fopen(pInputOriginFile, "r");
	JudgeOpenFile(fpReadFile, pInputOriginFile);

	while (!feof(fpReadFile))
	{
		if (BStrForceStop)
		{
			return;
		}
		///creat date  Buf name;
		pDataBuf[READ_SIZE - 2] = '\n';
		ReadedPackageLength = 0;
		while (fgets(pDataBuf, READ_SIZE, fpReadFile))
		{
			strncpy(pGetPackage + ReadedPackageLength, pDataBuf, READ_SIZE);
			ReadedPackageLength += (READ_SIZE - 1);
			if (pDataBuf[READ_SIZE - 2] == '\n')
			{
				break;
			}
			pDataBuf[READ_SIZE - 2] = '\n';
		}
		pManageThreadData->DataToManageThread = pGetPackage;
		emit AppendData(pGetPackage);
		emit AppendDataManage(pManageThreadData);
		EnterCriticalSection(&(CSTCQThreadTextBrowser->JudgeWriteDataCRITICAL_SECTION));
		fpWriteFile = CSTCQThreadTextBrowser->GetTextBrowserCorFile();
		if (NULL != fpWriteFile)
		{
			fprintf(fpWriteFile, "%s", pGetPackage);
		}
		LeaveCriticalSection(&(CSTCQThreadTextBrowser->JudgeWriteDataCRITICAL_SECTION));
		Sleep(1000);
	}
	///pAppendDataCorespond->ThreadCorrespondTextbrowser = NULL;
	///
	///free the malloc
	free(pGetPackage);
	fclose(fpReadFile);
}
