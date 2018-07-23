#pragma once

#include <QtWidgets/QMainWindow>
#include <qgridlayout.h>
#include <qtextedit.h>
#include <qdialog.h>
#include <qpushbutton.h>
#include <qaction.h>
#include <qstatusbar.h>
#include <qtablewidget.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qthread.h>
#include "ui_CFemtoMonitorcenter.h"
#include "ManageThreadObject.h"
#include "ThreadQtextbrowser.h"
#include <qcombobox.h>
#include <stdio.h>
#include <qgroupbox.h>
#include <qradiobutton.h>
#include <qdatetimeedit.h>
#include <qcheckbox.h>

class DockGuiderImpl;
class CManageThreadObject;

#ifndef __QSETTINGS_ARRAY_LENGTH__
#define __QSETTINGS_ARRAY_LENGTH__
#define QSETTINGS_ARRAY_LENGTH 7
#endif
class CFemtoMonitorcenter : public QMainWindow
{
	Q_OBJECT

public:
	CFemtoMonitorcenter(QWidget *parent = Q_NULLPTR);
	~CFemtoMonitorcenter();
private:
	///manage thread and object create
	CManageThreadObject  *pCManageThreadObject;
	QThread *pManagethread;
	///
	Ui::CFemtoMonitorcenterClass ui;
	///Create main windows pointer
	QTabWidget*  pQMainTabWidget;
	QWidget* pQMainWidget;
	QGridLayout* pQMainGridLayout;
	QTextEdit* pQMainTextEdit;
	QTableWidget* pQTableWidgetManageWidgets;
	CThreadQtextbrowser* pCThreadQtextbrowser;
	///
	///main windows action 
	QAction *pQActionOpenFileDialog;
	QAction *pQActionOpenHighlighterDialog;
	QAction *pQActionOpenLogFileDialog;
	QStatusBar *pQStatusBarMainWindows;
	QMenu *pQMenuMainwindows;
	///
	///OpenFileDialog Widget 
	QPushButton *pQPushButtonOpenFileCancel;
	QPushButton *pQPushButttonOpenFileConfirm;
	QPushButton *pQPushButtonOpenFilePath;
	QComboBox *pQTextEditOpenFilePath;
	QLabel *pQLabelOpenFilePath;
	QDialog *pDialogOpenFile;
	QGridLayout *pGridLayoutOpenFileDialog;

	///
	///Highlighting childDialog widgets
	QDialog* pQDialogHighlighter;
	QGridLayout* pQgridLayoutHighlighterDialog;
	QComboBox* pQComboBoxHighlighterDialogStr;
	QLabel* pQLabelSampleStr;
	QPushButton* pQOpenColorDialog;
	QPushButton* pQHighlighterDialogConfirm;
	QPushButton* pQHighlighterDialogCancel;
	QColor  *pQColorSelected;                           ///<record the Color selected
	///
	///Create WriteFileDialog widgets
	QDialog *pWriteDialog;
	QGridLayout *pWriteGridLayout;
	QComboBox *pQWriteDialogFileDirectory;
	
	QLineEdit *pQWriteDialogEdit;
	QCheckBox *pQWriteDialogFileAddCheckBox;
	QLineEdit *pQWriteDialogFileAdd;
	QCheckBox *pQWriteDialogFileSuffixCheckBox;
	QLineEdit *pQWriteDialogFileSuffix;
	QPushButton *pQWriteDialogFileButton;
	QPushButton *pQWriteDialogConfirmButton;
	QPushButton *pQWriteDialogCancelButton;
	///Automatic Log Dialog
	QGroupBox* pQGroupBoxAutomaticLog;
	QGridLayout* pQGridlayoutAutomaticLog;
	QGroupBox* pQGroupBoxLogTime;
	QVBoxLayout* pQVBoxLayoutRadioButton;
	QRadioButton* pQRadioButtonOnce;
	QRadioButton* pQRadioButtonDay;
	QRadioButton* pQRadioButtonWeekly;
	QGroupBox* pQGroupBoxDataTime;
	QVBoxLayout* pQVBoxLayoutDataTime;
	QDateTimeEdit* pQDateTimeEditStart;
	QDateTimeEdit* pQDateTimeEditEnd;
	///function to create the 
	QGroupBox* CreatepCombinationWindows();

	///function 

	///function to create main window GUI
	void CreateMainWindowsGUI();
	///main windows  an aggregate function that connectuser requirements and slots
	void FunctionConnectMainWindowsRequirementSlot();
	void AddMainMenuAction();
	///
	void CreateOpenFileChildWindows();
	void CreateHighlightingWindows();
	void CreateWriteFileWindow();
	///function to creaete manage thread object 
	void StartManageThread();
signals:
	///tips for user
	void EmitQmessageInformation(QString QSInformation);
	///Open Serious Port in GUI request
	void emitOpenSeriousPortGUI(QString EmitOpenFilePath);
	///eimt close qwidgets request
	void emitCloseCurrentQtextbrowserGUI(int indexGUI);
	///emit the log data FILE pointer

	void emitLogDataFile(QString LogDataindex, char* fpLogDataFile);
	///stop Log

	void  emitStopLogGUI(int IndexStopLog);
public slots:
    ///
    /// main windows slot 
	void On_TabWidget_CloseButton(int index);
	void On_pQActionOpenFileDialog_triggered();
	void On_pQActionOpenHighlighterDialog_triggered();
	void On_pQActionOpenLogFileDialog_triggered();
	void On_pQTableWidgets_RightButton(const QPoint*);
	///
	///child window slots 
	void On_OpenFileChildDialogSelectFile_Clicked();
	void On_pQPushButttonOpenFileConfirm_Clicked();
	void On_pQPushButtonOpenFileCancel_Clicked();
	///
	///highlighter dialog slots 
	void On_pQHighlighterDialogConfirm_Triggered();
	void On_pQHighlighterDialogCancel_Triggered();
	void On_pQOpenColorDialog_Triggered();
	///LOG windows slots
	void On_pQWriteDialogFileButton_clicked();
	void On_pQWriteDialogConfirmButton_clicked();
	void On_pQWriteDialogCancelButton_clicked();
	void On_pQWriteDialogFileAddCheckBox_StateChange(int stats);
	void On_pQWriteDialogFileSuffixCheckBox_StateChange(int stats);

	///SLOT to qmessage to show user information 
	void QMessageBoxFailure(QString QSInformation);

	///
	///managethread slots
	void On_CreateGUIQTextbrowserManagethread_Triggered(QString Tabtitle);
	///append data to FUI (from managethread)
	void On_AppendDataManagethread_Triggered(int NumberWindowManage, char* pAppendDataPointerManage);
	///refresh the data speed in manage windows 
	void On_EmitRefreshReceivingRateManage_Triggered();
	///
	void On_emitCloseQtextbrowserRecordManage_triggered(int index);   
	///user requset stop log
	void On_emitStopLogTextbrowser_Request();
};
