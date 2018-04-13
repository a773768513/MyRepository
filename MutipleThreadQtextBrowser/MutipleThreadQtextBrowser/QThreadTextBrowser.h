#pragma once

#include <QtWidgets/QMainWindow>
#include <qtextbrowser.h>
#include "QRingBuf.h"
#include <qmenu.h>
#include <qaction.h>
#include <qcolor.h>
#include <Windows.h>
class CQThreadTextBrowser :
	public QTextBrowser
{
	Q_OBJECT
public:
	CQThreadTextBrowser(QWidget *parent = Q_NULLPTR);
	~CQThreadTextBrowser();
	

	QRingBuf *pQRingBuf;
	void  HighlightingAndAsertTextBrowser(char* pLineData);
	void  AddHighlightingRule(QString pAddRegExp, QColor* pAddColor);
	void  HighlightingTextBrowser();
	///add Critical section to protect the fpwritefile;
	CRITICAL_SECTION  JudgeWriteDataCRITICAL_SECTION;
	///fp ponit function 
	FILE* GetTextBrowserCorFile();
	BOOL  OpenWriteFilefpWriteFile(char* pWriteFilePath);
	void  ResetfpWriteFile();
private:
	FILE*  fpWriteFile;
	struct HighlighterStrColor
	{
		QRegExp QRegExpHighlighterStr;
		QTextCharFormat QtextCharFormatColor;
	};
	QVector<HighlighterStrColor>   QVectorHighligingRule;
	/// create the right menu in this class
	QMenu  *pThreadTextBrowserRightMenu;
	QAction *pTextBrowserMenuActionContinueData;
	QAction *pTextBrowserMenuActionCopy;
	QAction *pHighlighterTextBrowserSelect;
	QAction *pCancelHighlightrTextBrowser;
	QAction *pThreadTextBrowserStopWriteData;
	
	bool   bCacheMode;

	void  OutputRingBufData();
	/// create the right menu in this class(function)
	void CreatethisRightMouseButtonMenu();
	void HighlignhtingLastStr();
private slots:
	void On_this_CustomContextMenuRequesred(const QPoint &);
	void On_pTextBrowserMenuActionContinueData_Triggered();
	void On_pHighlighterTextBrowserSelect_Triggered();
	void On_pCancelHighlightrTextBrowser_Triggered();
	void On_pTextBrowserMenuActionCopy_Triggered();
	void On_pThreadTextBrowserStopWriteData_Triggered();

};

