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
@param     ***pAllLength        store input character
           *ActualTotalLength   record the actual length of input character
		   &NumberNhead         record confirm there are several logo head
@retval    0  success
@author YHF
@data    2018/2/4 
@design:
judge whether the last character read whether cover and cycle memory allocation
*****************************************************************/

int RecordInputCharBuf (char*** pAllChar,unsigned int** pActualTotalLength,int  &NumberMarks)
{  
	NumberMarks = 0;                                             ///number of marks
	int NumberNHead = 0;                                         ///number Nidentification header
	printf("请确认要输入的标识头个数：\n");
	scanf_s("%d",&NumberMarks,1);
	getchar();
	///pointer to the pointer to record different header
	*pAllChar = (char**)malloc(sizeof(char)*NumberMarks);
	*pActualTotalLength = (unsigned int*)malloc(sizeof(int)*NumberMarks);
	while(1)
	{
		if(NumberNHead == NumberMarks)
		{
			break;
		}
		const int ReadSize = 101;                ///<the length of the array to first read the character each time(reset)
		char *pEachRead;                         ///<cached fixed-length character
		int NumLoopRead = 0;
		int TotalLength = 0;                     ///<the total length of the allocate dynamic memory
		pEachRead = (char*)malloc(sizeof(char)*ReadSize);
		JudgeMemory(pEachRead);
		printf("请输入第%d个需要匹配的标识头字符：\n",NumberNHead+1);
		///read fixed length character form input stream

		TotalLength = ReadSize;
		(*pAllChar)[NumberNHead] = (char*)malloc(sizeof(char)*(TotalLength));
		JudgeMemory((*pAllChar)[NumberNHead]);
		(*pAllChar)[NumberNHead][TotalLength-2] = '\n';
		(*pAllChar)[NumberNHead] = fgets((*pAllChar)[NumberNHead],ReadSize,stdin);
		///judge the last one character whether be cover 
		///allocate new length to pAllChar rach time
		while((*pAllChar)[NumberNHead][TotalLength-2] != '\n')
		{
			fgets(pEachRead,ReadSize,stdin);                                  ///<read data  from the input stream 
			TotalLength += 100;                                               ///<read up to 100 character at a time 

			(*pAllChar)[NumberNHead] = (char*)realloc(*pAllChar,sizeof(char)*TotalLength);   ///<realloc space in the tail
			JudgeMemory ((*pAllChar)[NumberNHead]);
			(*pAllChar)[NumberNHead][TotalLength-2] = '\n';
			strcpy((*pAllChar)[NumberNHead]+TotalLength-101,pEachRead);                    ///<write data to the new allocate memory (cover '\0')
			NumLoopRead++;
		}
		if(NumLoopRead == 0)
		{
			(*pActualTotalLength)[NumberNHead] = strlen((*pAllChar)[NumberNHead])-1;
		}
		else
		{
			(*pActualTotalLength)[NumberNHead] = 100*NumLoopRead  + strlen(pEachRead)-1;
		}
		NumberNHead++;
		free(pEachRead);
	}
	return 0;
}
/*************************************************************//**
@brief    open file and write the Matching line in file
@param    *pMatch   enter matching character into function
          InputTotalLength  enter input character length into function
@retval   0  success
@author  YHF
@data     2018/2/8
@
*****************************************************************/
int OutputSpecialLineToFile(char **pMatch,const unsigned int*const InputCharLength,const int &NumberMarks)
{
	FILE *fpReadFile;  
	FILE *fpWriteFile; 
	const int   ReadSize = 101;
	char  SectLine[101];                   ///<read a section line in the readfile
	char  *pGetLine;                       ///<save a complete line
	int   LineTotalLength;                 ///<the total of the allocate memory line length
	int   LineActualTotalLength = 0;       ///record the actual length of each line
	char  ReadFile[100];                   ///<save the readfile path
	char  WriteFile[100];                  ///<save the outputfile  path
	int   ClearBuf=0;                      ///<clear the buffer stuck due to error
	int   NumberNHead = 0;                 ///<number N logo head

	printf("请输入原文件：\n");
	scanf_s("%s",ReadFile,100);
	fpReadFile = fopen(ReadFile,"r");
	printf("筛选出数据存放至：\n");
	scanf_s("%s",WriteFile,100);
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
	while (fgets(SectLine,ReadSize,fpReadFile))          
	{
		NumberNHead = 0;                               ///<reset
		pGetLine = (char*)malloc(sizeof(char)*(ReadSize));
		JudgeMemory(pGetLine);
		LineTotalLength = ReadSize;
		pGetLine[LineTotalLength-2] = '\n';
		strcpy(pGetLine,SectLine);
		while(pGetLine[LineTotalLength-2] != '\n')
		{
			if(NULL == fgets(SectLine,101,fpReadFile))
			{
				break;
			}
			LineTotalLength += 100;
			pGetLine = (char*)realloc(pGetLine,sizeof(char)*LineTotalLength);
			JudgeMemory(pGetLine);
			pGetLine[LineTotalLength-2] = '\n';
			strcpy(pGetLine+LineTotalLength-101,SectLine);
		}
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