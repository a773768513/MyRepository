#ifndef HELLOQT_H
#define HELLOQT_H

#include <QtWidgets/QMainWindow>
#include "ui_helloqt.h"

class helloqt : public QMainWindow
{
	Q_OBJECT

public:
	helloqt(QWidget *parent = 0);
	~helloqt();
	char* QStringToChar(QString QSOriginStr,char**StrArray);
	void  InputUIDataMatch();
	void  ProgressBarRun();
private:
	Ui::helloqtClass ui;
private slots:
   void Btn_OpenClick();
   void Btn_MatchClick();
};
#endif // HELLOQT_H
