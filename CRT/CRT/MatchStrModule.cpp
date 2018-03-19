/******************************
Match String module
@file  MatchStrInFile.cpp
@author YHF
@data  2018/3/14
@brief
*****************************/
#include "cpackageinput.h"
#include "DialogMatch.h"
#include "MatchStrModule.h"
#include <qmessagebox.h>


extern bool  BStartWriteFile;
/****************************************************//**
													  @brief  Judge the allocate memory sucess
													  @param  char* pJudgeMemory [IN] Judge this pointer
													  @author  YHF
													  @data   2018/2/25
													  @
													  ********************************************************/
int  JudgeMemory(char* pJudgeMemory)
{
	if (pJudgeMemory == NULL)
	{
		printf("No enough stroage,Memory allocate failed;\npress any key to exit");
		getchar();
		getchar();
		exit(EXIT_FAILURE);
	}
	return 0;
}
/************************************************************//**
@brief     Judge file whther success open;
@param     * fpFile[IN]  pointer file
															  @param     *pFile  [IN]  file name
															  @retval    0  success
															  @retval    1  success
															  @author YHF
															  @data    2018/2/25
															  @design:
															  judge whether the fpFile id NULL
															  *****************************************************************/
int  JudgeOpenFile(FILE* fpFile, char* pFile)
{
	if (NULL == fpFile)
	{
		QString QSfpFile = QString(QLatin1String(pFile));
		QMessageBox msg_OpenFileFailure;
		msg_OpenFileFailure.setText("cannot open the file" + QSfpFile);
		msg_OpenFileFailure.exec();
		return 1;
	}
	return 0;
}
/**************************************************************
@brief     Open the thread entrance
@param
@retval    void
@author YHF
@data    2018/3/14
@design:

*****************************************************************/
unsigned __stdcall StartMatchStrThread(void* param)
{
	CPackageInput *pPackageInput = (CPackageInput*)param;
	pPackageInput->ChangeQStringChar();
	return 0;
}

/**************************************************************
@brief     Qmessage for the prompt the failure information
@param
@retval    void
@author YHF
@data    2018/3/14
@design:

*****************************************************************/
void QMessageBoxFailure(QString QSFailureInformation)
{
	QMessageBox MsgFailure;
	MsgFailure.setWindowTitle("FailurePrompt");
	MsgFailure.setText(QSFailureInformation);
	MsgFailure.setIcon(QMessageBox::Information);
	MsgFailure.addButton("ok", QMessageBox::ActionRole);
	MsgFailure.exec();
}
/**************************************************************
@brief     Qmessage for the prompt the failure information
@param
@retval    void
@author YHF
@data    2018/3/14
@design:

*****************************************************************/
void CPackageInput::ChangeQStringChar()
{
	char* pMatchStr;                                                         ///<storage the matchstr within char
	char* pInputOriginFile;                                                  ///<storage the inputoriginfile path within char

	///
	///storage the information in the dialog and change the format with char
	QString QSInputFile = pCDialogMatch->pQLEInputOtiginFile->text();
	QString QSMatchStr = pCDialogMatch->pQCBMatchStr->currentText();
	QByteArray pMatchStrBuf = QSMatchStr.toLatin1();
	QByteArray pInputOriginFileBuf = QSInputFile.toLatin1();

	pMatchStr = pMatchStrBuf.data();
	pInputOriginFile = pInputOriginFileBuf.data();
	this->MatchStrOriginFile(pMatchStr, pInputOriginFile);
}
int CPackageInput::MatchStrOriginFile(char* pMatchStr, char* pInputOriginFile)
{
	FILE *fpReadFile;          ///<file pointer to open read file 
	FILE *fpWriteFile;         ///<file pointer to open write in file 

	char *pGetPackage = (char*)malloc(sizeof(char)* PACKAGE_LENGTH); ///malloc a enough space to store all the data of a package
	JudgeMemory(pGetPackage);
	char pDataBuf[READ_SIZE];
	
	int  ReadEveryLength(0);
	int  ReadedPackageLength(0);                                    ///judge the total length append to data                                ///
	QString   QStrTextBrowser;
	int  MatchStrLength = strlen(pMatchStr);
	///
	///
	pHighlighterStr = new CHighLighterStr(ui.textBrowser->document());
	pHighlighterStr->addnewRegExp(pCDialogMatch->pQCBMatchStr->currentText());
	///
	///write in file param
	QString  QSWriteFileBuf;
	char* pWriteFile;
	memset(pDataBuf, 0, READ_SIZE);

	fpReadFile = fopen(pInputOriginFile, "r");
	JudgeOpenFile(fpReadFile, pInputOriginFile);

	///
	///delete the useless character at begin
	while (fgets(pDataBuf, READ_SIZE, fpReadFile))
	{
		if (!strncmp(pDataBuf, pMatchStr, MatchStrLength))
		{
			break;
		}
	}
	///
	///clear the buf
	
	while (!feof(fpReadFile))
	{
		ReadedPackageLength = 0;
		ReadEveryLength = strlen(pDataBuf);
		strncpy(pGetPackage + ReadedPackageLength, pDataBuf, READ_SIZE);
		ReadedPackageLength += ReadEveryLength;
		while (fgets(pDataBuf, READ_SIZE, fpReadFile))
		{
			if (strncmp(pDataBuf, pMatchStr, MatchStrLength))
			{
				strncpy(pGetPackage + ReadedPackageLength, pDataBuf, READ_SIZE);
				ReadEveryLength = strlen(pDataBuf);
				ReadedPackageLength += ReadEveryLength;
			}
			else
			{

				break;
			}
		}
		
		QStrTextBrowser = pGetPackage;
		WaitForSingleObject(hMutexTextBrowser, INFINITE);
		ui.textBrowser->append(QStrTextBrowser);
		ReleaseMutex(hMutexTextBrowser);
		///
		///judge whether to write data to write file 
		if (BStartWriteFile)
		{
			///
			///judge the path whether reselect
			if (QSWriteFileBuf != this->pStorageWriteFile->text())
			{
				if (NULL != QSWriteFileBuf)
				{
					QSWriteFileBuf = this->pStorageWriteFile->text();
					QByteArray QBWriteFileBuf = QSWriteFileBuf.toLatin1();
					pWriteFile = QBWriteFileBuf.data();
					fpWriteFile = fopen(pWriteFile, "a+");
					JudgeOpenFile(fpWriteFile, pWriteFile);
				}
			}
			fprintf(fpWriteFile, "%s", pGetPackage);
		}
		Sleep(5000);
	}
	///
	///add the last package if the last package length less than 512
	if (!strncmp(pDataBuf, pMatchStr, MatchStrLength))
	{
		QStrTextBrowser = pGetPackage;
		ui.textBrowser->append(pDataBuf);

		///
		///judge whether to write data to write file 
		if (BStartWriteFile)
		{
			///
			///judge the path whether reselect
			if (QSWriteFileBuf != this->pStorageWriteFile->text())
			{
				if (NULL != QSWriteFileBuf)
				{
					QSWriteFileBuf = this->pStorageWriteFile->text();
					QByteArray QBWriteFileBuf = QSWriteFileBuf.toLatin1();
					pWriteFile = QBWriteFileBuf.data();
					fpWriteFile = fopen(pWriteFile, "a+");
					JudgeOpenFile(fpWriteFile, pWriteFile);
				}
			}
			fprintf(fpWriteFile, "%s", pDataBuf);
		}
	}



	///
	///free the malloc
	free(pGetPackage);
	return 0;
}