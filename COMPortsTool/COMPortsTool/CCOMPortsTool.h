#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CCOMPortsTool.h"
#include <qlayout.h>
#include <qtextedit.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qlabel.h>
#include "QThreadTextBrowser.h"

class CCOMPortsTool : public QMainWindow
{
	Q_OBJECT

public:
	CCOMPortsTool(QWidget *parent = Q_NULLPTR);
	~CCOMPortsTool();
private:
	///
	///Create WriteFileDialog widgets
	QDialog *pWriteDialog;
	QGridLayout *pWriteGridLayout;
	QLineEdit *pQWriteDialogEdit;
	QPushButton *pQWriteDialogFileButton;
	QPushButton *pQWriteDialogConfirmButton;
	QPushButton *pQWriteDialogCancelButton;

	Ui::CCOMPortsToolClass ui;
	///main windows 
	QTabWidget*  pQMainTabWidget;
	QWidget* pQMainWidget;
	QGridLayout* pQMainGridLayout;
	QTextEdit* pQMainTextEdit;
	///
	/// main windows action 
	QAction *pQConnectDialogAction;
	QAction *pQOpenHighlighterDialogAction;
	QAction *pQOpenWriteFileDialogAction;
	QStatusBar *pQMainStatusBar;
	QMenu *pQMainMenu;

	/// storage the connect COM ports 
	TCHAR          m_PortList[32 * 50];
	unsigned int   m_ComCount;
	///
	///ConnectDialog Widget 
	QPushButton *pQPushButtonOpenFileCancel;
	QPushButton *pQPushButttonOpenFileConfirm;
	QComboBox *pQCOMPortsList;
	QLabel *pQLabelConnectChildTitle;
	QDialog *pDialogOpenFile;
	QGridLayout *pGridLayoutOpenFileDialog;

	/// main windows set 
	void SetMainWindows();
	void AddMainMenuAction();

	///connect child windows
	void CreateConnectChildWindows();
	/// get all useable  connect 
	void FillPortListComboBox();
	///Open logFile dialog 
	void CreateWriteFileWindow();
public slots:
    ///connect dialog slots
	void On_pConnectDialogAction_Triggered();
	void On_pQConnectOpenFileConfirm_Clicked();
	void On_pQConnectOpenFileCancel_Clicked();

	///close the tabwidgets
	void On_tabCloseRequested_Triggered(int CurrentIndex);
	////
	///Open The WriteFileDialogAction
	void On_pQOpenWriteFileDialogAction_Triggered();
	void On_pQWriteDialogFileButton_clicked();
	void On_pQWriteDialogConfirmButton_clicked();
	void On_pQWriteDialogCancelButton_clicked();

};
