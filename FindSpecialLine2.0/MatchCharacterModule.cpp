/********************************************//**
              Match Char  module
*-
@file MatchCharacterModule.cpp
@author  YHF
@data  2018/2/25
@brief  Match char function
******************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "InputCharStorage.h"
#include "CommandLineInput.h"
#include "MatchCharacterModule.h"
#include "storageFileMode.h"

/****************************************************//**
@brief  processing Mode 
@param  pInputComleteLine     [out] relloc memory until end the line 
        pFunctionReadlength   [out] record the length of thid function read
		pMemoryTotalLength    [out] record the total length of memory
@retval UNIFIED_OUTPUT_MODE       [1] all  result output to one file
        SEPARATE_INPUT_FILE_OUTPUT[3] corresponding input file and output file separate 
		SEPARATE_CHAR_OUTPUT      [2] corresponding char and output file separate
		exit(EXIT_FAILURE);        error
		
@author  YHF
@data   2018/2/25
@
********************************************************/
int ProcessMode(const int InputCharNum,const int ReadFileNum,const int WriteFileNum)
{
	if(InputCharNum != 1)
	{
		if(ReadFileNum != 1 )
		{
			printf("error1");
			getchar();
			exit(EXIT_FAILURE);
		}
	}
	if(WriteFileNum == 1)
	{
		return UNIFIED_OUTPUT_MODE;
	}
	if(InputCharNum == 1)
	{
		if(ReadFileNum == WriteFileNum)
		{
			return SEPARATE_INPUT_FILE_OUTPUT;
		}
		printf("error1");
		getchar();
		exit(EXIT_FAILURE);
	}
	if(ReadFileNum == 1)
	{
		if(InputCharNum == WriteFileNum)
		{
			return SEPARATE_CHAR_OUTPUT;
		}
		printf("error1");
		getchar();
		exit(EXIT_FAILURE);
	}
	return 0;
}
/************************************************************//**
@brief     Read first line of fpReadFile into  pGetLine completely
@param     **pAllLength        store input character
           **pGetLine         record a Line comletely
		   LineTotalLength    allocate memory 
@retval    0  success
@author YHF
@data    2018/2/19
@design:
judge whether the last character read whether cover
*****************************************************************/
int ReadFileFirstLine(FILE* fpReadFile,char** pGetLine,int* LineTotalLength)
{
	*LineTotalLength = READ_SIZE;                                       ///<the total of the allocate memory line length
	char* pSectLine = (char*)(sizeof(char)*READ_SIZE);           ///<read a section line in the readfile
	JudgeMemory(pSectLine);
	(*pGetLine)[(*LineTotalLength)-2] = '\n';
	fgets(*pGetLine,READ_SIZE,fpReadFile);  
	while((*pGetLine)[*LineTotalLength-2] != '\n')
	{
		if(NULL == fgets(pSectLine,READ_SIZE,fpReadFile))
		{
			break;
		}
		LineTotalLength += (READ_SIZE-1);
		*pGetLine = (char*)realloc(pGetLine,sizeof(char)*(*LineTotalLength));
		JudgeMemory(*pGetLine);
		(*pGetLine)[(*LineTotalLength)-2] = '\n';
		strncpy((*pGetLine)+(*LineTotalLength)-READ_SIZE,pSectLine,READ_SIZE);
	}
	free(pSectLine);
	return 0;
}


/************************************************************//**
@brief     Read first line of fpReadFile into  pGetLine completely
@param     **pAllLength        store input character
           **pGetLine         record a Line comletely
		   LineTotalLength    allocate memory 
@retval    0  success
@author YHF
@data    2018/2/19
@design:
judge whether the last character read whether cover
*****************************************************************/

int ExecuteFindSpecial(int MatchMode,char* pInputChar,int* pInputCharLength,const int InputCharNum,char* pReadFile,const int ReadFileNum,char* pWriteFile,const int WriteFileNum)
{
	if(UNIFIED_OUTPUT_MODE ==MatchMode)
	{
		UnifiedOutputMode(pInputChar,pInputCharLength,InputCharNum,pReadFile,ReadFileNum,pWriteFile,WriteFileNum);
	}
	if(SEPARATE_CHAR_OUTPUT == MatchMode)
	{
		SeparateCharOutput(pInputChar,pInputCharLength,InputCharNum,pReadFile,ReadFileNum,pWriteFile,WriteFileNum);
	}
	if(SEPARATE_INPUT_FILE_OUTPUT == MatchMode)
	{
		SeparateInputFileOutput(pInputChar,pInputCharLength,InputCharNum,pReadFile,ReadFileNum,pWriteFile,WriteFileNum);
	}
	return 0;
}
/************************************************************//**
@brief     Judge file whther success open;
@param     * fpFile[IN]  pointer file
           *pFile  [IN]  file name
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
/************************************************************//**
@brief     position of char N
@param     *pInputCharLength[IN]  pointer storage the Char
           NumNChar         [IN]  Char N
@retval    PositionNChar  the position of the char N
@author YHF
@data    2018/2/25
@design:

*****************************************************************/
int PositionNChar(int* pInputCharLength,int NumNChar)
{
	int CycleNChar = 0;
	int PositionNChar = 0;
	while(CycleNChar != NumNChar)
	{
		PositionNChar += pInputCharLength[CycleNChar];
		CycleNChar++;
	}
	return PositionNChar;
}
/************************************************************//**
@brief     UNIFIED_OUTPUT_MODE       [1] all  result output to one file
@param     char* pInputChar,         [IN] storage input char
           int* pInputCharLength,    [IN] storage input char length 
		   const int InputCharNum,   [IN] storage input char number
		   char* pReadFile,          [IN] storage Readfile
		   const int ReadFileNum,    [IN] storage read file number
		   char* pWriteFile,         [IN] storage write in file 
		   const int WriteFileNum    [IN] storage write in file number
@retval    0             success
@author YHF
@data    2018/2/25
@design:
*****************************************************************/
int UnifiedOutputMode(char* pInputChar,int* pInputCharLength,const int InputCharNum,char* pReadFile,const int ReadFileNum,char* pWriteFile,const int WriteFileNum)
{
	FILE *fpReadFile;
	FILE *fpWriteFile;

	char* pGetLine = (char*)malloc(sizeof(char)*READ_SIZE);

	int NumNChar = 0;
	int NumNInputFile =0;
	int LineTotalLength = 0;
	fpWriteFile = fopen (pWriteFile,"a");
	JudgeOpenFile(fpWriteFile,pWriteFile);
	while( ReadFileNum != NumNInputFile)
	{
		fpReadFile = fopen(pReadFile + ( NumNInputFile * READ_SIZE),"r");
		JudgeOpenFile(fpReadFile,pReadFile + ( NumNInputFile * READ_SIZE));
		while(!feof(fpReadFile))
			{
				ReadFileFirstLine(fpReadFile,&pGetLine,&LineTotalLength);
				while(NumNChar != InputCharNum)
				{
					if(LineTotalLength > pInputCharLength[NumNChar])
					{
						if(!strncmp(pGetLine,pInputChar+ PositionNChar(pInputCharLength,NumNChar),pInputCharLength[NumNChar]))
						{
							fprintf(fpWriteFile,"%s",pGetLine);
						}
					}
					NumNChar++;
				}
			}
		NumNInputFile++;
		fclose(fpReadFile);
	}
	fclose(fpWriteFile);
	return 0;
}

       
		
/************************************************************//**
@brief     SEPARATE_CHAR_OUTPUT      [2] corresponding char and output file separate
@param     char* pInputChar,         [IN] storage input char
           int* pInputCharLength,    [IN] storage input char length 
		   const int InputCharNum,   [IN] storage input char number
		   char* pReadFile,          [IN] storage Readfile
		   const int ReadFileNum,    [IN] storage read file number
		   char* pWriteFile,         [IN] storage write in file 
		   const int WriteFileNum    [IN] storage write in file number
@retval    0             success
@author YHF
@data    2018/2/25
@design:
 SEPARATE_INPUT_FILE_OUTPUT[3] corresponding input file and output file separate 
*****************************************************************/
int SeparateCharOutput(char* pInputChar,int* pInputCharLength,const int InputCharNum,char* pReadFile,const int ReadFileNum,char* pWriteFile,const int WriteFileNum)
{
	FILE *fpReadFile;
	FILE *fpWriteFile;
	char* pGetLine = (char*)malloc(sizeof(char)*READ_SIZE);

	int NumNChar = 0;
	int NumNInputFile =0;
	int LineTotalLength=0;
	fpReadFile = fopen(pReadFile ,"r");
	JudgeOpenFile(fpReadFile,pReadFile);
	while(NumNChar != InputCharNum)
	{
		fpWriteFile = fopen(pReadFile + (NumNInputFile * READ_SIZE),"a");
		JudgeOpenFile(fpWriteFile,pReadFile + (NumNInputFile * READ_SIZE));
		while(!feof(fpReadFile))
		{
			ReadFileFirstLine(fpReadFile,&pGetLine,&LineTotalLength);
			if(LineTotalLength > pInputCharLength[NumNChar])
			{
				if(!strncmp(pGetLine,pInputChar+ PositionNChar(pInputCharLength,NumNChar),pInputCharLength[NumNChar]))
				{
					fprintf(fpWriteFile,"%s",pGetLine);
				}
			}
			NumNChar++;
			
		}
		fclose(fpWriteFile);
		NumNChar++;
	}
	return 0;
}
/************************************************************//**
@brief     SEPARATE_INPUT_FILE_OUTPUT[3] corresponding input file and output file separate 
@param     char* pInputChar,         [IN] storage input char
           int* pInputCharLength,    [IN] storage input char length 
		   const int InputCharNum,   [IN] storage input char number
		   char* pReadFile,          [IN] storage Readfile
		   const int ReadFileNum,    [IN] storage read file number
		   char* pWriteFile,         [IN] storage write in file 
		   const int WriteFileNum    [IN] storage write in file number
@retval    0             success
@author YHF
@data    2018/2/25
@design:
 SEPARATE_INPUT_FILE_OUTPUT[3] corresponding input file and output file separate 
*****************************************************************/
int SeparateInputFileOutput(char* pInputChar,int* pInputCharLength,const int InputCharNum,char* pReadFile,const int ReadFileNum,char* pWriteFile,const int WriteFileNum)
{
	FILE *fpReadFile;
	FILE *fpWriteFile;
	char* pGetLine = (char*)malloc(sizeof(char)*READ_SIZE);

	int NumNChar = 0;
	int NumNInputFile =0;
	int LineTotalLength=0;
	while(NumNInputFile != ReadFileNum)
	{
		fpReadFile = fopen(pReadFile + (NumNInputFile * READ_SIZE),"r");
		JudgeOpenFile(fpReadFile,pReadFile + (NumNInputFile * READ_SIZE));
		fpWriteFile = fopen(pWriteFile + (NumNInputFile * READ_SIZE),"a");
		JudgeOpenFile(fpWriteFile,pWriteFile + (NumNInputFile * READ_SIZE));
		while(!feof(fpReadFile))
		{
			ReadFileFirstLine(fpReadFile,&pGetLine,&LineTotalLength);
			if(LineTotalLength > pInputCharLength[NumNChar])
			{
				if(!strncmp(pGetLine,pInputChar+ PositionNChar(pInputCharLength,NumNChar),pInputCharLength[NumNChar]))
				{
					fprintf(fpWriteFile,"%s",pGetLine);
				}
			}
			NumNInputFile++;
			
		}
		fclose(fpReadFile);
		fclose(fpWriteFile);
		NumNChar++;
	}
	return 0;
}