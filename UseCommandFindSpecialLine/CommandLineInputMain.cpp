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
#include "MatchStrlenFile.h"
#include "StorageModule.h"
#include "CommandLineInputMain.h"
/****************************************************//**
@brief  main
@param  argc    the param number of  command line
@param  argv[]   
@retval 1  error input param
@author  YHF
@data   2018/2/25
@
********************************************************/
int main(int argc,char* argv[])
{
	char* pInputStr;
	int   InputStrLength;
	char* pInputFile;
	char* pOutputFile;

	if(argc !=4)
	{
		if (!strcmp(argv[1],"-help"))
		{
			HelpCommandPrintf();
			return HELP;
		}
		printf("input error,you must input data inthe format:\nprogram str OriginFilePath  OutputFileDataPath");
		return ARGUMENT_COUNT_ERROR;
	}
	pInputStr = argv[1];
	InputStrLength = strlen(pInputStr);
	pInputFile = argv[2];
	pOutputFile = argv[3];
	MatchStrInFile(pInputStr,InputStrLength,pInputFile,pOutputFile);
	return SUCCESS;

}
/*****************************************************//*
@brief   -help  give user message to operation
@param   NO only output message
@author YHF
@data  2018/2/25
@brief

*******************************************************/
void HelpCommandPrintf()
{
	printf("use the follow format to input the data\n program  str  OriginFilePath  OutputFileDataPath \n");
	printf("prompt:the Path must be less than 260 character, \n");
	printf("-help  check this tips \n");
	
}