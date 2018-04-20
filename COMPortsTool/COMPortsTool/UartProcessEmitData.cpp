#include "QThreadTextBrowser.h"


CUartProcessEmitData::CUartProcessEmitData(CQThreadTextBrowser* UartCorTextBrowser)
{
	CUartCorTextBrowser = UartCorTextBrowser;
}


CUartProcessEmitData::~CUartProcessEmitData()
{
	free(pEmitData);
}
int CUartProcessEmitData::QuickRead(char * pDataBuffer, unsigned int * pDataSizeInBuffer)
{
	int CycleTime = *pDataSizeInBuffer >> 7;
	CycleTime++;
	char *pReadDataBuffer = pDataBuffer;
	while (CycleTime)
	{
		memcpy(pEmitData, pReadDataBuffer, 128);
		pEmitData[128] = '\0';
		pReadDataBuffer += 128;
		emit CUartCorTextBrowser->EmitDataOutThread(pEmitData);
		CycleTime--;
	}
		return 0;
}
