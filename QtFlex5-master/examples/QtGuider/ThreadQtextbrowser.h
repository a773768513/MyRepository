#pragma once
#include <qtextbrowser.h>
#include <qvector.h>
#include <qmenu.h>
#include <QAction>
#include <qtextcursor.h>
#include "QRingBuf.h"
class CThreadQtextbrowser :
	public QTextBrowser
{
	Q_OBJECT
public:
	CThreadQtextbrowser(QWidget *parent);
	~CThreadQtextbrowser();
	void CThreadQtextbrowserLogStates(bool LogStates);
	void AppendDataTextbrowser(char* pReadData);
	///addhighlighterrule and highlighter exsit document
	void AddHighlightingRule(QString  QSCurrentHighlightingStrTextbrowser,QColor* pQColorSelectedTextbrowser);
	void HighlightingTextBrowser();
	void setTextBrowserTitle(QString InputTextBrowserTitle);
private:
	bool BLogStates;
	QString TextBrowserTitle;
	/// create the right menu in this class
	QMenu  *pThreadTextBrowserRightMenu;
	QAction *pTextBrowserMenuActionContinueData;
	QAction *pTextBrowserMenuActionCopy;
	QAction *pHighlighterTextBrowserSelect;
	QAction *pCancelHighlightrTextBrowser;
	QAction *pThreadTextBrowserStopWriteData;
	QAction *pThreadTextBrowserDeleteHighlihgting;
	
	///
	QTextDocument *pThidQThreadTextbrowserDocument;
	///ring buf
	QRingBuf *pQRingBuf;

	///record the highterule in this qtextbrowser
	struct HighlighterStrColor
	{
		QRegExp QRegExpHighlighterStr;
		QTextCharFormat QtextCharFormatColor;
	};
	QVector<HighlighterStrColor>   QVectorHighligingRule;
	///bool to judge show data 
	bool bCacheMode;
	///intital function 
	void  ConnectQtextbrowserSlot();
	void  IntitalQtextBrowser();
	///highlighing function 
	void OutputRingBufData();
protected:
	virtual void focusInEvent(QFocusEvent *e);

	virtual void focusOutEvent(QFocusEvent *e);
signals:
	void emitRingBufDataToTextbrowser(char* pBufData);
	///to signal to GUI close the log
	void emitStopLogTextbrowser();
	void emitFocuseInTextbrowser(QString ThisTextBrowserTitle);


	public slots:
	void On_this_CustomContextMenuRequesred(const QPoint &Qpoint);
	void  HighlighingStrAppendStr(char* pHighlightReadData);

	///right button slots function 
	void On_pTextBrowserMenuActionContinueData_Triggered();
	///slot to signal to GUI close the log 
	void On_pThreadTextBrowserStopWriteData_Triggered();
};

