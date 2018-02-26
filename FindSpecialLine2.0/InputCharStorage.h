/*******************************************************//**

                storage Char module 
@file  InputCharStorage.h      
@author YHF
@data 2018/2/25
@
***********************************************************/

#ifndef __INPUT_CHAR_STORAGE__
#define __INPUT_CHAR_STORAGE__

#ifndef   __READ_SIZE__
#define     READ_SIZE 128  
#endif
char* ArrayLengthToDynamicMemory(char* pOriginArray,int Length);
void  JudgeMemory(char* pJudgeMemory);
int RecordInputCharBuf (char* pInputCompleteLine,int* pFunctionReadLength,int* pMemoryTotalLength);
#endif