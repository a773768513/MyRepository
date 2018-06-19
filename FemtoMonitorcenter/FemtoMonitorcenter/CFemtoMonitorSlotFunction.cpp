#include "CFemtoMonitorcenter.h"
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qcolor.h>
#include <qcolordialog.h>
#include <qpalette.h>
/**********************************************************************//**
@brief  slot of main windows widgets qtabwidgets close button clicked
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CFemtoMonitorcenter::On_TabWidget_CloseButton(int index)
{
	emit emitCloseCurrentQtextbrowserGUI(index);
}
/**********************************************************************//**
@brief  slots of Qaction to create OpenFileDialog 
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CFemtoMonitorcenter::On_pQActionOpenFileDialog_triggered()
{
	CreateOpenFileChildWindows();
}
/**********************************************************************//**
@brief  slots to Qaction To Open highter dialog 
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CFemtoMonitorcenter::On_pQActionOpenHighlighterDialog_triggered()
{
	CreateHighlightingWindows();
}
/**********************************************************************//**
@brief  slot of qaction to log data to seleteddialog 
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CFemtoMonitorcenter::On_pQActionOpenLogFileDialog_triggered()
{
	CreateWriteFileWindow();
}
/**********************************************************************//**
@brief slot of  manage thread to qtable widgets righter button 
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CFemtoMonitorcenter::On_pQTableWidgets_RightButton(const QPoint*)
{

}

/**********************************************************************//**
@brief  slot of user confirm to open the COM and read data 
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CFemtoMonitorcenter::On_pQPushButttonOpenFileConfirm_Clicked()
{
	if (NULL == pQTextEditOpenFilePath->text())
	{
		EmitQmessageInformation("Please select the serial port");
		return;
	}
	QString QSOpenFilePath = pQTextEditOpenFilePath->text();
	pQTextEditOpenFilePath->close();
	emit emitOpenSeriousPortGUI(QSOpenFilePath);
	pDialogOpenFile->close();
}
/**********************************************************************//**
@brief slot to user cancel the Open COM dialog 
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CFemtoMonitorcenter::On_pQPushButtonOpenFileCancel_Clicked()
{
	pDialogOpenFile->close();
}
/**********************************************************************//**
@brief slot to  seleted the file in compute
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CFemtoMonitorcenter::On_OpenFileChildDialogSelectFile_Clicked()
{
	QString QSOpenFile = QFileDialog::getOpenFileName(NULL, "OpenFile", ".", NULL);
	this->pQTextEditOpenFilePath->setText(QSOpenFile);
}
/**********************************************************************//**
@brief slot to add Qtextbrower
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CFemtoMonitorcenter::On_CreateGUIQTextbrowserManagethread_Triggered(QString Tabtitle)
{
	pCThreadQtextbrowser = new CThreadQtextbrowser(this);
	pQMainTabWidget->addTab(pCThreadQtextbrowser, Tabtitle);

	int CurrentRowNum = pQTableWidgetManageWidgets->rowCount();
	CurrentRowNum++;
	pQTableWidgetManageWidgets->setRowCount(CurrentRowNum);
	QTableWidgetItem *pQtableWidgetItemPortName = new QTableWidgetItem(Tabtitle);
	pQTableWidgetManageWidgets->setItem(CurrentRowNum-1,0,pQtableWidgetItemPortName);
	QTableWidgetItem *pQTableWidgetItemStatus = new QTableWidgetItem("transiting");
	pQTableWidgetManageWidgets->setItem(CurrentRowNum - 1, 1, pQTableWidgetItemStatus);
	QTableWidgetItem *pQTableWidgetItemSpeed = new QTableWidgetItem("starting");
	pQTableWidgetManageWidgets->setItem(CurrentRowNum - 1, 2, pQTableWidgetItemSpeed);
	QTableWidgetItem *pQTableWidgetItemLogStatus = new QTableWidgetItem("NO");
	pQTableWidgetManageWidgets->setItem(CurrentRowNum - 1, 3, pQTableWidgetItemLogStatus);
}
/**********************************************************************//**
@brief slot to show the qmessage to user 
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CFemtoMonitorcenter::QMessageBoxFailure(QString QSInformation)
{
	QMessageBox MsgFailure;
	MsgFailure.setWindowTitle("Failure!");
	MsgFailure.setText(QSInformation);
	MsgFailure.setIcon(QMessageBox::Information);
	MsgFailure.addButton("OK", QMessageBox::ActionRole);
	MsgFailure.exec();
}


/**********************************************************************//**
@brief slot to receive  the qmessage to CThreadQtextbrowser
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CFemtoMonitorcenter::On_AppendDataManagethread_Triggered(int NumberWindowManage, char* pAppendDataPointerManage)
{
	CThreadQtextbrowser *pAppendDataCThreadQTextBrowser = dynamic_cast<CThreadQtextbrowser*> (pQMainTabWidget->widget(NumberWindowManage));
	if (NULL == pAppendDataCThreadQTextBrowser)
	{
		emit EmitQmessageInformation("Error!Data not found in window dispaly!");
		return;
	}
	pAppendDataCThreadQTextBrowser->AppendDataTextbrowser(pAppendDataPointerManage);
}
/**********************************************************************//**
@brief slot to refresh the receiving rate
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CFemtoMonitorcenter::On_EmitRefreshReceivingRateManage_Triggered()
{
	int AllOverCycleNum = 0;
	QString QSNumSpeedBuf; 
	QTableWidgetItem *pTablewidgetsSpeed;
	for each (int  QVectorRecoredReceiveDataSpeed in  pCManageThreadObject->QVectorRecoredReceiveData)
	{
		pTablewidgetsSpeed = pQTableWidgetManageWidgets->item(AllOverCycleNum, 2);
		QSNumSpeedBuf.setNum(QVectorRecoredReceiveDataSpeed);
		QSNumSpeedBuf += "b/s";
		pTablewidgetsSpeed->setText(QSNumSpeedBuf);
		AllOverCycleNum++;
	}

}
/**********************************************************************//**
@brief slot to clse the GUI record
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CFemtoMonitorcenter::On_emitCloseQtextbrowserRecordManage_triggered(int index)
{
	CThreadQtextbrowser* pDeleteCThreadQtextbrowser = dynamic_cast<CThreadQtextbrowser*> (pQMainTabWidget->widget(index));
	delete pDeleteCThreadQtextbrowser;

	this->pQTableWidgetManageWidgets->removeRow(index);
}
/**********************************************************************//**
@brief slot of highter dialog slot 
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/

void CFemtoMonitorcenter::On_pQHighlighterDialogConfirm_Triggered()
{
	if (pQComboBoxHighlighterDialogStr->currentText() == NULL)
	{
		QMessageBoxFailure("No Input Character");
		return;
	}
	QString QSCurrentHighlightingStr = pQComboBoxHighlighterDialogStr->currentText();
	CThreadQtextbrowser  *pQTextbrowserContinue = dynamic_cast<CThreadQtextbrowser*>(pQMainTabWidget->currentWidget());
	pQDialogHighlighter->close();
	if (NULL == pQTextbrowserContinue)
	{
		QMessageBoxFailure("tranfer type failure");
		return;
	}
	pQTextbrowserContinue->AddHighlightingRule(QSCurrentHighlightingStr, pQColorSelected);
	pQTextbrowserContinue->HighlightingTextBrowser();
	pQDialogHighlighter->close();
}
void CFemtoMonitorcenter::On_pQHighlighterDialogCancel_Triggered()
{
	pQDialogHighlighter->close();
}
void CFemtoMonitorcenter::On_pQOpenColorDialog_Triggered()
{
	*pQColorSelected = QColorDialog::getColor(Qt::black, this);
	QPalette  pa;
	pa.setColor(QPalette::WindowText, *pQColorSelected);
	pQLabelSampleStr->setPalette(pa);
}
/**********************************************************************//**
@brief slot of log current windows data 
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CFemtoMonitorcenter::On_pQWriteDialogFileButton_clicked()
{
	QString QSOpenFile = QFileDialog::getOpenFileName(NULL, "OpenFile", ".", NULL);
	this->pQWriteDialogEdit->setText(QSOpenFile);
}
void CFemtoMonitorcenter::On_pQWriteDialogConfirmButton_clicked()
{
	if (NULL == pQWriteDialogEdit->text())
	{
		QMessageBoxFailure("Please Select Log File Path");
		return;
	}
	QByteArray QByteArrayWriteFilePath = pQWriteDialogEdit->text().toLatin1();
	char *pWriteFilePath = QByteArrayWriteFilePath.data();
	pWriteDialog->close();
	///enter critical section
	FILE* fpLogDataFile = fopen(pWriteFilePath, "a+");
	int LogDataindex = pQMainTabWidget->currentIndex();
	emit emitLogDataFile( LogDataindex, fpLogDataFile);
}
void CFemtoMonitorcenter::On_pQWriteDialogCancelButton_clicked()
{
	pWriteDialog->close();
}