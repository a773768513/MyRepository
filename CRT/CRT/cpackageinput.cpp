#include "cpackageinput.h"
#include "MatchStrModule.h"
#include <process.h>
#include <Windows.h>
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qevent.h>
#include <assert.h>
#include "HighLighterStr.h"
bool  BStartWriteFile = 0;
CPackageInput::CPackageInput(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	pCDialogMatch = new CDialogMatch();
	///
	///storage the Write INfile (hide)
	pStorageWriteFile = new QLineEdit;
	///connect the confirm button and the function of confirmBtn
	///connect the btn of matchSTR and dialog
	connect(pCDialogMatch->pQPBConfirm, SIGNAL(clicked()), this, SLOT(ConfirmBtn()));
	connect(ui.actionMatchStr, SIGNAL(triggered()), this, SLOT(ShowDialogMatch()));
	///
	///fixed the cursuor in the bottom
	connect(ui.textBrowser, SIGNAL(textChanged()), this, SLOT(On_TextBrowser_TextChange()));
	///
	///
	connect(ui.actionWriteInFile, SIGNAL(triggered()), this, SLOT(On_ActionWriteInFile_Triggered()));
	///
	///
	ui.textEdit->installEventFilter(this);
	///
	//
	hMutexTextBrowser = CreateMutex(NULL, FALSE, NULL);
	////
	///
	///pHighlighterStr = new CHighLighterStr(ui.textBrowser->document());
	///pHighlighterStr->addnewRegExp(pCDialogMatch->pQCBMatchStr->currentText());

}

CPackageInput::~CPackageInput()
{

}
/**************************************************************
@brief     show the dialog
@param
@retval    void
@author YHF
@data    2018/3/14
@design:

*****************************************************************/
void CPackageInput::ShowDialogMatch()
{
	if (pCDialogMatch->isHidden())
	{
		pCDialogMatch->show();
	}
	else
	{
		pCDialogMatch->hide();
	}
}
/**************************************************************
@brief     the execute the function to match str
@param
@retval    void
@author YHF
@data    2018/3/14
@design:

*****************************************************************/
void CPackageInput::ConfirmBtn()
{
	///start a thread (processes matching character in the background
	///function to execute the match str
	HANDLE ThreadHandle = (HANDLE)_beginthreadex(NULL, READ_SIZE * 2, StartMatchStrThread, this, NULL, NULL);
	if (NULL == ThreadHandle)
	{
		QMessageBoxFailure("Failed to start multithreading");
	}
	
}
void  CPackageInput::On_TextBrowser_TextChange()
{
	WaitForSingleObject(hMutexTextBrowser, INFINITE);
	/**********************
	ui.textBrowser->moveCursor(QTextCursor::Start);
	QTextCursor  pQTCTextBrowserDocu(ui.textBrowser->document());
	QTextDocument  *document;
	QTextCharFormat  QTFHighlighting;
	QTFHighlighting.setForeground(Qt::red);
	QTextCursor   mycursor = ui.textBrowser->textCursor();
	pQTCTextBrowserDocu = ui.textBrowser->document()->find(pCDialogMatch->pQCBMatchStr->currentText(), mycursor, QTextDocument::FindCaseSensitively);
	pQTCTextBrowserDocu.setCharFormat(QTFHighlighting);
	
	*///
	ui.textBrowser->moveCursor(QTextCursor::End);	
	ReleaseMutex(hMutexTextBrowser);
}
/**************************************************************
@brief    
@param
@retval    void
@author YHF
@data    2018/3/14
@design:

*****************************************************************/
void  CPackageInput::On_ActionWriteInFile_Triggered()
{
	QString QSWriteFile = QFileDialog::getOpenFileName(NULL, "OpenFile", ".", NULL);
	if (QSWriteFile != NULL)
	{
		this->pStorageWriteFile->setText(QSWriteFile);
		if (BStartWriteFile = !BStartWriteFile)
		{
			ui.actionWriteInFile->setText("stop");
		}
		else
		{
			ui.actionWriteInFile->setText("WriteInFile");
		}
	}
}
/**************************************************************
@brief   rewrite the virtual function change the return press to emit signal and shift+return to 
@param
@retval    void
@author YHF
@data    2018/3/14
@design:

*****************************************************************/
bool CPackageInput::eventFilter(QObject* pObj, QEvent* pE)
{
	if (pObj == ui.textEdit)
	{
		if (pE->type() == QEvent::KeyPress)
		{
			QKeyEvent *pTextEditKeyPress = static_cast<QKeyEvent*>(pE);
			if ((pTextEditKeyPress->key() == Qt::Key_Return) && (pTextEditKeyPress->modifiers() == Qt::ShiftModifier))
			{
				ui.textEdit->insertPlainText("\r\n");
				return true;
			}
			if (pTextEditKeyPress->key() == Qt::Key_Return)
			{
				this->TextEditCommand();
				return true;
			}
		}
		return false;
	}
}
/**************************************************************
@brief   rewrite the virtual function change the return press to emit signal and shift+return to
@param
@retval    void
@author YHF
@data    2018/3/14
@design:

*****************************************************************/
void CPackageInput::TextEditCommand()
{
	QString pQSTextEditBuf = ui.textEdit->toPlainText();
	WaitForSingleObject(hMutexTextBrowser, INFINITE);
	ui.textBrowser->append(pQSTextEditBuf);
	ReleaseMutex(hMutexTextBrowser);
	ui.textEdit->clear();
}



///

