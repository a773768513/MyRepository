#pragma once
#include <qdialog.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qgridlayout.h>
#include <qlineedit.h>
#include <qcombobox.h>
class CDialogMatch :
	public QDialog
{
	Q_OBJECT

public:
	CDialogMatch(QWidget* parent=0);
	~CDialogMatch();
	///
	///return the information of the dialog
public:
	///
	///this widget uesed in the mainwindow
	QComboBox *pQCBconnectStyle;
	QLineEdit   *pQLEInputOtiginFile;
	QComboBox  *pQCBMatchStr;
	QPushButton *pQPBConfirm;
private:
	///
	///connect style
	QLabel    *pQLConnectStyle;

	///
	/// the widget of input origin file 
	QLabel      *pQLInputOriginFile;
	QPushButton *pQPBInputOriginFile;

	///XIA
	///the widget of the input match string(using combo box)
	QLabel     *pQLMatchStr;
	

	///
	///control button
	
	QPushButton *pQPBCancel;
	QGridLayout *pQGLDialogLayout;
	///
	///slots function
private slots:
	void  OpenDialogFile();
	void  ConfirmBtn();
	void  CancelBtn();
};

