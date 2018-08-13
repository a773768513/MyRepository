#include "ThreadQtextbrowser.h"
#include <Windows.h>
#include <qapplication.h>

CThreadQtextbrowser::CThreadQtextbrowser(QWidget *parent)
:QTextBrowser(parent)
{
	IntitalQtextBrowser();
	ConnectQtextbrowserSlot();
}


CThreadQtextbrowser::~CThreadQtextbrowser()
{
	delete pQRingBuf;
}
void  CThreadQtextbrowser::IntitalQtextBrowser()
{
	this->document()->setMaximumBlockCount(100);
	///this->setLineWrapMode(QTextEdit::NoWrap);
	this->setContextMenuPolicy(Qt::CustomContextMenu);
	bCacheMode = false;
	pThidQThreadTextbrowserDocument = this->document();
	pQRingBuf = new QRingBuf;
	BLogStates = false;
}

void  CThreadQtextbrowser::ConnectQtextbrowserSlot()
{
	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(On_this_CustomContextMenuRequesred(const QPoint &)));
	///connect(this, SIGNAL(), this, SLOT());
	void emitRingBufDataToTextbrowser(char* pBufData);
	connect(this, SIGNAL(emitRingBufDataToTextbrowser(char*)), this, SLOT(HighlighingStrAppendStr(char*)));
}

void CThreadQtextbrowser::On_this_CustomContextMenuRequesred(const QPoint &Qpoint)
{
	///
	pThreadTextBrowserRightMenu = new QMenu;
	///Action to stop the textbrowser data input
	pTextBrowserMenuActionContinueData = new QAction(pThreadTextBrowserRightMenu);
	if (bCacheMode == FALSE)
	{
		pTextBrowserMenuActionContinueData->setText("Stop");
	}
	else
	{
		pTextBrowserMenuActionContinueData->setText("continue");
	}
	connect(pTextBrowserMenuActionContinueData, SIGNAL(triggered()), this, SLOT(On_pTextBrowserMenuActionContinueData_Triggered()));
	///copy cursor data 
	pTextBrowserMenuActionCopy = new QAction(pThreadTextBrowserRightMenu);
	pTextBrowserMenuActionCopy->setText("Copy");
	connect(pTextBrowserMenuActionCopy, SIGNAL(triggered()), this, SLOT(On_pTextBrowserMenuActionCopy_Triggered()));
	///action to highlighter the select
	pHighlighterTextBrowserSelect = new QAction(pThreadTextBrowserRightMenu);
	pHighlighterTextBrowserSelect->setText("Highlighting");
	connect(pHighlighterTextBrowserSelect, SIGNAL(triggered()), this, SLOT(On_pHighlighterTextBrowserSelect_Triggered()));
	///action to cancel highlighter the select
	pCancelHighlightrTextBrowser = new QAction(pThreadTextBrowserRightMenu);
	pCancelHighlightrTextBrowser->setText("Normal");
	connect(pCancelHighlightrTextBrowser, SIGNAL(triggered()), this, SLOT(On_pCancelHighlightrTextBrowser_Triggered()));
	///action to stop write data;
	pThreadTextBrowserStopWriteData = new QAction(pThreadTextBrowserRightMenu);
	pThreadTextBrowserStopWriteData->setText("Stop Log");
	
	
	connect(pThreadTextBrowserStopWriteData, SIGNAL(triggered()), this, SLOT(On_pThreadTextBrowserStopWriteData_Triggered()));
	///action to delete the Highlighting 
	pThreadTextBrowserDeleteHighlihgting = new QAction(pThreadTextBrowserRightMenu);
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

	pThreadTextBrowserRightMenu->exec(QCursor::pos());

	delete pThreadTextBrowserRightMenu;
}

void CThreadQtextbrowser::AddHighlightingRule(QString  QSCurrentHighlightingStrTextbrowser, QColor* pQColorSelectedTextbrowser)
{
	HighlighterStrColor  HighlighterNewRule;
	QTextCharFormat  QtextCharFormatSelect;
	QtextCharFormatSelect.setForeground(*pQColorSelectedTextbrowser);
	HighlighterNewRule.QRegExpHighlighterStr = QRegExp(QSCurrentHighlightingStrTextbrowser);
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
void CThreadQtextbrowser::HighlightingTextBrowser()
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

void CThreadQtextbrowser::AppendDataTextbrowser(char* pReadData)
{
	if (false == bCacheMode)
	{
		HighlighingStrAppendStr(pReadData);
	}
	else
	{
		this->pQRingBuf->RingBufWriteData(pReadData);
	}
}

void  CThreadQtextbrowser::HighlighingStrAppendStr(char* pHighlightReadData)
{
	///this->insertPlainText(pHighlightReadData);
	/****
	QTextCursor QTextCursorFindAppend(pThidQThreadTextbrowserDocument);
	QString QSReadData = pHighlightReadData;
	///record the cursor position in last 
	this->moveCursor(QTextCursor::End);
	
	QTextCursorFindAppend = this->textCursor();
	QTextCursorFindAppend.movePosition(QTextCursor::Up);
	this->insertPlainText(QSReadData);
	for each (HighlighterStrColor EveryHighlightingRule in QVectorHighligingRule)
	{
		
		while (!QTextCursorFindAppend.isNull())
		{
			if (QTextCursorFindAppend.atEnd())
			{
				break;
			}
			QTextCursorFindAppend = pThidQThreadTextbrowserDocument->find(EveryHighlightingRule.QRegExpHighlighterStr, QTextCursorFindAppend, QTextDocument::FindCaseSensitively);
			QTextCursorFindAppend.mergeCharFormat(EveryHighlightingRule.QtextCharFormatColor);
		}
	}
	this->moveCursor(QTextCursor::End);
	*************/
}

void CThreadQtextbrowser::On_pTextBrowserMenuActionContinueData_Triggered()
{
	if (false == bCacheMode)
	{
		bCacheMode = true;
	}
	else
	{
		bCacheMode = false;
		OutputRingBufData();
	}
}

void CThreadQtextbrowser::OutputRingBufData()
{
	char  *pBufLineData = (char*)malloc(sizeof(char)*RING_BUF_LENGTH);    /// malloc memory to storge the data in ring buf 
	char  *JudgeNULL;
	JudgeNULL = this->pQRingBuf->ReadOneLineRingBufReadData(pBufLineData);    ///read a line in ring buf 

	while (NULL != JudgeNULL)
	{
		emit emitRingBufDataToTextbrowser(pBufLineData);
		JudgeNULL = this->pQRingBuf->ReadOneLineRingBufReadData(pBufLineData);   ///cycle read a line until the ringbuf is emrty
		QApplication::processEvents();
	
	}
	free(pBufLineData);
}

void CThreadQtextbrowser::CThreadQtextbrowserLogStates(bool LogStates)
{
	BLogStates = LogStates;
}

void CThreadQtextbrowser::On_pThreadTextBrowserStopWriteData_Triggered()
{
	emit emitStopLogTextbrowser();
}