#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
	FILE *rfile;
	FILE *wfile; 
	char line[100];               /*����ÿ���ļ�*/
	char result[50][100];         /*���������*/
	char  match[4]={"aaa"};       /*��ҪѰ�ҵ������ַ�*/
	char  buf[10];                /* ���ÿ�е�ǰ�����ַ�  */
	rfile = fopen("D:test.txt","r");
	wfile=fopen("D:xieru.txt","a");             /*��д���ļ�*/
	if((NULL == rfile)||(NULL==wfile))
		{
			printf("Can not open file data!\n");
			exit(EXIT_FAILURE);
	    }
	while (fgets(line,sizeof(line),rfile))            /*ʹ��fget������������*/
	{
		sscanf(line,"%3s",buf);
		if(0 == strcmp(buf,match))
		{
			fprintf(wfile,"%s",line);
		}
	}
	fclose(rfile);
	fclose(wfile);
	return 0;
}

