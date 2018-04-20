#pragma once
#include <qtextbrowser.h>
#ifndef  __RING_BUF_LENGTH__
#define  __RING_BUF_LENGTH__
#define  RING_BUF_LENGTH   256
#endif

class QRingBuf
{
public:
	QRingBuf();
	~QRingBuf();
	
	char*  ReadOneLineRingBufReadData(char* pReadOneLineRingBuf);
	void RingBufWriteData(char* pInputData);
private:
	char* prbHead;      /// record the head of memory
	char* prbTail;      /// record the tail of memory 
	char* prbBegin;     /// record the begin of memory;
	char* prbAfterTail; /// record the after tail memory to tranfer the point to head ;

	char* NextDataHandle(char* prbJudgeBoundary);        ///

};

