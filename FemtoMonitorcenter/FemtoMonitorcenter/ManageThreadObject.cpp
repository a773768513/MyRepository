#include "CFemtoMonitorcenter.h"
#include "ReadDataThread.h"
#include <stdlib.h>
#include <qdebug.h>
CManageThreadObject::CManageThreadObject(CFemtoMonitorcenter *parent)
:QObject()
{
	parentGUIObject = parent;
	this->startTimer(1000, Qt::CoarseTimer);
	ConnectGUIManageThreadSlot();
	QStandardDate = QDate::fromString("20000101", "yyyyMMdd");
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
		FILE *fpCLosePreviousFile = (QVectorLogFileInfo.at(cycle)).logFilePointer;
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
	QVectorLogFileInfoReadWriteLock.lockForWrite();
	int Cycle = 0;
	for each (LogFileInfo JudgeLofFileInfoTime in QVectorLogFileInfo)
	{
		if (JudgeLofFileInfoTime.logFilePointer == NULL)
		{
			JudgeLogTimeStart(&JudgeLofFileInfoTime);
		}
		else
		{
			JudgeLogTimeEnd(&JudgeLofFileInfoTime);
		}

		QVectorLogFileInfo.replace(Cycle, JudgeLofFileInfoTime);
		Cycle++;
	}
	QVectorLogFileInfoReadWriteLock.unlock();
	emit EmitRefreshReceivingRateManage();
	Cycle = 0;
	QVectorRecoredReceiveDataReadWriteLock.lockForWrite();
	for each (int alternationValue  in QVectorRecoredReceiveData)
	{
		QVectorRecoredReceiveData.replace(Cycle, 0);
		Cycle++;
	}
	QVectorRecoredReceiveDataReadWriteLock.unlock();
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
	///
	connect(this, SIGNAL(Emit_QMessageBoxFailureManage_Info(QString)), parentGUIObject, SLOT(QMessageBoxFailure(QString)));
	///connect the signal and slot in GUI and manage thread  to create the port 
	connect(parentGUIObject, SIGNAL(emitOpenSeriousPortGUI(QString)), this, SLOT(On_UserRequestOpenPort_Triggered(QString)));
	connect(this, SIGNAL(CreateGUIQTextbrowserManagethread(QString)), parentGUIObject, SLOT(On_CreateGUIQTextbrowserManagethread_Triggered(QString)));

	///Log Data of GUI and manage thread 
	connect(parentGUIObject, SIGNAL(emitLogDataFile(QString, char*)), this, SLOT(On_emitLogDataFile_Triggered(QString, char*)),Qt::BlockingQueuedConnection);
	///append data to GUIto show 
	connect(this, SIGNAL(AppendDataManagethread(int, char*)), parentGUIObject, SLOT(On_AppendDataManagethread_Triggered(int, char*)));
	///connect the timerevent
	connect(this, SIGNAL(EmitRefreshReceivingRateManage()), parentGUIObject, SLOT(On_EmitRefreshReceivingRateManage_Triggered()),Qt::BlockingQueuedConnection);
	///connect the GUI and this in close event
	connect(parentGUIObject, SIGNAL(emitCloseCurrentQtextbrowserGUI(int)), this, SLOT(On_emitCloseCurrentQtextbrowserGUI_triggered(int)));
	connect(this, SIGNAL(emitCloseQtextbrowserRecordManage(int)), parentGUIObject, SLOT(On_emitCloseQtextbrowserRecordManage_triggered(int)));
	///stop Log connect 
	connect(parentGUIObject, SIGNAL(emitStopLogGUI(int)), this, SLOT(On_emitStopLogGUI_Request(int)));
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
	LogFileInfo LogFileInfoObj;
	LogFileInfoObj.LogMode = 0;
	LogFileInfoObj.LogSartTime.setDate(QStandardDate);
	LogFileInfoObj.LogEndTime.setDate(QStandardDate);
	memset(LogFileInfoObj.LogFileName,0,256);
	LogFileInfoObj.logFilePointer = NULL;
	QVectorLogFileInfo.append(LogFileInfoObj);
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
	
	QVectorRecoredReceiveDataReadWriteLock.lockForWrite();
	QVectorLogFileInfoReadWriteLock.lockForWrite();
	FILE* fpLogData = (QVectorLogFileInfo.at(NumberWindow)).logFilePointer;
	if (NULL != fpLogData)
	{
		fprintf(fpLogData, "%s", ThreadPushData);
	}
	int TempReciveNum = QVectorRecoredReceiveData.at(NumberWindow);
	TempReciveNum += strlen(ThreadPushData);
	QVectorRecoredReceiveData.replace(NumberWindow, TempReciveNum);
	QVectorRecoredReceiveDataReadWriteLock.unlock();
	QVectorLogFileInfoReadWriteLock.unlock();
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
	FILE *fpCLosePreviousFile = (QVectorLogFileInfo.at(indexGUI)).logFilePointer;
	if (NULL != fpCLosePreviousFile)
	{
		fclose(fpCLosePreviousFile);
	}
	QVectorLogFileInfo.removeAt(indexGUI);
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
void CManageThreadObject::On_emitLogDataFile_Triggered(QString QSIndexManage, char* fpLogDataFile)
{
	LogFileInfo NewLogFileInfo;
	NewLogFileInfo.logFilePointer = NULL;
	memcpy(NewLogFileInfo.LogFileName, fpLogDataFile,256);
	FILE* fpLogDataFileJudgePathCorrect = fopen(NewLogFileInfo.LogFileName, "a+");
	if (NULL == fpLogDataFile)
	{
		emit Emit_QMessageBoxFailureManage_Info("Can Not Open Log File!");
		return;
	}
	
	NewLogFileInfo.logFilePointer = fpLogDataFileJudgePathCorrect;
	///parse incoming data decompose items from data 
	QString QSStartTime = QSIndexManage.mid(2, 14);
	QString QSEndTime = QSIndexManage.mid(17, 14);
	QString NumWindows = QSIndexManage.mid(32);
	NewLogFileInfo.LogMode = (QSIndexManage.mid(0, 1)).toInt();
	NewLogFileInfo.LogSartTime = QDateTime::fromString(QSStartTime,"yyyyMMddhhmmss");
	NewLogFileInfo.LogEndTime = QDateTime::fromString(QSEndTime, "yyyyMMddhhmmss");
	///
	int IndexManage = NumWindows.toInt();
	FILE *fpCLosePreviousFile = (QVectorLogFileInfo.at(IndexManage)).logFilePointer;
	if (NULL != fpCLosePreviousFile)
	{
		fclose(fpCLosePreviousFile);
	}
	///Judge Log status now
	switch (NewLogFileInfo.LogMode)
	{
		///NO automic
	case 0:
		break;
		///Only Once
	case 1:
		QObtainCurrentDateTime = QDateTime::currentDateTime();
		if (QObtainCurrentDateTime < NewLogFileInfo.LogSartTime)
		{
			fclose(NewLogFileInfo.logFilePointer);
			break;
		}
		else
		{

			break;
		}
		///Dayly
	case 2:
		QObtainCurrentDateTime = QDateTime::currentDateTime();
		QObtainCurrentDateTime.setDate(QStandardDate);
		if (QObtainCurrentDateTime < NewLogFileInfo.LogSartTime)
		{
			fclose(NewLogFileInfo.logFilePointer);
			NewLogFileInfo.logFilePointer = NULL;
			break;
		}
		else
		{
			break;
		}
		///weekly
	case 3:
		QObtainCurrentDateTime = QDateTime::currentDateTime();
		if (QObtainCurrentDateTime < NewLogFileInfo.LogSartTime)
		{
			fclose(NewLogFileInfo.logFilePointer);
			break;
		}
		else
		{
			break;
		}
	} 
	QVectorLogFileInfo.replace(IndexManage, NewLogFileInfo);
}

void CManageThreadObject::JudgeLogTimeStart(LogFileInfo* TimeEventLogFileInfo)
{
	//Start Only the FILE*  have NULL
	switch (TimeEventLogFileInfo->LogMode)
	{
		///NO automic
	case 0:
		return;
		///Only Once
	case 1:
		QObtainCurrentDateTime = QDateTime::currentDateTime();
		if (QObtainCurrentDateTime < TimeEventLogFileInfo->LogSartTime)
		{
			return;
		}
		else
		{
			FILE* fpLogDataFile = fopen(TimeEventLogFileInfo->LogFileName, "a+");
			if (NULL == fpLogDataFile)
			{
				emit Emit_QMessageBoxFailureManage_Info("Invalid Log Path of" + QString((TimeEventLogFileInfo->LogFileName)) + " !\n possibly stored path has been destroyed");
				TimeEventLogFileInfo->LogMode = 0;
				TimeEventLogFileInfo->LogSartTime.setDate(QStandardDate);
				TimeEventLogFileInfo->LogEndTime.setDate(QStandardDate);
				return;
			}
			else
			{
				TimeEventLogFileInfo->logFilePointer = fpLogDataFile;
				return;
			}
		}

		///Dayly  change  the date id 20010101 to  compare
	case 2:
		QObtainCurrentDateTime = QDateTime::currentDateTime();
		QObtainCurrentDateTime.setDate(QStandardDate);
		if (QObtainCurrentDateTime < TimeEventLogFileInfo->LogSartTime)
		{
			return;
		}
		else
		{
			FILE* fpLogDataFile = fopen(TimeEventLogFileInfo->LogFileName, "a+");
			if (NULL == fpLogDataFile)
			{
				emit Emit_QMessageBoxFailureManage_Info("Invalid Log Path of" + QString((TimeEventLogFileInfo->LogFileName)) + " !\n possibly stored path has been destroyed");
				TimeEventLogFileInfo->LogMode = 0;
				TimeEventLogFileInfo->LogSartTime.setDate(QStandardDate);
				TimeEventLogFileInfo->LogEndTime.setDate(QStandardDate);
				return;
			}
			else
			{
				TimeEventLogFileInfo->logFilePointer = fpLogDataFile;
				return;
			}
		}
		///weekly add  7 day if the FILE is NULL and the time is readly
	case 3:
		QObtainCurrentDateTime = QDateTime::currentDateTime();
		if (QObtainCurrentDateTime < TimeEventLogFileInfo->LogSartTime)
		{
			return;
		}
		else
		{
			FILE* fpLogDataFile = fopen(TimeEventLogFileInfo->LogFileName, "a+");
			TimeEventLogFileInfo->LogSartTime.addDays(7);
			if (NULL == fpLogDataFile)
			{
				
				emit Emit_QMessageBoxFailureManage_Info("Invalid Log Path of" + QString((TimeEventLogFileInfo->LogFileName)) + " !\n possibly stored path has been destroyed");
				TimeEventLogFileInfo->LogMode = 0;
				TimeEventLogFileInfo->LogSartTime.setDate(QStandardDate);
				TimeEventLogFileInfo->LogEndTime.setDate(QStandardDate);
				return;
			}
			else
			{
				TimeEventLogFileInfo->logFilePointer = fpLogDataFile;
				return;
			}
		}
	}
}
void CManageThreadObject::JudgeLogTimeEnd(LogFileInfo* TimeEventLogFileInfo)
{
	///End File Judge
	switch (TimeEventLogFileInfo->LogMode)
	{
		///NO automic
	case 0:
		return;
		///Only Once
	case 1:
		QObtainCurrentDateTime = QDateTime::currentDateTime();
		qDebug() << QObtainCurrentDateTime;
		qDebug() << TimeEventLogFileInfo->LogEndTime;
		if (QObtainCurrentDateTime < (TimeEventLogFileInfo->LogEndTime))
		{
			return;
		}
		else
		{
			TimeEventLogFileInfo->LogMode = 0;
			TimeEventLogFileInfo->LogSartTime.setDate(QStandardDate);
			TimeEventLogFileInfo->LogEndTime.setDate(QStandardDate);
			fclose(TimeEventLogFileInfo->logFilePointer);
			TimeEventLogFileInfo->logFilePointer = NULL;
			return;
		}

		///Dayly  change  the date id 20010101 to  compare
	case 2:
		QObtainCurrentDateTime = QDateTime::currentDateTime();
		QObtainCurrentDateTime.setDate(QStandardDate);
		if (QObtainCurrentDateTime < TimeEventLogFileInfo->LogEndTime)
		{
			return;
		}
		else
		{
			fclose(TimeEventLogFileInfo->logFilePointer);
			TimeEventLogFileInfo->logFilePointer = NULL;
			return;
		}
		///weekly add  7 day if the FILE is NULL and the time is readly
	case 3:
		QObtainCurrentDateTime = QDateTime::currentDateTime();
		if (QObtainCurrentDateTime < TimeEventLogFileInfo->LogEndTime)
		{
			return;
		}
		else
		{
			TimeEventLogFileInfo->LogEndTime.addDays(7);
			fclose(TimeEventLogFileInfo->logFilePointer);
			TimeEventLogFileInfo->logFilePointer = NULL;
			return;
		}
	}

}

void CManageThreadObject::On_emitStopLogGUI_Request(int IndexStopLogManage)
{
	LogFileInfo LogFileInfoObjCloseFile = QVectorLogFileInfo.at(IndexStopLogManage);
	if (NULL != LogFileInfoObjCloseFile.logFilePointer)
	{
		fclose(LogFileInfoObjCloseFile.logFilePointer);
	}
	LogFileInfo LogFileInfoObj;
	LogFileInfoObj.LogMode = 0;
	LogFileInfoObj.LogSartTime.setDate(QStandardDate);
	LogFileInfoObj.LogEndTime.setDate(QStandardDate);
	memset(LogFileInfoObj.LogFileName, 0, 256);
	LogFileInfoObj.logFilePointer = NULL;
	QVectorLogFileInfo.replace(IndexStopLogManage,LogFileInfoObj);
}
