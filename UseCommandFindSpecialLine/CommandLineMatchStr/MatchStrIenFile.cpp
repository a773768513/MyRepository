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
	return 0;
}
/****************************************************//**
@brief  judge the length of fp
@param  fp  File pointer
@retval length   
@author  YHF
@data   2018/2/25
@
********************************************************/
int JudgefpLength(FILE* fp)
{
	int length;
	fseek(fp,0L,SEEK_END);
	length =  ftell(fp);
	fseek(fp,0L,SEEK_SET);
	return length;
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
int MatchStrInFile(char* pInputStr,const int InputStrLength,char* pInputFile,char* pWriteFile,char* pStandardFile)
{
	FILE *fpReadFile;          ///<file pointer to open read file 
	FILE *fpWriteFile;         ///<file pointer to open write in file 
	FILE *fpStandardFile;

	char pGetLine[READ_SIZE];                 ///<stack memory if the Line is short
	char* pGetLineConvers;                    ///<untie the pointer name if user heap memory
	int LineMemoryLength = READ_SIZE;         ///<pGetLineConvers occupied memory
	char* LineOfStandard;
	LineOfStandard = (char*)malloc(sizeof(char)*READ_SIZE);
	JudgeMemory(LineOfStandard);

	int StandardLength = 0;
	int WriteFileLength = 0 ;
	char  StandardCompare[READ_SIZE];
	char  WriteFileCompare[READ_SIZE];
	int   ReadTimes = 0;

	fpReadFile = fopen(pInputFile,"r");
	JudgeOpenFile(fpReadFile,pInputFile);
	fpWriteFile = fopen(pWriteFile,"w+");
	JudgeOpenFile(fpWriteFile,pWriteFile);

	fpStandardFile = fopen(pStandardFile,"r");
	JudgeOpenFile(fpStandardFile,pStandardFile);

	while(!feof(fpReadFile))
	{
		LineMemoryLength = READ_SIZE;

		///reset the last position to judge whether cover
		///
		pGetLine[READ_SIZE-2] = '\0';
		///
		///Judge whether finished the file 
		if(NULL == fgets(pGetLine,READ_SIZE,fpReadFile))
		{
			if(feof(fpReadFile))
			{
				break;
			}
			printf("读取行数据失败");
			getchar();
			exit(EXIT_FAILURE);
		}
		if(pGetLine[READ_SIZE-2] != '\0')
		{
			if(pGetLine[READ_SIZE-2] != '\n')
			{
				///chang the stack memory to heap memory and copy the data in
				///read the complete line
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
	StandardLength = JudgefpLength(fpStandardFile);
	WriteFileLength = JudgefpLength(fpWriteFile);
	
	if(StandardLength != WriteFileLength)
	{
		printf("diffent lenth");

	}
	while((ReadTimes*(READ_SIZE-1))<StandardLength)
	{
		fgets(StandardCompare,READ_SIZE,fpStandardFile);
		fgets(WriteFileCompare,READ_SIZE,fpWriteFile);
		if(memcmp(StandardCompare,WriteFileCompare,READ_SIZE))
		{
			printf("program failure");
			exit(EXIT_FAILURE);
		}
		ReadTimes++;
	}
	fclose(fpReadFile);
	fclose(fpWriteFile);
	return 0;
}