#include "ManageThreadObject.h"
#include <qheaderview.h>
#include <qpoint.h>
#include <qmenu.h>
#include <qaction.h>
CManageThreadObject::CManageThreadObject() :
QObject()
{
	CreateInformationWindows();
	this->startTimer(1000,Qt::CoarseTimer);
}


CManageThreadObject::~CManageThreadObject()
{
	RecordDataSpeed->clear();
	delete RecordDataSpeed;
}
/**********************************************************************//**
@brief slots	CreatetextbrowserRecord ,for record the textbrowser 
accept GUI thread signal and send dignal to GUI thread to request create  a textbrowser

@return 

@author YHF
@date 2018/05/23 13:42:30
@note 
History:
**************************************************************************/
void CManageThreadObject::CreatetextbrowserRecord(QString QSOpenFileName)
{
	this->QSRecordOpenFileName = QSOpenFileName;
	emit SignalCreateTextbrowser(QSRecordOpenFileName);
	for (int CycleFind = 0; CycleFind < ManageTableWidgetRowNum; CycleFind++)
	{
		if (QSRecordOpenFileName == QVectorQString.at(CycleFind))
		{
			return;
		}
	}
	QVectorQString.append(QSRecordOpenFileName);
	/*************
	record
	***************/
	RecordOpenFileList << QSRecordOpenFileName;
	QString addRowQstring = RecordOpenFileList.last();
	ManageTableWidgetRowNum++;
	pQTableWidget->setRowCount(ManageTableWidgetRowNum);
	///
	QTableWidgetItem  *pQTableWidgetItem = new QTableWidgetItem();
	pQTableWidgetItem->setText(QSRecordOpenFileName);
	pQTableWidget->setItem((ManageTableWidgetRowNum - 1), 0, pQTableWidgetItem);
	///
	QTableWidgetItem  *pQTableWidgetItem2 = new QTableWidgetItem();
	pQTableWidgetItem2->setText("transiting");
	pQTableWidget->setItem((ManageTableWidgetRowNum - 1), 1, pQTableWidgetItem2);
	
	///
	QTableWidgetItem  *pQTableWidgetItem3 = new QTableWidgetItem();
	pQTableWidgetItem3->setText("starting");
	pQTableWidget->setItem((ManageTableWidgetRowNum - 1), 2, pQTableWidgetItem3);
	///pQTableWidget->resizeColumnToContents();
	///add the receive data speed
	int RecordNum = 0;
	RecordDataSpeed->append(RecordNum);
}

void CManageThreadObject::timerEvent(QTimerEvent *event)
{
	emit EmitSignal(RecordDataSpeed);
	for (int Cycle = 0; Cycle < ManageTableWidgetRowNum; Cycle++)
	{
		RecordDataSpeed->replace(Cycle, 0);
	}
}
void CManageThreadObject::CreateInformationWindows()
{
	pQManageDialog = new QDialog();
	pQManageLayout = new QGridLayout(pQManageDialog);
	pQTableWidget = new QTableWidget(pQManageDialog);
	pQManageLayout->addWidget(pQTableWidget);
	///resize the dialog 
	pQManageDialog->resize(500, 200);
	///set de column num
	pQTableWidget->setColumnCount(3);
	pQTableWidget->setRowCount(0);
	///add column header label 
	QStringList ColumnHeaderLabel;
	ColumnHeaderLabel <<"COM List"<< "Operating status" << "Acceptance rate";
	pQTableWidget->setHorizontalHeaderLabels(ColumnHeaderLabel);
	///
	pQTableWidget->setShowGrid(false);
	///
	pQTableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	///fix the item and selection to select the rows 
	pQTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	pQTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	////pQTableWidget->resize(500, 300);
	pQTableWidget->verticalHeader()->hide();
	pQTableWidget->setColumnWidth(0, 200);
	pQTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	///pQTableWidget->horizontalHeader()->setStretchLastSection(true);

	pQManageDialog->show();
	/// add the right button customContextMenuRequested(const QPoint&)
	pQTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(pQTableWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(On_pQTableWidget_ContextMenuPolicy(const QPoint&)));
}

void CManageThreadObject::JudgeReadDataStatus(ManageThreadData* AppendDataManageThread)
{
	int Num = 0;
	for (Num; Num < ManageTableWidgetRowNum; Num++)
	{
		QTableWidgetItem *FindCorItem = pQTableWidget->item(Num, 0);
		if (FindCorItem == NULL)
		{
			return;
		}
		if (AppendDataManageThread->OpenFilePath == FindCorItem->text())
		{
			break;
		}
	}
	int TempReciveNum = RecordDataSpeed->at(Num);
	TempReciveNum += strlen(AppendDataManageThread->DataToManageThread);
	RecordDataSpeed->replace(Num, TempReciveNum);
}

void CManageThreadObject::On_GUI_SignalManageThreadCloseTab(int CloseIndex)
{
	RecordDataSpeed->remove(CloseIndex);
	QVectorQString.remove(CloseIndex);
	ManageTableWidgetRowNum--;
	emit SignalToGUICloseCOM(CloseIndex);
}
void CManageThreadObject::On_pQTableWidget_ContextMenuPolicy(const QPoint&Pos)
{
	emit SignalToGUICreateRightMenu();
	/**************
	QMenu* pQMenuQtableWidgets = new QMenu;
	QAction* pDleteRowAction = new QAction;
	pDleteRowAction->setText("delete");
	connect(pDleteRowAction, SIGNAL(triggered()), this, SLOT(On_DeleteRowAction_Triggered()));
	///copy cursor data 
	pQMenuQtableWidgets->addAction(pDleteRowAction);
	pQMenuQtableWidgets->exec(QCursor::pos());
	**********************/
}
