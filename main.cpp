#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
	FILE *rfile;
	FILE *wfile; 
	char line[100];               /*处理每行文件*/
	char result[50][100];         /*存放输出结果*/
	char  match[4]={"aaa"};       /*需要寻找的特殊字符*/
	char  buf[10];                /* 存放每行的前几个字符  */
	rfile = fopen("D:test.txt","r");
	wfile=fopen("D:xieru.txt","a");             /*打开写入文件*/
	if((NULL == rfile)||(NULL==wfile))
		{
			printf("Can not open file data!\n");
			exit(EXIT_FAILURE);
	    }
	while (fgets(line,sizeof(line),rfile))            /*使用fget函数进行输入*/
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

