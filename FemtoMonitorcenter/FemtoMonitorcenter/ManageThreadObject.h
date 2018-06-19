#pragma once

#include <qstringlist.h>
#include <qvector.h>
#include "qobject.h"
#include "ReadDataThread.h"
#include "CFemtoMonitorcenter.h"

class  CFemtoMonitorcenter;

class CManageThreadObject :
	public QObject
{
	Q_OBJECT
public:
	CManageThreadObject(CFemtoMonitorcenter *parent);
	~CManageThreadObject();
	QVector<int> QVectorRecoredReceiveData;          ///<vector to accumulate received data (USE in GUI to show Spped
protected:

	virtual void timerEvent(QTimerEvent *event);
private:
	QStringList RecordOpenPort;                      ///<record the Open Port name 
	CFemtoMonitorcenter* parentGUIObject;           ///<incomint GUI Object pointer 
	QVector<CReadDataThread*> QVectorCReadDataThreadPPointer;          ///<vector of the Qthread 
	///FILEPointer of LOG data 
	QVector<FILE*>  QVectorFILEPointer;


	void ConnectGUIManageThreadSlot();
signals:
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
	void On_emitLogDataFile_Triggered(int IndexManage, FILE* fpLogDataFile);
};

