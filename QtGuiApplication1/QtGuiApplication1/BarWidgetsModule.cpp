#include "BarWidgetsModule.h"


CBarWidgetsModule::CBarWidgetsModule()
{
	InitChart();
}


CBarWidgetsModule::~CBarWidgetsModule()
{
	delete pBarSeries;
	delete pQChartView;
	delete pQGriLayout;

}
void CBarWidgetsModule::InitChart()
{
	
	pQGriLayout->addWidget(pQChartView);
	this->setLayout(pQGriLayout);
	pQChartView->setRenderHint(QPainter::Antialiasing);
}

void CBarWidgetsModule::EnterSetData(char* SetDataName, double*  pdouSetData,int datalength)
{
	memcpy(BarSetName, SetDataName, 64);
	pQbarSet = new QBarSet(BarSetName);
	XDataLength = datalength;
	int addDataNum = 0;
	///add all data to barset
	while (addDataNum != datalength)
	{
		*pQbarSet << pdouSetData[addDataNum];
		addDataNum++;
	}

	pBarSeries->append(pQbarSet);
	pQbarSet = NULL;

}
void CBarWidgetsModule::EnterSetXName(char *pSetXName)
{
	int AddDATANum = 0;
	while (AddDATANum != XDataLength)
	{
		pBarAxisX->append(pSetXName);
		pSetXName += SET_X_NAME;
		AddDATANum++;
	}
}

void CBarWidgetsModule::DataMapping()
{
	pQChart->addSeries(pBarSeries);
	pQChart->createDefaultAxes();
	pQChart->setAxisX(pBarAxisX, pBarSeries);

	pQChart->setAnimationOptions(QChart::SeriesAnimations);
	pQChart->legend()->setVisible(true);
	pQChart->legend()->setAlignment(Qt::AlignBottom);
	
}
void CBarWidgetsModule::SetChartTitle(char *ChartTitle)
{

	pQChart->setTitle(ChartTitle);
}