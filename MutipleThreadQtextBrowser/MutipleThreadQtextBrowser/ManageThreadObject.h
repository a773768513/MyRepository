#pragma once


#include <QtWidgets/QMainWindow>
#include <qobject.h>
#include <qdialog.h>
#include <qgridlayout.h>
#include <qtablewidget.h>
#include <time.h>
#include <qvector.h>
class CManageThreadObject :
	public QObject
{
	Q_OBJECT

public:
	CManageThreadObject();
	~CManageThreadObject();

	struct ManageThreadData
	{
		QString OpenFilePath;
		char* DataToManageThread;
	};
	QVector<int>* RecordDataSpeed = new QVector<int>;
	QVector<QString> QVectorQString;
	QTableWidget *pQTableWidget;
private:
	QString QSRecordOpenFileName;
	/// the manage child windows information 
	QStringList RecordOpenFileList;
	int  ManageTableWidgetRowNum = 0;
	///manage child dialog to show the data 
	QDialog *pQManageDialog;
	QGridLayout *pQManageLayout;


	void CreateInformationWindows();
signals:
	///signal to create the textbrowser
	void SignalCreateTextbrowser(QString TabTitle);
	void EmitSignal(QVector<int>* RecordDataSpeedPara);
	void SignalToGUICloseCOM(int CloseIndex);
	void SignalToGUICreateRightMenu();
protected:
	virtual void timerEvent(QTimerEvent *event);
	
public slots :
    ///slots to signal and record the thread
void CreatetextbrowserRecord(QString TabTitle);
	///slots to record data 
void JudgeReadDataStatus(ManageThreadData* AppendDataManageThread);
///slot receive the signal to clear the data 
void On_GUI_SignalManageThreadCloseTab(int CloseIndex);
///right button  triggered
void On_pQTableWidget_ContextMenuPolicy(const QPoint&);

};

