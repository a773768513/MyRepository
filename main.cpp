#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
	FILE *pReadFile;
	FILE *pWriteFile;  
	char  cLine[100];               /*����ÿ���ļ�*/
	char  cMatch[4]={"aaa"};       /*��ҪѰ�ҵ������ַ�*/
	char  cBuf[10];                /* ���ÿ�е�ǰ�����ַ�  */
	pReadFile = fopen("D:test.txt","r");
	pWriteFile=fopen("D:xieru.txt","a");             /*��д���ļ�*/
	if((NULL == pReadFile)||(NULL==pWriteFile))
		{
			printf("Can not open file data!\n");
			exit(EXIT_FAILURE);
	    }
	while (fgets(cLine,sizeof(cLine),pReadFile))            /*ʹ��fget������������*/
	{
		sscanf(cLine,"%3s",cBuf);                        /*ʹ��sscanf����Ѱ��ǰ�����ַ������Ĳ����㣩*/
		if(0 == strcmp(cBuf,cMatch))
		{
			fprintf(pWriteFile,"%s",cLine);
		}
	}
	fclose(pReadFile);
	fclose(pWriteFile);
	return 0;
}

