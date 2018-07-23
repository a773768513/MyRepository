#pragma once

#include <qstringlist.h>
#include <qvector.h>
#include "qobject.h"
#include "ReadDataThread.h"
#include <qdatetime.h>
#include <qreadwritelock.h>
class QtGuider;
class CManageThreadObject :
	public QObject
{
	Q_OBJECT
public:
	CManageThreadObject(QtGuider *parent);
	~CManageThreadObject();
	QVector<int> QVectorRecoredReceiveData;          ///<vector to accumulate received data (USE in GUI to show Spped
	struct LogFileInfo
	{
		int LogMode;
		QDateTime LogSartTime;
		QDateTime LogEndTime;
		FILE* logFilePointer;
		char  LogFileName[256];
	};
	QVector<LogFileInfo>  QVectorLogFileInfo;
	///ReadWriteLock if you get both locks at the same time ,you must get them in this order 
	QReadWriteLock QVectorRecoredReceiveDataReadWriteLock;
	QReadWriteLock QVectorLogFileInfoReadWriteLock;

protected:

	virtual void timerEvent(QTimerEvent *event);
private:
	///enum enumLogMode
	
	QStringList RecordOpenPort;                      ///<record the Open Port name 
	QtGuider* parentGUIObject;           ///<incomint GUI Object pointer 
	QVector<CReadDataThread*> QVectorCReadDataThreadPPointer;          ///<vector of the Qthread 
	///struct to storage the  FILEPointer of LOG data 
	
	QDateTime QObtainCurrentDateTime;
	QString  QObtainCurrentString;
	QDate QStandardDate ;                           ///<use this to confirm the yyyyMMdd  to 00000000;

	char *ManageThreadBuf = (char*)malloc(sizeof(char)* 1024);
	void ConnectGUIManageThreadSlot();

	void JudgeLogTimeStart(LogFileInfo* TimeEventLogFileInfo);
	void JudgeLogTimeEnd(LogFileInfo* TimeEventLogFileInfo);
signals:
	///
	void Emit_QMessageBoxFailureManage_Info(QString QMessageFailure);
	///to GUI createqTextbrower
	void CreateGUIQTextbrowserManagethread(QString QSOpenFilePathTitle);
	///to GUIshow the port data 
	void AppendDataManagethread(int NumberWindowManage, char* pAppendDataPointerManage);
	///refresh the rate every mintue
	void EmitRefreshReceivingRateManage();
	///to GUI delete the qtxtbrowser
	void emitCloseQtextbrowserRecordManage(int index);
public slots :
    ///user request
	void On_UserRequestOpenPort_Triggered(QString QSOpenFilePathManageThread);
	void On_ReadDataThread_Push(char* ThreadPushData);
	///
	void On_emitCloseCurrentQtextbrowserGUI_triggered(int indexGUI);
	void On_emitLogDataFile_Triggered(QString IndexManage, char* fpLogDataFile);
	///stop log 
	void On_emitStopLogGUI_Request(int IndexStopLogManage);
};

