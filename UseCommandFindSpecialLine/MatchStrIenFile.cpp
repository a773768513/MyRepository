/****************************//**
          Match String module
@file  MatchStrInFile.cpp
@author YHF
@data  2018/2/27
@brief
*****************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "MatchStrlenFile.h"
#include "StorageModule.h"
#include "CommandLineInputMain.h"
/************************************************************//**
@brief     Judge file whther success open;
@param     * fpFile[IN]  pointer file
@param     *pFile  [IN]  file name
@retval    0  success
@author YHF
@data    2018/2/25
@design:
judge whether the fpFile id NULL
*****************************************************************/
int  JudgeOpenFile(FILE* fpFile,char* pFile)
{
	if(NULL == fpFile)
	{
		printf("无法打开文件%128s!\n",pFile);
		getchar();
		exit(EXIT_FAILURE);
	}
	return 0 ;
}
/****************************************************//**
@brief  Judge the allocate memory sucess
@param  pInputStr        [IN] storage the input string
@param  InputStrLength   [IN] storage the input string length
@param  pInputFile       [IN] storage input file to find special line
@param  pWriteFile       [IN] storage output file to write in data
@author  YHF
@data   2018/2/25
@
********************************************************/
int MatchStrInFile(char* pInputStr,const int InputStrLength,char* pInputFile,char* pWriteFile)
{
	FILE *fpReadFile;          ///<file pointer to open read file 
	FILE *fpWriteFile;         ///<file pointer to open write in file 

	char pGetLine[READ_SIZE];                 ///<stack memory if the Line is short
	char* pGetLineConvers;                    ///<untie the pointer name if user heap memory
	int LineMemoryLength = READ_SIZE;         ///<pGetLineConvers occupied memory

	fpReadFile = fopen(pInputFile,"rb");
	JudgeOpenFile(fpReadFile,pInputFile);
	fpWriteFile = fopen(pWriteFile,"a");
	JudgeOpenFile(fpWriteFile,pWriteFile);
	while(!feof(fpReadFile))
	{
		LineMemoryLength = READ_SIZE;

		///reset the last position to judge whether cover
		///
		pGetLine[READ_SIZE-2] = '\0';
		fgets(pGetLine,READ_SIZE,fpReadFile);
		if(pGetLine[READ_SIZE-2] != '\0')
		{
			if(pGetLine[READ_SIZE-2] != '\n')
			{
				MallocAndCopy(&pGetLineConvers,pGetLine,READ_SIZE);
				fpReadFile = ReadCompleteLine(pGetLineConvers,&LineMemoryLength,fpReadFile);
			}
		}
		else
		{
			pGetLineConvers = pGetLine;
		}
		if(LineMemoryLength > InputStrLength)
		{
			if(!strncmp(pGetLineConvers,pInputStr,InputStrLength))
			{
				fprintf(fpWriteFile,"%s",pGetLineConvers);
			}
		}
		if(LineMemoryLength != READ_SIZE)
		{
			free(pGetLineConvers);
		}
	}
	return 0;
}