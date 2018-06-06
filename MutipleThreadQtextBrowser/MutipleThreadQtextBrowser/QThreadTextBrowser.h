#pragma once

#include <QtWidgets/QMainWindow>
#include <qtextbrowser.h>
#include "QRingBuf.h"
#include <qmenu.h>
#include <qaction.h>
#include <qcolor.h>
#include <Windows.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qgridlayout.h>
#include <qdialog.h>
#include <qdebug.h>
#include "StrProcessingThread.h"

class CMutipleThreadQtextBrowser;
class CQThreadTextBrowser :
	public QTextBrowser
{
	Q_OBJECT
public:
	CQThreadTextBrowser(CMutipleThreadQtextBrowser *parent);
	~CQThreadTextBrowser();
	///
	void InputCorFile(QString QCorFileName);
	///
	void StartReadData();
	/// ring buf to get data
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
	///incoming pointer
	CMutipleThreadQtextBrowser *pCMitipleThreadQtextBrowser;
	QString TextbrowserCorQstring;
	/// receive data thread (textbrowser correspond a thread )
	CStrProcessingThread  *CStrProcessingDataThread;

	FILE*  fpWriteFile;
	char  OpenFilePath[370];
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
	QAction *pThreadTextBrowserDeleteHighlihgting;
	
	///Create Clear Higlighting Dialog Widget
	QDialog *pQDialogClearHighlighting;
	QGridLayout *pQGridLayoutDialogClearHighlighting;
	QComboBox *pQComboBoxShowStr;
	QLabel   *pQLabelExampleColor;
	QPushButton *pPushButtonClearHighlightingComfirm;
	QPushButton *pPushButtonClearHighlightingCancel;

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
	///Create the Dialog And Clear the Highlighting 
	void On_pThreadTextBrowserDeleteHighlihgting_Triggered();
	///change the Clear the Highlighting  dialog Color
	void On_currentIndexChanged_pQComboBoxShowStr(int index);
	///slots to Delete the Highlighting
	void On_pPushButtonClearHighlightingComfirm_Triggered();
	void On_pPushButtonClearHighlightingCancel_Triggered();
	///append the data to textbrowser
	void AppendDataTextbrowser(char* pReadData);
};
