/**************************************************//**
			Training  Module
*-
@file function.h
@author YHF
@data 2018/1/31
@package try to package

**********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/************************************************************//**
@brief    judge memory allocate is successful
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
@author YHF
@data    2018/2/4 
@design:
judge whether the last character read is new line 
*****************************************************************/

int ReadBuf (char** pAllChar,int &TotalLength)
{
	int ReadSize = 100;                  ///<the length of the array to first read the character each time
	char *pEachRead;
	TotalLength = 0;               ///<the total length of the input character
	int ActualLength = 0;          ///<the length of each actual read
	pEachRead = (char*)malloc(sizeof(char)*ReadSize);
	JudgeMemory(pEachRead);

	printf("请输入需要匹配的字符：\n");
	///read fixed length character form input stream
	pEachRead = fgets(pEachRead,ReadSize,stdin);
	TotalLength = strlen(pEachRead);  
	TotalLength++;       ///<one more for storage '\0'

	*pAllChar = (char*)malloc(sizeof(char)*(TotalLength));
	JudgeMemory(*pAllChar);
	strcpy(*pAllChar,pEachRead);
	///judge whether newline in the last one
	///allocate new length to pAllChar rach time
	while((*pAllChar)[TotalLength-2] != '\n')
	{
		fgets(pEachRead,ReadSize,stdin);                    ///<read data  from the input stream
		ActualLength = strlen (pEachRead);
		TotalLength += ActualLength;
		*pAllChar = (char*)realloc(*pAllChar,sizeof(char)*TotalLength);   ///<realloc space in the tail
		JudgeMemory (*pAllChar);
		strcpy((*pAllChar)+TotalLength-ActualLength-1,pEachRead);   ///<write data to the end (cover '\0')
	}
	free(pEachRead);
	return 0;
}
/*************************************************************//**
@brief    open file and write the Matching line in file
@author  YHF
@data     2018/2/8
@
*****************************************************************/
int OutputFile(char *pMatch,const int &InputTotalLength)
{
	FILE *fpReadFile;  
	FILE *fpWriteFile;      
	char  SectLine[100];                  ///<read a section line in the readfile
	char  *pGetLine;                ///<save a complete line
	int   ActualLength = 0;          ///<the length of line each read
	int   LineTotalLength = 0;            ///<the total of line length
	char  ReadFile[100];              ///<save the readfile path
	char  WriteFile[100];             ///<save the output path
	int   ClearBuf=0;                ///<clear the buffer stuck due to error

	printf("请输入原文件：\n");
	scanf("%s",&ReadFile);
	fpReadFile = fopen(ReadFile,"r");
	printf("筛选出数据存放至：\n");
	scanf("%s",&WriteFile);
	fpWriteFile=fopen(WriteFile,"a"); 
	if((NULL == fpReadFile)||(NULL==fpWriteFile))
	{
		printf("Can not open file data!\nPress any key to exit");
		/// clear the console
		while((ClearBuf=getchar())!='\n')
		{
			if(ClearBuf==EOF)
			{
				break;
			}
		}
		getchar();
		exit(EXIT_FAILURE);
	}
	///match characters to each line and output
	///design idea consistent with reading character
	while (fgets(SectLine,sizeof(SectLine),fpReadFile))          
	{
		LineTotalLength = strlen(SectLine)+1;
		pGetLine = (char*)malloc(sizeof(char)*(LineTotalLength));
		strcpy(pGetLine,SectLine);
		while(pGetLine[LineTotalLength-2] != '\n')
		{
			if(NULL == fgets(SectLine,sizeof(SectLine),fpReadFile))
			{
				break;
			}
			ActualLength = strlen(SectLine);
			LineTotalLength += ActualLength;
			pGetLine = (char*)realloc(pGetLine,sizeof(char)*LineTotalLength);

			JudgeMemory(pGetLine);
			strcpy(pGetLine+LineTotalLength-ActualLength-1,SectLine);
		}
		if(!strncmp(pGetLine,pMatch,(InputTotalLength-2)))
		{
			fprintf(fpWriteFile,"%s",pGetLine);
		}
		free(pGetLine);
	}
	
	fclose(fpReadFile);
	fclose(fpWriteFile);
	return 0;
}