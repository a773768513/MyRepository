#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QbarsetChartModule.h"
#include "BarWidgetsModule.h"


class QbarsetChartModule : public QMainWindow
{
	Q_OBJECT

public:
	QbarsetChartModule(QWidget *parent = Q_NULLPTR);
	
private:
	Ui::QbarsetChartModuleClass ui;
	CBarWidgetsModule *pCBarWidget ;
	/// main GUI


	void InputDataToChart();
	
	
};
