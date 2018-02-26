/*******************************************************//**


@file  storageFileMode.cpp     
@author YHF
@data 2018/2/25
@

***********************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "InputCharStorage.h"
#include "CommandLineInput.h"
#include "MatchCharacterModule.h"
#include "storageFileMode.h"

/*****************************************************//*
@brief   Manual input the file 
@param   pReadFile [out] record the read file 
         ReadFileNum[IN]  use to allocate memory total length
@author YHF
@data  2018/2/25
@brief

*******************************************************/
int FileManualMode(char* pReadFile,int ReadFileNum)
{
	pReadFile = (char*)realloc(pReadFile,sizeof(char)*(ReadFileNum*READ_SIZE));
<<<<<<< HEAD
=======
		
>>>>>>> 1beafd57d64c2b16fba953f285cd7fbdd25fcdcf
	JudgeMemory(pReadFile);
	pReadFile = fgets(pReadFile+(ReadFileNum-1)*READ_SIZE,READ_SIZE,stdin);
	
	
	return 0;
}