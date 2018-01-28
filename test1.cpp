/*************************************************************//**
            Training  One

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
	char  Line[100];              
	char  Buf[10];                
	char  ReadFile[100];
    char  Match[50];
    char  WriteFile[100];
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
			getchar();
			exit(EXIT_FAILURE);
	    }
	///match characters to each line and output
	while (fgets(Line,sizeof(Line),fpReadFile))          
	{
		if(0 == strncmp(Line,Match,count))
		{
			fprintf(fpWriteFile,"%s",Line);
		}
	}
	fclose(fpReadFile);
	fclose(fpWriteFile);
	return 0;
}

