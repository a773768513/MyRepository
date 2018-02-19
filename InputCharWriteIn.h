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
///
///marco defines a fixed length
#ifndef  __READ_SIZE__
#define   READ_SIZE 128  
#endif

///
///function declaration
void JudgeMemory(char* pJudgeMemory);
int MultipleIdentiHead(char ***pMatch,unsigned int** pInputCharLength,int &NumberMarks);
int OutputSpecialLineToFile(char **pMatch,const unsigned int*const InputCharLength,const int &NumberMarks);
#endif

