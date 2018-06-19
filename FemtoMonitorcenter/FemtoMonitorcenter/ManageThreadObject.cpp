#include "CFemtoMonitorcenter.h"
#include "ReadDataThread.h"
#include <stdlib.h>
CManageThreadObject::CManageThreadObject(CFemtoMonitorcenter *parent)
:QObject()
{
	parentGUIObject = parent;
	this->startTimer(1000, Qt::CoarseTimer);
	ConnectGUIManageThreadSlot();
}


CManageThreadObject::~CManageThreadObject()
{
	///
	
	///stop all read data thread
	int OpenPortNum = QVectorCReadDataThreadPPointer.length();
	int cycle = 0;
	while (cycle < OpenPortNum)
	{
		///fclose all log data 
		FILE *fpCLosePreviousFile = QVectorFILEPointer.at(cycle);
		if (NULL != fpCLosePreviousFile)
		{
			fclose(fpCLosePreviousFile);
		}
		///stop thread
		CReadDataThread* pDeleteReadDataqThread = dynamic_cast<CReadDataThread*> (QVectorCReadDataThreadPPointer.at(cycle));
		pDeleteReadDataqThread->BThreadForceStop = true;
		WaitForSingleObject(pDeleteReadDataqThread->HEndThreadFlag,INFINITE);
		cycle++;
	}

}


/**********************************************************************//**
@brief  slot of timer signal refresh the speed every minute
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void  CManageThreadObject::timerEvent(QTimerEvent *event)
{
	emit EmitRefreshReceivingRateManage( );
	int Cycle = 0;
	for each (int alternationValue  in QVectorRecoredReceiveData)
	{
		QVectorRecoredReceiveData.replace(Cycle, 0);
		Cycle++;
	}
}
/**********************************************************************//**
@brief  connect all slots managethread and GUI thread 
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CManageThreadObject::ConnectGUIManageThreadSlot()
{
	///connect the signal and slot in GUI and manage thread  to create the port 
	connect(parentGUIObject, SIGNAL(emitOpenSeriousPortGUI(QString)), this, SLOT(On_UserRequestOpenPort_Triggered(QString)));
	connect(this, SIGNAL(CreateGUIQTextbrowserManagethread(QString)), parentGUIObject, SLOT(On_CreateGUIQTextbrowserManagethread_Triggered(QString)));

	///Log Data of GUI and manage thread 
	connect(parentGUIObject, SIGNAL(emitLogDataFile(int, FILE*)), this, SLOT(On_emitLogDataFile_Triggered(int, FILE*)));
	///append data to GUIto show 
	connect(this, SIGNAL(AppendDataManagethread(int, char*)), parentGUIObject, SLOT(On_AppendDataManagethread_Triggered(int, char*)));
	///connect the timerevent
	connect(this, SIGNAL(EmitRefreshReceivingRateManage()), parentGUIObject, SLOT(On_EmitRefreshReceivingRateManage_Triggered()),Qt::BlockingQueuedConnection);
	///connect the GUI and this in close event
	connect(parentGUIObject, SIGNAL(emitCloseCurrentQtextbrowserGUI(int)), this, SLOT(On_emitCloseCurrentQtextbrowserGUI_triggered(int)));
	connect(this, SIGNAL(emitCloseQtextbrowserRecordManage(int);), parentGUIObject, SLOT(On_emitCloseQtextbrowserRecordManage_triggered()));
}
/**********************************************************************//**
@brief  slot user request  Open Port and record the Port
@param  QSOpenFilePathManageThread[IN] Open File Manage
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CManageThreadObject::On_UserRequestOpenPort_Triggered(QString QSOpenFilePathManageThread)
{
	emit CreateGUIQTextbrowserManagethread(QSOpenFilePathManageThread);
	CReadDataThread *pCReadDataThread = new CReadDataThread;
	pCReadDataThread->InputOpenFilePath(QSOpenFilePathManageThread);
	connect(pCReadDataThread, SIGNAL(EmitDataManageThread(char*)), this, SLOT(On_ReadDataThread_Push(char*)));
	connect(pCReadDataThread, SIGNAL(EmitErrorMessage(QString)), parentGUIObject, SLOT(QMessageBoxFailure(QString)));
	pCReadDataThread->start();
	QVectorCReadDataThreadPPointer.append(pCReadDataThread);
	QVectorRecoredReceiveData.append(0);
	FILE* fpLogData = NULL;
	QVectorFILEPointer.append(fpLogData);
}
/**********************************************************************//**
@brief  slot user request  Open Port and record the Port
@param  QSOpenFilePathManageThread[IN] Open File Manage
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CManageThreadObject::On_ReadDataThread_Push(char* ThreadPushData)
{
	///
	///secondary processing data

	///
	CReadDataThread *pSenderCReadDataThread = dynamic_cast<CReadDataThread*> (sender());
	int NumberWindow = QVectorCReadDataThreadPPointer.indexOf(pSenderCReadDataThread);
	if (NumberWindow < 0)
	{
		///WaitForSingleObject(pSenderCReadDataThread->HEndThreadFlag, INFINITE);
		return;
	}
	FILE* fpLogData = QVectorFILEPointer.at(NumberWindow);
	if (NULL != fpLogData)
	{
		fprintf(fpLogData, "%s", ThreadPushData);
	}
	int TempReciveNum = QVectorRecoredReceiveData.at(NumberWindow);
	TempReciveNum += strlen(ThreadPushData);
	QVectorRecoredReceiveData.replace(NumberWindow, TempReciveNum);
	emit AppendDataManagethread(NumberWindow, ThreadPushData);
}
/**********************************************************************//**
@brief  slot user request  close the qtextbrower and srop port connect 
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CManageThreadObject::On_emitCloseCurrentQtextbrowserGUI_triggered(int indexGUI)
{
	QVectorRecoredReceiveData.removeAt(indexGUI);
	FILE *fpCLosePreviousFile = QVectorFILEPointer.at(indexGUI);
	if (NULL != fpCLosePreviousFile)
	{
		fclose(fpCLosePreviousFile);
	}
	QVectorFILEPointer.removeAt(indexGUI);
	CReadDataThread* pDeleteReadDataqThread = dynamic_cast<CReadDataThread*> (QVectorCReadDataThreadPPointer.at(indexGUI));
	pDeleteReadDataqThread->BThreadForceStop = true;
	QVectorCReadDataThreadPPointer.removeAt(indexGUI);
	emit emitCloseQtextbrowserRecordManage(indexGUI);
}
/**********************************************************************//**
@brief  slot Open EmitLog FILE pointer and storage
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CManageThreadObject::On_emitLogDataFile_Triggered(int IndexManage, FILE* fpLogDataFile)
{
	FILE *fpCLosePreviousFile = QVectorFILEPointer.at(IndexManage);
	if (NULL != fpCLosePreviousFile)
	{
		fclose(fpCLosePreviousFile);
	}
	QVectorFILEPointer.replace(IndexManage, fpLogDataFile);
}