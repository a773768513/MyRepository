/******************************
Match String module
@file  MatchStrInFile.cpp
@author YHF
@data  2018/3/28
@brief
*****************************/
#include <qmessagebox.h>
#include <Windows.h>
#include <qdatetime.h>
#include "AssertModule.h"
/***************************************************
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
/***********************************************************
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