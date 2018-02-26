/********************************************//**
              InputCharacterStorage module
*-
@file InputCharStorage.cpp
@author  YHF
@data  2018/2/25
@brief  Input character and storage to memeory
******************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "InputCharStorage.h"
#include "CommandLineInput.h"
#include "MatchCharacterModule.h"
#include "storageFileMode.h"
///
///define fixed length 
#ifndef _READ_SIZE_
#define  READ_SIZE 128
#endif


void  JudgeMemory(char* pJudgeMemory)
{
   if (pJudgeMemory ==NULL)
   {
	   printf("No enough stroage,Memory allocate failed;\npress any key to exit");
	   getchar();
	   getchar();
	   exit(EXIT_FAILURE);
   }
}
/****************************************************//**
@brief  storage input char
@param  pInputComleteLine [out] relloc memory until end the line 
        pFunctionReadlength  [out] record the length of thid function read
		pMemoryTotalLength    [out] record the total length of memory
@author  YHF
@data   2018/2/25
@
********************************************************/
char* ArrayLengthToDynamicMenmory(char* pOriginArray,int Length)
{
	char* pArrayBuf = (char*)malloc(sizeof(char)*Length);
	JudgeMemory(pArrayBuf);
	strncpy(pArrayBuf,pOriginArray,Length);
	pOriginArray = pArrayBuf;
	return pOriginArray;
}


/****************************************************//**
@brief  storage input char
@param  pInputComleteLine [out] relloc memory until end the line 
        pFunctionReadlength  [out] record the length of thid function read
		pMemoryTotalLength    [out] record the total length of memory
@author  YHF
@data   2018/2/25
@
********************************************************/
int RecordInputCharBuf (char* pInputCompleteLine,int* pFunctionReadLength,int* pMemoryTotalLength)
{
	char pEachRead[READ_SIZE];
	(*pMemoryTotalLength) += (READ_SIZE-1);                ///<the total length of the allocate dynamic memory
	*pFunctionReadLength = 0;              ///<the length of each actual read(does not contain unfill character)
	int NumLoopRead = 1;               ///record the numble of cycyle
	///read fixed length character form input strea
	pInputCompleteLine = (char*)realloc(pInputCompleteLine,sizeof(char)*(*pMemoryTotalLength));
	JudgeMemory(pInputCompleteLine);
	pInputCompleteLine[(*pMemoryTotalLength)-2] = '\n';
	fgets(pInputCompleteLine,READ_SIZE,stdin);
	///judge the last one character whether be cover
	///allocate new length to pAllChar rach time
	while(pInputCompleteLine[(*pMemoryTotalLength)-2] != '\n')
	{
		(*pMemoryTotalLength) += (READ_SIZE-1); 
		pInputCompleteLine = (char*)realloc(pInputCompleteLine,sizeof(char)*(*pMemoryTotalLength));
		JudgeMemory(pInputCompleteLine);
		pInputCompleteLine[(*pMemoryTotalLength)-2] = '\n';
		fgets(pInputCompleteLine,READ_SIZE,stdin);
		NumLoopRead++;
	}
	/// 
	///
	
	*pFunctionReadLength = strlen(pInputCompleteLine+(*pMemoryTotalLength)-NumLoopRead*(READ_SIZE-1))-1;
	return 0;
}