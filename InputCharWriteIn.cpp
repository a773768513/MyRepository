/**************************************************//**
			Training  Module
*-
@file InputCharWriteIn.cpp
@author YHF
@data 2018/1/31
@package try to package

**********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "InputCharWriteIn.h"

/************************************************************//**
@brief    judge memory allocate is successful
@param    pJudgeMemory  pointer to dynamic memory
@retval   directly exit if the memory allocation fails
@author   YHF
@date     2018/2/3
@note     
history:

*****************************************************************/
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

/************************************************************//**
@brief     read a complete input character
@param     **pAllLength        store input character
           ActualTotalLength   record the actual length of input character
		   NumberNHead         record  there are Nth logo head
		   NumberMarks         
@retval    0  success
@author YHF
@data    2018/2/19
@design:
judge whether the last character read whether cover
*****************************************************************/

int RecordInputCharBuf (char** pAllChar,unsigned int &ActualTotalLength,const int NumberNHead,const int NumberMarks)
{
	char *pEachRead;
	int TotalLength = 0;                ///<the total length of the allocate dynamic memory
	ActualTotalLength = 0;              ///<the length of each actual read(does not contain unfill character)
	int NumLoopRead = 0 ;               ///record the numble of cycyle
	pEachRead = (char*)malloc(sizeof(char)*(READ_SIZE));
	JudgeMemory(pEachRead);
	printf("Please enter the characters you want to match(the current input %d/%d）：\n",(NumberNHead+1),NumberMarks);
	///read fixed length character form input stream
	
	TotalLength = READ_SIZE;
	*pAllChar = (char*)malloc(sizeof(char)*(TotalLength));
	JudgeMemory(*pAllChar);
	(*pAllChar)[TotalLength-2] = '\n';
	*pAllChar = fgets(*pAllChar,READ_SIZE,stdin);
	
	///judge the last one character whether be cover
	///allocate new length to pAllChar rach time
	while((*pAllChar)[TotalLength-2] != '\n')
	{
		fgets(pEachRead,READ_SIZE,stdin);                                  ///<read data  from the input stream 
		TotalLength += (READ_SIZE-1);                                               ///<read up to 100 character at a time 

		*pAllChar = (char*)realloc(*pAllChar,sizeof(char)*TotalLength);   ///<realloc space in the tail
		JudgeMemory (*pAllChar);
		(*pAllChar)[TotalLength-2] = '\n';
		strncpy((*pAllChar)+TotalLength-READ_SIZE,pEachRead,READ_SIZE);                    ///<write data to the new allocate memory (cover '\0')
		NumLoopRead++;
	}
	if(NumLoopRead == 0)
	{
		ActualTotalLength = strlen(*pAllChar)-1;
	}
	else
	{
		ActualTotalLength = (READ_SIZE-1)*NumLoopRead  + strlen(pEachRead)-1;
	}
	free(pEachRead);
	return 0;
}
/************************************************************//**
@brief     Read first line of A into  B completely
@param     **pAllLength        store input character
           ActualTotalLength   record the actual length of input character
		   NumberNHead         record  there are Nth logo head
		   NumberMarks         
@retval    0  success
@author YHF
@data    2018/2/19
@design:
judge whether the last character read whether cover
*****************************************************************/
int ReadFileFristLine(FILE* &fpReadFile,char* &pGetLine)
{
	int LineTotalLength = 128;                                  ///<the total of the allocate memory line length
	char* pSectLine = (char*)(sizeof(char)*READ_SIZE);           ///<read a section line in the readfile
	pGetLine = (char*)malloc(sizeof(char)*READ_SIZE);
	JudgeMemory(pGetLine);
	JudgeMemory(pSectLine);
	pGetLine[LineTotalLength-2] = '\n';
	fgets(pGetLine,READ_SIZE,fpReadFile);  
	while(pGetLine[LineTotalLength-2] != '\n')
	{
		if(NULL == fgets(pSectLine,READ_SIZE,fpReadFile))
		{
			break;
		}
		LineTotalLength += READ_SIZE;
		pGetLine = (char*)realloc(pGetLine,sizeof(char)*LineTotalLength);
		JudgeMemory(pGetLine);
		pGetLine[LineTotalLength-2] = '\n';
		strncpy(pGetLine+LineTotalLength-READ_SIZE,pSectLine,ReadSize);
	}
}

/************************************************************//**
@brief     record multiple match character
@param     ***pAllLength        store input character
           *pInputCharLength   record the actual length of input character
		   &NumberNhead         record confirm there are Nth several logo head
@retval    0  success
@author YHF
@data    2018/2/4 
@design:
creat two-dimensional pointers
*****************************************************************/


int MultipleIdentiHead(char*** pAllChar,unsigned int** pInputCharLength,int &NumberMarks)
{
	NumberMarks = 0;                                             ///number of marks
	int NumberNHead = 0;                                         ///number Nidentification header
	printf("please confirm that you need to enter the number of matching character：\n");
	scanf_s("%d",&NumberMarks,1);
	fflush(stdin);
	///pointer to the pointer to record different header
	*pAllChar = (char**)malloc(sizeof(char)*NumberMarks);
	*pInputCharLength = (unsigned int*)malloc(sizeof(int)*NumberMarks);
	while(1)
	{
		if(NumberNHead == NumberMarks)
		{
			break;
		}
		RecordInputCharBuf(&(*pAllChar)[NumberNHead],(*pInputCharLength)[NumberNHead],NumberNHead,NumberMarks);
		NumberNHead++;
	}
	return 0;
}
/**
@brif     sanve the the multiple file to  open
@param
	**/
int FileNormallyMode(char* &pReadFile,int &FileNum)
{
	printf("请输入要打开的文件：\n");
	FileNum = 1;
	fgets(pReadFile,READ_SIZE,stdin);
	return 0;
}
/**
@brif     sanve the the multiple file to  open
@param
	**/
int FileListMode(char* &pReadFile,int &RecordFileLine)
{
	char pFileListMode[READ_SIZE];
	FILE *fpFileListMode;
	RecordFileLine = 1;                                        ///<记录多少行
	printf("进入文件列表打开模式，请输入包含文件列表文件：\n");
	scanf_s("%s",pFileListMode,READ_SIZE);
	fpFileListMode = fopen(pFileListMode,"r");
	fgets(pReadFile,READ_SIZE,fpFileListMode);
	while(!feof(fpFileListMode))
	{
		RecordFileLine++;
		pReadFile = (char*)realloc(pReadFile,sizeof(char)*(RecordFileLine*READ_SIZE));
		fgets(pReadFile+(RecordFileLine-1)*READ_SIZE,READ_SIZE,fpFileListMode);
	}
	return 0;
}
/**
@brif     sanve the the multiple file to  open
@param
	**/
int FileManualMode(char* &pReadFile,int &FileNth)
{
	FileNth = 1;
	printf("进入手动输入模式，请输入第%d个文件，直接回车结束手动输入模式",FileNth);
	fgets(pReadFile,READ_SIZE,stdin);
	while(*(pReadFile+(FileNth-1)*READ_SIZE) != '\n')
	{
		FileNth++;
		printf("进入手动输入模式，请输入第%d个文件，直接回车结束手动输入模式",FileNth);
		pReadFile = (char*)realloc(pReadFile,sizeof(char)*(FileNth*READ_SIZE));
		JudgeMemory(pReadFile);
		pReadFile = fgets(pReadFile+(FileNth-1)*READ_SIZE,READ_SIZE,stdin);
	}
	FileNth--;
	pReadFile = (char*)realloc(pReadFile,sizeof(char)*(FileNth*READ_SIZE));
	return 0;
}
/**
@brif     sanve the the multiple file to  open
@param
	**/
int FileModeStorage(char* &pFileStorage,int FileNum)
{
	char PressKey;                   ///<用户案件决定模式
	printf("手动输入模式请按H/h，文件列表输入请按F/f\n");
	while((PressKey = getchar()) != 'h')
	{
		if(PressKey =='H')
		{
			break;
		}
		if(PressKey == 'F')
		{
			break;
		}
		if(PressKey == 'f')
		{
			break;
		}
		printf("输入错误，请从新输入");
		getchar();
	}
	if(PressKey != 'h')
	{
		if(PressKey != 'H')
		{
			FileListMode(pFileStorage,FileNum);
			return 1;
		}
	}
	FileManualMode(pFileStorage,FileNum);
	return 2;
}

/**
@brif     sanve the the multiple file to  open
@param
	**/
int SaveMultipleFileInput(char* &pReadFile,const int NumberMarks,int &FileNumInput)
{
	int FileMode;
	char PressKey;
	printf("是否需要打开多个文件读取？（仅当多个标识头有此提示）按Y/y确认，任意键取消\n");
    ///确认用户是否需要查找多个文件
	while (NumberMarks == 1)
	{
		if((PressKey = getchar()) != 'y')
		{
			if (PressKey != 'Y')
			{
				getchar();
				break;
			}
		}
		getchar();
		FileMode = FileModeStorage(pReadFile,FileNumInput);
		return FileMode;
	}
	FileNormallyMode(pReadFile,FileNumInput);
	return 3;
}
/**
@brif     sanve the the multiple file to  open
@param
	**/
int SaveMuptipleFileOutput(char* &pWriteFile,int FileNumOutput,const int NumberMarks,const int NumberFileInput,const int FileInputMode)
{
	char  PressKey;
	printf("当前输入%d个表示头，在%d个文件忠匹配，是否将匹配结果分开输出？（Y/y确认，任意键取消",NumberMarks,NumberFileInput);
	if((PressKey = getchar()) != 'Y')
	{
		if(PressKey != 'y')
		{
			FileNormallyMode(pWriteFile,FileNumOutput);
			return 1;
		}
	}
	if (NumberMarks != 1)
	{
		printf("

/*************************************************************//**
@brief    open file and write the Matching line in file
@param    *pMatch           enter matching character into function
          InputTotalLength  enter input character length into function
		  NumberMarks       a total of match character are required
@retval   0  success
@author  YHF
@data     2018/2/8
@
*****************************************************************/
int OutputSpecialLineToFile(char **pMatch,const unsigned int*const InputCharLength,const int &NumberMarks)
{
	FILE *fpReadFile;  
	FILE *fpWriteFile; 
	int   FileInputMode;
	int   NumberOfCycle = 0;               ///<The number of specialized to cycles
	char  *pGetLine;                       ///<save a complete line
	int   LineTotalLength;                 ///<the total of the allocate memory line length
	char  *pReadFile;                     ///<save the readfile path
	char  *WriteFile;                    ///<save the outputfile  path
	int   ClearBuf=0;                      ///<clear the buffer stuck due to error
	int   NumberNHead = 0;                 ///<number N logo head
	int  FileNumInput;
	pReadFile = (char*)malloc(sizeof(char)*READ_SIZE);
	JudgeMemory(pReadFile);
	FileInputMode = SaveMultipleFileInput(pReadFile,NumberMarks,FileNumInput);
	
	
		
		

			
		
	}
	printf("请输入原文件：\n");
	scanf_s("%s",READ_SIZE,100);
	fpReadFile = fopen(ReadFile,"r");
	printf("筛选出数据存放至：\n");
	scanf_s("%s",WriteFile,100);
	fpWriteFile=fopen(WriteFile,"a"); 
	if((NULL == fpReadFile)||(NULL==fpWriteFile))
	{
		printf("Can not open file data!\nPress any key to exit");
		
		getchar();
		exit(EXIT_FAILURE); 
	}
	///match characters to each line and output
	///design idea consistent with reading character
	
		while(NumberNHead != NumberMarks)
		{
			if(LineTotalLength > InputCharLength[NumberNHead])
			{
				if(!strncmp(pGetLine,pMatch[NumberNHead],InputCharLength[NumberNHead]))
				{
					fprintf(fpWriteFile,"%s",pGetLine);
				}
			}
			NumberNHead++;
		}
		free(pGetLine);
	}
		fclose(fpReadFile);
		fclose(fpWriteFile);
		return 0;
}