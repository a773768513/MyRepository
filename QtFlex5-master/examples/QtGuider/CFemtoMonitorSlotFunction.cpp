#include "QtGuider.h"
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qcolor.h>
#include <qcolordialog.h>
#include <qpalette.h>
#include <qsettings.h>

#include "QtFlexWidget.h"
#include "QtFlexHelper.h"
#include "QtDockGuider.h"
#include "QtDockWidget.h"
#include "QtFlexManager.h"
#include "ThreadQtextbrowser.h"
#include "ManageThreadObject.h"
#include <QtWidgets\QTableWidgetItem>
#include <qevent.h>
/**********************************************************************//**
@brief  slots of Qaction to create OpenFileDialog 
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void QtGuider::On_pQActionOpenFileDialog_triggered()
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
void QtGuider::On_pQActionOpenHighlighterDialog_triggered()
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
void QtGuider::On_pQActionOpenLogFileDialog_triggered()
{
	CreateWriteFileWindow();
}
/**********************************************************************//**
@brief  Create a child dialog to Open COM
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void QtGuider::CreateOpenFileChildWindows()
{
	/// create dialog and close when delete 
	pDialogOpenFile = new QDialog(this);
	pDialogOpenFile->setAttribute(Qt::WA_DeleteOnClose, true);
	pGridLayoutOpenFileDialog = new QGridLayout(pDialogOpenFile);
	////pGridLayoutOpenFileDialog->setSizeConstraint(QLayout::SetFixedSize);  ///fixed dialog (for hide the pQWidgetDetail but no change the widget relative position
	pGridLayoutOpenFileDialog->setSpacing(20);
	pGridLayoutOpenFileDialog->setMargin(20);
	///
	pQLabelOpenFilePath = new QLabel(pDialogOpenFile);
	pQLabelOpenFilePath->setText("OpenFilePath");
	pGridLayoutOpenFileDialog->addWidget(pQLabelOpenFilePath, 0, 0, 1, 1);

	///line edit to input the opwn file path  change of qcombox to record the setting value 
	pQTextEditOpenFilePath = new  QComboBox(pDialogOpenFile);
	pQTextEditOpenFilePath->setEditable(true);
	pGridLayoutOpenFileDialog->addWidget(pQTextEditOpenFilePath, 0, 1, 1, 2);
	///setting 
	QSettings CFemtoMonitorCentersettings("FemtoMonitorCenter", "CRT");
	CFemtoMonitorCentersettings.beginReadArray("OpenFilePathSetting");
	QString originValue;
	for (int i = 0; i < QSETTINGS_ARRAY_LENGTH; ++i)
	{
		CFemtoMonitorCentersettings.setArrayIndex(i);
		originValue = CFemtoMonitorCentersettings.value("Open File String", QString("AAAAAAAAAA")).toString();
		if (originValue == "AAAAAAAAAA")
		{
			break;
		}
		pQTextEditOpenFilePath->addItem(originValue);

	}
	CFemtoMonitorCentersettings.endArray();
	///push button to use filedialog select file path 
	pQPushButtonOpenFilePath = new QPushButton(pDialogOpenFile);
	pQPushButtonOpenFilePath->setText("OpenFile");
	connect(pQPushButtonOpenFilePath, SIGNAL(clicked()), this, SLOT(On_OpenFileChildDialogSelectFile_Clicked()));
	pGridLayoutOpenFileDialog->addWidget(pQPushButtonOpenFilePath, 1, 2, 1, 1);
	///confirm button  and cancel button pQPushButttonOpenFileConfirm
	pQPushButttonOpenFileConfirm = new QPushButton(pDialogOpenFile);
	pQPushButttonOpenFileConfirm->setText("Confirm");
	pGridLayoutOpenFileDialog->addWidget(pQPushButttonOpenFileConfirm, 3, 1);
	pQPushButtonOpenFileCancel = new QPushButton(pDialogOpenFile);
	pQPushButtonOpenFileCancel->setText("Cancel");
	pGridLayoutOpenFileDialog->addWidget(pQPushButtonOpenFileCancel, 3, 2);

	pGridLayoutOpenFileDialog->setColumnStretch(0, 0);
	pGridLayoutOpenFileDialog->setColumnStretch(1, 1);
	pGridLayoutOpenFileDialog->setColumnStretch(2, 1);
	///connect the object and slot (only the object exist can connect this )
	connect(pQPushButttonOpenFileConfirm, SIGNAL(clicked()), this, SLOT(On_pQPushButttonOpenFileConfirm_Clicked()));
	connect(pQPushButtonOpenFileCancel, SIGNAL(clicked()), this, SLOT(On_pQPushButtonOpenFileCancel_Clicked()));
	
	pDialogOpenFile->exec();
}
/**********************************************************************//**
@brief  Create a child dialog to add highlighter rule 
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void QtGuider::CreateHighlightingWindows()
{
	///new a dialog and add the grid layout
	pQDialogHighlighter = new QDialog;
	pQDialogHighlighter->setAttribute(Qt::WA_DeleteOnClose, true);
	pQgridLayoutHighlighterDialog = new QGridLayout(pQDialogHighlighter);
	pQDialogHighlighter->resize(QSize(280, 150));
	pQgridLayoutHighlighterDialog->setMargin(20);
	pQgridLayoutHighlighterDialog->setSpacing(15);
	/// combobox to input highlighter string
	pQComboBoxHighlighterDialogStr = new QComboBox(pQDialogHighlighter);
	pQComboBoxHighlighterDialogStr->setEditable(1);
	pQComboBoxHighlighterDialogStr->addItem("");
	pQComboBoxHighlighterDialogStr->addItem("#RANGE");
	///qsetting add the user last use
	QSettings CFemtoMonitorCentersettings("FemtoMonitorCenter", "CRT");
	CFemtoMonitorCentersettings.beginReadArray("Highlighter String");
	for (int i = 0; i < QSETTINGS_ARRAY_LENGTH; ++i)
	{
		CFemtoMonitorCentersettings.setArrayIndex(i);
		QString originValue = CFemtoMonitorCentersettings.value("Highligher String", QString("AAAAAAAAAA")).toString();
		if (originValue == "AAAAAAAAAA")
		{
			break;
		}
		pQComboBoxHighlighterDialogStr->addItem(originValue);
	}
	CFemtoMonitorCentersettings.endArray();
	pQgridLayoutHighlighterDialog->addWidget(pQComboBoxHighlighterDialogStr, 0, 0, 1, 2);
	///pQLabelSampleStr new 
	pQLabelSampleStr = new QLabel(pQDialogHighlighter);
	pQLabelSampleStr->setText("Sample");
	QFont QQFontinpQLabelSampleStr("Times New Roman", 15, 75);
	pQLabelSampleStr->setFont(QQFontinpQLabelSampleStr);
	pQgridLayoutHighlighterDialog->addWidget(pQLabelSampleStr, 0, 2);

	///new push to open color dialog
	pQOpenColorDialog = new QPushButton(pQDialogHighlighter);
	pQOpenColorDialog->setText("SelectColor");
	pQgridLayoutHighlighterDialog->addWidget(pQOpenColorDialog, 1, 2);
	connect(pQOpenColorDialog, SIGNAL(clicked()), this, SLOT(On_pQOpenColorDialog_Triggered()));
	///
	///Confirm and cancel button pQPushButttonOpenFileConfirm
	pQHighlighterDialogConfirm = new QPushButton(pQDialogHighlighter);
	pQHighlighterDialogConfirm->setText("Confirm");
	pQgridLayoutHighlighterDialog->addWidget(pQHighlighterDialogConfirm, 2, 1);
	pQHighlighterDialogCancel = new QPushButton(pQDialogHighlighter);
	pQHighlighterDialogCancel->setText("Cancel");
	pQgridLayoutHighlighterDialog->addWidget(pQHighlighterDialogCancel, 2, 2);
	connect(pQHighlighterDialogConfirm, SIGNAL(clicked()), this, SLOT(On_pQHighlighterDialogConfirm_Triggered()));
	connect(pQHighlighterDialogCancel, SIGNAL(clicked()), this, SLOT(On_pQHighlighterDialogCancel_Triggered()));
	///hide and wait for show
	pQDialogHighlighter->exec();
}
/**********************************************************************//**
@brief  Create a child dialog to log data to seleted file 
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void QtGuider::CreateWriteFileWindow()
{
	///dialog and gridlayout 
	pWriteDialog = new QDialog;
	pWriteDialog->resize(QSize(300, 50));
	pWriteDialog->setAttribute(Qt::WA_DeleteOnClose, true);
	pWriteGridLayout = new QGridLayout(pWriteDialog);
	pWriteGridLayout->setMargin(20);
	pWriteGridLayout->setSpacing(15);
	////new windows designs
	pQWriteDialogFileDirectory = new QComboBox(pWriteDialog);
	pQWriteDialogFileDirectory->setEditable(true);
	pWriteGridLayout->addWidget(pQWriteDialogFileDirectory, 0, 0, 1, 3);
	
	pQWriteDialogFileButton = new QPushButton(pWriteDialog);
	pQWriteDialogFileButton->setText("Open Directory");
	pWriteGridLayout->addWidget(pQWriteDialogFileButton, 1, 2, 1, 1);
	connect(pQWriteDialogFileButton, SIGNAL(clicked()), this, SLOT(On_pQWriteDialogFileButton_clicked()));
	///
	QLabel *pQWriteDialogEditLabel = new QLabel("Log File Name",pWriteDialog);
	pQWriteDialogEdit = new  QLineEdit(pWriteDialog);
	pWriteGridLayout->addWidget(pQWriteDialogEditLabel, 2, 0, 1, 1);
	pWriteGridLayout->addWidget(pQWriteDialogEdit, 2, 1, 1, 2);

	////
	pQWriteDialogFileAddCheckBox = new QCheckBox("Add Date", pWriteDialog);
	pQWriteDialogFileAddCheckBox->setChecked(true);
	pQWriteDialogFileAdd = new QLineEdit(pWriteDialog);
	QString QSCurrentDateTime = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
	pQWriteDialogFileAdd->setText(QSCurrentDateTime);
	pQWriteDialogFileAdd->setEnabled(false);
	connect(pQWriteDialogFileAddCheckBox, SIGNAL(stateChanged(int)), this, SLOT(On_pQWriteDialogFileAddCheckBox_StateChange(int)));
	pWriteGridLayout->addWidget(pQWriteDialogFileAddCheckBox, 3, 0, 1, 1);
	pWriteGridLayout->addWidget(pQWriteDialogFileAdd, 3, 1, 1, 2);
	///.txt
	pQWriteDialogFileSuffix = new QLineEdit(pWriteDialog);
	pQWriteDialogFileSuffix->setText(".txt");
	pQWriteDialogFileSuffixCheckBox = new  QCheckBox("Default Suffix", pWriteDialog);
	connect(pQWriteDialogFileSuffixCheckBox, SIGNAL(stateChanged(int)), this, SLOT(On_pQWriteDialogFileSuffixCheckBox_StateChange(int)));
	pQWriteDialogFileSuffixCheckBox->setChecked(true);
	pWriteGridLayout->addWidget(pQWriteDialogFileSuffixCheckBox, 4, 0, 1, 1);
	pWriteGridLayout->addWidget(pQWriteDialogFileSuffix, 4, 1, 1, 2);

	///qsetting add to pQWriteDialogEdit
	QSettings CFemtoMonitorCentersettings("FemtoMonitorCenter", "CRT");
	CFemtoMonitorCentersettings.beginReadArray("Log String");
	for (int i = 0; i < QSETTINGS_ARRAY_LENGTH; ++i)
	{
		CFemtoMonitorCentersettings.setArrayIndex(i);
		QString originValue = CFemtoMonitorCentersettings.value("Log Path String", QString("AAAAAAAAAA")).toString();
		if (originValue == "AAAAAAAAAA")
		{
			break;
		}
		pQWriteDialogFileDirectory->addItem(originValue);
	}
	CFemtoMonitorCentersettings.endArray();
	///add  linedit  and open file button
	///CreatepCombinationWindows
	pWriteGridLayout->addWidget(CreatepCombinationWindows(), 5, 0, 1, -1);
	/// add  confirm button and cancel button 
	pQWriteDialogConfirmButton = new QPushButton(pWriteDialog);
	pQWriteDialogConfirmButton->setText("Confirm");
	pWriteGridLayout->addWidget(pQWriteDialogConfirmButton, 6, 1, 1, 1);
	pQWriteDialogCancelButton = new QPushButton(pWriteDialog);
	pQWriteDialogCancelButton->setText("Cancel");
	pWriteGridLayout->addWidget(pQWriteDialogCancelButton, 6, 2, 1, 1);
	///write data to file dialog 
	connect(pQWriteDialogConfirmButton, SIGNAL(clicked()), this, SLOT(On_pQWriteDialogConfirmButton_clicked()));
	connect(pQWriteDialogCancelButton, SIGNAL(clicked()), this, SLOT(On_pQWriteDialogCancelButton_clicked()));
	pWriteDialog->exec();
}
QGroupBox* QtGuider::CreatepCombinationWindows()
{
	///Qgroup and 
	pQGroupBoxAutomaticLog = new QGroupBox("Automatic Log", pWriteDialog);
	pQGroupBoxAutomaticLog->setCheckable(true);
	pQGroupBoxAutomaticLog->setChecked(false);
	pQGridlayoutAutomaticLog = new QGridLayout(pQGroupBoxAutomaticLog);
	pQGroupBoxAutomaticLog->setLayout(pQGridlayoutAutomaticLog);

	/// select the autoic mode 
	pQGroupBoxLogTime = new QGroupBox("Setting", pWriteDialog);
	pQVBoxLayoutRadioButton = new QVBoxLayout(pQGroupBoxAutomaticLog);
	pQGroupBoxLogTime->setLayout(pQVBoxLayoutRadioButton);
	pQRadioButtonOnce = new QRadioButton("Only Once", pQGroupBoxAutomaticLog);
	pQRadioButtonDay = new QRadioButton("Every Day", pQGroupBoxAutomaticLog);
	pQRadioButtonWeekly = new QRadioButton("Weekly", pQGroupBoxAutomaticLog);
	pQRadioButtonOnce->setChecked(true);
	pQVBoxLayoutRadioButton->addWidget(pQRadioButtonOnce);
	pQVBoxLayoutRadioButton->addWidget(pQRadioButtonDay);
	pQVBoxLayoutRadioButton->addWidget(pQRadioButtonWeekly);
	pQVBoxLayoutRadioButton->addStretch();
	pQGridlayoutAutomaticLog->addWidget(pQGroupBoxLogTime, 0, 0, 1, 1);
	///
	///
	pQGroupBoxDataTime = new QGroupBox("Setting", pQGroupBoxAutomaticLog);
	pQVBoxLayoutDataTime = new QVBoxLayout(pQGroupBoxAutomaticLog);
	pQGroupBoxDataTime->setLayout(pQVBoxLayoutDataTime);

	QLabel *pQDateTimeEditStartLabel = new QLabel("Starting", pQGroupBoxAutomaticLog);
	pQDateTimeEditStart = new QDateTimeEdit(pQGroupBoxAutomaticLog);
	pQDateTimeEditStart->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
	pQDateTimeEditStart->setCalendarPopup(true);
	pQDateTimeEditStart->setMinimumDateTime(QDateTime::currentDateTime());
	QLabel *pQDateTimeEditEndLabel = new QLabel("End", pQGroupBoxAutomaticLog);
	pQDateTimeEditEnd = new QDateTimeEdit(pQGroupBoxAutomaticLog);
	pQDateTimeEditEnd->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
	pQDateTimeEditEnd->setCalendarPopup(true);
	pQDateTimeEditEnd->setMinimumDateTime(QDateTime::currentDateTime());

	pQVBoxLayoutDataTime->addWidget(pQDateTimeEditStartLabel);
	pQVBoxLayoutDataTime->addWidget(pQDateTimeEditStart);
	pQVBoxLayoutDataTime->addWidget(pQDateTimeEditEndLabel);
	pQVBoxLayoutDataTime->addWidget(pQDateTimeEditEnd);
	pQVBoxLayoutDataTime->addStretch();
	pQGridlayoutAutomaticLog->addWidget(pQGroupBoxDataTime, 0, 1, 1, 1);

	return  pQGroupBoxAutomaticLog;
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
void QtGuider::On_pQPushButttonOpenFileConfirm_Clicked()
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
void QtGuider::On_pQPushButtonOpenFileCancel_Clicked()
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
void QtGuider::On_OpenFileChildDialogSelectFile_Clicked()
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
void QtGuider::On_CreateGUIQTextbrowserManagethread_Triggered(QString Tabtitle)
{
	CThreadQtextbrowser* pCThreadQtextbrowser = new CThreadQtextbrowser(this);
	pCThreadQtextbrowser->setTextBrowserTitle(Tabtitle);
	pShowFocusEvent->addItem(Tabtitle);
	FlexWidget* flexWidget = FlexManager::instance()->createFlexWidget(Flex::FileView, Flex::parent(Flex::FileView), Flex::windowFlags());
	DockWidget* dockWidget = FlexManager::instance()->createDockWidget(Flex::FileView, flexWidget, Flex::widgetFlags(), Tabtitle);
	connect(dockWidget, SIGNAL(focusInThisWindows(QString)), this, SLOT(On_DockWidget_focusInThisWindows(QString)));
	dockWidget->setViewMode(Flex::FileView);
	flexWidget->installEventFilter(this);
	QvectorFlexWidgets.append(flexWidget);
	QVectorThreadTextbrowser.append(pCThreadQtextbrowser);
	QvectorFlexWidgets.append(flexWidget);
	connect(pCThreadQtextbrowser, SIGNAL(emitStopLogTextbrowser()), this, SLOT(On_emitStopLogTextbrowser_Request()));
	connect(pCThreadQtextbrowser, SIGNAL(emitFocuseInTextbrowser(QString)), this, SLOT());
	dockWidget->attachWidget(pCThreadQtextbrowser);
	dockWidget->setWindowTitle(Tabtitle);
	flexWidget->addDockWidget(dockWidget);
	flexWidget->show();

	

	int CurrentRowNum = this->pQTableWidgetManageWidgets->rowCount();
	CurrentRowNum++;
	this->pQTableWidgetManageWidgets->setRowCount(CurrentRowNum);
	QTableWidgetItem *pQtableWidgetItemPortName = new QTableWidgetItem(Tabtitle);
	this->pQTableWidgetManageWidgets->setItem(CurrentRowNum - 1, 0, pQtableWidgetItemPortName);
	QTableWidgetItem *pQTableWidgetItemStatus = new QTableWidgetItem("transiting");
	this->pQTableWidgetManageWidgets->setItem(CurrentRowNum - 1, 1, pQTableWidgetItemStatus);
	QTableWidgetItem *pQTableWidgetItemSpeed = new QTableWidgetItem("starting");
	this->pQTableWidgetManageWidgets->setItem(CurrentRowNum - 1, 2, pQTableWidgetItemSpeed);
	QTableWidgetItem *pQTableWidgetItemLogStatus = new QTableWidgetItem("No");
	this->pQTableWidgetManageWidgets->setItem(CurrentRowNum - 1, 3, pQTableWidgetItemLogStatus);
	(dynamic_cast<QtCentral*> (this->centralWidget()))->content->addFlexWidget(flexWidget,Flex::M,0);
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
void QtGuider::QMessageBoxFailure(QString QSInformation)
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
void QtGuider::On_AppendDataManagethread_Triggered(int NumberWindowManage, char* pAppendDataPointerManage)
{
	CThreadQtextbrowser *pAppendDataCThreadQTextBrowser = (QVectorThreadTextbrowser.at(NumberWindowManage));
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
void QtGuider::On_EmitRefreshReceivingRateManage_Triggered()
{
	int AllOverCycleNum = 0;
	QString QSNumSpeedBuf; 
	QTableWidgetItem *pTablewidgetsSpeed;
	QTableWidgetItem *pTablewidgetsLogState;
	pCManageThreadObject->QVectorRecoredReceiveDataReadWriteLock.lockForRead();
	pCManageThreadObject->QVectorLogFileInfoReadWriteLock.lockForRead();
	for each (int  QVectorRecoredReceiveDataSpeed in  pCManageThreadObject->QVectorRecoredReceiveData)
	{
		pTablewidgetsSpeed = this-> pQTableWidgetManageWidgets->item(AllOverCycleNum, 2);
		pTablewidgetsLogState = this->pQTableWidgetManageWidgets->item(AllOverCycleNum, 3);
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
void QtGuider::On_emitCloseQtextbrowserRecordManage_triggered(int index)
{
	///CThreadQtextbrowser* pDeleteCThreadQtextbrowser = dynamic_cast<CThreadQtextbrowser*> (pQMainTabWidget->widget(index));
	///delete pDeleteCThreadQtextbrowser;

	///this->pQTableWidgetManageWidgets->removeRow(index);
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

void QtGuider::On_pQHighlighterDialogConfirm_Triggered()
{
	/***********
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
	
	*********/
	pQDialogHighlighter->close();
}
void QtGuider::On_pQHighlighterDialogCancel_Triggered()
{
	pQDialogHighlighter->close();
}
void QtGuider::On_pQOpenColorDialog_Triggered()
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
void QtGuider::On_pQWriteDialogFileButton_clicked()
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
void QtGuider::On_pQWriteDialogConfirmButton_clicked()
{
	/********
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
	int LogDataindex = pQMainTabWidget->currentIndex();
	QString QSLogDataindex;
	QSLogDataindex.setNum(LogDataindex);
	StorageUserSelectInformation.append(","+ QSLogDataindex);
	emit emitLogDataFile(StorageUserSelectInformation, pWriteFilePath);
	***********/
}
void QtGuider::On_pQWriteDialogCancelButton_clicked()
{
	pWriteDialog->close();
}

void QtGuider::On_pQWriteDialogFileAddCheckBox_StateChange(int stats)
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

void QtGuider::On_pQWriteDialogFileSuffixCheckBox_StateChange(int stats)
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

void QtGuider::On_emitStopLogTextbrowser_Request()
{
	/*******
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
	*********/
}
bool QtGuider::eventFilter(QObject *watched, QEvent *event)
{
	if (event->type() == QEvent::FocusIn)
	{
		return true;
	}
	return false;
}


void QtGuider::on_flexWidgetDestroying(FlexWidget* flexWidget)
{

}

void QtGuider::on_dockWidgetDestroying(DockWidget* dockWidget)
{
	CThreadQtextbrowser* deleteCthreadTextbrowser = (CThreadQtextbrowser*)(dockWidget->widget());
	
	int index = QVectorThreadTextbrowser.indexOf(deleteCthreadTextbrowser);
	if (-1 == index)
	{
		return;
	}
	QVectorThreadTextbrowser.removeAt(index);
	QvectorFlexWidgets.removeAt(index);
	this->pQTableWidgetManageWidgets->removeRow(index);
	emit emitCloseCurrentQtextbrowserGUI(index);
}



void QtGuider::On_Textbrowser_emitFocuseInTextbrowser(QString focusWidgetsTitle)
{
	int index = pShowFocusEvent->findText(focusWidgetsTitle);
	if (-1 == index)
	{
		qDebug("On_Textbrowser_emitFocuseInTextbrowser index == -1");
	}
	pShowFocusEvent->setCurrentIndex(index);
	
}