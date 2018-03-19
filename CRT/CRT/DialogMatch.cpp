#include "DialogMatch.h"
#include <qfiledialog.h>
#include <qmessagebox.h>
CDialogMatch::CDialogMatch(QWidget* parent)
:QDialog(parent)
{
	setWindowTitle("InputInformation");
	pQGLDialogLayout = new QGridLayout(this);
	///
	///set the connect mode 
	pQLConnectStyle = new QLabel;
	pQLConnectStyle->setText("SelctConnectStyle");

	pQCBconnectStyle = new QComboBox;
	pQCBconnectStyle->insertItem(0, "mode1");
	pQCBconnectStyle->insertItem(1, "mode2");

	pQGLDialogLayout->addWidget(pQLConnectStyle, 0, 0);    /// setLayout
	pQGLDialogLayout->addWidget(pQCBconnectStyle, 0, 1);  

	///
	///set the attributes of the input origin file widgets
	pQLInputOriginFile = new QLabel;
	pQLInputOriginFile->setText("InputOriginFilePath");

	pQLEInputOtiginFile = new QLineEdit;

	pQPBInputOriginFile = new QPushButton;
	pQPBInputOriginFile->setText("OpenFile");

	pQGLDialogLayout->addWidget(pQLInputOriginFile, 1, 0);
	pQGLDialogLayout->addWidget(pQLEInputOtiginFile, 1, 1, 1, 2);
	pQGLDialogLayout->addWidget(pQPBInputOriginFile, 2, 2);
	///
	///set the attributes of the MatchStr
	pQLMatchStr = new QLabel;
	pQLMatchStr->setText("MatchStr");
	
	pQCBMatchStr = new QComboBox;
	pQCBMatchStr->insertItem(0, "#RANGE");
	pQCBMatchStr->setEditable(1);

	pQGLDialogLayout->addWidget(pQLMatchStr, 3, 0);
	pQGLDialogLayout->addWidget(pQCBMatchStr, 3, 1, 1, 2);
	///
	/// confrim button and cancel button
	pQPBConfirm = new QPushButton;
	pQPBConfirm->setText("Confirm");

	pQPBCancel = new QPushButton;
	pQPBCancel->setText("Cancel");

	pQGLDialogLayout->addWidget(pQPBConfirm, 4, 1);
	pQGLDialogLayout->addWidget(pQPBCancel, 4, 2);
	///
	///set Margin and space 
	pQGLDialogLayout->setSpacing(15);
	pQGLDialogLayout->setMargin(20);

	///
	///connect signal and slots
	connect(pQPBInputOriginFile, SIGNAL(clicked()), this, SLOT(OpenDialogFile()));
	connect(pQPBConfirm, SIGNAL(clicked()), this, SLOT(ConfirmBtn()));
	connect(pQPBCancel, SIGNAL(clicked()), this, SLOT(CancelBtn()));

}

void CDialogMatch::msg_test()
{
	QMessageBox msg;
	msg.exec();
}
CDialogMatch::~CDialogMatch()
{
}
/**************************************************************
@brief    select the  open file path with file dialog
@param
@retval    void
@author YHF
@data    2018/3/14
@design:

*****************************************************************/
void  CDialogMatch::OpenDialogFile()
{
	QString QSOpenFile = QFileDialog::getOpenFileName(NULL, "OpenFile", "C:\\softwareinstall", NULL);
	this->pQLEInputOtiginFile->setText(QSOpenFile);
}
/**************************************************************
@brief    confirm btn to hide the dialog (the execute in main windows)
@param
@retval    void
@author YHF
@data    2018/3/14
@design:

*****************************************************************/
void  CDialogMatch::ConfirmBtn()
{
	this->hide();
}
/**************************************************************
@brief     cancel btn to hide the dialog
@param
@retval    void
@author YHF
@data    2018/3/14
@design:

*****************************************************************/
void  CDialogMatch::CancelBtn()
{
	this->hide();
}