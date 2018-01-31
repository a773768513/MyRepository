/**************************************************//**
			Training  Module
*-
@file package.cpp
@author YHF
@data 2018/1/31
@package try to package

**********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *InputCharacter(int *iNum=NULL)
{
	char *pMatch;
	printf("请输入匹配字符：\n");
	*iNum = 0;
	while(1)
	{ 
		pMatch = new char[100];
		if(pMatch==NULL)
		{
			printf("memory allocation failed;\npress any key to exit \n");
			getchar();
			exit(EXIT_FAILURE);
		}
	    if(scanf("%s",&pMatch))
		{
			iNum += 1;
			return pMatch;
		}
		else
		{
			return pMatch;
			break;
		}
	}
}
int OutputFile(char *pMatch)
{
	FILE *fpReadFile;
	FILE *fpWriteFile;  
	char  Line[100];                  ///<read a line in the readfile
	char  ReadFile[100];              ///<save the readfile path
    char  WriteFile[100];             ///<save the output path
	int   iClearBuf=0;  
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
        	char clear;

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

	while (fgets(Line,sizeof(Line),fpReadFile))          
	{
		///
		if(0 == strncmp(Line,pMatch,count))
		{
			 fprintf(fpWriteFile,"%s",Line);
             ///judge whether the function is complete read a line
			 ///judge whether the 99th character of the array is overwritten
			 while(Line[98]!='\0')
			 {
				 if(Line[98]!='\n')
				 {
					 fgets(Line,sizeof(Line),fpReadFile);
					 fprintf(fpWriteFile,"%s",Line);
					 Line[98]='\0';
				 }
				 else 
				 {
					 Line[98]='\0';
					 break;
				 }
			 }
		}
		else
		{
			///judge whether the function is complete read aline 
			///judge whether the 99th chartacter of the array is overwritten
			 while(Line[98]!='\0')
			 {
				 if(Line[98]!='\n')
				 {
					 fgets(Line,sizeof(Line),fpReadFile);
					 Line[98]='\0';
				 }
				 else 
				 {
					 Line[98]='\0';
					 break;
				 }
			 }
		}
	}
	fclose(fpReadFile);
	fclose(fpWriteFile);
	return 0;
}
int main()
{
	char *pMatch;
	int *iNum;
	pMatch = InputCharacter(iNum);
	OutputFile(pMatch);
	return 0;
}