#ifndef CPACKAGEINPUT_H
#define CPACKAGEINPUT_H

#include <QtWidgets/QMainWindow>
#include "ui_cpackageinput.h"
#include "DialogMatch.h"
#include <Windows.h>
#include "HighLighterStr.h"

///
///define the length to storage the package data
#ifndef __PACKAGE_LENGTH__
#define __PACKAGE_LENGTH__
#define PACKAGE_LENGTH  1024*64
#endif // !__PACKE_LENGTH__

///
///define the length to stack fgets the line data
#ifndef __READ_SIZE__
#define __READ_SIZE__
#define READ_SIZE  512
#endif // !__READ-SIZE__


#ifndef __RETURN_TYPE__
#define __RETURN_TYPE__


#endif

class CPackageInput : public QMainWindow
{
	Q_OBJECT

public:
	CPackageInput(QWidget *parent = 0);
	~CPackageInput();
	CDialogMatch *pCDialogMatch;
	int MatchStrOriginFile(char* pMatchStr,char* pInputOriginFile);
	void ChangeQStringChar();
	void TextEditCommand();

	CHighLighterStr *pHighlighterStr;

	struct SHighLightingRule
	{
		QRegExp Qpattern;
		QTextCharFormat QFormat;
	};
	QVector<SHighLightingRule>  QVSHighLightingRule;
	QTextCharFormat  QKeyStrFormat;

	HANDLE hMutexTextBrowser;
private:

	Ui::CPackageInputClass ui;
	QLineEdit *pStorageWriteFile;
protected:
	virtual bool eventFilter(QObject *pObj, QEvent* pE);
	
private slots:
	void ShowDialogMatch();
	void ConfirmBtn();
	void On_TextBrowser_TextChange();
	void On_ActionWriteInFile_Triggered();
};

#endif // CPACKAGEINPUT_H
