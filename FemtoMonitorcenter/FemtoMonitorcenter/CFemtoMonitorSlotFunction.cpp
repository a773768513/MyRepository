#include "CFemtoMonitorcenter.h"
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qcolor.h>
#include <qcolordialog.h>
#include <qpalette.h>
#include <qsettings.h>
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
	if (NULL == pQTextEditOpenFilePath->currentText())
	{
		EmitQmessageInformation("Please select the serial port");
		return;
	}
	QString QSOpenFilePath = pQTextEditOpenFilePath->currentText();
	QSettings CFemtoMonitorCentersettings("FemtoMonitorCenter", "CRT");
	CFemtoMonitorCentersettings.beginWriteArray("OpenFilePathSetting");
	QString QSOpenFilePathChange = QSOpenFilePath;
	QString originValue;
	for (int i = 0; i < QSETTINGS_ARRAY_LENGTH; ++i)
	{
		CFemtoMonitorCentersettings.setArrayIndex(i);
		originValue = CFemtoMonitorCentersettings.value("Open File String", QString("AAAAAAAAAA")).toString();
		if (originValue == QSOpenFilePath)
		{
			CFemtoMonitorCentersettings.setValue("Open File String", QVariant(QSOpenFilePathChange));
			break;
		}
		CFemtoMonitorCentersettings.setValue("Open File String", QVariant(QSOpenFilePathChange));
		if (originValue == "AAAAAAAAAA")
		{
			break;
		}
		QSOpenFilePathChange = originValue;
	}
	CFemtoMonitorCentersettings.endArray();
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

	QSettings CFemtoMonitorCentersettings("FemtoMonitorCenter", "CRT");
	CFemtoMonitorCentersettings.beginReadArray("OpenFilePathSetting");
	CFemtoMonitorCentersettings.setArrayIndex(0);
	QString QSOpenFilePathSetting = CFemtoMonitorCentersettings.value("Open File String", QString(".")).toString();
	QString QSOpenFile = QFileDialog::getOpenFileName(NULL, "OpenFile", QSOpenFilePathSetting, NULL);
	this->pQTextEditOpenFilePath->setCurrentText(QSOpenFile);

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
	connect(pCThreadQtextbrowser, SIGNAL(emitStopLogTextbrowser()), this, SLOT(On_emitStopLogTextbrowser_Request()));

	int CurrentRowNum = pQTableWidgetManageWidgets->rowCount();
	CurrentRowNum++;
	pQTableWidgetManageWidgets->setRowCount(CurrentRowNum);
	QTableWidgetItem *pQtableWidgetItemPortName = new QTableWidgetItem(Tabtitle);
	pQTableWidgetManageWidgets->setItem(CurrentRowNum-1,0,pQtableWidgetItemPortName);
	QTableWidgetItem *pQTableWidgetItemStatus = new QTableWidgetItem("transiting");
	pQTableWidgetManageWidgets->setItem(CurrentRowNum - 1, 1, pQTableWidgetItemStatus);
	QTableWidgetItem *pQTableWidgetItemSpeed = new QTableWidgetItem("starting");
	pQTableWidgetManageWidgets->setItem(CurrentRowNum - 1, 2, pQTableWidgetItemSpeed);
	QTableWidgetItem *pQTableWidgetItemLogStatus = new QTableWidgetItem("No");
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
	QTableWidgetItem *pTablewidgetsLogState;
	pCManageThreadObject->QVectorRecoredReceiveDataReadWriteLock.lockForRead();
	pCManageThreadObject->QVectorLogFileInfoReadWriteLock.lockForRead();
	for each (int  QVectorRecoredReceiveDataSpeed in  pCManageThreadObject->QVectorRecoredReceiveData)
	{
		pTablewidgetsSpeed = pQTableWidgetManageWidgets->item(AllOverCycleNum, 2);
		pTablewidgetsLogState = pQTableWidgetManageWidgets->item(AllOverCycleNum, 3);
		QSNumSpeedBuf.setNum(QVectorRecoredReceiveDataSpeed);
		QSNumSpeedBuf += "b/s";
		pTablewidgetsSpeed->setText(QSNumSpeedBuf);
		pCManageThreadObject->QVectorRecoredReceiveData.replace(AllOverCycleNum,0);
		if (pCManageThreadObject->QVectorLogFileInfo.at(AllOverCycleNum).LogMode == 0)
		{
			if (pCManageThreadObject->QVectorLogFileInfo.at(AllOverCycleNum).logFilePointer == NULL)
			{
				pTablewidgetsLogState->setText("No");
			}
			else
			{
				pTablewidgetsLogState->setText("Loging");
			}
		}
		else if (pCManageThreadObject->QVectorLogFileInfo.at(AllOverCycleNum).LogMode == 1)
		{
			pTablewidgetsLogState->setText("Loging");
		}
		else 
		{
			if (pCManageThreadObject->QVectorLogFileInfo.at(AllOverCycleNum).logFilePointer == NULL)
			{
				if (pCManageThreadObject->QVectorLogFileInfo.at(AllOverCycleNum).LogFileName[0] == 0)
				{
					pTablewidgetsLogState->setText("No");

				}
				else
				{
					pTablewidgetsLogState->setText("Waiting");
				}
			}
			else
			{
				pTablewidgetsLogState->setText("Loging");
			}
		}
		AllOverCycleNum++;
	}
	
	pCManageThreadObject->QVectorRecoredReceiveDataReadWriteLock.unlock();
	pCManageThreadObject->QVectorLogFileInfoReadWriteLock.unlock();
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
	if (pQMainTabWidget->currentIndex() == -1)
	{
		QMessageBoxFailure("Currently No Open Serial Port!!! ");
		return;
	}
	if (pQComboBoxHighlighterDialogStr->currentText() == NULL)
	{
		QMessageBoxFailure("No Input Character");
		return;
	}
	QString QSCurrentHighlightingStr = pQComboBoxHighlighterDialogStr->currentText();
	////add the Qstring To qsettting
	QSettings CFemtoMonitorCentersettings("FemtoMonitorCenter", "CRT");
	CFemtoMonitorCentersettings.beginReadArray("Highlighter String");
	QString QSCurrentHighlightingStrChange = QSCurrentHighlightingStr;
	QString QSSettingClaue;
	for (int i = 0; i < QSETTINGS_ARRAY_LENGTH; ++i)
	{
		CFemtoMonitorCentersettings.setArrayIndex(i);
		QSSettingClaue = CFemtoMonitorCentersettings.value("Highligher String", QString("AAAAAAAAAA")).toString();
		if (QSSettingClaue == QSCurrentHighlightingStr)
		{
			CFemtoMonitorCentersettings.setValue("Highligher String", QVariant(QSCurrentHighlightingStrChange));
			break;
		}
		CFemtoMonitorCentersettings.setValue("Highligher String", QVariant(QSCurrentHighlightingStrChange));
		if (QSSettingClaue == "AAAAAAAAAA")
		{
			break;
		}
		QSCurrentHighlightingStrChange = QSSettingClaue;
	}
	CFemtoMonitorCentersettings.endArray();
	///
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
@brief slot of log current windows data (select the file directory)
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CFemtoMonitorcenter::On_pQWriteDialogFileButton_clicked()
{
	QSettings CFemtoMonitorCentersettings("FemtoMonitorCenter", "CRT");
	CFemtoMonitorCentersettings.beginWriteArray("openFileDirectory");
	CFemtoMonitorCentersettings.setArrayIndex(0);
	QString OpenFileRecord = CFemtoMonitorCentersettings.value("Log Path String", QString(".")).toString();
	QString OpenFileRecordSelect = QFileDialog::getExistingDirectory(this, "Open Directory", OpenFileRecord);
	this->pQWriteDialogFileDirectory->setCurrentText(OpenFileRecordSelect);
}
/**********************************************************************//**
@brief slot of log Data judge to manage
@param  
@return 
@author YHF
@date 2018/06/26  10:51
@note 
History:
**************************************************************************/
void CFemtoMonitorcenter::On_pQWriteDialogConfirmButton_clicked()
{
	QString QSpQWriteDialogFileDirectory = pQWriteDialogFileDirectory->currentText();
	QString QSLogString = (QSpQWriteDialogFileDirectory)+'/' + pQWriteDialogEdit->text() + pQWriteDialogFileAdd->text() + pQWriteDialogFileSuffix->text();
	if (pQMainTabWidget->currentIndex() == -1)
	{
		QMessageBoxFailure("Currently No Open Serial Port!!! ");
		pWriteDialog->close();
		return;
	}
	if (NULL == pQWriteDialogFileDirectory->currentText())
	{
		QMessageBoxFailure("Please Select Log File Path");
		return;
	}
	QSettings CFemtoMonitorCentersettings("FemtoMonitorCenter", "CRT");
	CFemtoMonitorCentersettings.beginWriteArray("Log String");
	QString QSWriteFileChange = QSpQWriteDialogFileDirectory;
	QString SettingData;
	for (int i = 0; i < QSETTINGS_ARRAY_LENGTH; ++i)
	{
		CFemtoMonitorCentersettings.setArrayIndex(i);
		SettingData = CFemtoMonitorCentersettings.value("Log Path String", QString("AAAAAAAAAA")).toString();
		if (SettingData == QSpQWriteDialogFileDirectory)
		{
			CFemtoMonitorCentersettings.setValue("Log Path String", QSWriteFileChange);
			break;
		}
		CFemtoMonitorCentersettings.setValue("Log Path String", QSWriteFileChange);
		if (SettingData == "AAAAAAAAAA")
		{
			break;
		}
		QSWriteFileChange = SettingData;
	}
	QByteArray QByteArrayWriteFilePath = QSLogString.toLatin1();
	char *pWriteFilePath = QByteArrayWriteFilePath.data();
	QString StorageUserSelectInformation;
	///
	if (pQGroupBoxAutomaticLog->isChecked())
	{
		///Confirm user inpur mode is correct
		QDateTime QDateTimeStart;
		QDateTimeStart = pQDateTimeEditStart->dateTime();
		QString QSQDateTimeStart = QDateTimeStart.toString("yyyyMMddhhmmss");
		QDateTime QDateTimeEnd;
		QDateTimeEnd = pQDateTimeEditEnd->dateTime();
		QString QSQDateTimeEnd = QDateTimeEnd.toString("yyyyMMddhhmmss");
		if (QDateTimeStart > QDateTimeEnd)
		{
			QMessageBoxFailure("The end time is earlier than the start time !");
			return;
		}
		///User Only lOG once
		if (pQRadioButtonOnce->isChecked())
		{
			StorageUserSelectInformation.append('1');
		}
		else if (pQRadioButtonDay->isChecked())
		{
			StorageUserSelectInformation.append('2');
			QDateTimeStart.setDate(QDate::fromString("20000101", "yyyyMMdd"));
			QDateTimeEnd.setDate(QDate::fromString("20000101", "yyyyMMdd"));
			QSQDateTimeStart = QDateTimeStart.toString("yyyyMMddhhmmss");
			QSQDateTimeEnd = QDateTimeEnd.toString("yyyyMMddhhmmss");
			if (QDateTimeStart > QDateTimeEnd)
			{
				QMessageBoxFailure("The end time is earlier than the start time !\n(The system only focuses on H:M:S when selecting Every Date)");
				return;
			}
		}
		else if (pQRadioButtonDay->isChecked())
		{
			StorageUserSelectInformation.append('3');
		}
		StorageUserSelectInformation.append("," + QSQDateTimeStart + "," + QSQDateTimeEnd);
	}
	else
	{
		StorageUserSelectInformation.append("0" );
		StorageUserSelectInformation.append( "," );
		StorageUserSelectInformation.append("20000101000000");
		StorageUserSelectInformation.append(",");
		StorageUserSelectInformation.append("20000101000000");
	}
	pWriteDialog->close();
	/*****
	FILE* fpLogDataFile = fopen(pWriteFilePath, "a+");
	if (NULL == fpLogDataFile)
	{
		QMessageBoxFailure("Can Not Open Log File!");
		return;
	}
	***************/
	int LogDataindex = pQMainTabWidget->currentIndex();
	QString QSLogDataindex;
	QSLogDataindex.setNum(LogDataindex);
	StorageUserSelectInformation.append(","+ QSLogDataindex);
	emit emitLogDataFile(StorageUserSelectInformation, pWriteFilePath);
}
void CFemtoMonitorcenter::On_pQWriteDialogCancelButton_clicked()
{
	pWriteDialog->close();
}

void CFemtoMonitorcenter::On_pQWriteDialogFileAddCheckBox_StateChange(int stats)
{
	if (stats == 0)
	{
		pQWriteDialogFileAdd->clear();
	}
	else
	{
		QString QSCurrentDateTime = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
		pQWriteDialogFileAdd->setText(QSCurrentDateTime);
	}
}

void CFemtoMonitorcenter::On_pQWriteDialogFileSuffixCheckBox_StateChange(int stats)
{
	if (stats == 0)
	{
		pQWriteDialogFileSuffix->setEnabled(true);
		pQWriteDialogFileSuffix->clear();
	}
	else
	{
		pQWriteDialogFileSuffix->setEnabled(false);
		pQWriteDialogFileSuffix->setText(".txt");
	}
}

void CFemtoMonitorcenter::On_emitStopLogTextbrowser_Request()
{
	CThreadQtextbrowser* pDeleteCThreadQtextbrowser = dynamic_cast<CThreadQtextbrowser*> (sender());
	int TabCount =  pQMainTabWidget->count();
	bool SenderIndexSuccess = false; 
	int IndexSender = 0;
	while (IndexSender < TabCount)
	{
		if (pDeleteCThreadQtextbrowser == dynamic_cast<CThreadQtextbrowser*> (pQMainTabWidget->widget(IndexSender)))
		{
			SenderIndexSuccess = true;
			break;
		}
		IndexSender++;
	}
	if (false == SenderIndexSuccess)
	{
		qDebug("Stop Log No index Sender");
	}
	emit emitStopLogGUI(IndexSender);
}