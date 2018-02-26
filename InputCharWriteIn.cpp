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
	int TotalLength  = READ_SIZE ;                ///<the total length of the allocate dynamic memory
	ActualTotalLength = 0;              ///<the length of each actual read(does not contain unfill character)
	int NumLoopRead = 0 ;               ///record the numble of cycyle
	pEachRead = (char*)malloc(sizeof(char)*(READ_SIZE));
	JudgeMemory(pEachRead);
	printf("Please enter the characters you want to match(the current input %d/%d）：\n",(NumberNHead+1),NumberMarks);
	///read fixed length character form input stream
	///

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
	/// 
	///
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
@brief     Read first line of fpReadFile into  pGetLine completely
@param     **pAllLength        store input character
           pGetLine         record a Line comletely
		   LineTotalLength    allocate memory 
@retval    0  success
@author YHF
@data    2018/2/19
@design:
judge whether the last character read whether cover
*****************************************************************/
int ReadFileFirstLine(FILE* &fpReadFile,char* &pGetLine,int &LineTotalLength)
{
	LineTotalLength = 128;                                       ///<the total of the allocate memory line length
	char* pSectLine = (char*)(sizeof(char)*READ_SIZE);           ///<read a section line in the readfile
	JudgeMemory(pSectLine);
	pGetLine[LineTotalLength-2] = '\n';
	fgets(pGetLine,READ_SIZE,fpReadFile);  
	while(pGetLine[LineTotalLength-2] != '\n')
	{
		if(NULL == fgets(pSectLine,READ_SIZE,fpReadFile))
		{
			break;
		}
		LineTotalLength += (READ_SIZE-1);
		pGetLine = (char*)realloc(pGetLine,sizeof(char)*LineTotalLength);
		JudgeMemory(pGetLine);
		pGetLine[LineTotalLength-2] = '\n';
		strncpy(pGetLine+LineTotalLength-READ_SIZE,pSectLine,READ_SIZE);
	}
	free(pSectLine);
	return 0;
}

/************************************************************//**
@brief     record multiple match character
@param     ***pAllLength        store input character
           *pInputCharLength   record the actual length of input character
		   &NumberMarks         record confirm there are several logo head
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
	getchar();
	///record both character and order
	///pointer to the pointer to record different header
	*pAllChar = (char**)malloc(sizeof(char)*NumberMarks);
	*pInputCharLength = (unsigned int*)malloc(sizeof(int)*NumberMarks);
	while(NumberNHead != NumberMarks)
	{
		RecordInputCharBuf(&(*pAllChar)[NumberNHead],(*pInputCharLength)[NumberNHead],NumberNHead,NumberMarks);
		NumberNHead++;
	}
	return 0;
}
/************************************************************//**
@brief     read a complete input character
@param     **pAllLength        store input character
           ActualTotalLength   record the actual length of input character
	  	   NumberMarks         record  there are  logo head
@retval    0  success
@author YHF
@data    2018/2/20
@design:

*****************************************************************/
int FileNormallyMode(char* &pReadFile,int &FileNum)
{
	printf("please enter the file to open ：\n");
	FileNum = 1;
	fgets(pReadFile,READ_SIZE,stdin);
	return 0;
}
/************************************************************//**
@brief     File List input mode
@param     *&pReadFile   storage the readfile of the file list
           &RecordFileLine  record the Number of rows
@retval    0  success
@author YHF
@data    2018/2/19
@design:
manually change the one dimensional pointers to two-dimensional pointers
*****************************************************************/
int FileListMode(char* &pReadFile,int &RecordFileLine)
{
	char pFileListMode[READ_SIZE];
	FILE *fpFileListMode;
	RecordFileLine = 1;                                        ///<record the number of rows
	printf("enter file list open mode ,enter the file containing the file list：\n");
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
/************************************************************//**
@brief     record the manual input  mode 
@param     *&pReadFile   storage the readfile of the manual input 
           &FileNth      record the numberof the rows
@retval    0  success
@author YHF
@data    2018/2/20
@design:
manually change the one dimensional pointers to two-dimensional pointers
*****************************************************************/
int FileManualMode(char* &pReadFile,int &FileNth)
{
	FileNth = 1;              ///<record the number of the rows
	printf("Enter the manual input mode ,please enter the %d dfile ,press enter to end the manual input mode ",FileNth);
	fgets(pReadFile,READ_SIZE,stdin);

	while(*(pReadFile+(FileNth-1)*READ_SIZE) != '\n')
	{
		FileNth++;
		printf("Enter the manual input mode ,please enter the %d dfile ,press enter to end the manual input mode",FileNth);
		pReadFile = (char*)realloc(pReadFile,sizeof(char)*(FileNth*READ_SIZE));
		JudgeMemory(pReadFile);
		pReadFile = fgets(pReadFile+(FileNth-1)*READ_SIZE,READ_SIZE,stdin);
	}
	FileNth--;
	pReadFile = (char*)realloc(pReadFile,sizeof(char)*(FileNth*READ_SIZE));
	return 0;
}
/************************************************************//**
@brief     Judge whether to enter the manual input mode or file list mode according the user'selection 
@param     *& pFileStorage    pass the file storage pointers
           FileNum            record the number of  rows 
@retval    0  success
@author YHF
@data    2018/2/19
@design:
judge whether the last character read whether cover
*****************************************************************/
int FileModeStorage(char* &pFileStorage,int FileNum)
{
	char PressKey;                   ///<用户案件决定模式
	printf("Press F/f for the file list mode,press H/h for the manual mode \n");
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
		getchar();
		printf("Input errors,please re-enter\n");
		
	}
	getchar();
	if(PressKey != 'h')
	{
		if(PressKey != 'H')
		{
			FileListMode(pFileStorage,FileNum);
			return 0;
		}
	}
	FileManualMode(pFileStorage,FileNum);
	return 0;
}

/************************************************************//**
@brief     Save the file input,
@param     *&pReadFile   pass the file  storage pointers
           NumberMarks   pass the pointers of the number of match character
		   FileNumInput  
@retval    0  success
@author YHF
@data    2018/2/19
@design:
judge whether the last character read whether cover
*****************************************************************/
int SaveMultipleFileInput(char* &pReadFile,const int NumberMarks,int &FileNumInput)
{
	char PressKey;
	while (NumberMarks == 1)
	{
		printf("Need to open multiple file to read?(only when a single logo head has this prompt)\n pressY/y to confirm,any key to cancel\n");
		if((PressKey = getchar()) != 'y')
		{
			if (PressKey != 'Y')
			{
				getchar();
				break;
			}
		}
		getchar();
		FileModeStorage(pReadFile,FileNumInput);
		return 0;
	}
	FileNormallyMode(pReadFile,FileNumInput);
	return 0;
}
/************************************************************//**
@brief     read a complete output character
@param     *&pWriteFile  save the write in character file 
           FileNumOutput  
@retval    1   only a output file 
           2   multiple match character and write in different output files separately(only one input file)
		   3   multiple input file and write in different output file (only one match character)
@author YHF
@data    2018/2/19
@design:

*****************************************************************/
int SaveMultipleFileOutput(char* &pWriteFile,int FileNumOutput,const int NumberMarks,const int FileNumInput)
{
	if (NumberMarks ==1)
	{
		if(FileNumInput == 1)
		{
			FileNormallyMode(pWriteFile,FileNumOutput);
			return 0;
		}
	}
	char  PressKey;
	
	printf("当前输入%d个表示头，在%d个文件中匹配，是否将匹配结果分开输出？（Y/y确认，任意键取消)\n",NumberMarks,FileNumInput);
	if((PressKey = getchar()) != 'Y')
	{
		if(PressKey != 'y')
		{
			FileNormallyMode(pWriteFile,FileNumOutput);
			return 1;
		}
	}
	getchar();
	if (NumberMarks != 1)
	{
		FileModeStorage(pWriteFile,FileNumOutput);
		if(NumberMarks != FileNumOutput)
		{
			printf("错误，标识头数目和输出文件数目不等，无法正常运行程序");
			getchar();
			exit(EXIT_FAILURE);
		}
		return 2;
	}

	printf("当前查找多个文件，请按照文件输入顺序依次输入需要写入的文件，");
		FileModeStorage(pWriteFile,FileNumOutput);
		if(NumberMarks != FileNumOutput)
		{
			printf("错误，标识头数目和输出文件数目不等，无法正常运行程序");
			getchar();
			exit(EXIT_FAILURE);
		}
		return 3;
}
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
	char  *pGetLine;                       ///<save a complete line
	char  *pReadFile;                     ///<save the readfile path
	char  *pWriteFile;                    ///<save the outputfile  path
	
	int   NumberNHead = 0;                 ///<number N logo head
	int   FileNumInput = 0;
	int   FileNumOutput = 0;
	int   LineTotalLength;                 ///<the total of the allocate memory line length

	int   FileOutputMode;

	pReadFile = (char*)malloc(sizeof(char)*READ_SIZE);
	JudgeMemory(pReadFile);
	SaveMultipleFileInput(pReadFile,NumberMarks,FileNumInput);
	pWriteFile = (char*)malloc(sizeof(char)*READ_SIZE);
	FileOutputMode = SaveMultipleFileOutput(pWriteFile,FileNumOutput,NumberMarks,FileNumInput);
	for(int FileInputCycle = 0;FileInputCycle != FileNumInput;FileInputCycle++)
	{
		fpReadFile = fopen(pReadFile + ( FileInputCycle * READ_SIZE),"r");
		if(NULL == fpReadFile)
		{
			printf("无法打开文件%READ_SIZEs!\n",(pReadFile + (FileInputCycle*READ_SIZE)));
			getchar();
			exit(EXIT_FAILURE);
		}
		///
		///所有东西写入一个文件里面
		if(1 == FileOutputMode)
		{
			fpWriteFile = fopen (pWriteFile,"a");
			if(NULL == fpReadFile)
			{
				printf("无法打开文件%READ_SIZEs!\n",pWriteFile);
				getchar();
				exit(EXIT_FAILURE);
			}
			while(!feof(fpReadFile))
			{

				pGetLine = (char*)malloc(sizeof(char)*READ_SIZE);
				JudgeMemory(pGetLine);
				ReadFileFirstLine(fpReadFile,pGetLine,LineTotalLength);
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
		}
		///此时FileNumInput必然为1;
		///using NumberMarks == FileNumOutput
		if(2 == FileOutputMode)
		{
			
		}
		///此时输入文件数等于输出文件数
		if(FileOutputMode == 3)
		{
			fpWriteFile = fopen(pWriteFile + ( FileInputCycle * READ_SIZE),"a");
			if(NULL == fpReadFile)
			{
				printf("无法打开文件%READ_SIZEs!\n",(pWriteFile + (FileInputCycle*READ_SIZE)));
				getchar();
				exit(EXIT_FAILURE);
			}
			while(!feof(fpReadFile))
			{
				pGetLine = (char*)malloc(sizeof(char)*READ_SIZE);
				JudgeMemory(pGetLine);

				ReadFileFirstLine(fpReadFile,pGetLine,LineTotalLength);
				if(LineTotalLength > InputCharLength[NumberNHead])

				{
					if(!strncmp(pGetLine,pMatch[NumberNHead],InputCharLength[NumberNHead]))
					{
						fprintf(fpWriteFile,"%s",pGetLine);
					}
				}
				free(pGetLine);
			}
			fclose(fpReadFile);
			fclose(fpWriteFile);
		}
	}
	free(pReadFile);
	free(pWriteFile);
	return 0;
}
	
