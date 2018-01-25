#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
	FILE *pReadFile;
	FILE *pWriteFile;  
	char  cLine[100];               /*处理每行文件*/
	char  cMatch[4]={"aaa"};       /*需要寻找的特殊字符*/
	char  cBuf[10];                /* 存放每行的前几个字符  */
	pReadFile = fopen("D:test.txt","r");
	pWriteFile=fopen("D:xieru.txt","a");             /*打开写入文件*/
	if((NULL == pReadFile)||(NULL==pWriteFile))
		{
			printf("Can not open file data!\n");
			exit(EXIT_FAILURE);
	    }
	while (fgets(cLine,sizeof(cLine),pReadFile))            /*使用fget函数进行输入*/
	{
		sscanf(cLine,"%3s",cBuf);                        /*使用sscanf函数寻找前三个字符（更改不方便）*/
		if(0 == strcmp(cBuf,cMatch))
		{
			fprintf(pWriteFile,"%s",cLine);
		}
	}
	fclose(pReadFile);
	fclose(pWriteFile);
	return 0;
}

