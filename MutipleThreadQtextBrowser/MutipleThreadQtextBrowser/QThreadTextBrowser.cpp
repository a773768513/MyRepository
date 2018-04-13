#include "QThreadTextBrowser.h"
#include"CMutipleThreadQtextBrowser.h"
#include <qclipboard.h>
#include <qcolor.h>
#include "AssertModule.h"
CQThreadTextBrowser::CQThreadTextBrowser(QWidget *parent)
   : QTextBrowser(parent)
{
	CreatethisRightMouseButtonMenu();
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
}

CQThreadTextBrowser::~CQThreadTextBrowser()
{
	if (fpWriteFile != NULL)
	{
		fclose(fpWriteFile);
	}
	DeleteCriticalSection(&JudgeWriteDataCRITICAL_SECTION);
	delete  pQRingBuf;

	delete pTextBrowserMenuActionContinueData;
	delete pThreadTextBrowserStopWriteData;
	delete pTextBrowserMenuActionCopy;
	delete pHighlighterTextBrowserSelect;
	delete pCancelHighlightrTextBrowser;
	delete pThreadTextBrowserRightMenu;
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
	char  *pBufLineData = (char*)malloc(sizeof(char)*RING_BUF_LENGTH);    /// malloc memory to storge the data in ring buf 
	pBufLineData = this->pQRingBuf->ReadOneLineRingBufReadData(pBufLineData);    ///read a line in ring buf 
	this->moveCursor(QTextCursor::End);
	On_pCancelHighlightrTextBrowser_Triggered();
	while (NULL != pBufLineData)
	{
		this->moveCursor(QTextCursor::End);
		QString QSLineData = pBufLineData;
		this->insertPlainText(QSLineData);
		this->moveCursor(QTextCursor::End);
		///highlighting the last line (new add line )
		HighlignhtingLastStr();
		pBufLineData = this->pQRingBuf->ReadOneLineRingBufReadData(pBufLineData);   ///cycle read a line until the ringbuf is emrty
	}
	delete pBufLineData;
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
	///
	pThreadTextBrowserRightMenu->addAction(pTextBrowserMenuActionContinueData);
	pThreadTextBrowserRightMenu->addSeparator();
	pThreadTextBrowserRightMenu->addAction(pTextBrowserMenuActionCopy);
	pThreadTextBrowserRightMenu->addSeparator();
	pThreadTextBrowserRightMenu->addAction(pHighlighterTextBrowserSelect);
	pThreadTextBrowserRightMenu->addAction(pCancelHighlightrTextBrowser);
	pThreadTextBrowserRightMenu->addSeparator();
	pThreadTextBrowserRightMenu->addAction(pThreadTextBrowserStopWriteData);
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
	}
	QVectorHighligingRule.append(HighlighterNewRule);
	delete pAddColor;
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