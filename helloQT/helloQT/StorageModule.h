/********************************************//**
Storage input string  module
*-
@file    StorageInputStr.h
@author  YHF
@data  2018/2/27
@brief  Input character and storage to memeory
******************************************************/
#ifndef __STORAGE_MODULE__
#define __STORAGE_MODULE__
///
///define the fixed length 
#ifndef __READ_SIZE__
#define __READ_SIZE__
#define READ_SIZE 128
#endif

int JudgeMemory(char* pJudgeMemory);
char MallocAndCopy(char** pMallocMemory, char *pOriginData, int CopyLength);
FILE* ReadCompleteLine(char **pGetLine, int* pMemoryLength, FILE* fpReadFile);

#endif