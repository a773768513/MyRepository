#include "ReadDataThread.h"


CReadDataThread::CReadDataThread(QObject *parent)
{
	BThreadForceStop = FALSE;
	HEndThreadFlag = CreateEvent(NULL, TRUE, FALSE, NULL);   /// create event set manmual reset ,and initialize to untriggered state 
}


CReadDataThread::~CReadDataThread()
{
	if (HEndThreadFlag != NULL)
	{
		CloseHandle(HEndThreadFlag);
		HEndThreadFlag = NULL;
	}
}
/**********************************************************************//**
@brief	intput the open file in managethread

@param	QSOpenFilePath [In] 	input open file path 

@author YHF
@date 2018/06/14 13:42:30
@note 
History:
**************************************************************************/
void CReadDataThread::InputOpenFilePath(QString QSOpenFilePath)
{
	OpenFilePath = QSOpenFilePath;
	ResetEvent(HEndThreadFlag);
}
/**********************************************************************//**
@brief	vitual function  rewrite the function 
@param	

@author YHF
@date 2018/06/14 13:42:30
@note 
History:
**************************************************************************/
void CReadDataThread::run()
{
	OpenOriginFile();
	SetEvent(HEndThreadFlag);
}
/**********************************************************************//**
@brief	

@param	

@author YHF
@date 2018/06/14 13:42:30
@note 
History:
**************************************************************************/
void CReadDataThread::OpenOriginFile()
{
	///
	///change the QString to char*
	char* pInputOriginFile;
	QByteArray pQBInputOriginFileBuf = OpenFilePath.toLatin1();
	pInputOriginFile = pQBInputOriginFileBuf.data();
	
	///
	///start read data 
	FILE* fpReadFile;
	char* pGetPackage = (char*)malloc(sizeof(char)*PACKAGE_LENGTH);
	char pDataBuf[READ_SIZE];
	int ReadedPackageLength(0);

	if (pGetPackage == NULL)
	{
		emit EmitErrorMessage("Insufficient memory to open the serial port");
		///emit to close the qtextbrowser
		return;
	}
	fpReadFile = fopen(pInputOriginFile, "r");
	if (NULL == fpReadFile)
	{

		emit EmitErrorMessage("Fail to OpenFile ");
		return;
	}
	if (pGetPackage == NULL)
	{
		emit EmitErrorMessage("Fail to read serial port information ");
		///emit to close the qtextbrowser
		return;
	}
	while (!feof(fpReadFile))
	{
		if (BThreadForceStop)
		{
			return;
		}
		pDataBuf[READ_SIZE - 2] = '\n'; 
		ReadedPackageLength = 0;
		while (fgets(pDataBuf,128,fpReadFile))
		{
			pDataBuf[126] = '\n';
			emit EmitDataManageThread(pDataBuf);
			Sleep(10);
			///strncpy(pGetPackage + ReadedPackageLength, pDataBuf, READ_SIZE);
			///ReadedPackageLength += (READ_SIZE-1);
			if (pDataBuf[READ_SIZE - 2] == '\n')
			{
				break;
			}
			///sleep(1);
			pDataBuf[READ_SIZE - 2] = '\n';
		}
	}
	fclose(fpReadFile);
	free(pGetPackage);
}