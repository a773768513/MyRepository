/****************************//**
          CommandLine input module
@file  CommandLineInput.cpp
@author YHF
@data  2018/2/25
@brief
*****************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "InputCharStorage.h"
#include "CommandLineInput.h"
#include "MatchCharacterModule.h"
#include "storageFileMode.h"
/*****************************************************//*
@brief   Manual input the file 
@param   NO   all param come from user input 
@author YHF
@data  2018/2/25
@brief

*******************************************************/

int CommandLineInputAndOutput()
{
	char pCommandRecognition[COMMAND_LENGTH];
	char* pHelpCommand ={"-hp"};
	char* pInputChar = {"-ic"};
	char* pInputFile = {"-if"};
	char* pOutputFile = {"-of"};
	char* pEndOrder = {"-ed"};
	int   MatchMode;

	char pInputChar[READ_SIZE];
	int  InputCharTotalLength = 0;
	int* pInputCharLength;
	int  InputCharNum=0;
	bool bChangeCharMemory = 0;     ///Judge whther use dynamic memory

	char pReadFile[READ_SIZE];
	int  ReadFileNum=0;                 ///record the input num of file
	bool bChangeReadMemory = 0;          ///judge the whther use the dynamic memory

	char pWriteFile[READ_SIZE];
	int WriteFileNum=0;
	bool bChangeWriteMemory = 0;        ///judge the whther use the dynamic memory
	
	pInputChar[READ_SIZE-2] = '\n';
	pReadFile[READ_SIZE-2] = '\n';
	pWriteFile[READ_SIZE-2] = '\n';
	while(1)
	{
		printf("enter command to excution program(input”-hp“for  help");
		fgets(pCommandRecognition,COMMAND_LENGTH,stdin);
		getchar();
		if(!strncmp(pCommandRecognition,pHelpCommand,3))
		{
			HpleCommandPrintf();
		}
		else if(strncmp(pCommandRecognition,pInputChar,3))
		{
			if(0 == InputCharNum)
			{
				fgets(pInputChar,READ_SIZE,stdin);
				if('\n' == pInputChar[READ_SIZE-2])
				{
					InputCharNum++;
					pInputCharLength = (int*)malloc(sizeof(int)*1);
					*pInputCharLength = strlen(pInputChar)-1;
					
				}
				///第一次读取未读完，则改为动态内存
				///
				else
				{
					InputCharNum++;
					pInputChar = ArrayLengthToDynamicMemory(pInputChar,READ_SIZE);
					bChangeCharMemory = 1;
					pInputCharLength = (int*)malloc(sizeof(int)*1);
					RecordInputCharBuf (pInputChar,&(pInputCharLength[InputCharNum-1]),&InputCharTotalLength);
					pInputCharLength[InputCharNum] += (READ_SIZE-1);
					
				}
				///目的：读完未结束的一行，方式
			}
			///第二次读取  改为动态内存
			if(!bChangeCharMemory)
			{
				pInputChar = ArrayLengthToDynamicMemory(pInputChar,READ_SIZE);
				bChangeCharMemory = 1;
				pInputCharLength = (int*)malloc(sizeof(int)*1);
				RecordInputCharBuf (pInputChar,&(pInputCharLength[InputCharNum]),&InputCharTotalLength);
			}
			InputCharNum++;
			pInputCharLength = (int*)realloc(pInputCharLength,sizeof(int)*InputCharNum);
			RecordInputCharBuf (pInputChar,&(pInputCharLength[InputCharNum-1]),&InputCharTotalLength);
		}
		else if(!strncmp(pCommandRecognition,pInputFile,3))
		{
			if(0 == ReadFileNum)
			{
				ReadFileNum++;
				fgets(pReadFile,READ_SIZE,stdin);
				
			}
			else
			{
				ReadFileNum++;
				pReadFile = ArrayLengthToDynamicMemory(pReadFile,READ_SIZE);
				fgets(pReadFile+(ReadFileNum-1)*READ_SIZE,READ_SIZE,stdin);
				FileManualMode(pReadFile,ReadFileNum);
			}

		}
		else if(!strncmp(pCommandRecognition,pOutputFile,3))
		{
			if(0 == WriteFileNum)
			{
				WriteFileNum++;
				fgets(pWriteFile,READ_SIZE,stdin);
				
			}
			else
			{
				ReadFileNum++;
				pWriteFile = ArrayLengthToDynamicMemory(pReadFile,READ_SIZE);
				fgets(pReadFile+(ReadFileNum-1)*READ_SIZE,READ_SIZE,stdin);
				FileManualMode(pWriteFile,WriteFileNum);
			}
		}
		else if(!strncmp(pCommandRecognition,pEndOrder,3))
		{
			break;
		}
		else
		{
			printf("input error,please re-input");
			fflush(stdin);
		}
	}
	
	MatchMode = ProcessMode(InputCharNum,ReadFileNum,WriteFileNum);
	ExecuteFindSpecial(MatchMode,pInputChar,pInputCharLength,InputCharNum,pReadFile,ReadFileNum,pWriteFile,WriteFileNum);
	if(bChangeCharMemory )
	{
		free(pInputChar);
	}
	if(bChangeReadMemory)
	{
		free(pReadFile);
	}
	if(bChangeWriteMemory)
	{
		free(pWriteFile);
	}
	return 0 ;


}

/*****************************************************//*
@brief   -help  give user message to operation
@param   NO only output message
@author YHF
@data  2018/2/25
@brief

*******************************************************/
void HpleCommandPrintf()
{
	printf("using the following command to input matching character,find spcial line file and write in file(can be entered multiple times\n");
	printf("-ic_Character          to input the character character and InputFileName must have one can only enter once\n");
	printf("-if_InputFileName      to input the file you wang to find special line (character and InputFileName must have one can only enter once\n");
	printf("-of_OutputFileName     to input the outputFile you wang to write in the match result");
	printf("-ed_EndCommand         to end input and execute program");
}