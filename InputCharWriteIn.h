/**************************************************//**
			Training  Module
*-
@file InputCharWriteIn.h
@author YHF
@data 2018/1/31
@package try to package

**********************************************/
#ifndef __INPUTCHARWRITEIN_H_
#define __INPUTCHARWRITEIN_H_
///function declaration

void JudgeMemory(char* pJudgeMemory);
int RecordInputCharBuf(char**pAllChar,int &TotalLength);
int OutputSpecialLineToFile(char *pMatch,const int &InputLength);
#endif

