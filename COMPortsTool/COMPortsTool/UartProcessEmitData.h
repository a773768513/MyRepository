#pragma once
#include "UartProcess.h"
#include "QThreadTextBrowser.h"

class  CQThreadTextBrowser;
#ifndef  __ONE_READ_LENGTH__
#define  __ONE_READ_LENGTH__
#define ONE_READ_LENGTH  1024*8
#endif

class CUartProcessEmitData :
	public CUartProcess
{

public:
	CUartProcessEmitData(CQThreadTextBrowser* UartCorTextBrowser);
	~CUartProcessEmitData();
protected:
	virtual int QuickRead(char * pDataBuffer, unsigned int * pDataSizeInBuffer);
private:
	CQThreadTextBrowser* CUartCorTextBrowser;
	char  *pEmitData = (char*)malloc(sizeof(char)*ONE_READ_LENGTH);

};

