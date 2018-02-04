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
		   printf("No enough stroage,Memory allocate failed,press any key to exit");
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

int ReadBuf (char** pAllChar,int &iTotalLength)
{
	int size = 100;                  ///<the length of the array to first read the character each time
	char *pReadBuf;
	iTotalLength = 0;               ///<the total length of the input character
	int iActualLength = 0;          ///<the length of each actual read
	pReadBuf = (char*)malloc(sizeof(char)*size);
	void (*pReadBuf);
	///read fixed length character form input stream
	pReadBuf = fgets(pReadBuf,size,stdin);
	iTotalLength = strlen(pReadBuf);  
	++iTotalLength;                     ///<one more for storage '\0'
	*pAllChar = (char*)malloc(sizeof(char)*(iTotalLength));
	JudgeMemory(*pAllChar);
	strcpy(*pAllChar,pReadBuf);
	///judge whether newline in the last one
	///allocate new length to pAllChar rach time
	while((*pAllChar)[iTotalLength-1] != '\n')
	{
		fgets(pReadBuf,size,stdin);                    ///<read data  from the input stream
		iActualLength = strlen (pReadBuf);
		iTotalLength += iActualLength;
		*pAllChar = (char*)realloc(pAllChar,sizeof(char)*iTotalLength);   ///<realloc space in the tail
	    JudgeMemory (*pAllChar);
		strcpy((*pAllChar)+iTotalLength-iActualLength-1,pReadBuf);   ///<write data to the end (cover '\0')
	}
	free(pReadBuf);
	pReadBuf = NULL;
	return 0;
}


int OutputFile(char *pMatch,int &iTotalLength)
{
	FILE *fpReadFile;  
	FILE *fpWriteFile;      
	char  Line[100];                  ///<read a line in the readfile
	char  *pGetLine;                ///<save a complete line
	int   iActual_Length = 0;          ///<the length of line each read
	int   iTotal_Length = 0;            ///<the total of line length
	char  ReadFile[100];              ///<save the readfile path
    char  WriteFile[100];             ///<save the output path
	int   iClearBuf=0;                ///<clear the buffer stuck due to error

	printf("请输入原文件：\n");
	scanf("%s",&ReadFile);
	fpReadFile = fopen(ReadFile,"r");
	printf("筛选出数据存放至：\n");
	scanf("%s",&WriteFile);
	fpWriteFile=fopen(WriteFile,"a"); 
	int count=strlen(pMatch);            ///<record the length of the input character 
	if((NULL == fpReadFile)||(NULL==fpWriteFile))
		{
			printf("Can not open file data!\nPress any key to exit");
			/// clear the console
        	while((iClearBuf=getchar())!='\n')
			{
				if(iClearBuf==EOF)
				{
					break;
				}
			}
			getchar();
			exit(EXIT_FAILURE);
	     }
	///match characters to each line and output
	///design idea consistent with reading character
	while (fgets(Line,sizeof(Line),fpReadFile))          
	{
		iTotal_Length = strlen(Line)+1;
		pGetLine = (char*)malloc(sizeof(char)*(iTotal_Length));
		strcpy(pGetLine,Line);
		while(pGetLine[iTotal_Length-1] != '\n')
		{
			fgets(Line,sizeof(Line),fpReadFile);
			iActual_Length = strlen(Line);
			iTotal_Length += iActual_Length;
			pGetLine = (char*)malloc(sizeof(char)*iTotal_Length);
			JudgeMemory(pGetLine);
			strcpy(pGetLine+iTotal_Length-iActual_Length-1,Line);
		}
		if(strncmp(pGetLine,pMatch,iTotalLength))
		{
			fprintf(fpWriteFile,"%s",pGetLine);
		}
		delete[] pGetLine;
	    pGetLine = NULL;
	}
	
	fclose(fpReadFile);
	fclose(fpWriteFile);
	return 0;
}