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
	///record variables used to	corresponding command
	///
	char pCommandRecognition[COMMAND_LENGTH];
	char* pHelpCommand ={"-hp"};
	char* pInputCharCommand = {"-ic"};
	char* pInputFileCommand = {"-if"};
	char* pOutputFileCommand = {"-of"};
	char* pEndOrderCommand = {"-ed"};
	int   MatchMode;                              ///<record the Match character mode


	///Processing character related variables
	///
	char* pInputChar;                    ///<poniter the memory storage Char
	char pInputCharOnce[READ_SIZE];     ///<storage the smaller character
	int* pInputCharLength;              ///<record the length of each Char
	int  InputCharNum=0;                ///<record the num of input char
	bool bChangeCharMemory = 0;         ///<Judge whther use dynamic memory
	int  InputCharTotalLength ;          ///<record the total length of char,used to income function param and change

	char* pReadFile;
	char pReadFileOnce[READ_SIZE];          ///<pointer the memory storage read file 
	int  ReadFileNum=0;                 ///<record the input num of file
	bool bChangeReadMemory = 0;          ///<judge the whther use the dynamic memory

	char* pWriteFile;
	char pWriteFileOnce[READ_SIZE];         ///<pointer the memory storage write file
	int WriteFileNum=0;                 ///<record the need to output file 
	bool bChangeWriteMemory = 0;        ///<judge the whther use the dynamic memory
	
	///
	///refresh the last character used to judge whether finish
	pInputCharOnce[READ_SIZE-2] = '\n';
	pReadFileOnce[READ_SIZE-2] = '\n';
	pWriteFileOnce[READ_SIZE-2] = '\n';
	while(1)
	{
		printf("enter command to excution program(input”-hp“for  help)\n");
		fgets(pCommandRecognition,COMMAND_LENGTH,stdin);
		getchar();
		///
		///
		if(!strncmp(pCommandRecognition,pHelpCommand,(COMMAND_LENGTH-1)))
		{
			HpleCommandPrintf();
		}
		else if(!strncmp(pCommandRecognition,pInputCharCommand,(COMMAND_LENGTH-1)))
		{
			if(0 == InputCharNum)
			{
				fgets(pInputCharOnce,READ_SIZE,stdin);
				if('\n' == pInputCharOnce[READ_SIZE-2])
				{
					InputCharNum++;
					pInputChar = pInputCharOnce;
					pInputCharLength = (int*)malloc(sizeof(int)*1);
					JudgeMemory(pInputCharLength);
					*pInputCharLength = strlen(pInputChar)-1;
					
				}
				///if not finished in first time read,change to dynamic memory
				///
				else
				{
					InputCharNum++;
					bChangeCharMemory = 1;
					pInputChar = ArrayLengthToDynamicMemory(pInputCharOnce,READ_SIZE);
					pInputCharLength = (int*)malloc(sizeof(int)*1);
					RecordInputCharBuf (pInputChar,&(pInputCharLength[InputCharNum-1]),&InputCharTotalLength);
					pInputCharLength[InputCharNum] += (READ_SIZE-1);
					
				}
				///目的：读完未结束的一行，方式
			}
			///第二次读取  改为动态内存
			else
			{
				if(!bChangeCharMemory)
				{
					pInputChar = ArrayLengthToDynamicMemory(pInputCharOnce,READ_SIZE);
					bChangeCharMemory = 1;
					pInputCharLength = (int*)malloc(sizeof(int)*1);
					RecordInputCharBuf (pInputChar,&(pInputCharLength[InputCharNum]),&InputCharTotalLength);
				}
				InputCharNum++;
				pInputCharLength = (int*)realloc(pInputCharLength,sizeof(int)*InputCharNum);
				RecordInputCharBuf (pInputChar,&(pInputCharLength[InputCharNum-1]),&InputCharTotalLength);

			}
		}
		
		else if(!strncmp(pCommandRecognition,pInputFileCommand,COMMAND_LENGTH))
		{
			if(0 == ReadFileNum)
			{
				ReadFileNum++;
				scanf_s("%s",pReadFileOnce,READ_SIZE);
				getchar();
				pReadFile = pReadFileOnce;
			}
			else
			{
				ReadFileNum++;
				pReadFile = ArrayLengthToDynamicMemory(pReadFileOnce,READ_SIZE);
				FileManualMode(pReadFile,ReadFileNum);
				scanf_s("%s",pReadFile+(READ_SIZE-1)*ReadFileNum,READ_SIZE);
				getchar();
			}
		}
		else if(!strncmp(pCommandRecognition,pOutputFileCommand,3))
		{
			if(0 == WriteFileNum)
			{
				WriteFileNum++;
				scanf_s("%s",pWriteFileOnce,READ_SIZE);
				getchar();
				pWriteFile = pWriteFileOnce;
				
			}
			else
			{
				ReadFileNum++;
				pWriteFile = ArrayLengthToDynamicMemory(pWriteFileOnce,READ_SIZE);
				FileManualMode(pWriteFile,WriteFileNum);
				scanf_s("%s",pWriteFile+(READ_SIZE-1)*WriteFileNum,READ_SIZE);
				getchar();
			}
		}
		else if(!strncmp(pCommandRecognition,pEndOrderCommand,3))
		{
			fflush(stdin);
			break;
		}
		else
		{
			printf("input error,please re-input\n");
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
	printf("-of_OutputFileName     to input the outputFile you wang to write in the match result\n");
	printf("-ed_EndCommand         to end input and execute program\n");
}