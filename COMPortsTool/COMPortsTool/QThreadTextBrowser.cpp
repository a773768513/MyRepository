#include "QThreadTextBrowser.h"
#include <qclipboard.h>
#include <qcolor.h>
#include "AssertModule.h"
#include <qapplication.h>
CQThreadTextBrowser::CQThreadTextBrowser(QWidget *parent)
   : QTextBrowser(parent)
{
	CreatethisRightMouseButtonMenu();
	TextBrowserCorUartProcess = new CUartProcessEmitData(this);
	connect(this, SIGNAL(EmitDataOutThread(char*)), this, SLOT(AppendDataTextBrowser(char*)),Qt::BlockingQueuedConnection);
	pQRingBuf = new QRingBuf;
	/// set max line number
	this->document()->setMaximumBlockCount(100000);
	///set the wrap mode 
	this->setLineWrapMode(QTextEdit::NoWrap);
	fpWriteFile = NULL;
	///intitial bCacheMode;
	bCacheMode = false;
	///set the right button action 
	this->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(On_this_CustomContextMenuRequesred(const QPoint &)));
	///connect the action and the function 
	InitializeCriticalSectionAndSpinCount(&JudgeWriteDataCRITICAL_SECTION, 4000);
	this->setAttribute(Qt::WA_DeleteOnClose,true);
}
CQThreadTextBrowser::~CQThreadTextBrowser()
{
	TextBrowserCorUartProcess->m_bForceStop = true;
	WaitForSingleObject(TextBrowserCorUartProcess->m_ThreadEndFlag, INFINITE);
	TextBrowserCorUartProcess->CloseConnection();
	delete TextBrowserCorUartProcess;
	if (fpWriteFile != NULL)
	{
		fclose(fpWriteFile);
	}
	DeleteCriticalSection(&JudgeWriteDataCRITICAL_SECTION);
	delete  pQRingBuf;
	delete pThreadTextBrowserDeleteHighlihgting;
	delete pTextBrowserMenuActionContinueData;
	delete pThreadTextBrowserStopWriteData;
	delete pTextBrowserMenuActionCopy;
	delete pHighlighterTextBrowserSelect;
	delete pCancelHighlightrTextBrowser;
	delete pThreadTextBrowserRightMenu;
	///close the thread if thread is run;
	
}


void CQThreadTextBrowser::AppendDataTextBrowser(char* pAppendDataCorespond)
{
	this->HighlightingAndAsertTextBrowser(pAppendDataCorespond);
}

void  CQThreadTextBrowser::HighlightingTextBrowser()
{
	QTextDocument *pHighlighterDocument = this->document();
	QTextCursor QTextCursorTextStart(pHighlighterDocument);
	QTextCursor QTextCursorFind(pHighlighterDocument);
	QTextCursorTextStart.movePosition(QTextCursor::Start);
	for each (HighlighterStrColor EveryHighlightingRule in QVectorHighligingRule)
	{
		QTextCursorFind = QTextCursorTextStart;
		while (!QTextCursorFind.isNull())
		{
			if (QTextCursorFind.atEnd())
			{
				break;
			}
			QTextCursorFind = pHighlighterDocument->find(EveryHighlightingRule.QRegExpHighlighterStr, QTextCursorFind, QTextDocument::FindCaseSensitively);
			QTextCursorFind.mergeCharFormat(EveryHighlightingRule.QtextCharFormatColor);
		}
	}
}
void  CQThreadTextBrowser::HighlightingAndAsertTextBrowser(char* pLineData)
{
	if (false == bCacheMode)
	{
		QString QSLineData = pLineData;
		///move cursor and insert data to button 
		this->moveCursor(QTextCursor::End);
		this->insertPlainText(QSLineData);
		this->moveCursor(QTextCursor::End);
		this->moveCursor(QTextCursor::StartOfLine);
		///highlighting the last
		HighlignhtingLastStr();
	}
	else
	{
		this->pQRingBuf->RingBufWriteData( pLineData);
	}
}

void CQThreadTextBrowser::HighlignhtingLastStr()
{
	QTextDocument *pHighlighterDocument = this->document();
	QTextCursor QTextCursorFind(pHighlighterDocument);
	QTextCursor QTextCursorStartFind(pHighlighterDocument);
	///move Cursor to Match last  line
	QTextCursorStartFind.movePosition(QTextCursor::End);
	QTextCursorStartFind.movePosition(QTextCursor::StartOfLine);
	QTextCursorStartFind.movePosition(QTextCursor::Up);
	QTextCursorStartFind.movePosition(QTextCursor::Up);
	///
	///match each role in Vector
	for each (const HighlighterStrColor EveryHighlighterRule in QVectorHighligingRule)
	{
		QTextCursorFind = QTextCursorStartFind;
		while (!QTextCursorFind.isNull())
		{
			if (QTextCursorFind.atEnd())
			{
				break;
			}
			///find regexp and highlighting the str
			QTextCursorFind = pHighlighterDocument->find(EveryHighlighterRule.QRegExpHighlighterStr, QTextCursorFind, QTextDocument::FindCaseSensitively);
			QTextCursorFind.mergeCharFormat(EveryHighlighterRule.QtextCharFormatColor);
		}
	}
}
void CQThreadTextBrowser::OutputRingBufData()
{
	char  *JudgeNULL;
	JudgeNULL = this->pQRingBuf->ReadOneLineRingBufReadData(pBufLineData);    ///read a line in ring buf 

	while (NULL != JudgeNULL)
	{
		this->moveCursor(QTextCursor::End);
		QString QSLineData = pBufLineData;
		this->insertPlainText(QSLineData);
		this->moveCursor(QTextCursor::End);
		///highlighting the last line (new add line )
		HighlignhtingLastStr();
		JudgeNULL = this->pQRingBuf->ReadOneLineRingBufReadData(pBufLineData);   ///cycle read a line until the ringbuf is emrty
	}
}


void CQThreadTextBrowser::On_this_CustomContextMenuRequesred(const QPoint &)
{
		pThreadTextBrowserRightMenu->exec(QCursor::pos());
}
void CQThreadTextBrowser::CreatethisRightMouseButtonMenu()
{
	///
	pThreadTextBrowserRightMenu = new QMenu;
	///Action to stop the textbrowser data input
	pTextBrowserMenuActionContinueData = new QAction;
	pTextBrowserMenuActionContinueData->setText("Stop");
	connect(pTextBrowserMenuActionContinueData, SIGNAL(triggered()), this, SLOT(On_pTextBrowserMenuActionContinueData_Triggered()));
	///copy cursor data 
	pTextBrowserMenuActionCopy = new QAction;
	pTextBrowserMenuActionCopy->setText("Copy");
	connect(pTextBrowserMenuActionCopy, SIGNAL(triggered()), this, SLOT(On_pTextBrowserMenuActionCopy_Triggered()));
	///action to highlighter the select
	pHighlighterTextBrowserSelect = new QAction;
	pHighlighterTextBrowserSelect->setText("Highlighting");
	connect(pHighlighterTextBrowserSelect, SIGNAL(triggered()), this, SLOT(On_pHighlighterTextBrowserSelect_Triggered()));
	///action to cancel highlighter the select
	pCancelHighlightrTextBrowser = new QAction;
	pCancelHighlightrTextBrowser->setText("Normal");
	connect(pCancelHighlightrTextBrowser, SIGNAL(triggered()), this, SLOT(On_pCancelHighlightrTextBrowser_Triggered()));
	///action to stop write data;
	pThreadTextBrowserStopWriteData = new QAction;
	pThreadTextBrowserStopWriteData->setText("StopRecording");
	connect(pThreadTextBrowserStopWriteData, SIGNAL(triggered()), this, SLOT(On_pThreadTextBrowserStopWriteData_Triggered()));
	///action to delete the Highlighting 
	pThreadTextBrowserDeleteHighlihgting = new QAction;
	pThreadTextBrowserDeleteHighlihgting->setText("ClearHighlighter");
	connect(pThreadTextBrowserDeleteHighlihgting, SIGNAL(triggered()), this, SLOT(On_pThreadTextBrowserDeleteHighlihgting_Triggered()));
	///
	pThreadTextBrowserRightMenu->addAction(pTextBrowserMenuActionContinueData);
	pThreadTextBrowserRightMenu->addSeparator();
	pThreadTextBrowserRightMenu->addAction(pTextBrowserMenuActionCopy);
	pThreadTextBrowserRightMenu->addSeparator();
	pThreadTextBrowserRightMenu->addAction(pHighlighterTextBrowserSelect);
	pThreadTextBrowserRightMenu->addAction(pCancelHighlightrTextBrowser);
	pThreadTextBrowserRightMenu->addSeparator();
	pThreadTextBrowserRightMenu->addAction(pThreadTextBrowserStopWriteData);
	pThreadTextBrowserRightMenu->addSeparator();
	pThreadTextBrowserRightMenu->addAction(pThreadTextBrowserDeleteHighlihgting);
}

void CQThreadTextBrowser::On_pTextBrowserMenuActionContinueData_Triggered()
{
	if (false == bCacheMode)
	{
		bCacheMode = true;
		pTextBrowserMenuActionContinueData->setText("Continue");
	}
	else
	{
		bCacheMode = false;
		pTextBrowserMenuActionContinueData->setText("Stop");
		OutputRingBufData();
	}
}
void CQThreadTextBrowser::On_pHighlighterTextBrowserSelect_Triggered()
{
	QTextDocument *pHighlighterDocument = this->document();
	QTextCursor pQMainTextBrowserCursor(pHighlighterDocument);
	///get current cursor
	pQMainTextBrowserCursor = this->textCursor();
	QTextCharFormat pQMainTextBrowserSelectHighlighter;
	pQMainTextBrowserSelectHighlighter.setForeground(Qt::red);
	pQMainTextBrowserCursor.mergeCharFormat(pQMainTextBrowserSelectHighlighter);
}
void CQThreadTextBrowser::On_pCancelHighlightrTextBrowser_Triggered()
{
	QTextDocument *pHighlighterDocument = this->document();
	QTextCursor pQMainTextBrowserCursor(pHighlighterDocument);
	///get current cursor
	pQMainTextBrowserCursor = this->textCursor();
	QTextCharFormat pQMainTextBrowserSelectHighlighter;
	pQMainTextBrowserSelectHighlighter.setForeground(Qt::black);
	pQMainTextBrowserCursor.mergeCharFormat(pQMainTextBrowserSelectHighlighter);
}

void CQThreadTextBrowser::On_pTextBrowserMenuActionCopy_Triggered()
{
	QClipboard *clipboard = QApplication::clipboard();   
	QTextDocument *pHighlighterDocument = this->document();
	QTextCursor pQMainTextBrowserCursor(pHighlighterDocument);
	///get current cursor
	pQMainTextBrowserCursor = this->textCursor();
	QString QSCopyData = pQMainTextBrowserCursor.selectedText();
	clipboard->setText(QSCopyData);
}
void CQThreadTextBrowser::On_pThreadTextBrowserStopWriteData_Triggered()
{
	
	EnterCriticalSection(&(this->JudgeWriteDataCRITICAL_SECTION));
	if (NULL != fpWriteFile)
	{
		fclose(fpWriteFile);
		fpWriteFile = NULL;
		QMessageBoxFailure("Already Stop Data Saving!");
	}
	LeaveCriticalSection(&(this->JudgeWriteDataCRITICAL_SECTION));
}

void CQThreadTextBrowser::On_pThreadTextBrowserDeleteHighlihgting_Triggered()
{
	///create the dialog and set the attribute 
	pQDialogClearHighlighting = new QDialog;
	pQDialogClearHighlighting->setAttribute(Qt::WA_DeleteOnClose, true);
	///new a layout 
	pQGridLayoutDialogClearHighlighting = new QGridLayout(pQDialogClearHighlighting);
	QString HighlightingStr;
	pQComboBoxShowStr = new QComboBox(pQDialogClearHighlighting);
	pQComboBoxShowStr->addItem("");
	for each (HighlighterStrColor HiglightingStr in QVectorHighligingRule)
	{
		HighlightingStr = HiglightingStr.QRegExpHighlighterStr.pattern();
		pQComboBoxShowStr->addItem(HighlightingStr);
	}
	connect(pQComboBoxShowStr, SIGNAL(currentIndexChanged(int )), this, SLOT(On_currentIndexChanged_pQComboBoxShowStr(int)));
	pQLabelExampleColor = new QLabel(pQDialogClearHighlighting);
	pQLabelExampleColor->setText("Example");
	///Confirm and Cancel Button
	pPushButtonClearHighlightingComfirm = new QPushButton(pQDialogClearHighlighting);
	pPushButtonClearHighlightingComfirm->setText("Confirm");
	connect(pPushButtonClearHighlightingComfirm, SIGNAL(clicked()), this, SLOT(On_pPushButtonClearHighlightingComfirm_Triggered()));
	pPushButtonClearHighlightingCancel = new QPushButton(pQDialogClearHighlighting);
	pPushButtonClearHighlightingCancel->setText("Cancel");
	connect(pPushButtonClearHighlightingCancel, SIGNAL(clicked()), this, SLOT(On_pPushButtonClearHighlightingCancel_Triggered()));
	///set dialog widget
	pQGridLayoutDialogClearHighlighting->addWidget(pQComboBoxShowStr, 0, 0, 1, 2);
	pQGridLayoutDialogClearHighlighting->addWidget(pQLabelExampleColor, 0, 2, 1, 1);
	pQGridLayoutDialogClearHighlighting->addWidget(pPushButtonClearHighlightingComfirm, 1, 1, 1, 1);
	pQGridLayoutDialogClearHighlighting->addWidget(pPushButtonClearHighlightingCancel, 1, 2, 1, 1);
	pQGridLayoutDialogClearHighlighting->setHorizontalSpacing(15);
	pQGridLayoutDialogClearHighlighting->setMargin(10);

	pQDialogClearHighlighting->exec();
}
void CQThreadTextBrowser::On_pPushButtonClearHighlightingComfirm_Triggered()
{
	int  CurrentIndex = (pQComboBoxShowStr->currentIndex() -1);
	QVectorHighligingRule.removeAt(CurrentIndex);
	pQDialogClearHighlighting->close();
}
void CQThreadTextBrowser::On_pPushButtonClearHighlightingCancel_Triggered()
{
	pQDialogClearHighlighting->close();
}
void CQThreadTextBrowser::On_currentIndexChanged_pQComboBoxShowStr(int index)
{
	/*****************
	QColor  QCorrespondColor = QVectorHighligingRule.at(index-1).QtextCharFormatColor.underlineColor();
	QPalette  pa;
	pa.setColor(QPalette::WindowText, QCorrespondColor);
	pQLabelExampleColor->setPalette(pa);
	************************/
}
void CQThreadTextBrowser::AddHighlightingRule(QString pAddRegExp,QColor* pAddColor)
{
	HighlighterStrColor  HighlighterNewRule;
	QTextCharFormat  QtextCharFormatSelect;
	QtextCharFormatSelect.setForeground(*pAddColor);
	HighlighterNewRule.QRegExpHighlighterStr = QRegExp(pAddRegExp);
	HighlighterNewRule.QtextCharFormatColor = QtextCharFormatSelect;
	bool bFindSuccess = false;
	int QVectorHighligingRuleindex = 0;
	for each (HighlighterStrColor  IndexExists in QVectorHighligingRule)
	{
		if (HighlighterNewRule.QRegExpHighlighterStr == IndexExists.QRegExpHighlighterStr)
		{
			bFindSuccess = true;
			break;
		}
		else
		{
			QVectorHighligingRuleindex++;
		}
	}
	if (true == bFindSuccess)
	{
		QVectorHighligingRule.replace(QVectorHighligingRuleindex, HighlighterNewRule);
		return;
	}
	QVectorHighligingRule.append(HighlighterNewRule);
}
FILE* CQThreadTextBrowser::GetTextBrowserCorFile()
{
	return fpWriteFile;
}
BOOL  CQThreadTextBrowser::OpenWriteFilefpWriteFile(char* pWriteFilePath)
{
	fpWriteFile = fopen(pWriteFilePath, "a+");
	if (NULL == fpWriteFile)
	{
		return false;
	}
	return true;
}
void  CQThreadTextBrowser::ResetfpWriteFile()
{
	fclose(fpWriteFile);
	fpWriteFile = NULL;
}

void CQThreadTextBrowser::StartPortsConnect(const TCHAR * ptcUartName, unsigned int BaudRate)
{
	this->TextBrowserCorUartProcess->Initial();
	this->TextBrowserCorUartProcess->Connection(ptcUartName, BaudRate);
	this->TextBrowserCorUartProcess->StartUartService();
}