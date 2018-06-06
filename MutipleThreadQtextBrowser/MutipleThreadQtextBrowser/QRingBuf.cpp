#include "QRingBuf.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
QRingBuf::QRingBuf()
{
	prbBegin = (char*)malloc(sizeof(char)*RING_BUF_LENGTH*1000);
	if (NULL == prbBegin)
	{
		return;
	}
	prbHead = prbBegin;
	prbTail = prbBegin;
	prbAfterTail = prbBegin + RING_BUF_LENGTH * 1000;
}


QRingBuf::~QRingBuf()
{
	free(prbBegin);
}
char*  QRingBuf::NextDataHandle(char* prbJudgeBoundary)
{
	prbJudgeBoundary = prbJudgeBoundary + RING_BUF_LENGTH;
	if (prbJudgeBoundary == prbAfterTail)
	{
		return prbBegin;
	}
	else
	{
		return prbJudgeBoundary;
	}
}
char* QRingBuf::ReadOneLineRingBufReadData(char* pReadOneLineRingBuf)
{
	if (prbHead != prbTail)
	{
		strncpy(pReadOneLineRingBuf, prbHead, RING_BUF_LENGTH);
		prbHead = NextDataHandle(prbHead);
		return pReadOneLineRingBuf;
	}
	else
	{
		return NULL;
	}
}
void QRingBuf::RingBufWriteData(char* pInputData)
{
	if ((prbTail + RING_BUF_LENGTH) != prbHead)
	{
		if ((prbTail + RING_BUF_LENGTH) != prbAfterTail)
		{
			strncpy(prbTail, pInputData, RING_BUF_LENGTH);
			prbTail = NextDataHandle(prbTail);
		}
		else
		{
			prbHead = NextDataHandle(prbHead);
			strncpy(prbTail, pInputData, RING_BUF_LENGTH);
			prbTail = NextDataHandle(prbTail);
		}
	}
	else
	{
		prbHead = NextDataHandle(prbHead);
		strncpy(prbTail, pInputData, RING_BUF_LENGTH);
		prbTail = NextDataHandle(prbTail);
	}
}