
/*****************************************************//**
               Training  Module
*-
@file    test1.cpp
@author  YHF
@date    2018/01/27
@brief a test module
find rhe specified character and remove the entire line
*****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
	FILE *fpReadFile;
	FILE *fpWriteFile;  
	char  Line[100];                  ///<read a line in the readfile
	char  ReadFile[100];              ///<save the readfile path
    char  Match[50];                  ///<save the match character
    char  WriteFile[100];             ///<save the output path
	int   iClearBuf=0;                ///<clear the buffer if an error occurs
	///enter data from console
	printf("请输入原文件：\n");
	scanf("%s",&ReadFile);
	fpReadFile = fopen(ReadFile,"r");
	printf("请输入查找的字符：\n");
	scanf("%s",&Match);
	printf("筛选出数据存放至：\n");
	scanf("%s",&WriteFile);
	fpWriteFile=fopen(WriteFile,"a");   
	int count=strlen(Match);            ///<record the length of the input character 
	///file open failure message
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
		if(0 == strncmp(Line,Match,count))
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
					 Line[98]='\0';
					 break;
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
					 Line[98]='\0';
					 break;
			 }
		}
	}
	fclose(fpReadFile);
	fclose(fpWriteFile);
	return 0;
}