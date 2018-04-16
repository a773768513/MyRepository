#include "CMutipleThreadQtextBrowser.h"
#include <qfiledialog.h>
#include <qcolordialog.h>
#include <qmessagebox.h>
#include "AssertModule.h"
void CMutipleThreadQtextBrowser::On_pQOpenFileDialogAction_Triggered()
{
	CreateOpenFileChildWindows();
}
void CMutipleThreadQtextBrowser::On_pQOpenHighlighterDialogAction_Triggered()
{
	CreateHighlightingWindows();
}
void CMutipleThreadQtextBrowser::On_pQOpenWriteFileDialogAction_Triggered()
{
	CreateWriteFileWindow();
}
void CMutipleThreadQtextBrowser::CreateOpenFileChildWindows()
{
	pDialogOpenFile = new QDialog;
	pDialogOpenFile->setAttribute(Qt::WA_DeleteOnClose, true);
	pGridLayoutOpenFileDialog = new QGridLayout(pDialogOpenFile);
	////pGridLayoutOpenFileDialog->setSizeConstraint(QLayout::SetFixedSize);  ///fixed dialog (for hide the pQWidgetDetail but no change the widget relative position
	pGridLayoutOpenFileDialog->setSpacing(20);
	pGridLayoutOpenFileDialog->setMargin(20);
	///
	pQLabelOpenFilePath = new QLabel(pDialogOpenFile);
	pQLabelOpenFilePath->setText("OpenFilePath");
	pGridLayoutOpenFileDialog->addWidget(pQLabelOpenFilePath, 0, 0, 1, 1);

	///line edit to input the opwn file path
	pQTextEditOpenFilePath = new  QLineEdit(pDialogOpenFile);
	pGridLayoutOpenFileDialog->addWidget(pQTextEditOpenFilePath, 0, 1, 1, 2);

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
	connect(pQPushButttonOpenFileConfirm, SIGNAL(clicked()), this, SLOT(On_pQPushButttonOpenFileConfirm_Clicked()));
	connect(pQPushButtonOpenFileCancel, SIGNAL(clicked()), this, SLOT(On_pQPushButtonOpenFileCancel_Clicked()));

	pGridLayoutOpenFileDialog->setColumnStretch(0, 0);
	pGridLayoutOpenFileDialog->setColumnStretch(1, 1);
	pGridLayoutOpenFileDialog->setColumnStretch(2, 1);
	pDialogOpenFile->exec();
}
void CMutipleThreadQtextBrowser::CreateHighlightingWindows()
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
void CMutipleThreadQtextBrowser::CreateWriteFileWindow()
{
	///dialog and gridlayout 
	pWriteDialog = new QDialog;
	pWriteDialog->resize(QSize(280, 150));
	pWriteDialog->setAttribute(Qt::WA_DeleteOnClose, true);
	pWriteGridLayout = new QGridLayout(pWriteDialog);
	pWriteGridLayout->setMargin(20);
	pWriteGridLayout->setSpacing(15);
	pQWriteDialogEdit = new QLineEdit(pWriteDialog);
	///add  linedit  and open file button
	pWriteGridLayout->addWidget(pQWriteDialogEdit, 0, 0, 1, 2);
	pQWriteDialogFileButton = new QPushButton(pWriteDialog);
	pQWriteDialogFileButton->setText("OpenFile");
	pWriteGridLayout->addWidget(pQWriteDialogFileButton, 0, 2, 1, 1);
	connect(pQWriteDialogFileButton, SIGNAL(clicked()), this, SLOT(On_pQWriteDialogFileButton_clicked()));
	/// add  confirm button and cancel button
	pQWriteDialogConfirmButton = new QPushButton(pWriteDialog);
	pQWriteDialogConfirmButton->setText("Confirm");
	pWriteGridLayout->addWidget(pQWriteDialogConfirmButton, 1, 1, 1, 1);
	pQWriteDialogCancelButton = new QPushButton(pWriteDialog);
	pQWriteDialogCancelButton->setText("Cancel");
	pWriteGridLayout->addWidget(pQWriteDialogCancelButton, 1, 2, 1, 1);
	///write data to file dialog 
	connect(pQWriteDialogConfirmButton, SIGNAL(clicked()), this, SLOT(On_pQWriteDialogConfirmButton_clicked()));
	connect(pQWriteDialogCancelButton, SIGNAL(clicked()), this, SLOT(On_pQWriteDialogCancelButton_clicked()));
	pWriteDialog->exec();
}
void CMutipleThreadQtextBrowser::On_OpenFileChildDialogSelectFile_Clicked()
{
	QString QSOpenFile = QFileDialog::getOpenFileName(NULL, "OpenFile", ".", NULL);
	this->pQTextEditOpenFilePath->setText(QSOpenFile);
}
void CMutipleThreadQtextBrowser::On_pQPushButttonOpenFileConfirm_Clicked()
{
	if (NULL == pQTextEditOpenFilePath->text())
	{
		QMessageBoxFailure("Please Input File Path");
		return;
	}
	QString  TabTitle = pQTextEditOpenFilePath->text();
	pDialogOpenFile->close();
	///set max line and warp mode 
	pCQThreadTextBrowser = new CQThreadTextBrowser;
	pQMainTabWidget->addTab(pCQThreadTextBrowser, TabTitle);
	pCQThreadTextBrowser->SetthreadPropertiesStart(TabTitle);
	///connect the signal and the widgets close event
	connect(pQMainTabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(On_tabCloseRequested_Triggered(int )));

}
void CMutipleThreadQtextBrowser::On_pQPushButtonOpenFileCancel_Clicked()
{
	this->pDialogOpenFile->close();
}
void CMutipleThreadQtextBrowser::On_pQOpenColorDialog_Triggered()
{
	*pQColorSelected = QColorDialog::getColor(Qt::black, this);
	QPalette  pa;
	pa.setColor(QPalette::WindowText, *pQColorSelected);
	pQLabelSampleStr->setPalette(pa);
}
void CMutipleThreadQtextBrowser::On_pQHighlighterDialogConfirm_Triggered()
{
	if (pQComboBoxHighlighterDialogStr->currentText() == NULL)
	{
		QMessageBoxFailure("No Input Character");
		return;
	}

	QString QSCurrentHighlightingStr = pQComboBoxHighlighterDialogStr->currentText();
	CQThreadTextBrowser  *pQTextbrowserContinue = dynamic_cast<CQThreadTextBrowser*>(pQMainTabWidget->currentWidget());
	pQDialogHighlighter->close();
	if (NULL == pQTextbrowserContinue)
	{
		QMessageBoxFailure("tranfer type failure");
		return;
	}
	pQTextbrowserContinue->AddHighlightingRule(QSCurrentHighlightingStr, pQColorSelected);
	pQTextbrowserContinue->HighlightingTextBrowser();
}
void CMutipleThreadQtextBrowser::On_pQHighlighterDialogCancel_Triggered()
{
	pQDialogHighlighter->close();
}

void CMutipleThreadQtextBrowser::On_pQWriteDialogFileButton_clicked()
{
	QString QSOpenFile = QFileDialog::getOpenFileName(NULL, "OpenFile", ".", NULL);
	this->pQWriteDialogEdit->setText(QSOpenFile);
}
void CMutipleThreadQtextBrowser::On_pQWriteDialogConfirmButton_clicked()
{
	if (NULL == pQWriteDialogEdit->text())
	{
		QMessageBoxFailure("Please Input File Path");
		return;
	}
	CQThreadTextBrowser  *pQTextbrowserContinue = dynamic_cast<CQThreadTextBrowser*>(pQMainTabWidget->currentWidget());
	QByteArray QByteArrayWriteFilePath = pQWriteDialogEdit->text().toLatin1();
	char *pWriteFilePath = QByteArrayWriteFilePath.data();
	pWriteDialog->close();
	///enter critical section
	EnterCriticalSection(&(pQTextbrowserContinue->JudgeWriteDataCRITICAL_SECTION));
	if (NULL == pQTextbrowserContinue->OpenWriteFilefpWriteFile(pWriteFilePath))
	{
		QMessageBoxFailure("Open Write File Path Faliure!");
	}
	LeaveCriticalSection(&(pQTextbrowserContinue->JudgeWriteDataCRITICAL_SECTION));
}

void CMutipleThreadQtextBrowser::On_pQWriteDialogCancelButton_clicked()
{
	pWriteDialog->close();
}

///close slot and delete this widgets
void CMutipleThreadQtextBrowser::On_tabCloseRequested_Triggered(int CurrentIndex)
{
	CQThreadTextBrowser *pStopTextBrowser = dynamic_cast<CQThreadTextBrowser*>(pQMainTabWidget->currentWidget());
	pStopTextBrowser->close();
}
