#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CMutipleThreadQtextBrowser.h"
#include <qgridlayout.h>
#include <qtextedit.h>
#include "QThreadTextBrowser.h"
#include <qtabwidget.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qdialog.h>
#include <qcombobox.h>
#include <qcolor.h>
#include "ManageThreadObject.h"

class CMutipleThreadQtextBrowser : public QMainWindow
{
	Q_OBJECT

public:
	CMutipleThreadQtextBrowser(QWidget *parent = Q_NULLPTR);
	~CMutipleThreadQtextBrowser();
	///Manage thread object (move to thread )
	CManageThreadObject ObjCManageThreadObject;
	struct ManageThreadData
	{
		QString OpenFilePath;
		char* DataToManageThread;
	};
private:
	
	QThread ManageThread;
	///struct to accept the data in thread;
	struct AppendDataCorrespond
	{
		char* LineData;
		CQThreadTextBrowser*  ThreadCorrespondTextbrowser;
	};
	Ui::CMutipleThreadQtextBrowserClass ui;
	///new thread point 
	///main windows 
	QTabWidget*  pQMainTabWidget;
	QWidget* pQMainWidget ;
	QGridLayout* pQMainGridLayout ;
	QTextEdit* pQMainTextEdit;
	CQThreadTextBrowser*  pCQThreadTextBrowser;

	///
	/// main windows action 
	QAction *pQOpenFileDialogAction;
	QAction *pQOpenHighlighterDialogAction;
	QAction *pQOpenWriteFileDialogAction;
	QStatusBar *pQMainStatusBar;
	QMenu *pQMainMenu;
	
	///
	///OpenFileDialog Widget 
	QPushButton *pQPushButtonOpenFileCancel ;
	QPushButton *pQPushButttonOpenFileConfirm ;
	QPushButton *pQPushButtonOpenFilePath ;
	QLineEdit *pQTextEditOpenFilePath ;
	QLabel *pQLabelOpenFilePath ;
	QDialog *pDialogOpenFile ;
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
	QLineEdit *pQWriteDialogEdit;
	QPushButton *pQWriteDialogFileButton;
	QPushButton *pQWriteDialogConfirmButton ;
	QPushButton *pQWriteDialogCancelButton;

	///init the project
	void initProject();
	///set main windows function 
	void SetMainWindows();
	///set main windows action function 
	void AddMainMenuAction();
	/// create child window (in ChildWindowsAncorSlot.cpp)
	void CreateOpenFileChildWindows();
	void CreateHighlightingWindows();
	void CreateWriteFileWindow();

signals:
	void  SignalcreateTextbrowser(QString TabTitle);

	void  SignalManageThreadCloseTab(int CloseTabIndex);
public slots:
	void SlotCreateTextbrowser(QString TabTitle);
private slots:
    /// main Menu Action to Open Child Windows(in ChildWindowsAncorSlot.cpp)
	void On_pQOpenFileDialogAction_Triggered();
	void On_pQOpenHighlighterDialogAction_Triggered();
	void On_pQOpenWriteFileDialogAction_Triggered();

	///OpenFileChildDialog Open Slots(in ChildWindowsAncorSlot.cpp)
	void On_OpenFileChildDialogSelectFile_Clicked();
	void On_pQPushButttonOpenFileConfirm_Clicked();
	void On_pQPushButtonOpenFileCancel_Clicked();

	///OpenHiglighting ChildDialog slots(s(in ChildWindowsAncorSlot.cpp)
	void On_pQOpenColorDialog_Triggered();
	void On_pQHighlighterDialogConfirm_Triggered();
	void On_pQHighlighterDialogCancel_Triggered();

	///open WriteFile ChildeDialog Slots(in ChildWindowsAncorSlot.cpp)
	void On_pQWriteDialogFileButton_clicked();
	void On_pQWriteDialogConfirmButton_clicked();
	void On_pQWriteDialogCancelButton_clicked();
	///slot to change the manage thread dialog speed EmitSignal(QVector<int>*
	void On_ManageThread_speed(QVector<int>* RecordDataSpeedPara);
	///close tab current index slot (emit to manage thread and close )
	void On_TabWidget_CloseButton(int CloseTabIndex);
	void On_ManageThread_CloseCOM(int CloseTabIndex);
	///
	void On_SiganlManage_CreateRightMenu();
	///slot of right buuton action
	void On_DeleteRowAction_Triggered();
};
