/**************************************************//**
			Training  Module
*-
@file function.h
@author YHF
@data 2018/1/31
@package try to package

**********************************************/
#ifndef __INPUTCHARWRITEIN_H_
#define __INPUTCHARWRITEIN_H_
///function declaration

void JudgeMemory(char* pJudgeMemory);
int ReadBuf(char**pAllChar,int &TotalLength);
int OutputFile(char *pMatch,const int &InputLength);
#endif

