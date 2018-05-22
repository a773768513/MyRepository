#include "QbarsetChartModule.h"

QbarsetChartModule::QbarsetChartModule(QWidget *parent)
	: QMainWindow(parent)
{
	InputDataToChart();
	this->setCentralWidget(pCBarWidget);
}

void QbarsetChartModule::InputDataToChart()
{
	pCBarWidget = new  CBarWidgetsModule();
	int i = 5;
	char setname[12] = "LPS";
	double *pdoudata = (double*)malloc(sizeof(double)* 5);
	pdoudata[0] = 2.143;
	pdoudata[1] = 2.143;
	pdoudata[2] = 3.143;
	pdoudata[3] = 4.143;
	pdoudata[4] = 5.143;
	pdoudata[5] = 6.143;
	pCBarWidget->EnterSetData(setname, pdoudata, i);
	pCBarWidget->EnterSetData("LPS2", pdoudata, i);
	
	char *pXName = (char*)malloc(sizeof(char)* 1024);
	memset(pXName, 0, 1024);
	strcpy(pXName, "s");
	strcpy(pXName+128, "s2");
	strcpy(pXName + 128*2, "s3");
	strcpy(pXName + 128 * 3, "s4");
	strcpy(pXName + 128 * 4, "s5");
	strcpy(pXName + 128 * 5, "s6");
	pCBarWidget->EnterSetXName(pXName);
	
	pCBarWidget->DataMapping();

}