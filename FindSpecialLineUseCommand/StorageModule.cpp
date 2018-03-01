/********************************************//**
             Storage input string  module
*-
@file    StorageInputStr.cpp
@author  YHF
@data  2018/2/27
@brief  Input character and storage to memeory
******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MatchStrlenFile.h"
#include "StorageModule.h"
#include "CommandLineInputMain.h"

/****************************************************//**
@brief  Judge the allocate memory sucess
@param  char* pJudgeMemory [IN] Judge this pointer
@author  YHF
@data   2018/2/25
@
********************************************************/
int  JudgeMemory(char* pJudgeMemory)
{
   if (pJudgeMemory ==NULL)
   {
	   printf("No enough stroage,Memory allocate failed;\npress any key to exit");
	   getchar();
	   getchar();
	   exit(EXIT_FAILURE);
   }
   return 0;
}
/****************************************************//**
@brief  allocate memory for pMallocMemory and copy data from pOriginData
@param  pMallocMemory       [out] dynamic allocate memory for this pointer
@param  pMemoryLength       [out] copy this pointer data to dynamic memory
@param  fpReadFile          [out] file pointer 
@author  YHF
@data   2018/2/25
@
********************************************************/
char MallocAndCopy(char** pMallocMemory,char *pOriginData,int CopyLength)
{
	CopyLength = READ_SIZE;
	*pMallocMemory = (char*)malloc(sizeof(char)*READ_SIZE);
	JudgeMemory(*pMallocMemory);
	strncpy(*pMallocMemory,pOriginData,READ_SIZE);
	return 0;
}
/****************************************************//**
@brief  read a complete line 
@param  pGetLine            [out] storage the complete line 
@param  pMemoryLength       [out] record the length of the allocate memory length 
@param  fpReadFile          [out] file pointer 
@author  YHF
@data   2018/2/25
@
********************************************************/
FILE* ReadCompleteLine(char *pGetLine,int* pMemoryLength,FILE* fpReadFile)
{
	do
	{
		if(pGetLine[(*pMemoryLength)-2] == '\n')
		{
			break;
		}
		*pMemoryLength += (READ_SIZE-1);
		pGetLine = (char*)realloc(pGetLine,sizeof(char)*(*pMemoryLength));
		JudgeMemory(pGetLine);
		pGetLine[(*pMemoryLength)-2] = '\0';
		fgets(pGetLine+*pMemoryLength-READ_SIZE,READ_SIZE,fpReadFile);
	}while(pGetLine[(*pMemoryLength)-2] != '\0');
	return fpReadFile;
}