#pragma once
#include "qwidget.h"
#include <QtWidgets/QApplication>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <qdialog.h>
#include <qgridlayout.h>
QT_CHARTS_USE_NAMESPACE

#ifndef __SET_X_NAME__
#define SET_X_NAME 128
#endif


class CBarWidgetsModule :
	public QWidget
{
public:
	CBarWidgetsModule();
	~CBarWidgetsModule();

	void EnterSetData(char* SetDataName, double*  pdouSetData, int datalength);
	void EnterSetXName(char *pSetXName);
	void SetChartTitle(char *ChartTitle);
	void DataMapping();
private:
	///add a serious data and create a set of  entity
	QBarSet *pQbarSet;
	char  BarSetName[64];
	
	///append all barset in ;
	QChart *pQChart = new QChart();
	QBarSeries *pBarSeries = new  QBarSeries();
	
	QChartView *pQChartView = new QChartView(pQChart);
	QGridLayout* pQGriLayout = new QGridLayout();

	///X Name log 
	QBarCategoryAxis *pBarAxisX = new QBarCategoryAxis();;
	int XDataLength = 0;
	///init the chart 
	void InitChart();
};

