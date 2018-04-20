#pragma once

#include <QtWidgets/QMainWindow>
#include <qtextbrowser.h>
#include "QRingBuf.h"
<<<<<<< HEAD:COMPortsTool/COMPortsTool/QThreadTextBrowser.h
#include "UartProcessEmitData.h"
=======
#include "StrProcessingThread.h"
>>>>>>> 350336f8453755b0c8b8623fc0df203f4a273589:MutipleThreadQtextBrowser/MutipleThreadQtextBrowser/QThreadTextBrowser.h
#include <qmenu.h>
#include <qaction.h>
#include <qcolor.h>
#include <Windows.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qgridlayout.h>
#include <qdialog.h>
class CQThreadTextBrowser :
	public QTextBrowser
{
	Q_OBJECT
public:
	CQThreadTextBrowser(QWidget *parent = Q_NULLPTR);
	~CQThreadTextBrowser();
	void  HighlightingAndAsertTextBrowser(char* pLineData);
	void  AddHighlightingRule(QString pAddRegExp, QColor* pAddColor);
	void  HighlightingTextBrowser();
	///fp ponit function 
	FILE* GetTextBrowserCorFile();
	BOOL  OpenWriteFilefpWriteFile(char* pWriteFilePath);
	void  ResetfpWriteFile();
	///add Critical section to protect the fpwritefile;
	CRITICAL_SECTION  JudgeWriteDataCRITICAL_SECTION;
<<<<<<< HEAD:COMPortsTool/COMPortsTool/QThreadTextBrowser.h
	/// initial the  and connect 
	void StartPortsConnect(const TCHAR * ptcUartName, unsigned int BaudRate = 460800);
private:
	CUartProcessEmitData* TextBrowserCorUartProcess;
	///create the ring buf to storage data
	char  pBufLineData[RING_BUF_LENGTH];    /// malloc memory to storge the data in ring buf 
=======
	///set thread start 
	void  SetthreadPropertiesStart(QString  QSOpenFilePath);
private:
	/// start and stop the thread
	CStrProcessingThread *pQthreadCoTextBrowser;
	///create the ring buf to storage data
>>>>>>> 350336f8453755b0c8b8623fc0df203f4a273589:MutipleThreadQtextBrowser/MutipleThreadQtextBrowser/QThreadTextBrowser.h
	QRingBuf *pQRingBuf;
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
	///write data in this text browser
	void AppendDataTextBrowser(char* pAppendDataCorespond);
<<<<<<< HEAD:COMPortsTool/COMPortsTool/QThreadTextBrowser.h
signals:
	///emit the data 
	void EmitDataOutThread(char* EmitData);
=======
>>>>>>> 350336f8453755b0c8b8623fc0df203f4a273589:MutipleThreadQtextBrowser/MutipleThreadQtextBrowser/QThreadTextBrowser.h
};

