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
@brief  Judge the match result if the length of string less than READ_SIZE
@param  pInputStr        [IN] storage the input string
@param  InputStrLength   [IN] storage the input string length
@param  pInputFile       [IN] storage input file to find special line
@param  pWriteFile       [IN] storage output file to write in data
@param  pStandardFile    [IN] storage output fie to standard file 
@author  YHF
@data   2018/2/25
@
********************************************************/
int MatchLessLengthStrInFile(char* pInputStr,const int InputStrLength,char* pInputFile,char* pWriteFile,char* pStandardFile)
{
	FILE *fpReadFile;          ///<file pointer to open read file 
	FILE *fpWriteFile;         ///<file pointer to open write in file 
	FILE *fpStandardFile;

	char pGetLine[READ_SIZE];                 ///<stack memory if the Line is short
	int LineMemoryLength = READ_SIZE;         ///<pGetLineConvers occupied memory
	char LineOfStandard[READ_SIZE];

	int StandardLength = 0;
	int WriteFileLength = 0 ;

	char  StandardCompare[READ_SIZE];
	char  WriteFileCompare[READ_SIZE];
	int   ReadTimes = 0;

	fpReadFile = fopen(pInputFile,"r");
	JudgeOpenFile(fpReadFile,pInputFile);
	fpWriteFile = fopen(pWriteFile,"w+");
	JudgeOpenFile(fpWriteFile,pWriteFile);

	while(!feof(fpReadFile))
	{
		
		///reset the last position to judge whether cover
		///reset the string character to judge whether longer than string
		pGetLine[InputStrLength] = '\0';
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
		
			
		if(pGetLine[InputStrLength-1] == pInputStr[InputStrLength-1])
		{
			if(!strncmp(pGetLine,pInputStr,InputStrLength))
			{
				///read a comlete line if not finish
				///
				while(pGetLine[READ_SIZE-2] != '\0')
				{
					if(pGetLine[READ_SIZE-2] == '\n')
					{
						break;
					}
					fprintf(fpWriteFile,"%s",pGetLine);
					pGetLine[READ_SIZE-2] = '\0';
					fgets(pGetLine,READ_SIZE,fpReadFile);
					printf("1");
				}
				fprintf(fpWriteFile,"%s",pGetLine);
			}
		}
		while(pGetLine[READ_SIZE-2] != '\0')
		{
			if(pGetLine[READ_SIZE-2] == '\n')
			{
				break;
			}
			pGetLine[READ_SIZE-2] = '\0';
			fgets(pGetLine,READ_SIZE,fpReadFile);
		}
	}
	///judge the answer if exit the standard file
	///
	if(pStandardFile  != NULL)
	{
		
		fpStandardFile = fopen(pStandardFile,"r");
		JudgeOpenFile(fpStandardFile,pStandardFile);
		StandardLength  = JudgefpLength(fpStandardFile);
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
		fclose(fpStandardFile);
	}
	fclose(fpReadFile);
	fclose(fpWriteFile);
	return 0;
}
/****************************************************//**
@brief  Judge the match result if the length of string more than READ_SIZE
@param  pInputStr        [IN] storage the input string
@param  InputStrLength   [IN] storage the input string length
@param  pInputFile       [IN] storage input file to find special line
@param  pWriteFile       [IN] storage output file to write in data
@param  pStandardFile    [IN] storage output fie to standard file 
@author  YHF
@data   2018/2/25
@
********************************************************/
int MatchMoreLengthStrInFile(char* pInputStr,const int InputStrLength,char* pInputFile,char* pWriteFile,char* pStandardFile)
{
	FILE *fpReadFile;          ///<file pointer to open read file 
	FILE *fpWriteFile;         ///<file pointer to open write in file 
	FILE *fpStandardFile;

	///if the match character long the READ_SIZE(128)2^7
	///add 1 to fgets function add\0 automatically
	int MallocMemoryLength = (InputStrLength+1) >> 7;
	MallocMemoryLength++;
	char* pGetLine;                       ///< the pointer name if user heap memory
	int LineMemoryLength = (READ_SIZE*MallocMemoryLength);                 ///<compare the length of write in and standard
	char LineOfStandard[READ_SIZE];
	
	int StandardLength (0);
	int WriteFileLength (0);
	char  StandardCompare[READ_SIZE];
	char  WriteFileCompare[READ_SIZE];
	int   ReadTimes(0);

	pGetLine = (char*)malloc(sizeof(char)*LineMemoryLength);

	fpReadFile = fopen(pInputFile,"r");
	JudgeOpenFile(fpReadFile,pInputFile);
	fpWriteFile = fopen(pWriteFile,"w+");
	JudgeOpenFile(fpWriteFile,pWriteFile);

	while(!feof(fpReadFile))
	{
		///reset the last position to judge whether cover
		///
		pGetLine[LineMemoryLength-2] = '\0';
		///
		///Judge whether finished the file 
		if(NULL == fgets(pGetLine,LineMemoryLength,fpReadFile))
		{
			if(feof(fpReadFile))
			{
				break;
			}
			printf("读取行数据失败");
			getchar();
			exit(EXIT_FAILURE);
		}
		
		if(pGetLine[InputStrLength-1] == pInputStr[InputStrLength-1])
		{
			if(!strncmp(pGetLine,pInputStr,InputStrLength))
			{
				///read a comlete line if not finish
				///
				fprintf(fpWriteFile,"%s",pGetLine);
				while(pGetLine[LineMemoryLength-2] != '\0')
				{					
					if(pGetLine[LineMemoryLength-2] == '\n')
					{
						break;
					}
					fprintf(fpWriteFile,"%s",pGetLine);
					pGetLine[LineMemoryLength-2] = '\0';
					pGetLine[InputStrLength-1] = '\0';
					fgets(pGetLine,READ_SIZE,fpReadFile);
					printf("2");
				}
				
			}
		}
		while(pGetLine[LineMemoryLength-2] != '\0')
		{
			if(pGetLine[LineMemoryLength-2] == '\n')
			{
				break;
			}
			pGetLine[LineMemoryLength-2] = '\0';
			fgets(pGetLine,LineMemoryLength,fpReadFile);
		}
	}
	///judge the answer if exit the standard file
	///
	if(pStandardFile  != NULL)
	{
		fpStandardFile = fopen(pStandardFile,"r");
		JudgeOpenFile(fpStandardFile,pStandardFile);
		StandardLength  = JudgefpLength(fpStandardFile);
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
		fclose(fpStandardFile);
	}
	fclose(fpReadFile);
	fclose(fpWriteFile);
	return 0;
}