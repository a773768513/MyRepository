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

	void AppendDataTextbrowser(char* pReadData);
	///addhighlighterrule and highlighter exsit document
	void AddHighlightingRule(QString  QSCurrentHighlightingStrTextbrowser,QColor* pQColorSelectedTextbrowser);
	void HighlightingTextBrowser();
private:
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
signals:
	void emitRingBufDataToTextbrowser(char* pBufData);
	public slots:
	void On_this_CustomContextMenuRequesred(const QPoint &Qpoint);
	void  HighlighingStrAppendStr(char* pHighlightReadData);

	///right button slots function 
	void On_pTextBrowserMenuActionContinueData_Triggered();


};

